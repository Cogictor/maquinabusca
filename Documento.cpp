#include <iostream>
#include <fstream>
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

 int Documento::tamanho() const{
    return palavras;
 }

 int Documento::Aparicoes(std::string texto){
    int aux = 0;
    for(std::list<std::string>::iterator it=dados.begin();it!=dados.end();++it){
        if(*it==texto)
            aux++;
    }
    return aux;
 }

 bool Documento::Pertence(std::string texto){
    for(std::list<std::string>::iterator it=dados.begin();it!=dados.end();++it){
        if(*it==texto)
            return true;
    }
    return false;
 }

std::string Documento::UltimPalavra() const{
    return dados.back();
}

void Documento::RemoUltima(){
    palavras = palavras-1;
    dados.pop_back();
}

void Documento::operator=(Documento d1){
    palavras = d1.palavras;
    Apagar();
    for(std::list<std::string>::iterator it=d1.dados.begin();it!=d1.dados.end();++it){
        dados.push_back(*it);
    }
}

void Documento::Apagar(){
    while(palavras!=0)
        RemoUltima();
}

void Documento::Exibir(){
    for(std::list<std::string>::iterator it=dados.begin();it!=dados.end();++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

std::string Documento::Fonte() const{
    return arquivo;
}

    //Indice Invertido
         //adicionar a um dicionario, com os documentos que a possuem