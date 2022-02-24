#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COL_RED "\x1b[31m"
#define COL_CYAN "\x1b[36m"
#define COL_MAGENTA "\x1b[35m"
#define COL_RESET "\x1b[0m"

int scores[2];
char table[4][4];
int char_bucket[2][2];
long is_timeout;
int is_place_a[2];

void clear_console() {
    system("@cls||clear");
}

void draw_table() {
    clear_console();
    printf("-----Score-----\n");
    printf(COL_CYAN "  Player 1: %d\n" COL_RESET, scores[0]);
    printf(COL_MAGENTA "  Plater 2: %d\n" COL_RESET, scores[1]);
    printf("---------------\n");

    int i, j;
    for (i = 0; i < 4; i++) {
        printf("  %d ", i + 1);
    }
    printf("\n");
    for (i = 0; i < 4; i++) {
        printf("%d", i + 1);
        for (j = 0; j < 4; j++) {
            if (table[i][j] == 'c' || table[i][j] == 'b' || table[i][j] == 'a') {
                printf(COL_CYAN " %c " COL_RESET, table[i][j]);
            } else {
                printf(COL_MAGENTA " %c " COL_RESET, table[i][j]);
            }
            if (j < 3) {
                printf("|");
            }
        }
        printf("\n");
    }
}

int compare(char a, char b, char c) {
    return a == b && b == c;
}

void cal_score(int row, int col, int player) {
    int score = 0;

    //Row
    score += compare(table[row][col], table[row + 1][col], table[row + 2][col]) &&
             table[row][col] != table[row + 3][col];
    score += compare(table[row][col], table[row - 1][col], table[row - 2][col]) &&
             table[row][col] != table[row - 3][col];
    score += compare(table[row][col], table[row + 1][col], table[row - 1][col]);

    //Column
    score += compare(table[row][col], table[row][col + 1], table[row][col + 2]) &&
             table[row][col] != table[row][col + 3];
    score += compare(table[row][col], table[row][col - 1], table[row][col - 2]) &&
             table[row][col] != table[row][col - 3];
    score += compare(table[row][col], table[row][col + 1], table[row][col - 1]);

    //Topleft cross
    score += compare(table[row][col], table[row + 1][col + 1], table[row + 2][col + 2]) &&
             table[row][col] != table[row + 3][col + 3];
    score += compare(table[row][col], table[row - 1][col - 1], table[row - 2][col - 2]) &&
             table[row][col] != table[row - 3][col - 3];
    score += compare(table[row][col], table[row + 1][col + 1], table[row - 1][col - 1]);

    //Topright cross
    score += compare(table[row][col], table[row + 1][col - 1], table[row + 2][col - 2]) &&
             table[row][col] != table[row + 3][col - 3];
    score += compare(table[row][col], table[row - 1][col + 1], table[row - 2][col - 2]) &&
             table[row][col] != table[row - 3][col - 3];
    score += compare(table[row][col], table[row + 1][col - 1], table[row - 1][col + 1]);

    scores[player] += score;
}

int place_char(int row, int col, int player, time_t start) {
    time_t end, elapsed;
    time(&end);
    elapsed = end - start;
    if (elapsed > 30) {
        is_timeout = elapsed;
        scores[player]--;
        return 0;
    }

    int place = 0;
    if (table[row][col] == ' ') {
        table[row][col] = (player == 0 ? 'c' : 'C');
        is_place_a[player] = 0;
        place++;
    } else if (table[row][col] == (player == 0 ? 'c' : 'C')) {
        if (char_bucket[player][1] > 0) {
            table[row][col] = (player == 0 ? 'b' : 'B');
            char_bucket[player][1]--;
            is_place_a[player] = 0;
            place++;
        }
    } else if (table[row][col] == (player == 0 ? 'b' : 'B')) {
        if (char_bucket[player][0] > 0 && is_place_a[player] == 0) {
            table[row][col] = (player == 0 ? 'a' : 'A');
            char_bucket[player][0]--;
            is_place_a[player] = 1;
            place++;
        }
    }

    if (place != 0) {
        cal_score(row, col, player);
        return 0;
    }

    return 1;
}

int check_end() {
    int count_blank = 0;
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (table[i][j] == ' ') {
                count_blank++;
            }
        }
    }
    if (count_blank == 0) {
        if (0 == (char_bucket[0][0] || char_bucket[0][1] || char_bucket[1][0] || char_bucket[1][1])) {
            return 1;
        }
    }
    return 0;
}

int check_skip(int player) {
    int count_blank = 0;
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (table[i][j] == ' ') {
                count_blank++;
            }
        }
    }
    if (count_blank == 0) {
        if (0 == (char_bucket[player][0] || char_bucket[player][1])) {
            return 1;
        }
    }
    return 0;
}

void initial() {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            table[i][j] = ' ';
        }
    }
    for (i = 0; i < 2; i++) {
        char_bucket[i][0] = 3;
        char_bucket[i][1] = 6;

        scores[i] = 0;
        is_place_a[i] = 0;
    }

    is_timeout = 0;
}

int main_game() {
    int player = 0;
    while (1) {

        int row, col;
        time_t start;
        time(&start);
        do {
            if (check_skip(player)) {
                break;
            }
            draw_table();
            if (check_skip((player + 1) % 2)) {
                printf("Player %d has no place and char left to place, will be skipped\n", ((player + 1) % 2) + 1);
            }
            if (is_timeout != 0) {
                int pl = (player + 1) % 2;
                printf(COL_RED "Player %d take more than 30 seconds to place last turn (%lds), got -1\n" COL_RESET, pl + 1, is_timeout);
                is_timeout = 0;
            }
            if (player == 0) {
                printf(COL_CYAN "Player %d turn, you have %d a and %d b left\n" COL_RESET, player + 1, char_bucket[player][0], char_bucket[player][1]);
            } else {
                printf(COL_MAGENTA "Player %d turn, you have %d a and %d b left\n" COL_RESET, player + 1, char_bucket[player][0], char_bucket[player][1]);
            }
            printf("Enter row and column to place a character (e.g. 1 1) # ");
            scanf(" %d %d", &row, &col);
        } while (place_char(row - 1, col - 1, player, start));

        if (check_end()) {
            return 1;
        }

        player = (player + 1) % 2;
    }

    return 0;
}

int main() {
    while (1) {
        initial();
        main_game();

        draw_table();

        if (scores[0] == scores[1]) {
            printf("Draw...\n");
        } else if (scores[0] > scores[1]) {
            printf(COL_CYAN "Player 1 Win...\n" COL_RESET);
        } else {
            printf(COL_MAGENTA "Player 2 Win...\n" COL_RESET);
        }

        char restart;
        do {
            printf("Do you want to restart the game [y/n] # ");
            scanf(" %c", &restart);
            restart = tolower(restart);
        } while (restart != 'y' && restart != 'n');
        if (restart == 'n') {
            break;
        }
    }
    system("@PAUSE");
    return 0;
}