#include <stdio.h>

#define Tam_Tabuleiro 10
#define Tam_Navio 3
#define Agua 0
#define Navio 3

// Inicializa todas as posições do tabuleiro com 0 (água)
void inicializarTabuleiro(int tab[Tam_Tabuleiro][Tam_Tabuleiro]) {
    for(int i = 0; i < Tam_Tabuleiro; i++){
        for (int j = 0; j < Tam_Tabuleiro; j++)
        {
            tab [i][j] = Agua;
        }     
    }
}

// Exibe o tabuleiro no console (0 = água, 3 = navio)
// Agora as colunas são rotuladas com letras A, B, C, ..., J.
void exibirTabuleiro(const int tab[Tam_Tabuleiro][Tam_Tabuleiro]) {

    // Cabeçalho de colunas com letras
    printf("    ");
    for(int c = 0; c < Tam_Tabuleiro; c++){
        printf("%c ", 'A' + c);
    }
    printf("\n");

    // Linha separadora
    printf("   ");
    for(int c = 0; c < Tam_Tabuleiro; c++){
        printf("--");
    }
    printf("-\n");

    // Linhas do tabuleiro com índice da linha (0 a 9)
    for (int r = 0; r < Tam_Tabuleiro; r++){
        printf("%2d| ", r);
        for (int c = 0; c < Tam_Tabuleiro; c++){
            printf("%d ", tab[r][c]);
        }
        printf("\n");
        
    
    }
    


}


/*
    Verifica se um navio pode ser posicionado:
    - dentro dos limites do tabuleiro
    - sem sobrepor outro navio
    Retorna 1 (pode) ou 0 (não pode).
*/
int podePosicionarNavio(const int tab[Tam_Tabuleiro][Tam_Tabuleiro],
                    int linha, int coluna, int tamanho, char orientacao ){
    
    if (linha < 0 || coluna < 0) return 0;

    if (orientacao == 'H') {

        if (coluna + tamanho > Tam_Tabuleiro) return 0;

        for (int k = 0; k < tamanho; k++){
            if (tab[linha][coluna + k] != Agua) return 0;
        } 

    }else if (orientacao == 'V') {

        if (linha + tamanho > Tam_Tabuleiro) return 0;

        for (int k = 0; k < tamanho; k++) {
            if (tab[linha + k][coluna] != Agua) return 0;
        }
            
        } else {

            return 0;
        }
    }


 /*
    Posiciona o navio no tabuleiro copiando o valor do vetor do navio (3)
    em cada célula correspondente na matriz.
    Retorna 1 (sucesso) ou 0 (falha).
*/
int posicionarNavio(int tab[Tam_Tabuleiro][Tam_Tabuleiro],
                    const int navio[Tam_Navio],
                    int linha, int coluna, char orientacao) {
    
    if (!podePosicionarNavio(tab, linha, coluna, Tam_Navio, orientacao)) {
        return 0;
    }

    for (int k = 0; k < Tam_Navio; k++) {
        int r = linha  + (orientacao == 'V' ? k : 0);
        int c = coluna + (orientacao == 'H' ? k : 0);
        tab[r][c] = navio[k];
    }

    return 1;
  }
int main() {
    // Matriz do tabuleiro 10x10
    int tabuleiro[Tam_Tabuleiro][Tam_Tabuleiro];

    // Dois navios (vetores 1D) de tamanho 3, preenchidos com "3"
    int navioHorizontal[Tam_Navio] = {Navio, Navio, Navio};
    int navioVertical[Tam_Navio] = {Navio, Navio, Navio};

    // Inicializa o tabuleiro com agua
    inicializarTabuleiro(tabuleiro);

    /*
        Coordenadas iniciais (0-based) definidas no código:
        - navio horizontal começará em (linha=2, coluna=1) -> ocupa (2,B), (2,C), (2,D)
        - navio vertical   começará em (linha=5, coluna=7) -> ocupa (5,H), (6,H), (7,H)
        Observação: Internamente continua 0-based. As letras são só para exibição.
    */

    int linhaH = 2, colunaH = 1;
    int linhaV= 5, colunaV = 7;

    // Posiciona o navio horizontal
    if (!posicionarNavio(tabuleiro, navioHorizontal, linhaH, colunaH, 'H')) {
        printf("Erro: não foi possível posicionar o navio horizontal.\n");
        return 1;
    }

    // Posiciona o navio vertical (sem sobreposição)
    if (!posicionarNavio(tabuleiro, navioVertical, linhaV, colunaV, 'V')) {
        printf("Erro: não foi possível posicionar o navio vertical.\n");
        return 1;
    }

    // Exibe o tabuleiro final
    printf ("Tabuleiro 10x10 (0 = água, 3 = navio):\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
