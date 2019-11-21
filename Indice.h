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

        //Constroi um indice invertido a partir dos arquivos presentes no arquivo cujo nome foi recebido de entrada
        //PRE-CONDICAO = O arquivo nao deve estar vazio
        Indice(std::string arquivo);

        //Retorna se o elemento ja pertence ao indice ou nao
        bool Pertence(std::string texto) const;

        //Adiciona elementos de um novo doc ao indice
        void Adicionar(Documento const d2);

        //Remove o ultimo elemento das chaves do indice
        //PRE-CONDICAO = O indice deve possuir ao menos uma palavra
        void RemoUltim();

        //Retorna ultimo elemento das chaves do indice
        //PRE-CONDICAO = O indice nao deve estar sem palavras
        std::string UltimChave() const;

        //Retorna o numero de palavras do indice
        int Elementos() const;

        //Retorna o numero de documentos associados ao indice
        int NumDoc() const;

        //Retorna o numero de documentos associados aquela palavra
        int Associados(std::string texto);

        //Calcula coordenada de uma palavra e documento presente no indice, em um indice
        double Coordenada(Documento const d,std::string texto);

        //Calcula a importancia de uma palavra em um indice
        double Importancia(std::string texto);

        //Calcula a similaridade de um documento e uma pesquisa
        //PRE-CONDICAO = O documento deve estar presente no indice e o documento pesquisa nao deve ser vazio
        double Similaridadedoc(Documento const D,Documento const q);

        //retorna a similaridade dos documentos com a pesquisa
        //PRE-CONDICAO = O documento pesquisa nao deve ser vazio
        std::list<double> Similaridade(Documento q);

        //Gera um ranking com os nomes dos documentos em ordem decrescente de similaridade
        std::list<std::list<std::string>> Ranking(Documento q);

        //Exibe o Ranking do atual baseado no indice do arquivo
        void Exibir_Ranking(std::ostream& out,Documento q);
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

        friend class Teste;
};

#endif // INDICE_INVERTIDO_H_