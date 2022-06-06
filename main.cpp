#include <iostream>
#include <fstream>
#include "Cabecalho.h"

using namespace std;

int col, lin, max_tons, *img;
int matriz[1000][1000], matriz_resul[1000][1000], matriz_aux[1000][1000];

void le_img(string nome)
{
    string line;
    //define o arquivo da imagem
    ifstream image(nome);
    //verifica se a imagem esta aberta
    if (image.is_open())
    {
        //desconsidera o P2
        image >> line;
        //enquanto não chegar no fim do arquivo
        while ( !image.eof() )
        {
            //pega colunas linhas e o max de tons
            image >> col;
            image >> lin;
            image >> max_tons;
            img = &matriz[0][0];
            //pega todos os valores dos pixels
            for (; img < &matriz[0][0] + col*lin; img++)
            {
                image >> *img; 
            }
        }
        //fecha a imagem
        image.close();
    }
}

void escreve_nova_img(int col, int lin, int max_t, int *img, string nome)
{
    int *aux;
    ofstream image2;
    //da o nome passado por parametro
    image2.open (nome);
    if (image2.is_open())
    {
        //coloca os valores no arquivo P2, colunas, linhas e tons
        image2 << "P2" << endl;
        image2 << col << " " << lin << endl;
        image2 << max_t << endl;
        aux = img;
        //roda o ponteiro passado colocando todos os arquivos e de 17 em 17 pula linha
        for(int i = 0; img < aux + lin * col; img++, i++)
        {
            image2 << *img << " ";
            if (i % 17 == 0)
            {
                image2 << endl;
            }
        }
        //fecha o arquivo
        image2.close();
    }
}

int main (int argc, char**argv)
{   
    int aresta[3][3] = {{-1, -1 ,-1},
                         {-1, 8, -1},
                         {-1, -1, -1}};
    int nuc[3][3] = {{1, 1 ,1},
                         {1, 1, 1},
                         {1, 1, 1}};
    
    int comand, foto;
    
    cout << "escolha uma foto, digite:" << endl << "1 - foto de uma cidade" << endl << "2 - foto de uma mulher" << endl << "3 - foto de um totem" << endl << "4 - foto de dois caças" << endl << endl;
    cin >> foto;
    switch (foto)
    {
    case 1:
        le_img("_1-Cidade.pgm");
        
        break;
    case 2:
        le_img("_2-Mulher.pgm");
        
        break;
    case 3:
        le_img("_3-Totem.pgm");
        
        break;
    case 4:
        le_img("_4-Cacas.pgm");
        
        break;
    default:
        break;
    }

    cout << endl << "Digite:" << endl << "0 para finalizar o programa" << endl << "1 para negativar a imagem" << endl << "2 para espelhar a imagem horizontalmente" << endl << "3 para espelhar a imagem verticalmente" << endl << "4 para rotacionar a imagem para a direita" << endl << "5 para rotacionar a imagem para a esquerda" << endl << "6 para escurecer bordas" << endl << "7 para clarear a imagem" << endl << "8 para escurecer a imagem" << endl << "9 para destacar arestas" << endl << "10 para embaçar a imagem" << endl << "11 para limpar a imagem da taça" << endl << endl;

    do
    {
        cin >> comand;
        switch (comand)
        {
        case 1:
                negativa_img(&matriz[0][0], &matriz_resul[0][0], col, lin);
                escreve_nova_img(col, lin, max_tons, &matriz_resul[0][0], "1-Negativo.pgm");
            break;
        case 2:
                rotacao_horizontal_ponteiros(&matriz[0][0], col, lin, &matriz_resul[0][0]);
                escreve_nova_img(col, lin, max_tons, &matriz_resul[0][0], "2-Espelhar_Horizontal.pgm");
            break;
        case 3:
                rotacao_vertical_ponteiros(&matriz[0][0], col, lin, &matriz_resul[0][0]);
                escreve_nova_img(col, lin, max_tons, &matriz_resul[0][0], "3-Espelhar_Vertical.pgm");
            break;
        case 4:
                rotaciona_img_direita_ponteiro(lin, col, &matriz[0][0], &matriz_resul[0][0]);
                escreve_nova_img(lin, col, max_tons, &matriz_resul[0][0], "4-Rotacionar_Direita.pgm");
            break;
        case 5:
                rotaciona_img_esquerda_ponteiro(lin, col, &matriz[0][0], &matriz_resul[0][0]);
                escreve_nova_img(lin, col, max_tons, &matriz_resul[0][0], "5-Rotacionar_Esquerda.pgm");
            break;
        case 6:
                copia_img(&matriz[0][0], &matriz_resul[0][0], lin, col);
                escurece_bordas_ponteiros(col, lin, max_tons, 64, 1,&matriz[0][0], &matriz_resul[0][0]);
                escreve_nova_img(col, lin, max_tons, &matriz_resul[0][0], "6-Bordas.pgm");
            break;
        case 7:
                clarear_img(1.6, &matriz_resul[0][0], col, lin, &matriz[0][0], max_tons);
                escreve_nova_img(col, lin, max_tons, &matriz_resul[0][0], "7-Clarear.pgm");
            break;
        case 8:
                clarear_img(0.2, &matriz_resul[0][0], col, lin, &matriz[0][0], max_tons);
                escreve_nova_img(col, lin, max_tons, &matriz_resul[0][0], "8-Escurecer.pgm");
            break;
        case 9:
                copia_img(&matriz[0][0], &matriz_aux[0][0], lin, col);
                //ignora a primeira borda da matriz
                escurece_bordas_ponteiros(col, lin, max_tons, 255, 255, &matriz[0][0], &matriz_aux[0][0]);
                passa_alta(col, lin, max_tons, &matriz_resul[0][0], &matriz_aux[0][0], &aresta[0][0], 1);
                escreve_nova_img(col-2, lin-2, max_tons, &matriz_resul[0][0], "9-Destacar_Arestas.pgm");
            break;
        case 10:
                copia_img(&matriz[0][0], &matriz_aux[0][0], lin, col);
                //ignora a primeira borda da matriz
                escurece_bordas_ponteiros(col, lin, max_tons, 255, 255, &matriz[0][0], &matriz_aux[0][0]);
                passa_alta(col, lin, max_tons, &matriz_resul[0][0], &matriz_aux[0][0], &nuc[0][0], 9);
                escreve_nova_img(col-2, lin-2, max_tons, &matriz_resul[0][0], "10-Embacar.pgm");
            break;
        case 11:
                le_img("Tacas.pgm");
                copia_img(&matriz[0][0], &matriz_aux[0][0], lin, col);
                escurece_bordas_ponteiros(col, lin, max_tons, 255, 255, &matriz[0][0], &matriz_aux[0][0]);
                mediana(col, lin, max_tons, &matriz_resul[0][0], &matriz_aux[0][0]);
                escreve_nova_img(col-2, lin-2, max_tons, &matriz_resul[0][0], "11-Limpar_Taca.pgm");

            break;
        default:
            break;
        }   
    }while (comand != 0);
    
    cout << endl << "Obrigado querido Bressan!!!" << endl << endl << "Luiz Felipe dos Santos Nogueira - 2021.1.08.016" << endl << "Thiago Oliveira da Silva - 2019.1.08.028" << endl << "Túlio Sérgio Rosa Trombini - 2021.1.08.022" << endl;

    return 0;
}
