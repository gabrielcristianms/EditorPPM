#include <stdio.h>
#include <stdlib.h>
#include "img.h"

//Inicializa todos os elementos da matriz de pixels de uma imagem em 0 com base
//na largura e na altura. Ela tem como parâmetros uma váriavel do tipo *Imagem img que é a imagem a ser inicializada,
//uma do tipo int w que representa a largura da imagem e outro int h que é a altura. É uma função do tipo void
void init_img(Imagem *img, int w, int h){
	int i, j;
	img->width = w;
	img->height = h;

	img->matriz = malloc(h * sizeof(Pixel*));

	for(i = 0; i < h; i++){
        img->matriz[i] = malloc(w * sizeof(Pixel));
        if(img->matriz[i] == NULL)
        	printf("Houve um erro ao alocar memoria!\n");
    }
    if(img->matriz == NULL){
    	printf("Houve um erro ao alocar memoria!\n");
    }
    else{
		for(i = 0; i < h; i++){
			for(j = 0; j < w; j++){
				img->matriz[i][j].red   = 0;
				img->matriz[i][j].green = 0;
				img->matriz[i][j].blue  = 0;
			}
		}
	}
}
//Desaloca a memória que foi dinâmicamente alocada da matriz de pixels. Tem como parâmetro um *Imagem img que é a imagem cuja matriz de pixels
//será desalocada. É uma função do tipo void.
void clear_img(Imagem *img){
	int i, j;
	for(i = 0; i < img->height; i++)
        free((void *)img->matriz[i]);
    free((void *)img->matriz);
}
//Copia uma imagem source para uma imagem destino. Tem como parâmetros um *Imagem img_s que é a imagem source e um *Imagem img_d que é a imagem destiny
//É uma função do tipo void.
void copy_img(Imagem *img_s, Imagem *img_d){
	int i, j;

	init_img(img_d, img_s->width, img_s->height);

	for(i = 0; i < img_s->height; i++){
		for(j = 0; j < img_s->width; j++){
			img_d->matriz[i][j] = img_s->matriz[i][j];
		}
	}
}
//Função de diagnóstico durante fase inicial do projeto, imprime na saída padrão os valores da matriz de pixel de uma imagem
//Tem como parâmetro um *Imagem img da imagem cuja matriz de pixels será impresso. É uma função do tipo void.
void print_img(Imagem *img){
	int i, j;

	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){
			printf("%i %i %i   ", img->matriz[i][j].red, img->matriz[i][j].green, img->matriz[i][j].blue);
		}
		printf("\n");
	}
}