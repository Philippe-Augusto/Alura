#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include "pacman.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;

int main () {
    setlocale(LC_ALL, "Portuguese");

    leitura(&m);

    imprimeregras();

    int inicio;
    scanf("%d", &inicio);

    if (inicio == 1) {
         encontramapa(&m, &heroi, HEROI);

    int qtdmovimentos = 0;

    do {
        printf("Tem pilula: %s\n", (tempilula ? "SIM" : "NAO"));
        imprimemapa(&m);

        char comando;
        scanf(" %c", &comando); 
        comando = tolower(comando);

        if (!tempilula) qtdmovimentos++;

        move(comando); //primeiro move o heroi 
        if(comando == BOMBA) explodepilula();

        fantasmas();

        if ((qtdmovimentos % 5) == 0 && !tempilula) inserepilula();

    } while (!perdeu() && !ganhou());

    imprimemapa(&m);

    if (perdeu()) {
        printf("\nGAME OVER! Voce perdeu!\n");
        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
    
    if (ganhou()) {
        printf("\nParabéns, você destruiu todos os fantasmas!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    }
    
    liberamapa(&m);

    return 0;
    }

    else {
        printf("Caractere invalido!\n");
        return 0;
    }
}

void imprimeregras() {
    printf("******************************************************************************\n");
    printf("*******************************REGRAS DO JOGO*********************************\n");
    printf("******************************************************************************\n");

    printf("1 - Utilize as teclas 'A' 'S' 'D' 'W' para locomover o seu heroi\n");
    printf("2 - Quando começar o jogo, terá uma pilula no mapa,"); 
    printf("caso voce pegue a pilula voce ganha uma habilidade de explosao,");
    printf("para utilizar essa habilidade utilize a tecla 'B'\n");

    printf("3 - Voce recebera uma mensagem avisando se voce possui a pilula");
    printf("ao utilizar a habilidade voce perde a pilula e apos cinco movimentos é adicionada outra pilula ao mapa\n");
    printf("4 - Se o fantasma enconstar em voce, GAME OVER!\n");
    printf("5 - Caso voce destrua os dois fantasmas, voce ganha o jogo\n");
    printf("6 - Digite '1' para começar o jogo\n");
}

void move (char direcao) {

    if (!ehdirecao(direcao)) return; //validar a entrada do usuario

    int proximox = heroi.x;
    int proximoy = heroi.y;

    switch (direcao) {
        case ESQUERDA:  
            proximoy--;
            break;

        case CIMA:
            proximox--;
            break;

        case BAIXO:
            proximox++;
            break;

        case DIREITA:
            proximoy++;
            break;
    }

    if(!podeandar(&m, FANTASMA, proximox, proximoy)) 
        return;

    if(ehpersonagem(&m, PILULA, proximox, proximoy)) {
        tempilula = 1;
    }

    andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);

    heroi.x = proximox; //atualiza a posicao do heroi
    heroi.y = proximoy;
}

int inserepilula () {
    POSICAO pos;
    if (!encontramapa(&m, &pos, PILULA)) {
        
        srand(time(0));

        for (int i = rand() % m.linhas; i < m.linhas; i++) {
            for (int j = rand() %m.colunas; j < m.colunas; j++) {
                if(!ehparede(&m, i, j) && ehvalida(&m, i, j) && !ehpersonagem(&m, HEROI, i, j) && !ehpersonagem(&m, FANTASMA, i, j)) {
                    m.matriz[i][j] = PILULA;
                    return 1;
                }
            }
        }
    }

    return 0;
}

void explodepilula () {

    if (!tempilula) return;

    explodepilula2(heroi.x, heroi.y, 0, 1, 3);
    explodepilula2(heroi.x, heroi.y, 1, 0, 3);
    explodepilula2(heroi.x, heroi.y, 0, -1, 3);
    explodepilula2(heroi.x, heroi.y, -1, 0, 3);

    tempilula = 0;
}

void explodepilula2(int x, int y, int somax, int somay, int qtd) {

    if (qtd == 0) return;

    int novox = x + somax;
    int novoy = y + somay;  

    if (!ehvalida(&m, novox, novoy)) return;
    if (ehparede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] = VAZIO;
    explodepilula2(novox, novoy, somax, somay, qtd - 1);

}

int ehdirecao (char direcao) {
    return direcao == ESQUERDA || direcao == BAIXO || direcao == CIMA || direcao == DIREITA;
}

int direcaofantasma(int xatual, int yatual, int *xdestino, int *ydestino) {
    int opcoes[4][2] = {
        { xatual, yatual +1}, //direita
        { xatual +1, yatual}, //baixo
        { xatual, yatual -1}, //esquerda
        { xatual -1, yatual}  //cima
    };

    srand(time(0));

    for (int i = 0; i < 10; i++) {
        int posicao = rand () % 4; // numero <= 4

        if (podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1]) 
        && !ehpersonagem(&m, PILULA, opcoes[posicao][0], opcoes[posicao][1])) {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];

            return 1;
        }
    }

    return 0;
}

void fantasmas() {
    MAPA copia; //mapa exclusivo para econtrar o fantasma, o fantasma so se move no mapa original

    copiamapa(&copia, &m);

    for (int i = 0; i < copia.linhas; i++) {
        for (int j = 0; j < copia.colunas; j++) {
            
            if (copia.matriz[i][j] == FANTASMA) {
                
                int xdestino;
                int ydestino;

                int encontrou = direcaofantasma(i, j, &xdestino, &ydestino);

                if (encontrou) {
                    andanomapa(&m, i, j, xdestino, ydestino);
                }
            }

        }
    }

    liberamapa(&copia);
}

int perdeu () {
    POSICAO pos;

    int perdeu = !encontramapa(&m, &pos, HEROI);

    return perdeu;
}

int ganhou () {
    POSICAO pos;

    int ganhou = !encontramapa(&m, &pos, FANTASMA);

    return ganhou;
}
