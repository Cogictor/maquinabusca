#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

#include "Documento.h"

std::string CorrigirString(std::string texto){
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

 Documento::Documento(std::string arqui):Documento(){
    std::ifstream in;
    in.open(arqui);
    std::string texto;

    while(in >> texto){
        texto = CorrigirString(texto);
        if(texto!=""){
            dados.push_back(texto);
            palavras++;            
        }
    }

    arquivo = arqui;

    in.close();
 }

 int Documento::tamanho(){
    return palavras;
 }

 int Documento::Aparicoes(std::string texto){
    int aux = 0;
    for(int i=0;i<tamanho();i++){
        if(dados[i]==texto)
            aux++;
    }
    return aux;
 }

 bool Documento::Pertence(std::string texto){
    for(int i=0;i<tamanho();i++){
        if(dados[i]==texto)
            return true;
    }
    return false;
 }

std::string Documento::UltimPalavra(){
    return dados[palavras-1];
}

void Documento::RemoUltima(){
    palavras = palavras-1;
    dados.pop_back();
}

void Documento::operator=(Documento d1){
    palavras = d1.palavras;
    for(int i=0;i<d1.tamanho();i++){
        dados[i] = d1.dados[i];
    }
}

void Documento::Exibir(){
    for(int i=0;i<tamanho();i++){
        std::cout << dados[i] << " ";
    }
    std::cout << std::endl;
}

std::string Documento::Fonte(){
    return arquivo;
}

    //Indice Invertido
         //adicionar a um dicionario, com os documentos que a possuem