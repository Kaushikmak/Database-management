#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void show_help() {
    printf("Available commands:\n");
    printf("help        - Show this help message\n");
    printf("showdate    - Show current date and time\n");
    printf("exit        - Exit the application\n");
}

void show_date() {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    printf("Current date and time: %s", asctime(tm_info));
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    if (!lineptr || !n || !stream) return -1;

    size_t pos = 0;
    int c;

    if (*lineptr == NULL || *n == 0) {
        *n = 128; // Initial buffer size
        *lineptr = malloc(*n);
        if (!*lineptr) return -1;
    }

    while ((c = fgetc(stream)) != EOF) {
        if (pos + 1 >= *n) {
            *n *= 2; // Double buffer size
            char *new_ptr = realloc(*lineptr, *n);
            if (!new_ptr) return -1;
            *lineptr = new_ptr;
        }

        (*lineptr)[pos++] = c;

        if (c == '\n') break;
    }

    if (pos == 0 && c == EOF) return -1;

    (*lineptr)[pos] = '\0';
    return pos;
}