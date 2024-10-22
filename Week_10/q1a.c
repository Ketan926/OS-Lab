#include <stdio.h>
#include <stdlib.h>
struct mab 
{
    int offset;           
    int size;             
    int allocated;        
    struct mab *next;     
    struct mab *prev;     
};
typedef struct mab Mab;
typedef Mab *MabPtr;
typedef enum { FIRST_FIT, BEST_FIT, WORST_FIT, NEXT_FIT } AllocationStrategy;
MabPtr lastAllocated = NULL; 
MabPtr memChk(MabPtr m, int size, AllocationStrategy strategy);  
MabPtr memAlloc(MabPtr m, int size, AllocationStrategy strategy); 
MabPtr memFree(MabPtr m);                    
MabPtr memMerge(MabPtr m);                   
MabPtr memSplit(MabPtr m, int size);         
MabPtr memChk(MabPtr m, int size, AllocationStrategy strategy) 
{
    MabPtr bestBlock = NULL;
    MabPtr current = m;
    switch (strategy) 
    {
        case FIRST_FIT:
            while (current != NULL) 
            {
                if (!current->allocated && current->size >= size) 
                {
                    return current;  
                }
                current = current->next;
            }
            break;
        case BEST_FIT:
            while (current != NULL) 
            {
                if (!current->allocated && current->size >= size) 
                {
                    if (bestBlock == NULL || current->size < bestBlock->size) 
                    {
                        bestBlock = current;
                    }
                }
                current = current->next;
            }
            return bestBlock;
        case WORST_FIT:
            while (current != NULL) 
            {
                if (!current->allocated && current->size >= size) 
                {
                    if (bestBlock == NULL || current->size > bestBlock->size) 
                    {
                        bestBlock = current;
                    }
                }
                current = current->next;
            }
            return bestBlock;
        case NEXT_FIT:
            if (lastAllocated == NULL) 
            {
                lastAllocated = m;
            }
            current = lastAllocated;
            while (current != NULL) 
            {
                if (!current->allocated && current->size >= size) 
                {
                    lastAllocated = current;  
                    return current;
                }
                current = current->next;
            }
            current = m;
            while (current != lastAllocated) 
            {
                if (!current->allocated && current->size >= size) 
                {
                    lastAllocated = current;  
                    return current;
                }
                current = current->next;
            }
            break;
    }
    return NULL;
}
MabPtr memAlloc(MabPtr m, int size, AllocationStrategy strategy) 
{
    MabPtr block = memChk(m, size, strategy);  
    if (block == NULL) 
    {
        printf("No suitable block found for size %d\n", size);
        return NULL;  
    }
    if (block->size > size) 
    {
        block = memSplit(block, size);
    }
    block->allocated = 1;  
    printf("Allocated block at offset %d with size %d\n", block->offset, block->size);
    return block;
}
MabPtr memFree(MabPtr m) 
{
    if (m == NULL) return NULL;
    m->allocated = 0;
    printf("Freed block at offset %d with size %d\n", m->offset, m->size);
    m = memMerge(m);
    return m;
}
MabPtr memMerge(MabPtr m) 
{
    if (m == NULL) return NULL;
    if (m->next != NULL && !m->next->allocated) 
    {
        printf("Merging block at offset %d with next block at offset %d\n", m->offset, m->next->offset);
        m->size += m->next->size;
        m->next = m->next->next;
        if (m->next != NULL) {
            m->next->prev = m;
        }
    }
    if (m->prev != NULL && !m->prev->allocated) 
    {
        printf("Merging block at offset %d with previous block at offset %d\n", m->offset, m->prev->offset);
        m->prev->size += m->size;
        m->prev->next = m->next;
        if (m->next != NULL) 
        {
            m->next->prev = m->prev;
        }
        m = m->prev;
    }
    return m;
}
MabPtr memSplit(MabPtr m, int size) 
{
    if (m == NULL || m->size <= size) 
        return m;
    MabPtr newBlock = (MabPtr) malloc(sizeof(Mab));  
    newBlock->offset = m->offset + size;
    newBlock->size = m->size - size;
    newBlock->allocated = 0;
    newBlock->next = m->next;
    newBlock->prev = m;
    if (m->next != NULL) 
    {
        m->next->prev = newBlock;
    }
    m->next = newBlock;
    m->size = size;
    printf("Split block at offset %d into sizes %d and %d\n", m->offset, m->size, newBlock->size);
    return m;
}
void printMemory(MabPtr m) 
{
    MabPtr current = m;
    printf("Memory blocks:\n");
    while (current != NULL) 
    {
        printf("Offset: %d, Size: %d, Allocated: %d\n", current->offset, current->size, current->allocated);
        current = current->next;
    }
}
int main() 
{
    MabPtr memory = (MabPtr) malloc(sizeof(Mab));
    memory->offset = 0;
    memory->size = 1000;  
    memory->allocated = 0;
    memory->next = NULL;
    memory->prev = NULL;
    printMemory(memory);
    printf("\nFirst Fit Allocation:\n");
    MabPtr block1 = memAlloc(memory, 200, FIRST_FIT); 
    printMemory(memory);
    printf("\nBest Fit Allocation:\n");
    MabPtr block2 = memAlloc(memory, 300, BEST_FIT);
    printMemory(memory);
    printf("\nWorst Fit Allocation:\n");
    MabPtr block3 = memAlloc(memory, 100, WORST_FIT);  
    printMemory(memory);
    printf("\nNext Fit Allocation:\n");
    MabPtr block4 = memAlloc(memory, 150, NEXT_FIT);  
    printMemory(memory);
    memFree(block2);  
    printMemory(memory);
    memFree(block3);  
    printMemory(memory);
    return 0;
}
