#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ROWS 11
#define COLS 11
#define MAX_COLORS 4
#define MAX_MOVES 10000

//Se genereaza matricea initiala 11x11
void initializareMatrice(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = rand() % MAX_COLORS + 1;  // Bomboane random intre 1 și 4
        }
    }
}

// Functie pentru detectarea liniilor (orizontal si vertical)
bool detectareLinii(int board[ROWS][COLS], bool matches[ROWS][COLS], int *affected_columns) {
    bool match_linie3 = false;

    // Resetam matricea de "matches"
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matches[i][j] = false;
        }
    }

    // Detectam liniile orizontale
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 2; j++) {
            if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] != 0) {
                match_linie3 = true;
                matches[i][j] = matches[i][j + 1] = matches[i][j + 2] = true;
                affected_columns[j] = affected_columns[j + 1] = affected_columns[j + 2] = 1;
            }
        }
    }

    // Detectam liniile verticale
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS - 2; i++) {
            if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] != 0) {
                match_linie3 = true;
                matches[i][j] = matches[i + 1][j] = matches[i + 2][j] = true;
                affected_columns[i] = affected_columns[i + 1] = affected_columns[i + 2] = 1;
            }
        }
    }

    return match_linie3;
}

// Functie pentru eliminarea bomboanelor si calcularea punctajului
int eliminaBomboane(int board[ROWS][COLS], bool matches[ROWS][COLS]) {
    int scor = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matches[i][j]) {
                board[i][j] = 0;  // Eliminam linia de 3 bomboane
                scor += 5;       // Fiecare linie eliminata adauga 5 puncte
            }
        }
    }

    return scor;
}

// Functie pentru coborarea bomboanelor in coloanele afectate
void coboaraBomboane(int board[ROWS][COLS], int affected_columns[COLS]) {
    for (int j = 0; j < COLS; j++) {
        if (affected_columns[j] == 1) {
            for (int i = ROWS - 1; i >= 0; i--) {
                if (board[i][j] == 0) {
                    // Cautam cea mai apropiata bomboana deasupra pentru a o muta
                    for (int k = i - 1; k >= 0; k--) {
                        if (board[k][j] != 0) {
                            board[i][j] = board[k][j];
                            board[k][j] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
}

// Functie pentru generarea de bomboane noi în spatiile libere
void genereazaBomboaneNoi(int board[ROWS][COLS], int affected_columns[COLS]) {
    for (int j = 0; j < COLS; j++) {
        if (affected_columns[j] == 1) {
            for (int i = 0; i < ROWS; i++) {
                if (board[i][j] == 0) {
                    board[i][j] = rand() % MAX_COLORS + 1;  //Generam bomboane noi
                }
            }
        }
    }
}

//rularea unui singur joc
int rulareUnJoc() {
    int board[ROWS][COLS];
    bool matches[ROWS][COLS];
    int affected_columns[COLS] = {0};
    int scor = 0;
    int mutari = 0;

    initializareMatrice(board);

    while (mutari < MAX_MOVES) {
        // detectare si eliminare linii
        bool found_match = detectareLinii(board, matches, affected_columns);
        if (found_match) {
            scor += eliminaBomboane(board, matches);
            coboaraBomboane(board, affected_columns);
            genereazaBomboaneNoi(board, affected_columns);
            for (int i = 0; i < COLS; i++)
                affected_columns[i] = 0;  // Resetare coloanele afectate
        } else {
            // Daca nu mai exista mutari jocul se termina
            break;
        }
        mutari++;
    }

    return scor;
}

//simularea a 1000 de jocuri
void candyCrush(int nr_jocuri) {
    int total_scor = 0;

    for (int i = 0; i < nr_jocuri; i++) {
        int scor = rulareUnJoc();
        total_scor += scor;
        printf("Jocul %d: Scor: %d\n", i + 1, scor);
    }

    printf("\nScorul mediu dupa %d de jocuri: %.2f\n", nr_jocuri, total_scor / (double)nr_jocuri);
}

int main() {
    candyCrush(1000);  // ruleaza 1000 de jocuri
    return 0;
}
