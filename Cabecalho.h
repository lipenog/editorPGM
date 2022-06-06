#ifndef CABECALHO_H
#define CABECALHO_H

void negativa_img(int *img, int *img_res, int col, int lin);
void rotaciona_img_direita_ponteiro(int lin, int col, int *img, int *img_res);
void rotaciona_img_esquerda_ponteiro(int lin, int col, int *img, int *img_res);
void rotacao_horizontal_ponteiros(int *img, int col, int lin, int *img_res);
void escurece_bordas_ponteiros(int col, int lin, int max_t, int x, int passos, int *img, int *img_res);
void clarear_img(float x, int *img_res, int c, int l, int *img, int m_ton);
void rotacao_vertical_ponteiros(int *img, int col, int lin, int *img_res);
void passa_alta(int col, int lin, int max_t, int *img, int *img_res, int *nucleo, int media_div);
void copia_img(int *copia, int *cola, int lin, int col);
void mediana(int col, int lin, int max_t, int *img, int *img_res);
void bubble_sort(int *vet, int tam);

#endif 

