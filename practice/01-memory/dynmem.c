#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* dynamicString = malloc(10 * sizeof(char));

    if (dynamicString == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    strcpy(dynamicString, "Hello");
    printf("Dynamic String: %s\n", dynamicString);
    free(dynamicString);

    return 0;
}
