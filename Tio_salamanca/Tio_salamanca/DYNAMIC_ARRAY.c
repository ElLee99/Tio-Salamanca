/*
 * Dinamic_Array.c
 *
 * Created: 01/08/2022 03:17:44 p. m.
 *  Author: Johan Lee
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DYNAMIC_ARRAY.h"

//Initialize the array with 16 memory spaces from the type dyn_array
void init_Array(dyn_array *item){
	item -> size = 0;
	item -> elements = (uint8_t *)calloc(16, sizeof((*item).elements));
	item -> cap = 16;
}

//Increase capacity of array by 4 spaces
void increase_Array(dyn_array *item){
	item -> elements = (uint8_t *)realloc(item -> elements, (4 + item -> cap ));
	if (item -> elements != NULL){
		item -> cap += 4;
	}
}

//Add elements to the array and if is already full, go to the increase_Array function 
void add_Element_Array(dyn_array *item, uint8_t letter){
	if (item -> size < item -> cap){
		item -> elements [item -> size] = letter;
		item -> size ++;
	}
													//In case of the array is completely full, go to the increase_Array function and try again
	else{
		//printf("Need to increase the array");
		increase_Array(item);
		add_Element_Array(item, letter);
		//printf("Array increased by four");
	}
}

/*//Show array
void show_Array(dyn_array *item){
	for (int i = 0; i < item -> size; i++){
		printf("The elements of the array are %c\n", (uint8_t) item -> elements[i]);      
		printf("The address of  the elements on the array are %ld\n", (long int) (&(*item).elements[i]));
	}
	printf("The size of the array is %d\n", item -> size);              
	printf("The capacity of the array is %d\n", item -> cap);           
}*/


//Clear the array we have by setting all memory in 0
void clear_Array(dyn_array *item){
	memset(item -> elements, 0, (sizeof(item -> elements) * (item -> cap)));
	item -> size = 0;
	item -> cap = 16;
}

//Erase the array, releasing the memory we took
void erase_Array(dyn_array *item){
	free(item);
}