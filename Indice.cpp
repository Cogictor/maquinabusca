#include <iostream>
#include <map>
#include <vector>
#include <cmath>

#include "Indice.h"

Indice::Indice(){
    palavras = 0;
    docs = 0;
}

Indice::Indice(Documento d1):Indice(){
    docs ++;
    Documentos.push_back(d1);
    Documento copia = d1;
    std::list<std::string> Docs;
    Docs.push_back(d1.Fonte());    
    for(int i=0;i<d1.tamanho();i++){
        if(!Pertence(copia.UltimPalavra())){
            vocabulario.insert(make_pair(copia.UltimPalavra(),Docs));
            palavras++;
            Chaves.push_back(copia.UltimPalavra());
        }
        copia.RemoUltima();
    }
}

bool Indice::Pertence(std::string texto) const{
    if(vocabulario.count(texto)>0)
        return true;
    else
        return false;
}

int Indice::Elementos() const{
    return palavras;
}

int Indice::NumDoc() const{
    return docs;
}

int Indice::Associados(std::string texto){
    return vocabulario[texto].size();
}

std::string Indice::UltimChave() const{
    return Chaves.back();
}

void Indice::RemoUltim(){
    palavras = palavras-1;
    vocabulario.erase(Chaves.back());
    Chaves.pop_back();
}

void Indice::Adicionar(Documento d2){
    docs++;
    Documentos.push_back(d2);
    Indice Ind2(d2);
    std::list<std::string> Docs;
    Docs.push_back(d2.Fonte());
    int iteracoes = Ind2.Elementos();
    for(int i=0;i<iteracoes;i++){
        if(Pertence(Ind2.UltimChave())){
            vocabulario[Ind2.UltimChave()].push_back(d2.Fonte());
        }else {
            vocabulario.insert(make_pair(Ind2.UltimChave(),Docs));
            palavras++;
            Chaves.push_back(Ind2.UltimChave());
        }
        Ind2.RemoUltim();
    }
}

void Indice::Exibir(){
    for(std::list<std::string>::iterator it=Chaves.begin();it!=Chaves.end();++it){
        std::cout <<"\"" << *it << "\" ={";
        for(std::list<std::string>::iterator it2=vocabulario[*it].begin();it2!=vocabulario[*it].end();++it2){
            std::cout << *it2 << " ";
        } 
        std::cout << "};"<< "   ";
    }
}

double Indice::Importancia(std::string texto){
    double N = NumDoc(), nx = Associados(texto);
    if(nx == 0)
        return 0;
    std::cout << "Importancia" << texto << " " << N<<" " <<nx<< std::log(N/nx)<< std::endl;
    return std::log(N/nx);
}

double Indice::Coordenada(Documento d,std::string texto){
    int frequencia = d.Aparicoes(texto);
    double importancia = Importancia(texto);
    std::cout << "frequqencia"<< frequencia << "Coordenada" << frequencia*importancia <<std::endl;
    return frequencia*importancia;
}

double Indice::Similaridade(Documento D,Documento q){
    double numerador = 0,denominador1 = 0,denominador2 = 0;
    Documento copia = q;
    for(int i=0;i<q.tamanho();i++){
        numerador = numerador + Coordenada(D,copia.UltimPalavra())*Coordenada(q,copia.UltimPalavra());
        denominador1 = denominador1 + pow(Coordenada(D,copia.UltimPalavra()),2);
        denominador2 = denominador2 + pow(Coordenada(q,copia.UltimPalavra()),2);
        copia.RemoUltima();
    }
    std::cout << std::endl << numerador << " " << denominador1 << " " << denominador2 << std::endl;
    double similaridade = numerador/(sqrt(denominador1)*sqrt(denominador2));
    if(denominador2==0||denominador1==0)
        return 0;
    return similaridade;
}