#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define BOARD_SIZE 3

struct shared_use_st {
    int turn;                 // Indicates whose turn it is: 1 for Player 1, 2 for Player 2
    int board[BOARD_SIZE][BOARD_SIZE]; // Tic-Tac-Toe board (2D array with 0, 1, -1; -1 for empty cells)
    int game_over;            // Indicates if the game is over (1: game over, 0: ongoing)
    char message[100];        // For any additional messages or winner announcements
};

void display_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == -1)
                printf(" . ");
            else
                printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
}

int check_winner(int board[BOARD_SIZE][BOARD_SIZE]) {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] != -1 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];  // Return 1 for Player 1 win, 0 for Player 2 win
        if (board[0][i] != -1 && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }

    // Check diagonals
    if (board[0][0] != -1 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != -1 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    // Check for draw
    int empty_spaces = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == -1)
                empty_spaces++;
        }
    }

    if (empty_spaces == 0) {
        return -2;  // Indicating a draw
    }

    return -1;  // No winner or draw yet
}


int is_valid_move(int row, int col, int board[BOARD_SIZE][BOARD_SIZE]) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == -1;
}

int main() {
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    int shmid;
    
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    
    shared_stuff = (struct shared_use_st *)shared_memory;

    // Player 2 uses '0'
    printf("Player 2 (0) ready...\n");

    while (running) {
        while (shared_stuff->turn != 2 && !shared_stuff->game_over) {
            // Wait for Player 1 to make a move
            sleep(1);
        }

        if (shared_stuff->game_over) {
            printf("%s\n", shared_stuff->message);
            break;
        }

        // Display the current board
        printf("Current board:\n");
        display_board(shared_stuff->board);

        // Get move from Player 2
        int row, col;
        printf("Player 2, enter your move (row and column 0-2): ");
        scanf("%d %d", &row, &col);

        if (is_valid_move(row, col, shared_stuff->board)) 
        {
            shared_stuff->board[row][col] = 0;  // Player 2's move
            shared_stuff->turn = 1;  // Give the turn to Player 1

            // Check for a winner or draw
            int result = check_winner(shared_stuff->board);
            if (result == 1) {
                strcpy(shared_stuff->message, "Player 1 wins!");
                shared_stuff->game_over = 1;
            } else if (result == 0) {
                strcpy(shared_stuff->message, "Player 2 wins!");
                shared_stuff->game_over = 1;
            } else if (result == -2) {
                strcpy(shared_stuff->message, "It's a draw!");
                shared_stuff->game_over = 1;
            }
        } 
        else 
        {
            printf("Invalid move, try again.\n");
        }


        // Check for game over condition (you'll implement win/draw checking logic here)
    }

    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

