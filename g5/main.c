#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char table[4][4];
int score[2];
int options[2][2];

void cls() {
    system("@cls||clear");
}

void draw_table() {
    cls();
    printf("====Score board====\n");
    printf("Player 1: %d\n", score[0]);
    printf("Player 2: %d\n", score[1]);
    printf("===================\n");

    int i, j;
    printf("  ");
    for (i = 0; i < 4; i++) {
        printf("  %d ", i + 1);
    }
    printf("\n  -----------------\n");
    for (i = 0; i < 4; i++) {
        printf("%d ", i + 1);
        for (j = 0; j < 4; j++) {
            printf("| %c ", table[i][j]);
        }
        printf("|\n  -----------------\n");
    }
}

int place(int player, int row, int col) {
    if (table[row][col] == ' ' || table[row][col] == (player == 0 ? 'C' : 'c')) {
        table[row][col] = player == 0 ? 'c' : 'C';
        return 0;
    } else if (table[row][col] == (player == 0 ? 'c' : 'C')) {
        if (options[player][1] < 1) {
            return 1;
        }
        table[row][col] = player == 0 ? 'b' : 'B';
        options[player][1]--;
        return 0;
    } else if (table[row][col] == (player == 0 ? 'b' : 'B')) {
        if (options[player][0] < 1) {
            return 1;
        }
        table[row][col] = player == 0 ? 'a' : 'A';
        options[player][0]--;
        return 0;
    }
    return 1;
}

void check_score() {
    int p1 = 0, p2 = 0;
    int i, j;

    // Row check
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            if (table[i][j] != ' ' && table[i][j] == table[i][j + 1] &&
                table[i][j + 1] == table[i][j + 2] &&
                table[i][j + 2] != table[i][j + 3]) {
                if (table[i][j] == tolower(table[i][j])) {
                    if (table[i][j] == 'a') {
                        p1 += 2;
                    } else if (table[i][j] == 'b') {
                        p1++;
                    }
                    p1++;
                } else {
                    if (table[i][j] == 'A') {
                        p2 += 2;
                    } else if (table[i][j] == 'B') {
                        p2++;
                    }
                    p2++;
                }
            }
        }
    }

    // Column check
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (table[i][j] != ' ' && table[i][j] == table[i + 1][j] &&
                table[i + 1][j] == table[i + 2][j] &&
                table[i + 2][j] != table[i + 3][j]) {
                if (table[i][j] == tolower(table[i][j])) {
                    if (table[i][j] == 'a') {
                        p1 += 2;
                    } else if (table[i][j] == 'b') {
                        p1++;
                    }
                    p1++;
                } else {
                    if (table[i][j] == 'A') {
                        p2 += 2;
                    } else if (table[i][j] == 'B') {
                        p2++;
                    }
                    p2++;
                }
            }
        }
    }

    // Cross check
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (table[i][j] != ' ' && table[i][j] == table[i + 1][j + 1] &&
                table[i + 1][j + 1] == table[i + 2][j + 2] &&
                table[i + 2][j + 2] != table[i + 3][j + 3]) {
                if (table[i][j] == tolower(table[i][j])) {
                    if (table[i][j] == 'a') {
                        p1 += 2;
                    } else if (table[i][j] == 'b') {
                        p1++;
                    }
                    p1++;
                } else {
                    if (table[i][j] == 'A') {
                        p2 += 2;
                    } else if (table[i][j] == 'B') {
                        p2++;
                    }
                    p2++;
                }
            }
        }
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (table[i][j + 2] != ' ' && table[i][j + 2] == table[i + 1][j + 1] &&
                table[i + 1][j + 1] == table[i + 2][j] &&
                table[i + 2][j] != table[i + 3][j - 1]) {
                if (table[i + 1][j + 1] == tolower(table[i + 1][j + 1])) {
                    if (table[i + 1][j + 1] == 'a') {
                        p1 += 2;
                    } else if (table[i + 1][j + 1] == 'b') {
                        p1++;
                    }
                    p1++;
                } else {
                    if (table[i + 1][j + 1] == 'A') {
                        p2 += 2;
                    } else if (table[i + 1][j + 1] == 'B') {
                        p2++;
                    }
                    p2++;
                }
            }
        }
    }

    score[0] = p1;
    score[1] = p2;
}

void init() {
    score[0] = 0;
    score[1] = 0;

    int i, j, p;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            table[i][j] = ' ';
        }
    }

    for (p = 0; p < 2; p++) {
        options[p][0] = 3;
        options[p][1] = 6;
    }
}

int run() {
    int player = 0;
    while (1) {
        int row, col;
        char p_a = player == 0 ? 'a' : 'A';
        char p_b = player == 0 ? 'b' : 'B';
        do {
            draw_table();
            printf("Player %d turn, you have %d '%c' and %d '%c' left.\n", player + 1, options[player][0], p_a, options[player][1], p_b);
            printf("Choose row and column to place e.g. 1 1 >> ");
            scanf(" %d %d", &row, &col);
        } while (place(player, row - 1, col - 1));

        check_score();
        if (score[player] >= 5) {
            return player;
        }

        player++;
        player = player % 2;
    }
    return -1;
}

int main() {
    while (1) {
        init();
        int player = run();
        draw_table();
        printf("Player %d Win...\n", player + 1);

        char yn;
        do {
            printf("Do you want to restart the game [yes/no] >> ");
            scanf(" %c", &yn);
        } while (!(tolower(yn) == 'y' || tolower(yn) == 'n'));
        if (tolower(yn) == 'n') {
            system("PAUSE");
            return 0;
        }
    }
    return 0;
}