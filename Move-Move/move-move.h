#ifndef _PACMAN_H
#define _PACMAN_H

#define ESQUERDA 'a'
#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'

int perdeu ();
int ganhou ();
void move(char comando);
int ehdirecao(char direcao);
void fantasmas();
int direcaofantasma(int xatual, int yatual, int *xdestino, int *ydestino);
void explodepilula();
void explodepilula2(int x, int y, int somax, int somay, int qtd);
int inserepilula ();
void imprimeregras();

#endif
