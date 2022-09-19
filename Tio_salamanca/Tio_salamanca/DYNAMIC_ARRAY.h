
/*
 * Dinamic_Array.h
 *
 * Created: 01/08/2022 03:19:05 p. m.
 *  Author: Johan Lee
 *		Implementation notes:
 *		1-This library was made to be used with any char character, but it´s recommended to use it in uint8_t format
		2-Also, to use it correctly, characters must be added one by one 
 */ 


#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_


typedef struct{
	uint8_t *elements;
	uint8_t size;
	uint8_t cap;
}dyn_array;


void init_Array(dyn_array *item);
/*Initialize the array with 16 memory spaces
	The parameter must be the pointer of the dyn_array variable made previously 
*/


void increase_Array(dyn_array *item);
/*Increase capacity of array by 4 spaces
	The parameter must be the pointer of the dyn_array variable made previously 
*/


void add_Element_Array(dyn_array *item, uint8_t letter);
/*Add elements to the array and if is already full, go to the increase_Array function 
	The parameter must be:
							 *item: The pointer of the dyn_array variable
							 letter: The letter that must be add to the array in uint8_t format
*/


void clear_Array(dyn_array *item);
/*Clear the array we have by setting all memory in 0
	The parameter must be the pointer of the dyn_array variable made previously 
*/

void erase_Array(dyn_array *item);
/*Erase the array, releasing the memory we took
	The parameter must be the pointer of the dyn_array variable made previously 
*/


//void show_Array(dyn_array *item);
#endif /* DINAMIC_ARRAY_H_ */