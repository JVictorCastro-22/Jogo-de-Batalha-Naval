#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Cores ANSI para terminal
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AZUL "\033[34m"
#define RESET "\033[0m"

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // Inicializa com água (0)
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)
                printf(AZUL "~ " RESET);  // Água
            else if (tabuleiro[i][j] == 3)
                printf(VERMELHO "N " RESET);  // Navio
            else if (tabuleiro[i][j] == 5)
                printf(VERDE "* " RESET);  // Área afetada
        }
        printf("\n");
    }
}

// Posiciona navios de forma interativa
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogador) {
    int linha, coluna;
    printf("\nJogador %d, digite a linha e coluna para seu navio: ", jogador);
    scanf("%d %d", &linha, &coluna);

    if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO && tabuleiro[linha][coluna] == 0) {
        tabuleiro[linha][coluna] = 3; // Marca o navio
    } else {
        printf("Posição inválida! Tente novamente.\n");
        posicionarNavio(tabuleiro, jogador);
    }
}

// Ataque ao navio do adversário
void atacar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int jogador) {
    int linha, coluna;
    printf("\nJogador %d, digite a linha e coluna para atacar: ", jogador);
    scanf("%d %d", &linha, &coluna);

    if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
        if (tabuleiro[linha][coluna] == 3) {
            tabuleiro[linha][coluna] = 5;
            printf(VERDE "Acertou um navio!\n" RESET);
        } else {
            printf("Nada foi atingido.\n");
        }
    } else {
        printf("Ataque inválido, tente novamente.\n");
        atacar(tabuleiro, jogador);
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    printf("Bem-vindo ao Batalha Naval Multiplayer!\n");

    // Jogadores posicionam seus navios
    posicionarNavio(tabuleiro, 1);
    posicionarNavio(tabuleiro, 2);

    exibirTabuleiro(tabuleiro);

    // Alternando turnos para ataques
    for (int turno = 0; turno < 5; turno++) {  // Limita a 5 rodadas de ataque
        atacar(tabuleiro, (turno % 2 == 0) ? 1 : 2);
        exibirTabuleiro(tabuleiro);
    }

    printf("Fim do jogo! Obrigado por jogar.\n");
    return 0;
}
