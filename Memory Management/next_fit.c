/*
The next fit is a modified version of "first fit". It begins as the first fit
to find a free partition but when called next time it starts searching from
where it left off, not from the beginning. This policy makes use of a roving
pointer. The pointer moves along the memory chain to search for the next fit.
This helps in, to avoid the usage of memory always from the head (beginning)
of the free blockchain. 
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
int lastAllocatedIndex = 0; // To keep track of the last allocated block index

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
    for (int i = lastAllocatedIndex; i < numBlocks; i++) {
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

            lastAllocatedIndex = i;
            displayMemory();
            return;
        }
    }

    // Wrap around if not found from lastAllocatedIndex to the beginning
    for (int i = 0; i < lastAllocatedIndex; i++) {
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

            lastAllocatedIndex = i;
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
Enter the size of memory block to allocate: 160

Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 359        | 160        | Yes        |
| 3         | 360        | 499        | 140        | No         |
| 4         | 500        | 699        | 200        | No         |
| 5         | 700        | 999        | 300        | No         |
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
| 2         | 200        | 359        | 160        | Yes        |
| 3         | 360        | 499        | 140        | No         |
| 4         | 500        | 649        | 150        | Yes        |
| 5         | 650        | 699        | 50         | No         |
| 6         | 700        | 999        | 300        | No         |
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
| 2         | 200        | 359        | 160        | Yes        |
| 3         | 360        | 499        | 140        | No         |
| 4         | 500        | 649        | 150        | Yes        |
| 5         | 650        | 699        | 50         | No         |
| 6         | 700        | 819        | 120        | Yes        |
| 7         | 820        | 999        | 180        | No         |
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
| 2         | 200        | 359        | 160        | Yes        |
| 3         | 360        | 499        | 140        | No         |
| 4         | 500        | 649        | 150        | Yes        |
| 5         | 650        | 699        | 50         | No         |
| 6         | 700        | 819        | 120        | Yes        |
| 7         | 820        | 939        | 120        | Yes        |
| 8         | 940        | 999        | 60         | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 1
Enter the size of memory block to allocate: 130

Memory Status:
-------------------------------------------------------------------
| Block No. | Start      | End        | Size       | Allocated  |
-------------------------------------------------------------------
| 1         | 0          | 199        | 200        | Yes        |
| 2         | 200        | 359        | 160        | Yes        |
| 3         | 360        | 489        | 130        | Yes        |
| 4         | 490        | 499        | 10         | No         |
| 5         | 500        | 649        | 150        | Yes        |
| 6         | 650        | 699        | 50         | No         |
| 7         | 700        | 819        | 120        | Yes        |
| 8         | 820        | 939        | 120        | Yes        |
| 9         | 940        | 999        | 60         | No         |
-------------------------------------------------------------------

1. Allocate memory
2. Exit
Enter your choice: 2
Exiting.

D:\NSEC\MTech_OS\OS_Programs\Memory_Allocation>
*/
