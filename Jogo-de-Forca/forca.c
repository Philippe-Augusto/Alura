#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "forca.h"

int main () {
    setlocale(LC_ALL, "Portuguese");

    escolhepalavra();
    abertura();
    imprimeregras();

    int result = 2;
    int venceu = 0;
    int perdeu = 0;

    do {
        switch (result)
        {
        case 0:
            printf("Caractere invalido! Digite uma letra\n"); 
            result = 2;
            if (chutesdados > 0) {chutesdados--;}
            break; 
        case 1:
            if (chutapalavra() == 0) {
                venceu = 1;
            }
            else {
                perdeu = 1;
            }
            break;
        case 2:
            desenhaforca();
            chutou();

            result = validaletra(&chutes[chutesdados]);
            chutesdados++;

            venceu = ganhou();
            perdeu = enforcou();
            break;
        }
    } while (!venceu && !perdeu);

    if(ganhou() || venceu) {
        printf("\nParab�ns, voc� ganhou!\n\n");

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

    } else {
        printf("\nPuxa, voc� foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

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

    adicionapalavra();
}
