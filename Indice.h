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
        Indice(Documento const d1);

        //Retorna se o elemento ja pertence ao indice ou nao
        bool Pertence(std::string texto) const;

        //Adiciona elementos de dum novo doc ao indice
        //PRE-CONDICAO - O Indice ja deve possuir ao menos um documento
        void Adicionar(Documento const d2);

        //Retorna a ultima chave do vocabulario
        std::string UltimChave() const;

        //Remove ultimo elemento do vocabulario
        void RemoUltim();

        //Retorna o numero de elementos do indice
        int Elementos() const;

        //Retorna o numero de documentos associados ao indice
        int NumDoc() const;

        //Retorna o numero de documentos associasdos aquela palavra
        //PRE-CONDICAO - A palavra deve estar contida ema ao menos um documento (Deve pertencer ao Indice)
        int Associados(std::string texto);
        
        //Exibe o Indice
        void Exibir();

        //Calcula coordenada de uma palavra e documento em um indice
        double Coordenada(Documento const d,std::string texto);

        //Calcula a importancia de uma palavra em um indice
        double Importancia(std::string texto);

        //Calcula a similaridade de um documento e uma pesquisa
        double Similaridade(Documento const D,Documento const q);
    private:
        //Quantidade de palavras no vocabulario
        int palavras;

        //Quantidade de documentos fonte do indice
        int docs;

        //Documentos que formam o indice
        std::list<Documento> Documentos;

        //Dicionario que associa palavras a documentos
        std::map<std::string,std::list<std::string>> vocabulario;

        //Chaves do vocabulario
        std::list<std::string> Chaves;
};

#endif // INDICE_INVERTIDO_H_