#include "img.h"
#include <math.h>

//Função que amplia uma imagem em duas vezes. Tem como parâmetros um *Imagem img que é a imagem antes da modificação e um *Imagem img_alt que recebera
//as modificações feitas. É do tipo void.
void img_amp(Imagem *img, Imagem *img_alt){
	int i, j;
	init_img(img_alt, img->width * 2, img->height * 2);

	for(i = 0; i < img->height; i++){
		for(j = 0; j <img->width; j++){
			img_alt->matriz[i*2][j*2]         = img->matriz[i][j];
			img_alt->matriz[i*2][(j*2)+1]     = img->matriz[i][j];
			img_alt->matriz[(i*2)+1][j*2]     = img->matriz[i][j];
			img_alt->matriz[(i*2)+1][(j*2)+1] = img->matriz[i][j];
		}
	}
	copy_img(img_alt, img);
}
//Função que reduz uma imagem em duas vezes. Tem como parâmetros um *Imagem img que é a imagem antes da modificação e um *Imagem img_alt que recebera
//as modificações feitas. É do tipo void.
void img_reduc(Imagem *img, Imagem *img_alt){
	int i, j, sum;
	init_img(img_alt, img->width/2, img->height/2);

	for(i = 0; i < img_alt->height; i++){
		for(j = 0; j < img_alt->width; j++){
			sum = img->matriz[i*2][j*2].red + img->matriz[i*2][(j*2)+1].red + img->matriz[(i*2)+1][j*2].red + img->matriz[(i*2)+1][(j*2)+1].red;
			img_alt->matriz[i][j].red = sum/4;
			sum = 0;

			sum = img->matriz[i*2][j*2].green + img->matriz[i*2][(j*2)+1].green + img->matriz[(i*2)+1][j*2].green + img->matriz[(i*2)+1][(j*2)+1].green;
			img_alt->matriz[i][j].green = sum/4;
			sum = 0;

			sum = img->matriz[i*2][j*2].blue + img->matriz[i*2][(j*2)+1].blue + img->matriz[(i*2)+1][j*2].blue + img->matriz[(i*2)+1][(j*2)+1].blue;
			img_alt->matriz[i][j].blue = sum/4;
			sum = 0;
		}
	}
	copy_img(img_alt, img);
}
//Função que rotaciona uma imagem pra direita em 90°. Tem como parâmetros um *Imagem img que é a imagem antes da modificação e um *Imagem img_alt que recebera
//as modificações feitas. É do tipo void.
void img_rotate(Imagem *img, Imagem *img_alt){
	int i, j;
	init_img(img_alt, img->height, img->width);

	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){
			img_alt->matriz[j][img->height-1-i] = img->matriz[i][j]; 
		}
	}
	copy_img(img_alt, img);
}
//Função responsável por fazer o cálculo de um t (valor limite para binarização de imagens) dinâmico, baseado nas cores da imagem
//Tem como parâmetros um Pixel p, int i e int j que são responsável por servir como referência através das suas coordenadas para a função que faz a
//convolução entre as matrizes 3x3 de uma imagem com p sendo o centro e um filtro que também é uma matriz 3x3 (que nesse caso é um filtro neutro),
//um *Imagem img que será usada para calcular o t em relação aos valores RGB dessa imagem e um const float mat_filter[3][3] que é o filtro.
//É uma função do tipo int e retorna o valor de t.
int calc_t(Pixel p, int i, int j, Imagem *img, const float mat_filter[3][3]){
	Pixel temp;
	int t, p_media, media_aux;

	temp = pixel_filter(p, i, j, img, mat_filter);
	p_media = (temp.red + temp.green + temp.blue)/3;
	if(p_media > 255)
		p_media = 255;
	else
		if(p_media < 0)
			p_media = 0;
	media_aux = (p.red + p.green + p.blue)/3;
	t = abs(media_aux - p_media);
	return t;
}
//Função responsável pela binarização da imagem a partir de um certo t (valor limite), que define se o pixel será preto ou branco.
//Tem como parâmetros um *Imagem img que é a imagem antes das modificações e *Imagem img_alt que recebera as modificações. É uma função do tipo void.
void img_bin(Imagem *img, Imagem *img_alt){
	int i, j, media, t = 128;
	 const float n_filter[3][3] = { 
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 1, 1, 1 }
	};
	init_img(img_alt, img->width, img->height);

	for(i = 1; i < img->height-1; i++){
		for(j = 1; j < img->width-1; j++){
			media = (img->matriz[i][j].red + img->matriz[i][j].green + img->matriz[i][j].blue) / 3;
			t = calc_t(img->matriz[i][j], i, j, img, n_filter);
			if(media >= t){
				img_alt->matriz[i][j].red   = 255;
				img_alt->matriz[i][j].green = 255;
				img_alt->matriz[i][j].blue  = 255;
			}
			else{
				img_alt->matriz[i][j].red   = 0;
				img_alt->matriz[i][j].green = 0;
				img_alt->matriz[i][j].blue  = 0;
			}
			media = 0;
		}
	}
	copy_img(img_alt, img);
}
//Função responsável por transformar as cores da imagem em tons de cinza. Tem como parâmetros *Imagem img que é antes da modificação e *Imagem img_alt
//que irá receber as modificações. É uma função do tipo void.
void img_gray(Imagem *img, Imagem *img_alt){
	int i, j;
	init_img(img_alt, img->width, img->height);

	for(i = 0; i < img->height; i++){
		for(j = 0; j < img->width; j++){
			img_alt->matriz[i][j].red = (int)img->matriz[i][j].red * 0.21 + (int)img->matriz[i][j].green * 0.72 + (int)img->matriz[i][j].red * 0.07;
			img_alt->matriz[i][j].green = (int)img->matriz[i][j].red * 0.21 + (int)img->matriz[i][j].green * 0.72 + (int)img->matriz[i][j].red * 0.07;
			img_alt->matriz[i][j].blue = (int)img->matriz[i][j].red * 0.21 + (int)img->matriz[i][j].green * 0.72 + (int)img->matriz[i][j].red * 0.07;
		}
	}
	copy_img(img_alt, img);
}
//Função essencial para o cálculo da convolução entre uma matriz de pixels 3x3 e um filtro 3x3, ela pega um pixel e o altera em relação ao filtro e a imagem.
//Tem como parâmetros um Pixel p, int i, int j, que representam o pixel de referência para a matriz de pixels 3x3,
//*Imagem img que será usada para obter a matrix de pixels 3x3 em que o p é o centro e
//um const float mat_filter[3][3] que é o filtro escolhido. É uma função do tipo Pixel e retorna um Pixel p.
Pixel pixel_filter(Pixel p, int i, int j, Imagem *img, const float mat_filter[3][3]){
	int a, b, sum_r, sum_g, sum_b;
	sum_r = 0;
	sum_g = 0;
	sum_b = 0;

	for (a = 0; a < 3; ++a){
		for (b = 0; b < 3; ++b){
			sum_r = sum_r + (img->matriz[(i-1)+a][(j-1)+b].red * mat_filter[a][b]);
			sum_g = sum_g + (img->matriz[(i-1)+a][(j-1)+b].green * mat_filter[a][b]);
			sum_b = sum_b + (img->matriz[(i-1)+a][(j-1)+b].blue * mat_filter[a][b]);
		}
	}
	if(sum_r > 255)
		sum_r = 255;
	else
		if(sum_r < 0)
			sum_r = 0;

	if(sum_g > 255)
		sum_g = 255;
	else
		if(sum_g < 0)
			sum_g = 0;

	if(sum_b > 255)
		sum_b = 255;
	else
		if(sum_b < 0)
			sum_b = 0;

	p.red   = sum_r; 
	p.green = sum_g;
	p.blue  = sum_b;
	return p;
}
//Função responsável por aplicar um filtro em todos os pixels de uma imagem. Tem como parâmetros *Imagem img que é a imagem antes das modificações e
//*Imagem img_alt que irá receber as modificações. É do tipo void.
void apply_filter(Imagem *img, Imagem *img_alt, const float mat_filter[3][3]){
	int i, j;
	init_img(img_alt, img->width, img->height);

	for (i = 1; i < img->height-1; i++){
		for (j = 1; j < img->width-1; j++){
			img_alt->matriz[i][j] = pixel_filter(img->matriz[i][j], i, j, img, mat_filter);
		}
	}
	copy_img(img_alt, img);
}
//Função que seleciona qual filtro será usado na imagem. Tem como parâmetros *Imagem img que é a imagem antes das modificações e *Imagem img_alt
//que irá receber as modificações e FilterType type que são os nomes do filtros indexados a números inteiros começados do zero.
void img_filter(Imagem *img, Imagem *img_alt, FilterType type){
	const float BLUR_MAT[3][3] = { 
		{ 1/9.f, 1/9.f, 1/9.f },
		{ 1/9.f, 1/9.f, 1/9.f },
		{ 1/9.f, 1/9.f, 1/9.f }
	};
		
	const float BORDA_MAT[3][3] = { 
		{ -1, -1, -1 },
		{ -1,  8, -1 },
		{ -1, -1, -1 }
	};

	const float SHARP_MAT[3][3] = { 
		{  0, -1,  0 },
		{ -1,  5, -1 },
		{  0, -1,  0 }
	};

	switch(type){
		case 0 :
			apply_filter(img, img_alt, BLUR_MAT);
			break;
		case 1 :
			apply_filter(img, img_alt, SHARP_MAT);
			break;
		case 2 : 
			img_gray(img, img_alt);
			apply_filter(img, img_alt, BLUR_MAT);
			apply_filter(img, img_alt, BORDA_MAT);
			break;
		case 3 : 
			img_bin(img, img_alt);
			break;
		case 4 :
			img_gray(img, img_alt);
			break;
	}
}
//Função responsável por ampliar imagens n vezes utilizando img_amp recursivamente. Tem como parâmetros *Imagem img que é a imagem antes das modificações e
//*Imagem img_alt que irá receber as modificações e um int n que define quantas vezes a função img_amp será chamada.
void amp_rec(Imagem *img, Imagem *img_alt, int n){
	if(n == 1){
		img_amp(img, img_alt);
	}
	else{
		img_amp(img, img_alt);
		amp_rec(img, img_alt, n-1);
	}
}
//Função responsável por reduzir imagens n vezes utilizando img_reduc recursivamente. Tem como parâmetros *Imagem img que é a imagem antes das modificações e
//*Imagem img_alt que irá receber as modificações e um int n que define quantas vezes a função img_reduc será chamada.
void reduc_rec(Imagem *img, Imagem *img_alt, int n){
	if(n == 1){
		img_reduc(img, img_alt);
	}
	else{	
		img_reduc(img, img_alt);
		reduc_rec(img, img_alt, n-1);
	}		
}
//Função responsável por rotacionar imagens n vezes utilizando img_amp recursivamente. Tem como parâmetros *Imagem img que é a imagem antes das modificações e
//*Imagem img_alt que irá receber as modificações e um int n que define quantas vezes a função img_rotate será chamada.
void rotate_rec(Imagem *img, Imagem *img_alt, int n){
	if(n == 1){
		img_rotate(img, img_alt);
	}
	else{
		img_rotate(img, img_alt);
		rotate_rec(img, img_alt, n-1);
	}
}