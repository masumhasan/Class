#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_VALUES 100

int main()
{
    // Prompt user to enter integer values separated by $
    printf("Enter integer values separated by $: ");
    char input[MAX_VALUES];
    fgets(input, MAX_VALUES, stdin);
    printf("\n\n ");
    // Convert input string to integer array
    int array[MAX_VALUES];
    int n = 0;
    char *p = strtok(input, "$");
    while (p != NULL)
    {
        array[n++] = atoi(p);
        p = strtok(NULL, "$");
    }

    // Create child process 1
    int pid1 = fork();
    if (pid1 == 0)
    {
        // Child process 1
        printf("Child process 1 - PID: %d, Parent PID: %d\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        // Parent process
        printf("Parent process - PID: %d, Child PID: %d\n", getpid(), pid1);
        // Wait for child process 1 to complete
        int status;
        waitpid(pid1, &status, 0);
        // Create child process 2
        int pid2 = fork();
        if (pid2 == 0)
        {
            // Child process 2
            float sum = 0.0;
            for (int i = 0; i < n; i++)
            {
                sum += array[i];
            }
            float average = sum / n;
            printf("Child process 2 - Average: %.2f\n", average);
            exit(0);
        }
        else
        {
            // Parent process
            printf("Parent process - PID: %d, Child PID: %d\n", getpid(), pid2);
            // Wait for child process 2 to complete
            waitpid(pid2, &status, 0);
            // Create child process 3
            int pid3 = fork();
            if (pid3 == 0)
            {
                // Child process 3
                int max = array[0];
                for (int i = 1; i < n; i++)
                {
                    if (array[i] > max)
                    {
                        max = array[i];
                    }
                }
                printf("Child process 3 - Maximum: %d\n", max);
                exit(0);
            }
            else
            {
                // Parent process
                printf("Parent process - PID: %d, Child PID: %d\n", getpid(), pid3);
                // Wait for child process 3 to complete
                waitpid(pid3, &status, 0);
            }
        }
    }

    return 0;
}
