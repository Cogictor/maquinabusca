#ifndef DOCUMENTO_H_
#define DOCUMENTO_H_

#include <string>
#include <list>

class Documento{
    public:
        //Cria Documaento vazio
        Documento();

        //Funcao que recebe um arquivo e armazena seu conteudo no documento
        Documento(std::string arquivo);

        //Numero de dados do documento
        int tamanho() const;

        //Quantidade de vezes que uma palavra aparece
        int Aparicoes(std::string texto);

        //se a palavra existe no doc
        bool Pertence(std::string palavra);

        //Retorna a ultima palavra do documento
        std::string UltimPalavra() const;

        //Remove a ultima palavra do documento
        void RemoUltima();

        //exibe o documento
        void Exibir();

        //Copia os elementos de um documento para outro
        void operator=(Documento const d1);

        //Apaga os elementos de um documento
        void Apagar();

        //Retorna qual arquivo foi retirado o documento
        std::string Fonte() const;
    private:
        //lista armazenando as palavras do documento
        std::list<std::string> dados;
        //Numero de palavras do documento
        int palavras;
        
        //Nome do arquivo
        std::string arquivo;

        friend class Teste;
};


#endif // DOCUMENTO_H_