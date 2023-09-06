/*
Worst Fit is a memory allocation scheme in operating systems. It is the opposite of the
best-fit algorithm. In this method, the CPU searches for a memory block which is greater
than the memory in demand. The operating system searches for free memory blocks demanded
by the operating system and assigns an empty block to the processes as soon as the CPU
identifies it. Worst Fit allocates a process to the partition which is largest sufficient
among the freely available partitions available in the main memory.
*/

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MEMORY_SIZE 1000
#define MAX_BLOCKS 50

typedef struct {
    int start;
    int end;
    bool allocated;
} Block;

Block memory[MAX_BLOCKS];
int numBlocks = 0;

void initializeMemory() {
    memory[0].start = 0;
    memory[0].end = 199;
    memory[0].allocated = true;

    memory[1].start = 500;
    memory[1].end = 699;
    memory[1].allocated = false;

    memory[2].start = 200;
    memory[2].end = 499;
    memory[2].allocated = false;

    memory[3].start = 700;
    memory[3].end = MEMORY_SIZE - 1;
    memory[3].allocated = false;

    numBlocks = 4;
}

void sortMemory() {
    for (int i = 0; i < numBlocks - 1; i++) {
        for (int j = 0; j < numBlocks - i - 1; j++) {
            if (memory[j].start > memory[j + 1].start) {
                Block temp = memory[j];
                memory[j] = memory[j + 1];
                memory[j + 1] = temp;
            }
        }
    }
}

void displayMemory() {
    sortMemory();

    printf("\nMemory Status:\n");
    printf("-------------------------------------------------------------------\n");
    printf("| Block No. | Start      | End        | Size       | Allocated  |\n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("| %-9d | %-10d | %-10d | %-10d | %-10s |\n",
               i + 1, memory[i].start, memory[i].end, memory[i].end - memory[i].start + 1,
               memory[i].allocated ? "Yes" : "No");
    }
    printf("-------------------------------------------------------------------\n");
}

void allocateMemory(int size) {
    int worstFitIndex = -1;
    int maxFragmentation = -1;

    for (int i = 0; i < numBlocks; i++) {
        if (!memory[i].allocated && (memory[i].end - memory[i].start + 1) >= size) {
            int fragmentation = memory[i].end - memory[i].start + 1 - size;
            if (fragmentation > maxFragmentation) {
                worstFitIndex = i;
                maxFragmentation = fragmentation;
            }
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = true;

        if ((memory[worstFitIndex].end - memory[worstFitIndex].start + 1) > size) {
            Block newBlock;
            newBlock.start = memory[worstFitIndex].start + size;
            newBlock.end = memory[worstFitIndex].end;
            newBlock.allocated = false;

            memory[numBlocks] = newBlock;
            memory[worstFitIndex].end = memory[worstFitIndex].start + size - 1;
            numBlocks++;
        }

        displayMemory();
    } else {
        printf("Memory allocation failed for size %d.\n", size);
    }
}

int main() {
    initializeMemory();
    displayMemory();

    int choice, size;
    do {
        printf("\n1. Allocate memory\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Enter the size of memory block to allocate: ");
                scanf("%d", &size);
                allocateMemory(size);
                break;
            case 2:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 2);

    return 0;
}

/*
D:\NSEC\MTech_OS\OS_Programs\Memory_Allocation>a.exe

Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 499        | 300        | No         |
| 3         | 500        | 699        | 200        | No         |
| 4         | 700        | 999        | 300        | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 1
Enter the size of memory block to allocate: 150

Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 349        | 150        | Yes        |
| 3         | 350        | 499        | 150        | No         |
| 4         | 500        | 699        | 200        | No         |
| 5         | 700        | 999        | 300        | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 1
Enter the size of memory block to allocate: 100

Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 349        | 150        | Yes        |
| 3         | 350        | 499        | 150        | No         |
| 4         | 500        | 699        | 200        | No         |
| 5         | 700        | 799        | 100        | Yes        |
| 6         | 800        | 999        | 200        | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 1
Enter the size of memory block to allocate: 100

Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 349        | 150        | Yes        |
| 3         | 350        | 499        | 150        | No         |
| 4         | 500        | 599        | 100        | Yes        |
| 5         | 600        | 699        | 100        | No         |
| 6         | 700        | 799        | 100        | Yes        |
| 7         | 800        | 999        | 200        | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 1
Enter the size of memory block to allocate: 120

Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 349        | 150        | Yes        |
| 3         | 350        | 499        | 150        | No         |
| 4         | 500        | 599        | 100        | Yes        |
| 5         | 600        | 699        | 100        | No         |
| 6         | 700        | 799        | 100        | Yes        |
| 7         | 800        | 919        | 120        | Yes        |
| 8         | 920        | 999        | 80         | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 2
Exiting.

D:\NSEC\MTech_OS\OS_Programs\Memory_Allocation>
*/
