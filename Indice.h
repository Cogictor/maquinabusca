#ifndef INDICE_INVERTIDO_H_
#define INDICE_INVERTIDO_H_

#include <map>
#include <vector>
#include "Documento.h"

class Indice{
    public:
        //Construtor de um indice vazio
        Indice();

        //Constroi um indice com as palavras do documento
        Indice(Documento const d1);

        //Constroi um indice invertido a partir dos arquivos presentes no arquivo
        Indice(std::string arquivo);

        //Retorna se o elemento ja pertence ao indice ou nao
        bool Pertence(std::string texto) const;

        //Adiciona elementos de um novo doc ao indice
        void Adicionar(Documento const d2);

        //Retorna a ultima chave do vocabulario
        std::string UltimChave() const;

        //Remove ultimo elemento do vocabulario
        void RemoUltim();

        //Retorna o numero de palavras do indice
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
        double Similaridadedoc(Documento const D,Documento const q);

        //Calcula a similaridade dos documentos que compoem o indice coma a pesquisa, e retorna a similaridadedos documentos.
        std::list<double> Similaridade(Documento q);

        //Gera um ranking com os nomes dos documentos em ordem decrescente de similaridade
        std::list<std::list<std::string>> Ranking(Documento q);

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