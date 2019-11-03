#ifndef DOCUMENTO_H_
#define DOCUMENTO_H_

#include <string>
#include <vector>

class Documento{
    public:
        //Cria Documaento vazio
        Documento();

        //Funcao que recebe um arquivo e armazena seu conteudo no documento
        Documento(std::string arquivo);

        //Numero de dados do documento
        int tamanho();

        //Quantidade de vezes que uma palavra aparece
        int Aparicoes(std::string texto);

        //se a palavra existe no doc
        bool Pertence(std::string palavra);

        //Retorna a ultima palavra do documento
        std::string UltimPalavra();

        //Remove a ultima palavra do documento
        void RemoUltima();

        //exibe o doc
        void Exibir();

        //Copia os elementos de um documento para outro
        void operator=(Documento d1);

        //Retorna qual arquivo foi retirado o documento
        std::string Fonte();
    private:
        //Vector armazenando as palavras do documento
        std::vector<std::string> dados;
        //Numero de palavras do documento
        int palavras;
        
        //Nome do arquivo
        std::string arquivo;
};


#endif // DOCUMENTO_H_