#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main () {
    setlocale(LC_ALL, "Portuguese");
    
    //Imprime o cabeçalho do jogo
    printf("\n\n");
    printf("          P  /_\\  P                                \n"); 
    printf("     /_\\_|_|_/_\\                                  \n");    
    printf(" n_n | ||. .|| | n_n         Bem vindo ao           \n");
    printf(" |_|_|nnnn nnnn|_|_|     Jogo de Adivinhação!       \n");
    printf("|" "  |  |_|  |"  " |                               \n");
    printf("|_____| ' _ ' |_____|                               \n");
    printf("      \\__|_|__/                                    \n");
    printf("\n\n");

    //Gerar numeros diferentes
    srand(time(NULL));
    int numerosecreto = rand() % 100;

    int chute;

    double pontos = 1000;

    printf("Escolha a dificuldade do jogo:\n");
    printf("(1) Fácil (2) Médio (3) Difícil\n");

    int nivel, numerodetentativas;

    int i;

    scanf("%d", &nivel);

    switch (nivel) {
        case 1:
            numerodetentativas = 15;
            break;

        case 2:
            numerodetentativas = 10;
            break;
        
        default:
            numerodetentativas = 6;
            break;
    }

    for (i = 1; i <= numerodetentativas; i++) {
        printf("Tentativa %d\n", i);
        printf("Chute um número entre 0 e 100\n");
        scanf("%d", &chute);

        if (chute < 0) {
            printf("Chute inválido!\n");
            continue;
        }

        int acertou = (chute == numerosecreto);
        int maior = (chute > numerosecreto);

        if (acertou) {
            printf("Parabéns, você adivinhou o número secreto e fez %2.lf pontos\n", pontos);

            printf("\n\n");
            printf("             OOOOOOOOOOO               \n");
            printf("         OOOOOOOOOOOOOOOOOOO           \n");
            printf("      OOOOOO  OOOOOOOOO  OOOOOO        \n");
            printf("    OOOOOO      OOOOO      OOOOOO      \n");
            printf("  OOOOOOOO  #   OOOOO  #   OOOOOOOO    \n");
            printf(" OOOOOOOOOO    OOOOOOO    OOOOOOOOOO   \n");
            printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO  \n");
            printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO  \n");
            printf("OOOO  OOOOOOOOOOOOOOOOOOOOOOOOO  OOOO  \n");
            printf(" OOOO  OOOOOOOOOOOOOOOOOOOOOOO  OOOO   \n");
            printf("  OOOO   OOOOOOOOOOOOOOOOOOOO  OOOO    \n");
            printf("    OOOOO   OOOOOOOOOOOOOOO   OOOO     \n");
            printf("      OOOOOO   OOOOOOOOO   OOOOOO      \n");
            printf("         OOOOOO         OOOOOO         \n");
            printf("            OOOOOOOOOOOO               \n");
            printf("\n\n");

            system("pause");

            return 0;
        }

        else if (maior) {
            printf("Você errou!\nO número secreto é menor do que %d\n\n", chute);
        }

        else {
            printf("Você errou!\nO número secreto é maior do que %d\n\n", chute);
        }

        pontos -= abs((chute - numerosecreto)) / 2.0;
    }

    printf("Game Over! Tente novamente");

    printf("\n\n");
    printf("       \\|/ ____ \\|/       \n");
    printf("        @~/ ,. \\~@          \n");
    printf("       /_( \\__/ )_\\       \n");
    printf("          \\__U_/            \n");
    printf("\n\n");

    system("pause");

    return 0;
}
