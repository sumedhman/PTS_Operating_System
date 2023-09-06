/*
The operating system uses different memory management schemes to optimize
memory/resource block allocation to different processes. We will look at
one of such memory allocation processes in OS called First Fit in Operating
System. In this approach we allot the first available space that is large
enough to accommodate the process.
*/

#include <stdio.h>
#include <stdbool.h>

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
    memory[1].allocated = true;

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
    for (int i = 0; i < numBlocks; i++) {
        if (!memory[i].allocated && (memory[i].end - memory[i].start + 1) >= size) {
            memory[i].allocated = true;

            if ((memory[i].end - memory[i].start + 1) > size) {
                Block newBlock;
                newBlock.start = memory[i].start + size;
                newBlock.end = memory[i].end;
                newBlock.allocated = false;

                memory[numBlocks] = newBlock;
                memory[i].end = memory[i].start + size - 1;
                numBlocks++;
            }

            displayMemory();
            return;
        }
    }

    printf("Memory allocation failed for size %d.\n", size);
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
Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 499        | 300        | No         |
| 3         | 500        | 699        | 200        | Yes        |
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
| 4         | 500        | 699        | 200        | Yes        |
| 5         | 700        | 999        | 300        | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 1
Enter the size of memory block to allocate: 200

Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 349        | 150        | Yes        |
| 3         | 350        | 499        | 150        | No         |
| 4         | 500        | 699        | 200        | Yes        |
| 5         | 700        | 899        | 200        | Yes        |
| 6         | 900        | 999        | 100        | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 1
Enter the size of memory block to allocate: 300
Memory allocation failed for size 300.

1. Allocate memory
2. Exit
Enter your choice: 1
Enter the size of memory block to allocate: 60

Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 349        | 150        | Yes        |
| 3         | 350        | 409        | 60         | Yes        |
| 4         | 410        | 499        | 90         | No         |
| 5         | 500        | 699        | 200        | Yes        |
| 6         | 700        | 899        | 200        | Yes        |
| 7         | 900        | 999        | 100        | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 2
Exiting.

D:\NSEC\MTech_OS\OS_Programs\Memory_Allocation>
*/
