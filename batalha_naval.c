#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // Inicializa com água (0)
        }
    }
}

// Função para verificar se a posição do navio é válida
int verificarPosicaoNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int horizontal, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (diagonal ? i * diagonal : (horizontal ? 0 : i));
        int c = coluna + (diagonal ? i * diagonal : (horizontal ? i : 0));

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO || tabuleiro[l][c] != 0) {
            return 0; // Posição inválida
        }
    }
    return 1; // Posição válida
}

// Função para posicionar os navios no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int horizontal, int diagonal) {
    if (verificarPosicaoNavio(tabuleiro, linha, coluna, horizontal, diagonal)) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            int l = linha + (diagonal ? i * diagonal : (horizontal ? 0 : i));
            int c = coluna + (diagonal ? i * diagonal : (horizontal ? i : 0));

            tabuleiro[l][c] = 3; // Marca a posição do navio
        }
    } else {
        printf("Posição inválida! Tente novamente.\n");
    }
}

// Função para aplicar habilidades no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char tipo) {
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            int l = linha + i;
            int c = coluna + j;

            // Verifica se está dentro dos limites
            if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
                if (tipo == 'C' && (i == 0 || j == 0)) // Cruz
                    tabuleiro[l][c] = (tabuleiro[l][c] == 0) ? 5 : tabuleiro[l][c];
                else if (tipo == 'O' && (abs(i) + abs(j) <= 2)) // Octaedro (losango)
                    tabuleiro[l][c] = (tabuleiro[l][c] == 0) ? 5 : tabuleiro[l][c];
                else if (tipo == 'N' && i >= 0 && abs(j) <= i) // Cone
                    tabuleiro[l][c] = (tabuleiro[l][c] == 0) ? 5 : tabuleiro[l][c];
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    int linha, coluna, horizontal, diagonal;
    char tipo;

    // Interação para posicionar navios
    for (int i = 0; i < 3; i++) {
        printf("\nDigite linha, coluna, horizontal (1 ou 0) e diagonal (1, -1 ou 0) para o navio %d: ", i + 1);
        scanf("%d %d %d %d", &linha, &coluna, &horizontal, &diagonal);
        posicionarNavio(tabuleiro, linha, coluna, horizontal, diagonal);
    }

    exibirTabuleiro(tabuleiro);

    // Interação para aplicar habilidades
    printf("\nDigite linha, coluna e tipo de habilidade (C: Cruz, O: Octaedro, N: Cone): ");
    scanf("%d %d %c", &linha, &coluna, &tipo);
    aplicarHabilidade(tabuleiro, linha, coluna, tipo);

    exibirTabuleiro(tabuleiro);

    return 0;
}
