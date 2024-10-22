#include <stdio.h>
#include <stdlib.h>

// Structure definition for memory blocks
struct mab {
    int offset;
    int size;
    int allocated;
    struct mab *next;
    struct mab *prev;
};

typedef struct mab Mab;
typedef Mab *MabPtr;

// Function prototypes
MabPtr memChk(MabPtr m, int size);
MabPtr memAlloc(MabPtr m, int size);
MabPtr memFree(MabPtr m, MabPtr block);
MabPtr memMerge(MabPtr m);
MabPtr memSplit(MabPtr m, int size);

// Function to check if memory is available
MabPtr memChk(MabPtr m, int size) 
{
    while (m) 
    {
        if (!m->allocated && m->size >= size) 
        {
            return m; // Found a suitable block
        }
        m = m->next;
    }
    return NULL; // No suitable block found
}
// Function to allocate a memory block (using First Fit)
MabPtr memAlloc(MabPtr m, int size) 
{
    MabPtr block = memChk(m, size);
    if (!block) 
    {
        printf("No sufficient memory available.\n");
        return NULL;
    }
    // If the block is larger than needed, split it
    if (block->size > size) 
    {
        MabPtr newBlock = malloc(sizeof(Mab));
        newBlock->offset = block->offset + size;
        newBlock->size = block->size - size;
        newBlock->allocated = 0;
        newBlock->next = block->next;
        newBlock->prev = block;
        block->size = size;
        block->allocated = 1;
        block->next = newBlock;
        if (newBlock->next) 
        {
            newBlock->next->prev = newBlock;
        }
    } 
    else 
    {
        block->allocated = 1;
    }
    return block;
}
// Function to free a memory block
MabPtr memFree(MabPtr m, MabPtr block) 
{
    if (block) 
    {
        block->allocated = 0;
    }
    return memMerge(m);
}
// Function to merge two adjacent memory blocks
MabPtr memMerge(MabPtr m) 
{
    MabPtr current = m;
    while (current && current->next) 
    {
        if (!current->allocated && !current->next->allocated) 
        {
            current->size += current->next->size;
            MabPtr temp = current->next;
            current->next = current->next->next;
            if (current->next) 
            {
                current->next->prev = current;
            }
            free(temp);
        } 
        else 
        {
            current = current->next;
        }
    }
    return m;
}
// Function to split a memory block
MabPtr memSplit(MabPtr m, int size) 
{
    if (m && m->allocated && m->size > size) 
    {
        MabPtr newBlock = malloc(sizeof(Mab));
        newBlock->offset = m->offset + size;
        newBlock->size = m->size - size;
        newBlock->allocated = 0;
        newBlock->next = m->next;
        newBlock->prev = m;
        m->size = size;
        m->allocated = 1;
        m->next = newBlock;
        if (newBlock->next) 
        {
            newBlock->next->prev = newBlock;
        }
        return newBlock;
    }
    return NULL;
}
// Example usage of the memory allocation
int main() 
{
    // Initialize the memory with a single block of 100 bytes
    MabPtr memory = malloc(sizeof(Mab));
    memory->offset = 0;
    memory->size = 100;
    memory->allocated = 0;
    memory->next = NULL;
    memory->prev = NULL;
    // Allocate memory
    MabPtr allocatedBlock = memAlloc(memory, 30);
    printf("Allocated Block: Offset = %d, Size = %d\n", allocatedBlock->offset, allocatedBlock->size);
    // Free memory
    memFree(memory, allocatedBlock);
    printf("Freed Block: Offset = %d, Size = %d\n", allocatedBlock->offset, allocatedBlock->size);
    // Clean up
    free(memory);
    return 0;
}
