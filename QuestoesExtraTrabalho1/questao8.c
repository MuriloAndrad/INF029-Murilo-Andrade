#include <stdio.h>

char tab[3][3];

void iniciar() {
    int i, j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            tab[i][j] = ' ';
        }
    }
}

void mostrar() {
    int i, j;
    printf("\n  1 2 3\n");
    for(i = 0; i < 3; i++) {
        printf("%c ", 'A' + i);
        for(j = 0; j < 3; j++) {
            printf("%c", tab[i][j]);
            if(j < 2) printf("|");
        }
        printf("\n");
        if(i < 2) printf("  -+-+-\n");
    }
    printf("\n");
}

int ganhou(char p) {
    int i;
    for(i = 0; i < 3; i++) {
        if(tab[i][0] == p && tab[i][1] == p && tab[i][2] == p) return 1;
        if(tab[0][i] == p && tab[1][i] == p && tab[2][i] == p) return 1;
    }
    if(tab[0][0] == p && tab[1][1] == p && tab[2][2] == p) return 1;
    if(tab[0][2] == p && tab[1][1] == p && tab[2][0] == p) return 1;
    return 0;
}

int main() {
    int jogadas = 0, turno = 1;
    char entrada[5], marca;
    int l, c;

    iniciar();

    while(jogadas < 9) {
        mostrar();
        printf("Jogador %d, informe sua jogada: ", turno);
        scanf("%s", entrada);

        l = entrada[0] - 'A';
        if(l < 0 || l > 2) l = entrada[0] - 'a';
        c = entrada[1] - '1';

        if(l >= 0 && l <= 2 && c >= 0 && c <= 2 && tab[l][c] == ' ') {
            marca = (turno == 1) ? 'X' : '0';
            tab[l][c] = marca;
            
            if(ganhou(marca)) {
                mostrar();
                printf("O Jogador %d venceu!\n", turno);
                return 0;
            }
            
            turno = (turno == 1) ? 2 : 1;
            jogadas++;
        } else {
            printf("Jogada invalida. Tente novamente.\n");
        }
    }
    mostrar();
    printf("Empate!\n");
    return 0;
}
