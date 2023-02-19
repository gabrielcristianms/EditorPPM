//Header que define os tipos e assinaturas dos métodos relacionados a Imagem de uma forma geral.
#ifndef __IMG_H_
#define __IMG_H_
typedef struct{
	int red;
	int green;
	int blue;
} Pixel; //Estrutura que define um Pixel. Um Pixel é definido por 3 valores que variam de 0 a 255, representando as cores vermelho, verde e azul (RGB)

typedef struct{
	char extensao[10];
	int width;
	int height;
	int precisao;
	Pixel **matriz;
} Imagem; //Estrutura que define uma Imagem. Extensão denota o tipo de PPM (no caso, P3). Já width e height são, respectivamente largura e altura
		  //precisão representa a faixa de valores assumidos pelo Pixel e **matriz é um arranjo de duas dimensões de Pixels.

typedef enum {
	BLUR,
	SHARP,
	BORDA,
	BIN,
	GRAY
} FilterType; //Define FilterType, atribuindo valores inteiros, começando de 0, aos filtros que serão utilizados nas imagens.

void init_img (Imagem *img, int w, int h); //Inicializa um tipo Imagem, atribuindo largura e altura, definindo a matriz de Pixel em zero.
void clear_img(Imagem *img); //Desaloca a memória utilizada ao inicializar uma Imagem.	   
void copy_img(Imagem *img_s, Imagem *img_d); // Copia imagem source (img_s) para imagem destiny(img_d)
void print_img(Imagem *img); //Imprime a matriz de Pixel na saída padrão, com a finalidade de testes.
#endif
#include "img_file.h" //biblioteca com as funções relacionadas a IO de arquivos.
#include "img_edit.h" //biblioteca com as funções relacionadas a edição de Imagens.