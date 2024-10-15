#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BLOCKS 100

typedef struct {
    int bad_block;
    int spare_block;
} BadBlockEntry;

typedef struct {
    int total_blocks;
    int spare_blocks;
    char disk[MAX_BLOCKS];
    BadBlockEntry bad_blocks_table[MAX_BLOCKS];
    int spare_block_index;
    int bad_block_count;
} FileSystem;

void initialize_file_system(FileSystem *fs, int total_blocks, int spare_blocks) {
    fs->total_blocks = total_blocks;
    fs->spare_blocks = spare_blocks;
    fs->spare_block_index = total_blocks - spare_blocks;
    fs->bad_block_count = 0;
    
    for (int i = 0; i < total_blocks; i++) {
        fs->disk[i] = 'F'; 
    }
}

void mark_bad_block(FileSystem *fs, int bad_block) {
    if (fs->disk[bad_block] == 'F') {
        if (fs->spare_block_index < fs->total_blocks) {
            int spare_block = fs->spare_block_index;
            fs->bad_blocks_table[fs->bad_block_count].bad_block = bad_block;
            fs->bad_blocks_table[fs->bad_block_count].spare_block = spare_block;
            fs->bad_block_count++;

            fs->disk[bad_block] = 'B'; 
            fs->disk[spare_block] = 'S'; 
            fs->spare_block_index++;

            printf("Block %d marked as bad. Spare block allocated: %d.\n", bad_block, spare_block);
        } else {
            printf("No spare blocks available!\n");
        }
    } else {
        printf("Block %d is already marked as %c.\n", bad_block, fs->disk[bad_block]);
    }
}

void display_status(FileSystem *fs) {
    printf("\nDisk Status:\n");
    for (int i = 0; i < fs->total_blocks; i++) {
        printf("Block %d: %c\n", i, fs->disk[i]);
    }
    
    printf("\nBad Blocks Table:\n");
    for (int i = 0; i < fs->bad_block_count; i++) {
        printf("Bad Block: %d, Spare Block: %d\n", fs->bad_blocks_table[i].bad_block, fs->bad_blocks_table[i].spare_block);
    }
}

int main() {
    FileSystem fs;
    int total_blocks, spare_blocks;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &total_blocks);
    printf("Enter number of spare blocks: ");
    scanf("%d", &spare_blocks);

    if (total_blocks > MAX_BLOCKS || spare_blocks >= total_blocks) {
        printf("Invalid block numbers!\n");
        return 1;
    }

    initialize_file_system(&fs, total_blocks, spare_blocks);

    while (1) {
        char action[4];
        printf("\nDo you want to mark a block as bad? (yes/no): ");
        scanf("%s", action);

        if (strcmp(action, "yes") == 0) {
            int bad_block;
            printf("Enter the block number to mark as bad: ");
            scanf("%d", &bad_block);
            if (bad_block >= 0 && bad_block < total_blocks) {
                mark_bad_block(&fs, bad_block);
            } else {
                printf("Invalid block number!\n");
            }
        } else if (strcmp(action, "no") == 0) {
            break;
        } else {
            printf("Invalid input!\n");
        }
    }

    display_status(&fs);
    return 0;
}
