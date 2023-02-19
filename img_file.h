//Header que define as funções relacionadas a leitra e escrita de arquivos do tipo Imagem.
#ifndef __IMG_FILE_H_
#define __IMG_FILE_H_
void open_img (Imagem *img); //Abre um arquivo e joga as informações dele numa variável do tipo Imagem caso seja um arquivo no formato .PPM
void save_img (Imagem *img); //Salva as informações de uma variável do tipo Imagem em um arquivo no formato .PPM
#endif