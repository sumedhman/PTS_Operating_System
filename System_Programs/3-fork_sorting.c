// Process synchronization between parent and child processes
// Child process sorts array using bubble sort. Parent waits and prints original unsorted array

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int size) {
    // Bubble sort algorithm to sort an array of integers
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements if they are out of order
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int numbers[n];

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    pid_t child_pid = fork(); // Create a child process

    if (child_pid == -1) {
        perror("fork"); // Check if fork was successful
        exit(1);
    } else if (child_pid == 0) { // Child process
        bubbleSort(numbers, n); // Sort the array in the child process
        printf("Child process sorted the array:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", numbers[i]); // Print sorted array
        }
        printf("\n");
    } else { // Parent process
        wait(NULL); // Wait for the child process to complete
		// sleep(10);
        printf("Parent process generated the array:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", numbers[i]); // Print original array
        }
        printf("\n");
    }

    return 0;
}

/*
toor@LAPTOP-RLTA9ELC:~/system_progs$ gcc 3-fork_sorting.c
toor@LAPTOP-RLTA9ELC:~/system_progs$ ./a.out
Enter the number of elements: 6
Enter 6 numbers:
4
8
2
9
3
7
Child process sorted the array:
2 3 4 7 8 9
Parent process generated the array:
4 8 2 9 3 7
*/
