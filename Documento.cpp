#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

#include "Documento.h"

std::string CorrigirString(std::string texto)
{
    std::locale loc;

    //torna a string lowercase
    for (std::string::size_type i=0; i<texto.length(); ++i)
        texto[i] = std::tolower(texto[i],loc);

    //retira caracteres especias e sinais de pontuacao
    for(int i=0;texto[i]!='\0';i++){
        if ( !isdigit(texto[i],loc) ){
            if ( !isalpha(texto[i],loc) )
                texto.erase(i,1);
        }
    }// PROCURAR SABER COM O PROFESSOR SE DEVE ARMAZENAR OS NUMEROS FLOAT OU A VIRGULA PODE SUMIR TAMBEM

    return texto;
}

 Documento::Documento(){
     palavras = 0;
 }

 Documento::Documento(std::string arquivo):Documento(){
    std::ifstream in;
    in.open(arquivo);
    std::string texto;

    while(in >> texto){
        texto = CorrigirString(texto);
        dados.push_back(texto);
        palavras++;
    }

    in.close();
 }

 int Documento::tamanho(){
     return palavras;
 }

void Documento::Exibir(){
    for(int i=0;i<tamanho();i++){
        std::cout << dados[i] << " " ;
    }
    std::cout << std::endl;
}


    //Indice Invertido
         //adicionar a um dicionario, com os documentos que a possuem