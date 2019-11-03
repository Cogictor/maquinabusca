#ifndef INDICE_INVERTIDO_H_
#define INDICE_INVERTIDO_H_

#include <string>
#include <map>
#include <vector>
#include "Documento.h"

class Indice{
    public:
        //Construtor de um indice vazio
        Indice();

        //Constroi um indice com as palavras do documento
        Indice(Documento d1);

        //Retorna se o elemento ja pertence ao indice ou nao
        bool Pertence(std::string texto);

        //Adiciona elementos de dum novo doc ao indice
        //PRE-CONDICAO - O Indice ja deve possuir ao menos um documento
        void Adicionar(Documento d2);

        //Retorna a ultima chave do vocabulario
        std::string UltimChave();

        //Remove ultimo elemento do vocabulario
        void RemoUltim();

        //Retorna o numero de elementos de um indice
        int Elementos();
        
        //Exibe o Indice
        void Exibir();
    private:
        //Quantidade de palavras no vocabulario
        int palavras;

        //Vocabulario que associa palavras a documentos
        std::map<std::string,std::vector<std::string>> vocabulario;

        //Chaves do vocabulario
        std::vector<std::string> Chaves;
};

#endif // INDICE_INVERTIDO_H_