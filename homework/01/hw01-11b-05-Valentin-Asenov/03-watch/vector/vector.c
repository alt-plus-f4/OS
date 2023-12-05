#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

vector_t* vector_init() {
	vector_t* new_vec = malloc(sizeof(vector_t));
	
	new_vec->size = 0;
	new_vec->values = NULL;
	
	return new_vec;
}

void vector_push(vector_t* vec, void* value) {
	vec->values = realloc(vec->values, (vec->size + 1) * sizeof(void*));
	vec->values[vec->size] = value;
	vec->size++;
}

void vector_pop(vector_t* vec){
	vec->values[vec->size] = NULL;
	vec->size--;
}

void** vector_getall(vector_t* vec){
	return vec->values;
}

void* vector_at(vector_t* vec, size_t index) {
	if(index > vec->size) return NULL;
	return vec->values[index];
}

size_t vector_contains(vector_t* vec, void* value){
	for(size_t i = 0; i < vec->size; i++){
		if(vec->values[i] == value)
			return 1;
	}
	return 0;
}

void vector_clear(vector_t* vec){
	for(size_t i = 0; i < vec->size; i++)
		vec->values[i] = NULL;
}

void vector_destroy(vector_t* vec){
	free(vec->values);
	vec->size = 0;
}

void vector_print(vector_t* vec){
	for(size_t i = 0; i < vec->size; i++)
		printf("Vector data: %p\n", vec->values[i]);
}
