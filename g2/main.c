#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char table[4][4];

int p1_point;
int p2_point;

int player_alpha[2][2];

void cls() {
    system("@cls||clear");
}

void draw_table(int turn) {
    int i, j;
    cls();
    printf("-----Score board-----\n");
    printf("Player 1: %d (a:%d, b:%d)\n", p1_point, player_alpha[0][0], player_alpha[0][1]);
    printf("Player 2: %d (A:%d, B:%d)\n", p2_point, player_alpha[1][0], player_alpha[1][1]);
    printf("---------------------\n\n");
    printf("      Turn %d/30\n", turn);
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

int place_alpha(int p, int row, int col) {
    if (table[row][col] == ' ') {
        if (p == 0) {
            table[row][col] = 'c';
        } else {
            table[row][col] = 'C';
        }
        return 0;
    } else {
        if (p == 0) {
            if (table[row][col] == 'c') {
                table[row][col] = 'b';
                player_alpha[p][1]--;
                return 0;
            } else if (table[row][col] == 'b') {
                table[row][col] = 'a';
                player_alpha[p][0]--;
                return 0;
            }
        } else if (p == 1) {
            if (table[row][col] == 'C') {
                table[row][col] = 'B';
                player_alpha[p][1]--;
                return 0;
            } else if (table[row][col] == 'B') {
                table[row][col] = 'A';
                player_alpha[p][0]--;
                return 0;
            }
        }
    }

    return 1;
}

int calculate_score() {
    int p1 = 0, p2 = 0;
    int i, j;

    // Row check
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            if (table[i][j] != ' ' && table[i][j] == table[i][j + 1] &&
                table[i][j + 1] == table[i][j + 2]) {
                if (table[i][j] == tolower(table[i][j])) {
                    if (table[i][j] == 'a') {
                        return -1;
                    } else if (table[i][j] == 'b') {
                        p1++;
                    }
                    p1++;
                } else {
                    if (table[i][j] == 'A') {
                        return -2;
                    } else if (table[i][j] == 'B') {
                        p2++;
                    }
                    p2++;
                }
                break;
            }
        }
    }

    // Column check
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (table[i][j] != ' ' && table[i][j] == table[i + 1][j] &&
                table[i + 1][j] == table[i + 2][j]) {
                if (table[i][j] == tolower(table[i][j])) {
                    if (table[i][j] == 'a') {
                        return -1;
                    } else if (table[i][j] == 'b') {
                        p1++;
                    }
                    p1++;
                } else {
                    if (table[i][j] == 'A') {
                        return -2;
                    } else if (table[i][j] == 'B') {
                        p2++;
                    }
                    p2++;
                }
            }
        }
        break;
    }

    // Cross check
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (table[i][j] != ' ' && table[i][j] == table[i + 1][j + 1] &&
                table[i + 1][j + 1] == table[i + 2][j + 2]) {
                if (table[i][j] == tolower(table[i][j])) {
                    if (table[i][j] == 'a') {
                        return -1;
                    } else if (table[i][j] == 'b') {
                        p1++;
                    }
                    p1++;
                } else {
                    if (table[i][j] == 'A') {
                        return -2;
                    } else if (table[i][j] == 'B') {
                        p2++;
                    }
                    p2++;
                }
            }
        }
        break;
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (table[i][j + 2] != ' ' && table[i][j + 2] == table[i + 1][j + 1] &&
                table[i + 1][j + 1] == table[i + 2][j]) {
                if (table[i + 1][j + 1] == tolower(table[i + 1][j + 1])) {
                    if (table[i + 1][j + 1] == 'a') {
                        return -1;
                    } else if (table[i + 1][j + 1] == 'b') {
                        p1++;
                    }
                    p1++;
                } else {
                    if (table[i + 1][j + 1] == 'A') {
                        return -2;
                    } else if (table[i + 1][j + 1] == 'B') {
                        p2++;
                    }
                    p2++;
                }
            }
        }
        break;
    }
    p1_point = p1;
    p2_point = p2;

    return 1;
}

void setup() {
    p1_point = 0;
    p2_point = 0;

    int i, j, p;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            table[i][j] = ' ';
        }
    }

    for (p = 0; p < 2; p++) {
        player_alpha[p][0] = 3;
        player_alpha[p][1] = 6;
    }
}

int game_loop() {
    int turn = 0;
    int num_turn = 0;

    while (num_turn < 30) {
        draw_table(num_turn + 1);

        int row;
        int col;
        do {

            printf("Player %d turn, choose row and column to place (Ex: 1 1) > ", turn + 1);
            scanf(" %d %d", &row, &col);
        } while (place_alpha(turn, row - 1, col - 1));

        if (calculate_score() < 0) {
            return calculate_score();
        }

        turn++;
        num_turn++;
        turn = turn % 2;
    }

    return turn;
}

int main() {
    while (1) {

        setup();
        int win = game_loop();
        draw_table(win);

        if (win < 0) {
            if (win == -1) {
                printf("Player 1 Win...\n");
            } else {
                printf("Player 2 Win...\n");
            }
        } else {
            if (p1_point > p2_point) {
                printf("Player 1 Win...\n");
            } else if (p1_point < p2_point) {
                printf("Player 2 Win...\n");
            } else {
                printf("Draw...\n");
            }
        }

        char is_restart = ' ';
        do {
            printf("Do you want to restart the game ? [Y/N] > ");
            scanf(" %c", &is_restart);
        } while (!(tolower(is_restart) == 'y' || tolower(is_restart) == 'n'));

        if (tolower(is_restart) == 'n') {
            break;
        }
    }

    system("PAUSE");

    return 0;
}