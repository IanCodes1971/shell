#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CMD_LEN 1024

int main() {
    char command[MAX_CMD_LEN];
    char input[MAX_CMD_LEN];
    int option;

    while (1) {
        // Display menu
        printf("\nSelect a command to execute:\n");
        printf("1. Copy a file (cp)\n");
        printf("2. Move/Rename a file (mv)\n");
        printf("3. List files (ls)\n");
        printf("4. Create a directory (mkdir)\n");
        printf("5. Display file content (cat)\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");
        fgets(input, sizeof(input), stdin);
        option = atoi(input);

        switch (option) {
            case 1: // Copy a file
                printf("Enter source file: ");
                fgets(command, sizeof(command), stdin);
                command[strcspn(command, "\n")] = 0; // Remove newline
                printf("Enter destination file: ");
                char dest[MAX_CMD_LEN];
                fgets(dest, sizeof(dest), stdin);
                dest[strcspn(dest, "\n")] = 0; // Remove newline
                if (fork() == 0) {
                    execlp("cp", "cp", command, dest, (char *)NULL);
                    perror("cp failed");
                    exit(1);
                }
                wait(NULL);
                break;

            case 2: // Move/Rename a file
                printf("Enter source file: ");
                fgets(command, sizeof(command), stdin);
                command[strcspn(command, "\n")] = 0; // Remove newline
                printf("Enter destination file: ");
                fgets(dest, sizeof(dest), stdin);
                dest[strcspn(dest, "\n")] = 0; // Remove newline
                if (fork() == 0) {
                    execlp("mv", "mv", command, dest, (char *)NULL);
                    perror("mv failed");
                    exit(1);
                }
                wait(NULL);
                break;

            case 3: // List files
                if (fork() == 0) {
                    execlp("ls", "ls", NULL);
                    perror("ls failed");
					                    exit(1);
                }
                wait(NULL);
                break;

            case 4: // Create a directory
                printf("Enter directory name: ");
                fgets(command, sizeof(command), stdin);
                command[strcspn(command, "\n")] = 0; // Remove newline
                if (fork() == 0) {
                    execlp("mkdir", "mkdir", command, (char *)NULL);
                    perror("mkdir failed");
                    exit(1);
                }
                wait(NULL);
                break;

            case 5: // Display file content
                printf("Enter file to display: ");
                fgets(command, sizeof(command), stdin);
                command[strcspn(command, "\n")] = 0; // Remove newline
                if (fork() == 0) {
                    execlp("cat", "cat", command, (char *)NULL);
                    perror("cat failed");
                    exit(1);
                }
                wait(NULL);
                break;

            case 6: // Exit
			    printf("Exiting shell.\n");
                exit(0);
                break;

            default:
                printf("Invalid option. Please choose a number between 1 and 6.\n");
                break;
        }
    }
    return 0;
}



