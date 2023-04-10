#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_VALUES 100

int main() {
    // Prompt user to enter integer values separated by $
    printf("Enter integer values separated by $: ");
    char input[MAX_VALUES];
    fgets(input, MAX_VALUES, stdin);
    printf("\n\n ");

    // Convert input string to integer array
    int pids[3];
    int n = 0;
    char *p = strtok(input, "$");
    while (p != NULL && n < 3) {
        pids[n++] = atoi(p);
        p = strtok(NULL, "$");
    }

    // Create child processes with given pids
    for (int i = 0; i < 3; i++) {
        int pid = fork();
        if (pid == 0) {
            // Child process
            printf("Child process %d - PID: %d, Parent PID: %d\n", i+1, getpid(), getppid());
            sleep(2); // Sleep for 2 seconds to simulate some work
            exit(0);
        } else {
            // Parent process
            printf("Parent process - PID: %d, Child %d PID: %d\n", getpid(), i+1, pid);
            // Check if the current child process ID matches with the given pid
            if (pid != pids[i]) {
                printf("Error: Child %d PID did not match with the given PID %d\n", i+1, pids[i]);
                exit(1);
            }
        }
    }

    // Wait for all child processes to complete
    int status;
    for (int i = 0; i < 3; i++) {
        wait(&status);
    }

    return 0;
}