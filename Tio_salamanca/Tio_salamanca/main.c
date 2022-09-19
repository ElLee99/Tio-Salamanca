/*
 * Tio_salamanca.c
 *
 * Created: 31/07/2022 02:42:55 p. m.
 * Author : Johan Lee
 */ 

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DYNAMIC_ARRAY.h"
#include "LCD_SCREEN.h"
#include "USART_COMMUNICATION.h"

typedef struct{
	//uint8_t number;
	uint8_t letter;
}alphabet;

alphabet alph1 [26];
alphabet *ptr_Alphabet = &alph1;

dyn_array phrase;
dyn_array *ptr_Phrase = &phrase;

uint8_t boton_Interrupt = 0;
uint8_t already_Connected = 0;


void init_External_Interrupts(void){
	DDRD &= ~(1<<2);
	EICRA = (1<<ISC01);
	EICRA &= ~(1<<ISC00);
	EIMSK = (1<<INT0);
}


/*void unable_External_Interrupts(void){
	EIMSK &= ~(1<<INT0);
}*/


void init_Timer1(void){
	TCCR1A = 0X00;
	TCCR1B = (1<<CS02) | (1<<CS00);
	TIMSK1 = (1<<OCIE1B) | (1<<OCIE1A);
	OCR1A = 30000;
	OCR1B = 60000;
}


/*void unable_Timer1(void){
	TIMSK1 &= ~(1<<OCIE1B) | ~(1<<OCIE1A);
}*/

//Fill the alphabet from A to Z in the alphabet var
void fill_Alphabet(alphabet *pointer){
	for (uint8_t i = 1; i <= 26; i++, pointer++){
		pointer -> letter = i+64;
	}
}


//Prints the whole alphabet saved, just to test
/*void print_Alphabet(alphabet *pointer){
	for (uint8_t i = 1; i <= 26; i++, pointer++){
		write_LCD(2, pointer -> letter);
	}
}*/


//Writes one space on the LCD to the right 
void space_Cursor(void){
	write_LCD(1, 0x14);			//Move cursor one to the right
	write_LCD(2, 0x20);			//Writes a blank character
	write_LCD(1, 0x10);			//Move cursor one to the left
}


/*In case the phrase is bigger than 16 characters, moves the LCD cursor to the second row 
and in case is bigger than 32 characters, clean the screen*/
void check_Line_Break(void){
	if (ptr_Phrase -> size == 16){
		gotoXY_LCD(2, 1);
	}
	if (ptr_Phrase -> size >= 32){
		_delay_ms(500);
		clear_LCD();
	}
}


/*External Interrupt 
When the button is pressed writes a letter and moves the cursor one to the left
to change the letter in the same position*/
ISR(INT0_vect){
	TCNT1 = 0;
	boton_Interrupt = 1;
	write_LCD(2, ptr_Alphabet -> letter);
	write_LCD(1, 0x10);  //move cursor 1 to the left
	ptr_Alphabet ++;
}


//Comparation A Timer 1 Interrupt
ISR(TIMER1_COMPA_vect){

	if (boton_Interrupt == 1){
		TCNT1 = 0;
		ptr_Alphabet --;
		check_Line_Break();
		add_Element_Array(ptr_Phrase, ptr_Alphabet -> letter);
		
	}
	else{
		add_Element_Array(ptr_Phrase, ' ');
	}
	
	ptr_Alphabet = &alph1;
	space_Cursor();
	boton_Interrupt = 0;
	
}


/*Comparation B Timer 1 Interrupt
When reaches it, sends the string we wrote on the LCD, cleans the screen and starts again*/
ISR(TIMER1_COMPB_vect){
	
	TCNT1 = 0;
	boton_Interrupt = 0;
	ptr_Alphabet = &alph1;
	clear_LCD();
	return_Home_LCD();
	write_Serial(ptr_Phrase -> elements);
	_delay_ms(500);
	clear_Array(ptr_Phrase);
	clear_LCD();
	TCNT1 = 0;
	
}


//RX completed interrupt
ISR(USART_RX_vect){
											//Waits for a "M", which means that has been connected
	if (UDR0 == 'M'){
		already_Connected = 1;
		UDR0 = 0;
	}
}


int main(void)
{
	
	fill_Alphabet(ptr_Alphabet);
	init_LCD((uint8_t *)0x24);
	init_Array(ptr_Phrase);
	sei();									//Enables the interrupts
	init_USART();
	
											//While is disconncted, writes a sequence on the LCD
	while (already_Connected == 0){
		print_LCD("   Intentando");
		gotoXY_LCD(2,0);
		print_LCD("    conectar");
		_delay_ms(1500);
		clear_LCD();
		_delay_ms(1500);
	}
											/*Once it's connected, starts the sequence and initialize 
											the External Interrupts and the Timer*/
	if (already_Connected == 1){
		clear_LCD();
		print_LCD("   Conectado");
		gotoXY_LCD(2, 0);
		print_LCD(" Correctamente");
		_delay_ms(1000);
		clear_LCD();
		_delay_ms(1000);
		print_LCD("   Escriba su");
		gotoXY_LCD(2, 0);
		print_LCD ("    mensaje");
		_delay_ms(500);
		init_External_Interrupts();
		init_Timer1();
	}
	
	
    while (1) 
	{
	
	}

}
