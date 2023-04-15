#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void create_file(char *path) {
  FILE *file = fopen(path, "w");
  if (file == NULL) {
    printf("Error: Could not create file\n");
    return;
  }
  printf("File created successfully\n");
  fclose(file);
}

void create_folder(char *path) {
  int status = mkdir(path, 0777);
  if (status == -1) {
    printf("Error: Could not create folder\n");
    return;
  }
  printf("Folder created successfully\n");
}

void rename_file(char *path, char *new_name) {
  int status = rename(path, new_name);
  if (status == -1) {
    printf("Error: Could not rename file\n");
    return;
  }
  printf("File renamed successfully\n");
}

void search_files(char *path, char *name) {
  DIR *directory = opendir(path);
  if (directory == NULL) {
    printf("Error: Could not open directory\n");
    return;
  }
  struct dirent *entry;
  while ((entry = readdir(directory)) != NULL) {
    if (strcmp(entry->d_name, name) == 0) {
      printf("File found: %s/%s\n", path, name);
      closedir(directory);
      return;
    }
  }
  printf("File not found\n");
  closedir(directory);
}

void delete_file(char *path) {
  int status = remove(path);
  if (status == -1) {
    printf("Error: Could not delete file\n");
    return;
  }
  printf("File deleted successfully\n");
}

void delete_folder(char *path) {
  int status = rmdir(path);
  if (status == -1) {
    printf("Error: Could not delete folder\n");
    return;
  }
  printf("Folder deleted successfully\n");
}


void process() {

  int num1, num2, sum, n, arr[20], nprocess = 0;
  int choice;

  printf("Enter two numbers: ");
  scanf("%d %d", &num1, &num2);
  sum = num1 + num2;
  printf("\n\n");

  printf("Enter size of array: ");
  scanf("%d", &n);
  printf("enter array elements: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  printf("\n\n");

  int pid1, pid2, pid3;
  pid1 = fork();
  nprocess += 3;

  if (pid1 == 0) {

    sleep(4);

    printf("Child process with ID %d and parent ID %d is counting the number "
           "of process\n",
           getpid(), getppid());
    printf("total number of child process is %d with parent process %d\n\n",
           nprocess, getppid());

  }

  else {
    pid2 = fork();
    nprocess += 2;

    if (pid2 == 0) {

      sleep(3);
      printf("Child process with id: %d and parent id: %d is sorting an array "
             "of 5 elements\n",
             getpid(), getppid());
      printf("Sorted array: ");
      for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
      }
      printf("\n\n");

    }

    else {
      sleep(1);
      pid3 = fork();
      nprocess += 1;

      if (pid3 == 0) {

        sleep(1);

        printf("Child process with ID %d and parent ID %d is calculating the "
               "sum\n",
               getpid(), getppid());
        printf("Sum of %d and %d is %d.\n\n", num1, num2, sum);
      }

      else {
        sleep(5);
        printf("parent process with id: %d\n", getpid());
        printf("DONE\n");

        printf("\n\n\n");
        printf(
            "Select a process to kill (1 for sum, 2 for sort, 3 for count): ");
        scanf("%d", &choice);

        if (choice == 1) {
          kill(pid3, SIGKILL);
          printf("child process with ID %d killed successfully", pid1);
        } else if (choice == 2) {
          kill(pid2, SIGKILL);
          printf("child process with ID %d killed successfully", pid2);
        } else if (choice == 3) {
          kill(pid1, SIGKILL);
          printf("child process with ID %d killed successfully", pid3);

        } else
          printf("Invalid choice\n");
      }
    }
  }
}



int main() {
  char path[100], new_name[100], file_name[100];
  int a, b, size;
  int arr[100];

  while (1) {
    printf("\n______Welcome to Directory and Process building in C "
           "language______\n\n");
    printf("1. Create File\n");
    printf("2. Create Folder\n");
    printf("3. Rename File\n");
    printf("4. Search File\n");
    printf("5. Delete File\n");
    printf("6. Delete Folder\n");
    printf("7. Process Creation and Termination\n");

    printf("0. Exit\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("\nEnter path to create file: ");
      scanf("%s", path);
      create_file(path);
      break;

    case 2:
      printf("\nEnter path to create folder: ");
      scanf("%s", path);
      create_folder(path);
      break;

    case 3:
      printf("\nEnter path of file to rename: ");
      scanf("%s", path);
      printf("\nEnter new name for file: ");
      scanf("%s", new_name);
      rename_file(path, new_name);
      break;

    case 4:
      printf("\nEnter path to search file: ");
      scanf("%s", path);
      printf("\nEnter file name: ");
      scanf("%s", file_name);
      search_files(path, file_name);
      break;

    case 5:
      printf("\nEnter path to delete file: ");
      scanf("%s", path);
      delete_file(path);
      break;

    case 6:
      printf("\nEnter path to delete folder: ");
      scanf("%s", path);
      delete_folder(path);
      break;

    case 0:
      printf("\n\n\nExiting program...\n");
      exit(0);

    case 7:
      printf("\n\nProcess Creation and Termination----\n\n");
      process();
      exit(0);

    default:
      printf("\nInvalid choice\n");
      break;
    }
  }
  return 0;
}