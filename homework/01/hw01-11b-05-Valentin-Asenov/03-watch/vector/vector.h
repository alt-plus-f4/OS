typedef struct vector_t {
	void** values;
	size_t size;
} vector_t;

vector_t* vector_init();
void vector_push(vector_t* vec, void* value);
void vector_pop(vector_t* vec);
void** vector_getall(vector_t* vec);
void* vector_at(vector_t* vec, size_t index);
size_t vector_contains(vector_t* vec, void* value);
void vector_print(vector_t* vec); // Samo za debug
void vector_clear(vector_t* vec);
void vector_destroy(vector_t* vec);
