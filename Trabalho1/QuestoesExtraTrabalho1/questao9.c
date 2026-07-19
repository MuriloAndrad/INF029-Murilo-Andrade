#include <stdio.h>

int NUM_NAVIOS = 5;
int tam_navios[] = {4, 3, 1, 1, 1};

char tab[2][10][10];
char visao[2][10][10];

void iniciar() {
    int p, i, j;
    for(p = 0; p < 2; p++) {
        for(i = 0; i < 10; i++) {
            for(j = 0; j < 10; j++) {
                tab[p][i][j] = ' ';
                visao[p][i][j] = ' ';
            }
        }
    }
}

void mostrar_proprio(int p) {
    int i, j;
    printf("\nSeu Tabuleiro (Jogador %d):\n", p + 1);
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for(i = 0; i < 10; i++) {
        printf("%c ", 'A' + i);
        for(j = 0; j < 10; j++) {
            printf("[%c]", tab[p][i][j]);
        }
        printf("\n");
    }
}

void mostrar_adv(int p) {
    int i, j;
    int adv = (p == 0) ? 1 : 0;
    printf("\nTabuleiro do Adversario:\n");
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for(i = 0; i < 10; i++) {
        printf("%c ", 'A' + i);
        for(j = 0; j < 10; j++) {
            printf("[%c]", visao[adv][i][j]);
        }
        printf("\n");
    }
}

int validar_pos(int p, int l, int c, int tam, char ori) {
    int i;
    if(ori == 'H' || ori == 'h') {
        if(c + tam > 10) return 0;
        for(i = 0; i < tam; i++) {
            if(tab[p][l][c + i] != ' ') return 0;
        }
    } else {
        if(l + tam > 10) return 0;
        for(i = 0; i < tam; i++) {
            if(tab[p][l + i][c] != ' ') return 0;
        }
    }
    return 1;
}

void posicionar(int p) {
    int n, l, c;
    char ori, linha;
    printf("\n=== JOGADOR %d, POSICIONE SUA FROTA ===\n", p + 1);
    for(n = 0; n < NUM_NAVIOS; n++) {
        mostrar_proprio(p);
        printf("\nNavio tamanho %d.\nInforme Linha (A-J), Coluna (0-9) e Orientacao (H/V) separados por espaco (ex: A 0 H): ", tam_navios[n]);
        scanf(" %c %d %c", &linha, &c, &ori);
        
        l = linha - 'A';
        if(l < 0 || l > 9) l = linha - 'a';

        if(l >= 0 && l < 10 && c >= 0 && c < 10 && validar_pos(p, l, c, tam_navios[n], ori)) {
            int i;
            for(i = 0; i < tam_navios[n]; i++) {
                if(ori == 'H' || ori == 'h') {
                    tab[p][l][c + i] = 'N';
                } else {
                    tab[p][l + i][c] = 'N';
                }
            }
        } else {
            printf("Posicao invalida! Verifique o tamanho e se ja existe navio no local.\n");
            n--;
        }
    }
}

int venceu(int p) {
    int adv = (p == 0) ? 1 : 0;
    int i, j;
    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            if(tab[adv][i][j] == 'N') return 0;
        }
    }
    return 1;
}

int main() {
    int turno = 0, l, c;
    char linha;

    iniciar();
    posicionar(0);
    
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    
    posicionar(1);
    
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    while(1) {
        printf("\n=============================\n");
        printf("   TURNO DO JOGADOR %d\n", turno + 1);
        printf("=============================\n");
        mostrar_proprio(turno);
        mostrar_adv(turno);

        int adv = (turno == 0) ? 1 : 0;
        printf("\nInforme a coordenada do alvo - Linha (A-J) e Coluna (0-9) ex: A 5: ");
        scanf(" %c %d", &linha, &c);
        
        l = linha - 'A';
        if(l < 0 || l > 9) l = linha - 'a';

        if(l >= 0 && l < 10 && c >= 0 && c < 10) {
            if(visao[adv][l][c] != ' ') {
                printf("\nVoce ja atirou nessa coordenada. Perdeu a vez!\n");
            } else {
                if(tab[adv][l][c] == 'N') {
                    printf("\n>>> FOGO! TIRO CERTEIRO! <<<\n");
                    tab[adv][l][c] = '0';
                    visao[adv][l][c] = '0';
                } else {
                    printf("\n>>> AGUA! <<<\n");
                    tab[adv][l][c] = 'X';
                    visao[adv][l][c] = 'X';
                }
            }

            if(venceu(turno)) {
                printf("\n###############################\n");
                printf("    JOGADOR %d VENCEU A GUERRA!\n", turno + 1);
                printf("###############################\n");
                mostrar_proprio(adv); 
                break;
            }
            turno = adv;
        } else {
            printf("\nCoordenada invalida. Perdeu a vez!\n");
            turno = adv;
        }
    }
    return 0;
}
