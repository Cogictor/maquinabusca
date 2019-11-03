#include <iostream>
#include <map>
#include <vector>

#include "Indice.h"

Indice::Indice(){
    palavras = 0;
}

Indice::Indice(Documento d1):Indice(){
    Documento copia = d1;
    std::vector<std::string> Docs;
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

bool Indice::Pertence(std::string texto){
    if(vocabulario.count(texto)>0)
        return true;
    else
        return false;
}

int Indice::Elementos(){
    return palavras;
}

std::string Indice::UltimChave(){
    return Chaves[palavras-1];
}

void Indice::RemoUltim(){
    palavras = palavras-1;
    vocabulario.erase(Chaves[palavras-1]);
    Chaves.pop_back();
}

void Indice::Adicionar(Documento d2){
    Indice Ind2(d2);
    std::vector<std::string> Docs;
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
    for(int i=0;i<palavras;i++){
        std::cout <<"[" << Chaves[i] << "] = [";
        for(int k=0;k<vocabulario[Chaves[i]].size();k++){
            std::cout <<vocabulario[Chaves[i]][k] << " ";
        } 
        std::cout << "]"<< "   ";
    }
}