#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char player_table[4][4];

int player_bucket[2][2];

int p1_score;
int p2_score;

//ฟังก์ชันล้างหน้าจอ
void cls() {
    system("@cls||clear");
}

//ฟังก์ชันล้างเขียนหน้าจอ
void draw_table(int p_num) {
    cls();

    printf("Player 1 score: %d\n", p1_score);
    printf("Player 2 score: %d\n", p2_score);
    printf("-----------------\n");

    if (p_num < 2) {
        printf("Player %d turn.\n", p_num + 1);
        printf("Bucket: a=%d, b=%d\n", player_bucket[p_num][0], player_bucket[p_num][1]);
    }

    //วนลูปเพิ่อสร้างตาราง 4*4
    int i, j;
    for (i = 0; i < 4; i++) {
        printf("  %d ", i + 1);
    }
    printf("\n");
    for (i = 0; i < 4; i++) {
        printf("%d", i + 1);
        for (j = 0; j < 4; j++) {
            printf(" %c ", player_table[i][j]);
            if (j < 3) {
                printf("|");
            }
        }
        printf("\n");
    }
}
//ฟังก์ชัั่นเช็คตัวอักษรว่าเป็น A B C หรือ a b c
int check_alpha(char alpha) {
    alpha = tolower(alpha);
    if (alpha == 'a' || alpha == 'b' || alpha == 'c') {
        return 0;
    }
    return 1;
}

//ฟังก์ชั่นใส่ตัวอักษรลงกระดาน
int place_alpha(int p_num, char alpha, int row, int col) {
    char show_alpha = alpha;
    if (p_num % 2 == 0) {
        show_alpha = tolower(alpha);
        if (player_table[row - 1][col - 1] != ' ') {
            if (show_alpha == 'c') {
                return 1;
            } else if (show_alpha == 'a' && player_table[row - 1][col - 1] != 'b') {
                return 1;
            } else if (show_alpha == 'b' && player_table[row - 1][col - 1] != 'c') {
                return 1;
            }
        } else {
            if (show_alpha != 'c') {
                return 1;
            }
        }
    } else {
        show_alpha = toupper(alpha);
        if (player_table[row - 1][col - 1] != ' ') {
            if (show_alpha == 'C') {
                return 1;
            } else if (show_alpha == 'A' && player_table[row - 1][col - 1] != 'B') {
                return 1;
            } else if (show_alpha == 'B' && player_table[row - 1][col - 1] != 'C') {
                return 1;
            }
        } else {
            if (show_alpha != 'C') {
                return 1;
            }
        }
    }

    if (tolower(alpha) == 'a') {
        if (player_bucket[p_num][0] < 1) {
            return 1;
        } else {
            player_bucket[p_num][0]--;
        }
    } else if (tolower(alpha) == 'b') {
        if (player_bucket[p_num][1] < 1) {
            return 1;
        } else {
            player_bucket[p_num][1]--;
        }
    }

    player_table[row - 1][col - 1] = show_alpha;
    return 0;
}
//ฟังก์ชั่นเช็คคะแนน
int sum_points() {
    int p1 = 0, p2 = 0;
    int i, j;

    // Row check
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            if (player_table[i][j] != ' ' && player_table[i][j] == player_table[i][j + 1] &&
                player_table[i][j + 1] == player_table[i][j + 2] &&
                player_table[i][j + 2] != player_table[i][j + 3]) {
                if (player_table[i][j] == tolower(player_table[i][j])) {
                    if (player_table[i][j] == 'a') {
                        p1 = p1 + 4;
                    } else if (player_table[i][j] == 'b') {
                        p1 = p1 + 2;
                    }
                    p1++;
                } else {
                    if (player_table[i][j] == 'A') {
                        p2 = p2 + 4;
                    } else if (player_table[i][j] == 'B') {
                        p2 = p2 + 2;
                    }
                    p2++;
                }
            }
        }
    }

    // Column check
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (player_table[i][j] != ' ' && player_table[i][j] == player_table[i + 1][j] &&
                player_table[i + 1][j] == player_table[i + 2][j] &&
                player_table[i + 2][j] != player_table[i + 3][j]) {
                if (player_table[i][j] == tolower(player_table[i][j])) {
                    if (player_table[i][j] == 'a') {
                        p1 = p1 + 4;
                    } else if (player_table[i][j] == 'b') {
                        p1 = p1 + 2;
                    }
                    p1++;
                } else {
                    if (player_table[i][j] == 'A') {
                        p2 = p2 + 4;
                    } else if (player_table[i][j] == 'B') {
                        p2 = p2 + 2;
                    }
                    p2++;
                }
            }
        }
    }

    // Cross check
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (player_table[i][j] != ' ' && player_table[i][j] == player_table[i + 1][j + 1] &&
                player_table[i + 1][j + 1] == player_table[i + 2][j + 2] &&
                player_table[i + 2][j + 2] != player_table[i + 3][j + 3]) {
                if (player_table[i][j] == tolower(player_table[i][j])) {
                    if (player_table[i][j] == 'a') {
                        p1 = p1 + 4;
                    } else if (player_table[i][j] == 'b') {
                        p1 = p1 + 2;
                    }
                    p1++;
                } else {
                    if (player_table[i][j] == 'A') {
                        p2 = p2 + 4;
                    } else if (player_table[i][j] == 'B') {
                        p2 = p2 + 2;
                    }
                    p2++;
                }
            }
        }
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (player_table[i][j + 2] != ' ' && player_table[i][j + 2] == player_table[i + 1][j + 1] &&
                player_table[i + 1][j + 1] == player_table[i + 2][j] &&
                player_table[i + 2][j] != player_table[i + 3][j - 1]) {
                if (player_table[i + 1][j + 1] == tolower(player_table[i + 1][j + 1])) {
                    if (player_table[i + 1][j + 1] == 'a') {
                        p1 = p1 + 4;
                    } else if (player_table[i + 1][j + 1] == 'b') {
                        p1 = p1 + 2;
                    }
                    p1++;
                } else {
                    if (player_table[i + 1][j + 1] == 'A') {
                        p2 = p2 + 4;
                    } else if (player_table[i + 1][j + 1] == 'B') {
                        p2 = p2 + 2;
                    }
                    p2++;
                }
            }
        }
    }

    p1_score = p1;
    p2_score = p2;

    // Check game end
    if (player_bucket[0][0] == 0 && player_bucket[0][1] == 0 &&
        player_bucket[1][0] == 0 && player_bucket[1][1] == 0) {
        return 0;
    }
    return 1;
}
//กำหนดค่าเริ่มต้น
void initial() {
    p1_score = 0;
    p2_score = 0;

    int i, j, p;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            player_table[i][j] = ' ';
        }
    }
    for (p = 0; p < 2; p++) {
        player_bucket[p][0] = 3;
        player_bucket[p][1] = 6;
    }
}
//ฟังก์ชั่นวนลูปเล่นเกม
int main_loop(int turn) {
    while (1) {
        draw_table(turn);

        char alpha;
        int row, col;
        do {

            do {
                printf("Player %d choose alphabet to place [a,b,c] >> ", turn + 1);
                scanf(" %s", &alpha);
            } while (check_alpha(alpha));

            printf("Player %d choose row to place >> ", turn + 1);
            scanf(" %d", &row);
            printf("Player %d choose column to place >> ", turn + 1);
            scanf(" %d", &col);
        } while (place_alpha(turn, alpha, row, col));

        if (sum_points() == 0) {
            return 0;
        }

        turn++;
        turn = turn % 2;
    }
    return 0;
}

int main() {
    while (1) { // Restart loop
        int turn = 0;
        initial();

        // Main game loop
        main_loop(turn);

        draw_table(2);

        if (p1_score > p2_score) {
            printf("Player 1 Win.");
        } else if (p1_score < p2_score) {
            printf("Player 2 Win.");
        } else {
            printf("Draw.");
        }

        // Restart
        char is_restart;
        do {
            printf("Do you want to restart the game [y/n] >> ");
            scanf(" %c", &is_restart);
            is_restart = tolower(is_restart);
        } while (is_restart != 'y' && is_restart != 'n');
        if (is_restart == 'n') {
            break;
        }
    }

    return 0;
}