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

int main() {
    char command[100];
    system("cls");

    printf("myapp>> ");

    while (1) {
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "help") == 0) {
            show_help();
        } else if (strcmp(command, "showdate") == 0) {
            show_date();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting the program...\n");
            break;
        } else {
            printf("Unknown command. Type 'help' for available commands.\n");
        }
        printf("\nmyapp>> ");
    }

    return 0;
}
