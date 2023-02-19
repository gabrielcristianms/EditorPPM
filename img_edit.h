//Header que define as funções de edição e processamento de imagem
#ifndef __IMG_EDIT_H_
#define __IMG_EDIT_H_
void img_amp(Imagem *img, Imagem *img_alt);//Amplia imagens em duas vezes
void img_reduc(Imagem *img, Imagem *img_alt);//Reduz imagens em duas vezes
void img_rotate(Imagem *img, Imagem *img_alt);//Rotaciona imagens em 90° pra direita
int calc_t(Pixel p, int i, int j, Imagem *img, const float mat_filter[3][3]);//Calcula o valor limite da binarização
void img_bin(Imagem *img, Imagem *img_alt);//Binariza imagens
void img_gray(Imagem *img, Imagem *img_alt);//Deixa as cores de imagens em escala de cinza
void apply_filter(Imagem *img, Imagem *img_alt, const float mat_filter[3][3]);//Aplica um filtro em toda uma matriz
Pixel pixel_filter(Pixel p, int i, int j, Imagem *img, const float mat_filter[3][3]);//Modifica o valor de um pixel através da convolução entre filtro e imagem
void img_filter(Imagem *img, Imagem *img_alt, FilterType type);//Seleciona qual filtro será utilizado
void amp_rec(Imagem *img, Imagem *img_alt, int n);//Amplia imagens utilizando a funçao img_amp recursivamente
void reduc_rec(Imagem *img, Imagem *img_alt, int n);//Amplia imagens utilizando a funçao img_reduc recursivamente
void rotate_rec(Imagem *img, Imagem *img_alt, int n);//Amplia imagens utilizando a funçao img_rotate recursivamente
#endif