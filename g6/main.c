#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char table[4][4];
int traps[2][2];
int score[2];
int alphabet[2][2];
int first;
int is_trap;

void cls() {
    system("@cls||clear");
}

void draw() {
    cls();

    printf("======================\n");
    printf("Player 1: %d | a:%d, b:%d\n", score[0], alphabet[0][0], alphabet[0][1]);
    printf("Player 2: %d | A:%d, B:%d\n", score[1], alphabet[1][0], alphabet[1][1]);
    printf("======================\n");

    int i, j;
    printf("   ");
    for (i = 0; i < 4; i++) {
        printf("  %d ", i + 1);
    }
    printf("\n   -----------------\n");
    for (i = 0; i < 4; i++) {
        printf(" %d ", i + 1);
        for (j = 0; j < 4; j++) {
            printf("| %c ", table[i][j]);
        }
        printf("|\n   -----------------\n");
    }
}

int equals(char a, char b, char c) {
    return a == b && b == c;
}

int check_score(int p, int row, int col) {

    int temp_score = 0;

    // Trap check
    if (tolower(table[row][col]) == 'c') {
        int i;
        for (i = 0; i < 2; i++) {
            if (row == traps[i][0] && col == traps[i][1]) {
                int pen = (rand() % 1) + 1;
                temp_score -= pen;
                is_trap = pen;
            }
        }
    }

    // Row check
    temp_score += equals(table[row][col], table[row + 1][col], table[row + 2][col]) &&
                  table[row][col] != table[row + 3][col];
    temp_score += equals(table[row][col], table[row - 1][col], table[row - 2][col]) &&
                  table[row][col] != table[row - 3][col];
    temp_score += equals(table[row][col], table[row + 1][col], table[row - 1][col]);

    // Column check
    temp_score += equals(table[row][col], table[row][col + 1], table[row][col + 2]) &&
                  table[row][col] != table[row][col + 3];
    temp_score += equals(table[row][col], table[row][col - 1], table[row][col - 2]) &&
                  table[row][col] != table[row][col - 3];
    temp_score += equals(table[row][col], table[row][col + 1], table[row][col - 1]);

    // Cross topleft check
    temp_score += equals(table[row][col], table[row + 1][col + 1], table[row + 2][col + 2]) &&
                  table[row][col] != table[row + 3][col + 3];
    temp_score += equals(table[row][col], table[row - 1][col - 1], table[row - 2][col - 2]) &&
                  table[row][col] != table[row - 3][col - 3];
    temp_score += equals(table[row][col], table[row + 1][col + 1], table[row - 1][col - 1]);

    // Cross topright check
    temp_score += equals(table[row][col], table[row + 1][col - 1], table[row + 2][col - 2]) &&
                  table[row][col] != table[row + 3][col - 3];
    temp_score += equals(table[row][col], table[row - 1][col + 1], table[row - 2][col - 2]) &&
                  table[row][col] != table[row - 3][col - 3];
    temp_score += equals(table[row][col], table[row + 1][col - 1], table[row - 1][col + 1]);

    score[p] += temp_score;
    if (temp_score > 0)
        first++;
    return temp_score;
}

int place_alphabet(int p, int row, int col) {
    int count_place = 0;
    if (table[row][col] == ' ') {
        table[row][col] = p == 0 ? 'c' : 'C';
        count_place++;
    } else if (table[row][col] == (p == 0 ? 'c' : 'C')) {
        if (alphabet[p][1] > 0) {
            table[row][col] = p == 0 ? 'b' : 'B';
            alphabet[p][1]--;
            count_place++;
        }
    } else if (table[row][col] == (p == 0 ? 'b' : 'B')) {
        if (alphabet[p][0] > 0) {
            table[row][col] = p == 0 ? 'a' : 'A';
            alphabet[p][0]--;
            count_place++;
        }
    }
    if (count_place > 0) {
        check_score(p, row, col);
        return 0;
    }
    return 1;
}

void init() {
    srand(time(0));
    int i, j;
    for (i = 0; i < 2; i++) {
        do {
            traps[i][0] = rand() % 4;
            traps[i][1] = rand() % 4;
        } while (traps[i - 1][0] == traps[i][0] && traps[i - 1][1] == traps[i][1]);

        alphabet[i][0] = 3;
        alphabet[i][1] = 6;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            table[i][j] = ' ';
        }
    }

    score[0] = 0;
    score[1] = 0;

    first = 0;
    is_trap = -1;
}

void run() {
    int p = 0;
    while (1) {
        int row, col;
        do {
            draw();
            if (is_trap != -1) {
                printf("Player %d got trapped last turn, -%d\n", p == 0 ? 2 : 1, is_trap);
                is_trap = -1;
            }
            printf("Player %d turn.\n", p + 1);
            printf("Choose row and column to place e.g. 1,2 >> ");
            scanf(" %d,%d", &row, &col);
        } while (place_alphabet(p, row - 1, col - 1));

        if (first == 1) {
            do {
                draw();
                printf("Player %d bonus.\n", p + 1);
                printf("Choose row and column to place for player %d e.g. 1,2 >> ", p == 0 ? 2 : 1);
                scanf(" %d,%d", &row, &col);
            } while (place_alphabet(p == 0 ? 1 : 0, row - 1, col - 1));
            p = p == 0 ? 1 : 0;
        }

        p = p + 1;
        p = p % 2;
    }
}

int main() {
    while (1) {
        init();
        run();

        char is_restart;
        do {
            printf("Do you want to restart the game [y/n] >> ");
            scanf(" %c", &is_restart);
        } while (!(tolower(is_restart) == 'y' || tolower(is_restart) == 'n'));
        if (tolower(is_restart) == 'n') {
            break;
        }
    }

    system("PAUSE");
    return 0;
}