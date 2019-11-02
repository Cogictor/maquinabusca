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

        //se a palavra existe no doc
        bool Pertence(std::string palavra);

        //exibe o doc
        void Exibir();
    private:
        //Vector armazenando as palavras do documento
        std::vector<std::string> dados;
        //Numero de palavras do documento
        int palavras;
};


#endif // DOCUMENTO_H_