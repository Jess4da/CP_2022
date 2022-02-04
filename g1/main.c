#include <stdio.h>
#include <stdlib.h>

char player_table[2][4][4];

int is_runing;

void draw_table(int p_num) {
    int i, j;
    for (i = 0; i < 4; i++) {
        printf("  %d ", i + 1);
    }
    printf("\n");
    for (i = 0; i < 4; i++) {
        printf("%d", i + 1);
        for (j = 0; j < 4; j++) {
            printf(" %c ", player_table[p_num][i][j]);
            if (j < 3) {
                printf("|");
            }
        }
        printf("\n");
    }
    printf("Player %d turn.", p_num + 1);
}

void place_alpha(int p_num, char alpha, int col, int row) {
    player_table[p_num][row - 1][col - 1] = alpha;
}

void initial() {
    is_runing = 1;

    int i, j, p;
    for (p = 0; p < 2; p++) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                player_table[p][i][j] = ' ';
            }
        }
    }
}

void main_loop(int turn) {
    while (1) {
        initial();
        draw_table(turn);

        turn++;
        turn = turn % 2;
    }
}

int main() {
    int turn = 0;
    while (1) {
        main_loop(turn);
        // Restart
        char is_restart;
        do {
            printf("Do you want to restart the game [y/n] >> ");
            scanf(" %c", &is_restart);
        } while (is_restart != 'y' && is_restart != 'n');
        turn = 0;
        if (is_restart == 'n') {
            break;
        }
    }

    return 0;
}