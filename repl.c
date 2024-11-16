#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "terminalfunctions.h"

// Platform name
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_NAME "windows"
#elif defined(__linux__)
    #define PLATFORM_NAME "linux"
#else
    #define PLATFORM_NAME NULL
#endif

// Input buffer structure
typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

// Create a new InputBuffer
InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

// Read input into InputBuffer
void read_input_buffer(InputBuffer* input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = '\0'; // Remove newline
}

// Free InputBuffer resources
void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

int main() {
    InputBuffer* input_buffer = new_input_buffer();

    // Clear the screen based on the platform
    if (strcmp(PLATFORM_NAME, "windows") == 0) {
        system("cls");
    } else {
        system("clear");
    }

    printf("db>>> ");

    // Command loop
    while (true) {
        read_input_buffer(input_buffer);

        if (strcmp(input_buffer->buffer, "help") == 0) {
            show_help(); // Defined in terminalfunctions.h
        } else if (strcmp(input_buffer->buffer, "showdate") == 0) {
            show_date(); // Defined in terminalfunctions.h
        } else if (strcmp(input_buffer->buffer, "exit") == 0) {
            close_input_buffer(input_buffer);
            printf("Exiting the program...\n");
            exit(EXIT_SUCCESS); // Terminates the program
        } else {
            printf("Unknown command '%s'\nType 'help' for available commands.\n", input_buffer->buffer);
        }

        printf("db>>> ");
    }

    return 0;
}
