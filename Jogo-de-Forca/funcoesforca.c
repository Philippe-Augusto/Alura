char palavrasecreta[TAM_PALAVRA];
char chutes[26];
int chutesdados = 0;

int chutapalavra () {
    char palavra[20];
    printf("Chute a palavra que voce acredita ser a palavra secreta\n");
    scanf(" %s", palavra);

    for (int i = 0; i < strlen(palavra); i++) {
        palavra[i] = toupper(palavra[i]);
    }

    return strcmp(palavra, palavrasecreta);
}

void imprimeregras () {
    printf("*********************************\n");
    printf("*********REGRAS DO JOGO**********\n");
    printf("*********************************\n\n");

    printf("------------------------------------------------------------\n\n");

    printf("1 - Este é um jogo de forca, o tema do jogo é frutas\n");
    printf("2 - Digite apenas letras\n");
    printf("3 - Caso voce queira chutar a palavra, digite '1' no teclado quando aparecer a opção para realizar um chute e digite a palavra que voce acredita ser a palavra secreta\n");
    printf("4 - Voce possui cinco erros, caso ultrapasse cinco erros você será enforcado, ou se errar a palavra você também será enforcado\n\n\n");

    printf("------------------------------------------------------------\n\n");

}   
void abertura () {
    printf("*********************************\n");
    printf("***       Jogo de Forca       ***\n");
    printf("*********************************\n\n\n");
}

int validaletra (char* letra) {
    if (isalpha(*letra)) {
        *letra = toupper(*letra);

        return 2;
    }

    else if (*letra == '1') {
        return 1;
    }
    
    else {return 0;}
}

void chutou() {
    char chute;

    printf("Chute uma letra\n");
    scanf(" %c", &chute);

    validaletra(&chute);

    chutes[chutesdados] = chute;    
}

int jachutou (char letra) {
    int achou = 0;

    for (int j = 0; j < chutesdados; j++) {
        if (chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

int chuteserrados() {
    int erros = 0;

    for (int i = 0; i < chutesdados; i++) {
        int existe = 0; 

        for (int j = 0; j < strlen(palavrasecreta); j++) {
            if (chutes[i] == palavrasecreta[j]) {

                existe = 1;
                break;
            }
        }

        if (!existe) erros++;
    }

    return erros;
}

void desenhaforca () {  

    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
        (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
        (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), 
        (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for (int i = 0; i < strlen(palavrasecreta); i++) {
            
            int achou = jachutou(palavrasecreta[i]);

            if (achou) {
                printf("%c ", palavrasecreta[i]);
            } else {
                printf("_ ");
            }
            
        }
        printf("\n");
}

void escolhepalavra () {
    FILE* f;

    f = fopen("palavras.txt", "r");

    if (f == NULL) {
        printf("Desculpe, banco de dados não disponível\n\n");
        exit(1);
    }

    int numpalavras = 0;
    char buffer[20];

    while (!feof(f)) {
        fgets(buffer, 21, f);
        numpalavras++;
    }

    fseek(f, 0, SEEK_SET);

    srand(time(NULL));
    
    int randomico = rand() % numpalavras;

    for (int i = 0; i <= randomico; i++) {
        
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
    
}

void adicionapalavra () {
    char quer;

    printf("Voce deseja adicionar uma nova palavra ao jogo? (S/N)\n"); 
    scanf(" %c", &quer);

    validaletra(&quer);

    if (quer == 'S') {
        char novapalavra[TAM_PALAVRA];
        printf("Qual a nova palavra?\n");
        scanf(" %s", novapalavra);

        for (int i = 0; i < strlen(novapalavra); i++) {
            novapalavra[i] = toupper(novapalavra[i]);
        }

        FILE *f;

        f = fopen("palavras.txt", "r+");

        if (f == NULL) {
            printf("Desculpe, banco de dados não disponível\n\n");
            exit(1);
        }

        int quantidade;
        fscanf(f, "%d", &quantidade);
        quantidade++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", quantidade);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

int ganhou () {
    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if (!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}



int enforcou () {
    return chuteserrados() >= 5;
}
