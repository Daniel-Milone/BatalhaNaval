#include <stdio.h>
#define TAM_TABULEIRO 10
#define TAM_NAVIO     3
#define TAM_HABILIDADE 5   // tamanho ímpar para facilitar centralização

// Tipos de célula no tabuleiro
#define AGUA    0
#define NAVIO   3
#define ATAQUE  5

// -----------------------------------------------------------------------------
// Funções auxiliares
// -----------------------------------------------------------------------------

// Inicializa o tabuleiro inteiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Verifica se uma posição está dentro dos limites do tabuleiro
int posicaoValida(int linha, int coluna) {
    return linha >= 0 && linha < TAM_TABULEIRO &&
           coluna >= 0 && coluna < TAM_TABULEIRO;
}

// Tenta posicionar um navio reto (horizontal ou vertical)
// Retorna 1 se conseguiu, 0 se não (limite ou sobreposição)
int posicionarNavioReto(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                        int linhaInicio, int colunaInicio,
                        int orientacao, int tamanho) {  // 0 = horizontal, 1 = vertical

    int di = (orientacao == 1) ? 1 : 0;
    int dj = (orientacao == 0) ? 1 : 0;

    // Verifica se todo o navio cabe e não sobrepõe
    for (int k = 0; k < tamanho; k++) {
        int li = linhaInicio + k * di;
        int ci = colunaInicio + k * dj;
        if (!posicaoValida(li, ci) || tabuleiro[li][ci] != AGUA) {
            return 0;
        }
    }

    // Posiciona
    for (int k = 0; k < tamanho; k++) {
        int li = linhaInicio + k * di;
        int ci = colunaInicio + k * dj;
        tabuleiro[li][ci] = NAVIO;
    }
    return 1;
}

// Posiciona navio na diagonal principal (crescente) ou anti-diagonal
// dir = 1 → diagonal principal (↓→), dir = -1 → anti-diagonal (↓←)
int posicionarNavioDiagonal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                            int linhaInicio, int colunaInicio,
                            int dir, int tamanho) {

    int deltaCol = (dir == 1) ? 1 : -1;

    // Verifica limites e sobreposição
    for (int k = 0; k < tamanho; k++) {
        int li = linhaInicio + k;
        int ci = colunaInicio + k * deltaCol;
        if (!posicaoValida(li, ci) || tabuleiro[li][ci] != AGUA) {
            return 0;
        }
    }

    // Posiciona
    for (int k = 0; k < tamanho; k++) {
        int li = linhaInicio + k;
        int ci = colunaInicio + k * deltaCol;
        tabuleiro[li][ci] = NAVIO;
    }
    return 1;
}

// Exibe o tabuleiro com formatação clara
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], const char* titulo) {
    printf("\n%s\n", titulo);
    printf("   ");
    for (int j = 0; j < TAM_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == AGUA)   printf(" . ");
            else if (tabuleiro[i][j] == NAVIO) printf(" N ");
            else if (tabuleiro[i][j] == ATAQUE) printf(" X ");
            else printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// -----------------------------------------------------------------------------
// Habilidades especiais – construídas dinamicamente com loops e condicionais
// -----------------------------------------------------------------------------

// Cria área de efeito em formato de CONE (apontando para baixo)
// centro é a ponta superior do cone
void aplicarHabilidadeCone(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                           int centroLinha, int centroColuna) {

    // Largura máxima na base = 5 (tamanho ímpar)
    int raioMax = TAM_HABILIDADE / 2;  // 2

    for (int dy = 0; dy <= raioMax * 2; dy++) {           // altura do cone
        int larguraAtual = dy + 1;                         // aumenta 1 por linha
        int offsetEsquerda = (larguraAtual - 1) / 2;       // centraliza

        for (int dx = -offsetEsquerda; dx <= offsetEsquerda; dx++) {
            int linha = centroLinha + dy;
            int coluna = centroColuna + dx;

            if (posicaoValida(linha, coluna)) {
                if (tabuleiro[linha][coluna] != NAVIO) {   // não sobrescreve navio
                    tabuleiro[linha][coluna] = ATAQUE;
                }
            }
        }
    }
}

// Cria área em formato de CRUZ (horizontal + vertical)
void aplicarHabilidadeCruz(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                           int centroLinha, int centroColuna) {

    int raio = TAM_HABILIDADE / 2;  // 2

    // Linha horizontal
    for (int dc = -raio; dc <= raio; dc++) {
        int c = centroColuna + dc;
        if (posicaoValida(centroLinha, c) && tabuleiro[centroLinha][c] != NAVIO) {
            tabuleiro[centroLinha][c] = ATAQUE;
        }
    }

    // Linha vertical (sem repetir o centro)
    for (int dl = -raio; dl <= raio; dl++) {
        if (dl == 0) continue;
        int l = centroLinha + dl;
        if (posicaoValida(l, centroColuna) && tabuleiro[l][centroColuna] != NAVIO) {
            tabuleiro[l][centroColuna] = ATAQUE;
        }
    }
}

// Cria área em formato de losango (vista frontal de octaedro / diamante)
void aplicarHabilidadeOctaedro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                               int centroLinha, int centroColuna) {

    int raio = TAM_HABILIDADE / 2;  // 2

    for (int dy = -raio; dy <= raio; dy++) {
        int largura = raio - abs(dy) + 1;
        int offset = largura - 1;

        for (int dx = -offset; dx <= offset; dx++) {
            int linha = centroLinha + dy;
            int coluna = centroColuna + dx;

            if (posicaoValida(linha, coluna) && tabuleiro[linha][coluna] != NAVIO) {
                tabuleiro[linha][coluna] = ATAQUE;
            }
        }
    }
}

// -----------------------------------------------------------------------------
// Programa principal
// -----------------------------------------------------------------------------
int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    inicializarTabuleiro(tabuleiro);

    // Nível Novato + Aventureiro: posicionamento de 4 navios

    // Navio 1 – horizontal
    posicionarNavioReto(tabuleiro, 2, 3, 0, TAM_NAVIO);   // linha 2, col 3 → direita

    // Navio 2 – vertical
    posicionarNavioReto(tabuleiro, 5, 7, 1, TAM_NAVIO);   // linha 5, col 7 → baixo

    // Navio 3 – diagonal principal (↓→)
    posicionarNavioDiagonal(tabuleiro, 1, 1, 1, TAM_NAVIO);

    // Navio 4 – anti-diagonal (↓←)
    posicionarNavioDiagonal(tabuleiro, 6, 8, -1, TAM_NAVIO);

    // Exibe tabuleiro só com navios (como no nível aventureiro)
    exibirTabuleiro(tabuleiro, "Tabuleiro com os 4 navios posicionados");

    // Nível Mestre: aplicar as 3 habilidades em posições diferentes

    // Habilidade 1: Cone na posição (4,4)
    aplicarHabilidadeCone(tabuleiro, 4, 4);

    // Habilidade 2: Cruz na posição (1,6)
    aplicarHabilidadeCruz(tabuleiro, 1, 6);

    // Habilidade 3: Octaedro / losango na posição (8,2)
    aplicarHabilidadeOctaedro(tabuleiro, 8, 2);

    // Exibe o tabuleiro final com navios + áreas de efeito
    exibirTabuleiro(tabuleiro, "Tabuleiro FINAL com navios e áreas de efeito das habilidades");

    return 0;
}