#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 11
#define COLS 11
#define MAX_COLORS 4
#define MAX_MOVES 10000
#define MAX_SCORE 10000

// Se genereaza matricea initiala 11x11
void initializareMatrice(int board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = rand() % MAX_COLORS + 1;  // Bomboane random intre 1 și 4
        }
    }
}

// Functie pentru detectarea liniilor (orizontal si vertical)
bool detectareFormatiuni(int board[ROWS][COLS], bool matches[ROWS][COLS], int *affected_columns) {
    bool match_found = false;

    // Resetam matricea de "matches"
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matches[i][j] = false;
        }
    }

// Detectam formatiuni de tip linie, T si L in toate orientarile
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] != 0) {
                // Verificam linia de 5 (orizontal)
                if (j < COLS - 4 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3] && board[i][j] == board[i][j + 4]) {
                    match_found = true;
                    matches[i][j] = matches[i][j + 1] = matches[i][j + 2] = matches[i][j + 3] = matches[i][j + 4] = true;
                    affected_columns[j] = affected_columns[j + 1] = affected_columns[j + 2] = affected_columns[j + 3] = affected_columns[j + 4] = 0;
                }

                // Verificam linia de 5 (vertical)
                if (i < ROWS - 4 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j] && board[i][j] == board[i + 4][j]) {
                    match_found = true;
                    matches[i][j] = matches[i + 1][j] = matches[i + 2][j] = matches[i + 3][j] = matches[i + 4][j] = true;
                    affected_columns[j] = 0;
                }

                // Verificam formatiunea T (orizontal)
                if (j < COLS - 2 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]) {
                    if (i > 0 && board[i - 1][j + 1] == board[i][j]) { // T cu capul în sus
                        match_found = true;
                        matches[i][j] = matches[i][j + 1] = matches[i][j + 2] = matches[i - 1][j + 1] = true;
                        affected_columns[j] = affected_columns[j + 1] = affected_columns[j + 2] = 0;
                    }
                    if (i < ROWS - 1 && board[i + 1][j + 1] == board[i][j]) { // T cu capul în jos
                        match_found = true;
                        matches[i][j] = matches[i][j + 1] = matches[i][j + 2] = matches[i + 1][j + 1] = true;
                        affected_columns[j] = affected_columns[j + 1] = affected_columns[j + 2] = 0;
                    }
                }

                // Verificam formatiunea T (vertical)
                if (i < ROWS - 2 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j]) {
                    if (j > 0 && board[i + 1][j - 1] == board[i][j]) { // T cu capul la stanga
                        match_found = true;
                        matches[i][j] = matches[i + 1][j] = matches[i + 2][j] = matches[i + 1][j - 1] = true;
                        affected_columns[j] = 0;
                    }
                    if (j < COLS - 1 && board[i + 1][j + 1] == board[i][j]) { // T cu capul la dreapta
                        match_found = true;
                        matches[i][j] = matches[i + 1][j] = matches[i + 2][j] = matches[i + 1][j + 1] = true;
                        affected_columns[j] = 0;
                    }
                }

                // Verificam formatiunea L (orizontal)
                if (j < COLS - 2 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]) {
                    if (i < ROWS - 1 && board[i + 1][j] == board[i][j]) { // L in jos
                        match_found = true;
                        matches[i][j] = matches[i][j + 1] = matches[i][j + 2] = matches[i + 1][j] = true;
                        affected_columns[j] = affected_columns[j + 1] = affected_columns[j + 2] = 0;
                    }
                    if (i > 0 && board[i - 1][j] == board[i][j]) { // L in sus
                        match_found = true;
                        matches[i][j] = matches[i][j + 1] = matches[i][j + 2] = matches[i - 1][j] = true;
                        affected_columns[j] = affected_columns[j + 1] = affected_columns[j + 2] = 0;
                    }
                }

                // Verificam formatiunea L (vertical)
                if (i < ROWS - 2 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j]) {
                    if (j < COLS - 1 && board[i][j + 1] == board[i][j]) { // L in dreapta
                        match_found = true;
                        matches[i][j] = matches[i + 1][j] = matches[i + 2][j] = matches[i][j + 1] = true;
                        affected_columns[j] = 0;
                    }
                    if (j > 0 && board[i][j - 1] == board[i][j]) { // L in stanga
                        match_found = true;
                        matches[i][j] = matches[i + 1][j] = matches[i + 2][j] = matches[i][j - 1] = true;
                        affected_columns[j] = 0;
                    }
                }

                // Verificam linia de 4 (orizontal)
                if (j < COLS - 3 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3]) {
                    match_found = true;
                    matches[i][j] = matches[i][j + 1] = matches[i][j + 2] = matches[i][j + 3] = true;
                    affected_columns[j] = affected_columns[j + 1] = affected_columns[j + 2] = affected_columns[j + 3] = 0;
                }

                // Verificam linia de 4 (vertical)
                if (i < ROWS - 3 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j]) {
                    match_found = true;
                    matches[i][j] = matches[i + 1][j] = matches[i + 2][j] = matches[i + 3][j] = true;
                    affected_columns[j] = 0;
                }

                // Verificam linia de 3 (orizontal)
                if (j < COLS - 2 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2]) {
                    match_found = true;
                    matches[i][j] = matches[i][j + 1] = matches[i][j + 2] = true;
                    affected_columns[j] = affected_columns[j + 1] = affected_columns[j + 2] = 0;
                }

                // Verificam linia de 3 (vertical)
                if (i < ROWS - 2 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j]) {
                    match_found = true;
                    matches[i][j] = matches[i + 1][j] = matches[i + 2][j] = true;
                    affected_columns[j] = 0;
                }
            }
        }
    }


    return match_found;
}


// Functie pentru eliminarea bomboanelor si calcularea punctajului
int eliminaBomboane(int board[ROWS][COLS], bool matches[ROWS][COLS]) {
    int scor = 0;

    // Contor pentru a verifica cate bomboane sunt eliminate
    int temp_matches[ROWS][COLS] = {0};

    // Eliminarea bomboanelor
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matches[i][j]) {
                temp_matches[i][j] = 1;  // Marcam bomboana ca fiind eliminata
                board[i][j] = 0;  // Eliminam bomboana
            }
        }
    }

    // Calculam scorul bazat pe formatiuni
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Verificam liniile de 5 orizontal
            if (j < COLS - 4 && temp_matches[i][j] && temp_matches[i][j + 1] && temp_matches[i][j + 2] && temp_matches[i][j + 3] && temp_matches[i][j + 4]) {
                scor += 50;
            }

            // Verificam liniile de 5 (vertical)
            if (i < ROWS - 4 && temp_matches[i][j] && temp_matches[i + 1][j] && temp_matches[i + 2][j] && temp_matches[i + 3][j] && temp_matches[i + 4][j]) {
                scor += 50;
            }

            // Verificam formatiunile de tip T (orizontal)
            if (j < COLS - 2 && temp_matches[i][j] && temp_matches[i][j + 1] && temp_matches[i][j + 2] && i > 0 && temp_matches[i - 1][j + 1]) {
                scor += 30;
            }

            // Verificam formatiunile de tip T (vertical)
            if (i < ROWS - 2 && temp_matches[i][j] && temp_matches[i + 1][j] && temp_matches[i + 2][j] && j > 0 && temp_matches[i + 1][j - 1]) {
                scor += 30;
            }

            // Verificam formatiunile de tip L (orizontal)
            if (j < COLS - 2 && temp_matches[i][j] && temp_matches[i][j + 1] && temp_matches[i][j + 2] && i < ROWS - 1 && temp_matches[i + 1][j]) {
                scor += 20;
            }

            // Verificam formatiunile de tip L (vertical)
            if (i < ROWS - 2 && temp_matches[i][j] && temp_matches[i + 1][j] && temp_matches[i + 2][j] && j < COLS - 1 && temp_matches[i][j + 1]) {
                scor += 20;
            }

                // Verificam liniile de 4 orizontal
            else if (j < COLS - 3 && temp_matches[i][j] && temp_matches[i][j + 1] && temp_matches[i][j + 2] && temp_matches[i][j + 3]) {
                scor += 10;
            }

                // Verificam liniile de 4 (vertical)
            else if (i < ROWS - 3 && temp_matches[i][j] && temp_matches[i + 1][j] && temp_matches[i + 2][j] && temp_matches[i + 3][j]) {
                scor += 10;
            }

                // Verificam liniile de 3 orizontal
            else if (j < COLS - 2 && temp_matches[i][j] && temp_matches[i][j + 1] && temp_matches[i][j + 2]) {
                scor += 5;
            }

                // Verificam liniile de 3 (vertical)
            else if (i < ROWS - 2 && temp_matches[i][j] && temp_matches[i + 1][j] && temp_matches[i + 2][j]) {
                scor += 5;
            }

        }
    }

    return scor;
}

// Functie pentru coborarea bomboanelor in coloanele afectate
void coboaraBomboane(int board[ROWS][COLS], int affected_columns[COLS]) {
    for (int j = 0; j < COLS; j++) {
        if (affected_columns[j] == 0) {
            for (int i = ROWS - 1; i >= 0; i--) {
                if (board[i][j] == 0) {
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


// Functie pentru generarea de bomboane noi in spatiile libere
void genereazaBomboaneNoi(int board[ROWS][COLS], int affected_columns[COLS]) {
    // Daca o coloana a fost afectata, cautam de jos in sus pentru a umple golurile
    for (int j = 0; j < COLS; j++) {
        // Verificam daca coloana a fost afectata
        if (affected_columns[j] == 0) {
            // Cautam de jos in sus pentru a umple spatiile libere
            for (int i = ROWS - 1; i >= 0; i--) {
                if (board[i][j] == 0) {  // Daca gasim un spatiu liber
                    // Generam o bomboana noua
                    board[i][j] = rand() % MAX_COLORS + 1;
                }
            }
        }
    }
}


// Functie pentru a verifica daca interschimbarea genereaza o formatiune valida
bool interschimbaBomboane(int board[ROWS][COLS], int x1, int y1, int x2, int y2) {
    // Interschimbam bomboanele
    int temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;

    // Verificam daca schimbarea creeaza o formatiune valida
    bool matches[ROWS][COLS];  // Declaram matricea matches
    int affected_columns[COLS] = {0};

    bool is_valid = detectareFormatiuni(board, matches, affected_columns);

    // Revenim la starea initiala
    temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;

    return is_valid;  // Returnam daca schimbarea este valida
}

// Functie pentru a gasi mutari valide si cele mai profitabile
bool gasesteMutariValide(int board[ROWS][COLS], int *x1, int *y1, int *x2, int *y2) {
    int best_score = 0;
    bool found_move = false;
    bool matches[ROWS][COLS];  // Declara matricea matches

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Verifica mutarea orizontala spre dreapta
            if (j < COLS - 1) {
                if (interschimbaBomboane(board, i, j, i, j + 1)) {
                    int temp_score = eliminaBomboane(board, matches);
                    if (temp_score > best_score && temp_score <= MAX_SCORE) {
                        best_score = temp_score;
                        *x1 = i;
                        *y1 = j;
                        *x2 = i;
                        *y2 = j + 1;
                        found_move = true;
                    }
                }
                // Verifica mutarea orizontala spre stanga
                if (j > 0) {
                    if (interschimbaBomboane(board, i, j, i, j - 1)) {
                        int temp_score = eliminaBomboane(board, matches);
                        if (temp_score > best_score && temp_score <= MAX_SCORE) {
                            best_score = temp_score;
                            *x1 = i;
                            *y1 = j;
                            *x2 = i;
                            *y2 = j - 1;
                            found_move = true;
                        }
                    }
                }
            }
            // Verifica mutarea verticala in jos
            if (i < ROWS - 1) {
                if (interschimbaBomboane(board, i, j, i + 1, j)) {
                    int temp_score = eliminaBomboane(board, matches);
                    if (temp_score > best_score && temp_score <= MAX_SCORE) {
                        best_score = temp_score;
                        *x1 = i;
                        *y1 = j;
                        *x2 = i + 1;
                        *y2 = j;
                        found_move = true;
                    }
                }
            }
            // Verifica mutarea verticala in sus
            if (i > 0) {
                if (interschimbaBomboane(board, i, j, i - 1, j)) {
                    int temp_score = eliminaBomboane(board, matches);
                    if (temp_score > best_score && temp_score <= MAX_SCORE) {
                        best_score = temp_score;
                        *x1 = i;
                        *y1 = j;
                        *x2 = i - 1;
                        *y2 = j;
                        found_move = true;
                    }
                }
            }
        }
    }

    return found_move;  // Returneaza daca s-au gasit mutari
}

// Rularea unui singur joc
int rulareUnJoc(int *mutari_joc) {
    int board[ROWS][COLS];
    initializareMatrice(board);
    int mutari = 0;
    int scor = 0;
    int x1, y1, x2, y2;

    // Detectam si eliminam formatiunile inițiale
    while (scor < MAX_SCORE && *mutari_joc < MAX_MOVES) {
        bool matches[ROWS][COLS];
        int affected_columns[COLS] = {0};

        // Detectare si eliminare formatiuni valide
        while (detectareFormatiuni(board, matches, affected_columns)) {
            scor += eliminaBomboane(board, matches);
            coboaraBomboane(board, affected_columns);
            genereazaBomboaneNoi(board, affected_columns);

            // Opreste jocul daca s-a atins scorul de 10000
            if (scor >= MAX_SCORE) {
                *mutari_joc = mutari;
                printf("\nNumar mutari joc: %d!\n", *mutari_joc);
                return scor;
            }
        }

        // Cautare mutari valide daca nu mai exista formatiuni formate automat
        if (gasesteMutariValide(board, &x1, &y1, &x2, &y2)) {
            // Executa interschimbarea
            int temp = board[x1][y1];
            board[x1][y1] = board[x2][y2];
            board[x2][y2] = temp;

            // Verificam daca interschimbarea a generat o formatiune valida
            if (detectareFormatiuni(board, matches, affected_columns)) {
                do {
                    scor += eliminaBomboane(board, matches);
                    coboaraBomboane(board, affected_columns);
                    genereazaBomboaneNoi(board, affected_columns);
                    mutari++;
                    (*mutari_joc) = mutari;

                    // Opreste jocul daca s-a atins scorul de 10000
                    if (scor >= MAX_SCORE) {
                        printf("\nNumar mutari joc: %d!\n", *mutari_joc);
                        return scor;
                    }
                } while (detectareFormatiuni(board, matches, affected_columns));
            } else {
                // Revenim la starea initiala daca nu s-a realizat o formatiune valida
                temp = board[x1][y1];
                board[x1][y1] = board[x2][y2];
                board[x2][y2] = temp;
            }
        } else {
            // Iesim din bucla daca nu mai exista mutari valide
            break;
        }
    }

    // Afiseaza numarul total de mutari la finalul jocului
    printf("\nNumar mutari joc: %d!\n", *mutari_joc);
    return scor;
}


// Simularea a 100 de jocuri
void candyCrush(int nr_jocuri) {
    int total_scor = 0;
    int total_mutari = 0;
    int mutari_joc;

    for (int i = 0; i < nr_jocuri; i++) {
        int scor = rulareUnJoc(&mutari_joc);
        total_scor += scor;
        total_mutari += mutari_joc;
        printf("Jocul %d: Scor: %d\n", i + 1, scor);
    }
    printf("\nScorul mediu dupa %d de jocuri: %.2f\n", nr_jocuri, total_scor / (double)nr_jocuri);
    printf("Nr mediu mutari dupa %d de jocuri: %.2f\n", nr_jocuri, total_mutari / (double)nr_jocuri);
}

int main() {
    srand(time(NULL)); // Asigura generarea de numere diferite la fiecare rulare
    candyCrush(100);  // Ruleaza 100 de jocuri
    return 0;
}
