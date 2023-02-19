#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "img.h"

//Realiza a abertura de um arquivo e checando se ele está no formato .PPM e salva os contéudos desse arquivo em uma variável do tipo Imagem.
//Tem como parâmetro um *Imagem img que vai receber as informações do arquivo a ser aberto. É uma função do tipo void. 
void open_img(Imagem *img){
	int i, j;
	char nome_arq[25];

	printf("Digite o nome do arquivo:\n");
	gets(nome_arq);

	FILE *arquivo = fopen(nome_arq, "r");
	if(arquivo == NULL){
		printf("Erro na abertura do arquivo.\n");
		exit(1);
	}
	else{
		fscanf(arquivo, "%s", img->extensao);
		if(strcmp(img->extensao, "P3") == 0){
			fscanf(arquivo, "%i %i\n%i\n", &img->width, &img->height, &img->precisao);
			init_img(img, img->width, img->height);
			for(i = 0; i < img->height; i++){
				for(j = 0; j < img->width; j++){
					fscanf(arquivo, "%i %i %i", &img->matriz[i][j].red, &img->matriz[i][j].green, &img->matriz[i][j].blue);
				}
			}
			printf("O arquivo foi lido com sucesso!\n\n");
		}
		else{
			printf("A imagem nao esta no formato PPM.\n");
			strcpy(img->extensao, "\0");	
			exit(1);
		}
	}
	fclose(arquivo);
}
//Salva as informações de uma variável do tipo Imagem em um arquivo. Tem como parâmetro um *Imagem img que contêm as informações que serão salvas no arquivo
//É uma função do tipo void.
void save_img(Imagem *img){
	int i, j;
	char nome_arq[25];

	printf("Escreva o nome do arquivo a ser salvo.\n");
	gets(nome_arq);

	FILE *arquivo = fopen(nome_arq, "w");
	if(arquivo == NULL){
		printf("Erro ao salvar o arquivo\n");
		exit(1);
	}
	else{
		fprintf(arquivo, "P3\n%i %i\n255\n", img->width, img->height, img->precisao);
		for (i = 0; i < img->height; ++i){
			for (j = 0; j < img->width; ++j){
				fprintf(arquivo, "%i %i %i ", img->matriz[i][j].red, img->matriz[i][j].green, img->matriz[i][j].blue);
			}
			fprintf(arquivo, "\n");
		}
	}
	fclose(arquivo);
	printf("O arquivo foi salvo com sucesso!\n\n");
}