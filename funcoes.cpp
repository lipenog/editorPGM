#include <iostream>
#include <fstream>

void negativa_img(int *img, int *img_res, int col, int lin)
{
    int *aux;
    aux = img;
    //roda a imagem original e a resultado
    for (; img < aux + col*lin; img++, img_res++)
    {
        //guarda o valor do complemento da imagem original na imagem resultado
        *img_res = 255 - *img;
    }
}


void rotaciona_img_direita_ponteiro(int lin, int col, int *img, int *img_res)
{
    int aux, *q1, i, *img_rot;
    aux = lin;
    lin = col;
    col = aux;
    //marca o ultimo valor da imagem resultado e vai tirando até chegar no 
    //primeiro elemento da ultima linha
    for(q1 = img_res + (col*lin) -1, i = 0; q1 >= img_res + col*lin - col; q1--, i++)
    {
        //marca o ultimo elemento da primeira linha
        //o i faz com que ele vai voltando 
        //roda ate o q1 ou seja ele desloca do ultimo elemento da primeira linha
        //ate o ultimo da ultima linha e depois vai voltando
        for(img_rot = img_res + col - 1 - i; img_rot <= q1; img_rot += col, img++)
        {
            *img_rot = *img;
        }
    }   
}

void rotaciona_img_esquerda_ponteiro(int lin, int col, int *img, int *img_res)
{
    int aux, *q1, *q2, *p, i, *img_rot;
    aux = lin;
    lin = col;
    col = aux;
    //marca o primeiro elemento da imagem resultado e roda até o final da primeira linha
    for(q1 = img_res, i = 0; q1 < img_res + col; q1++, i++)
    {
        //marca o primeiro elemento da ultima coluna
        //o i faz com que esse ponto desloque pra frente
        //assim ele vai do primeiro elemento da ultima coluna até o primeiro elemento
        //e depois ele vai andando até o final
        for(img_rot = img_res + col*lin - col + i; img_rot >= q1; img++, img_rot -= col)
        {
            *img_rot = *img;
        }
    }
}


void rotacao_horizontal_ponteiros(int *img, int col, int lin, int *img_res)
{
    int aux2, *p1, *p2, *p3, *q1, *q2, *aux;
    //marca o inicio da imagem original
    p1 = img;
    //marca a ultima linha da imagem resultado
    p2 = img_res + (lin*col) - col;
    //p1 vai ate o ultimo elemento da 1 coluna
    //assim p1 e p2 deslocam pelas colunas
    //p1 de cima pra baixo e p2 de baixo pra cima
    for(; p1 < img + (lin*col)-col; p1 += col, p2 -= col)
    {
        //marca o começo de cada linha e caminha pelos elementos
        for(q1 = p1, q2 = p2; q1 < p1 + col; q1++, q2++)
        {
            *q2 = *q1;
        }
    }
}

void clarear_img(float x, int *img_res, int c, int l, int *img, int m_ton)
{  
    int *aux;
    aux = img_res;
    //caminha pela imagem original e multiplica por um escalar "x" e guarda em imagem resultante
    for(; img_res < aux+c*l; img_res++, img++)
    {
        *img_res = (int)*img * x;
        //verifica se os pixels ainda estão no escopo da imagem
        if(*img_res >= m_ton)
        {
            *img_res = m_ton;
        }
        if(*img_res <= 0)
        {
            *img_res = 0;
        }
    }
}

void rotacao_vertical_ponteiros(int *img, int col, int lin, int *img_res)
{
    int aux2, *p1, *p2, *p3, *q1, *q2, *aux;
    //marca a 1 posição da imagem
    p1 = img;
    //marca o ultimo elemento da primeira linha
    p2 = img_res + col - 1;
    //caminha pelas linhas
    for(; p1 <= img + col - 1; p1++, p2--)
    {
        //q1 e q2 caminham pelas colunas e trocam valores
        //ate o ultimo termo de cada coluna 
        for(q1 = p1, q2 = p2; q1 <= p1 +(lin*col)-col; q1 += col, q2 += col)
        {
            *q2 = *q1;
        }
    }
}

void passa_alta(int col, int lin, int max_t, int *img, int *img_res, int *nucleo, int media_div)
{
    int *p1, *p2, *p3, *p4, *q1, *q2;
    float media;


    //como a matriz de mudança é 3x3 o ponteiro tem que começar os ponteiros ignorando as posições das bordas 
    p1 = img_res + col + 1;
    p2 = img_res + 2*col - 2;
    //esses ponteiros marcam o início e final de cada linha ignorando as bordas
    //e caminham pelas colunas até a ultima posição ignorando também a ultima linha
    for (; p1 <= img_res + (col*lin) - 2*col + 1 ; p1 += col, p2 += col)
    {
        //p3 caminha por todos os elementos de p1 a p2
        //como cada p3 gera um pixel img caminhara junto de p3 
        p3 = p1;
        for (; p3 <= p2; p3++, img++)
        {
            //zera a media
            media = 0;
            //marca o nucleo "o filtro que sera aplicado"
            q2 = nucleo;
            //aqui delimitamos uma matriz 3x3 dentro da nossa imagem, cada termo vai ser multiplicado pelo seu correspondente no núcleo 
            //p4 vai marcar o primeiro termo dessa matriz 3x3 que retiramos da imagem
            //q1 vai caminhar pela linha marcada por p4 realizando a multiplicação de cada termo
            for(p4 = p3 - col - 1; p4 <= p3 + col - 1; p4 += col)
            {
                for(q1 = p4; q1 <= p4 + 2; q1++, q2++)
                {
                    media += *q1 * *q2; 
                }                
            }
            //divide caso o filtro utilize a media 
            media = media/media_div;
            //confere se o valor do pixel ainda esta no escopo da imagem
            if (media > max_t)
            {
                *img = max_t;
            }
            else if (media < 0)
            {
                *img = 0; 
            }
            else
                *img = media;
        }
    }
}

void escurece_bordas_ponteiros(int col, int lin, int max_t, int x, int passos, int *img, int *img_res)
{
    //marquei cada canto da imagem e eles caminham sempre uma posição pra dentro
    //na diagonal
    int *esq_sup, *dir_sup, *esq_inf, *dir_inf;
    int *p1, *p2;
    for(esq_sup = img, dir_sup = img + col - 1, esq_inf = img + col*lin - col, dir_inf = img + col*lin - 1; x >= 0; x -= passos, esq_sup += col + 1, dir_sup += col - 1, esq_inf += -col + 1, dir_inf += -col - 1)
    {
        //esquerda superior para direita superior
        //"linha de cima"
        for(p1 = esq_sup, p2 = img_res + (esq_sup - img) ; p1 <= dir_sup; p1++, p2++)
        {
            *p2 = *p1 - x;

            //verifica se os pixels ainda estão no escopo da imagem
            if (*p2 >= max_t)
            {
                *p2 = max_t;
            }
            if (*p2 <= 0)
            {
                *p2 = 0;
            }
        }
        //direita superior na coluna de baixo, para evitar repetição para direita inferior
        for(p1 = dir_sup + col, p2 = img_res + (dir_sup + col - img); p1 <= dir_inf; p1 += col, p2 += col)
        {
            *p2 = *p1 - x;

            //verifica se os pixels ainda estão no escopo da imagem
            if (*p2 >= max_t)
            {
                *p2 = max_t;
            }
            if (*p2 <= 0)
            {
                *p2 = 0;
            }
        }
        //esquerda inferior para direita inferior - 1 para evitar repetição
        for(p1 = esq_inf, p2 = img_res + (esq_inf - img); p1 <= dir_inf; p1++, p2++)
        {
            *p2 = *p1 - x;

            //verifica se os pixels ainda estão no escopo da imagem
            if (*p2 >= max_t)
            {
                *p2 = max_t;
            }
            if (*p2 <= 0)
            {
                *p2 = 0;
            }
        }
        //esquerda superior na coluna de baixo para esquerda inferior - 1 para evitar repetição
        for(p1 = esq_sup + col, p2 = img_res + (esq_sup + col - img); p1 <= esq_inf; p1 += col, p2 += col)
        {
            *p2 = *p1 - x;

            //verifica se os pixels ainda estão no escopo da imagem
            if (*p2 >= max_t)
            {
                *p2 = max_t;
            }
            if (*p2 <= 0)
            {
                *p2 = 0;
            }
        }
    }
}

void copia_img(int *copia, int *cola, int lin, int col)
{
    int *aux;
    aux = copia;
    for (; copia < aux + col*lin; copia++, cola++)
    {
        *cola = *copia;
    }
}

void bubble_sort(int *vet, int tam)
{
    int *p, *q, aux;
    for(p = vet + tam - 1; p > vet; p--)
    {
        for(q = vet; q < p; q++)
        {
            if(*q > *(q + 1))
            {
                aux = *q;
                *q = *(q + 1);
                *(q + 1) = aux;
            }
        }
    }
}

void mediana(int col, int lin, int max_t, int *img, int *img_res)
{
    int *p1, *p2, *p3, *p4, *q1, *q2, aux[9];


    //como a matriz de mudança é 3x3 o ponteiro tem que começar os ponteiros ignorando as posições das bordas 
    p1 = img_res + col + 1;
    p2 = img_res + 2*col - 2;
    //esses ponteiros marcam o início e final de cada linha ignorando as bordas
    //e caminham pelas colunas até a ultima posição ignorando também a ultima linha
    for (; p1 <= img_res + (col*lin) - 2*col + 1 ; p1 += col, p2 += col)
    {
        //marca o inicio da linha
        p3 = p1;
        for (; p3 <= p2; p3++, img++)
        {
            q2 = &aux[0];
            //caminha pelos valores da matriz 3x3 selecionada da imagem
            //passa todos os valores para o vetor
            for(p4 = p3 - col - 1; p4 <= p3 + col - 1; p4 += col)
            {
                for(q1 = p4; q1 <= p4 + 2; q1++, q2++)
                {
                    *q2 = *q1;
                }                
            }
            //ordena eles e pega a mediana
            bubble_sort(&aux[0], 9);
            q2 = &aux[0];
            *img = *(q2 + 4);
        }
    }
}
