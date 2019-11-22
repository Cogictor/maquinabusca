#include <iostream>
#include <fstream>
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
            Chaves.push_front(copia.UltimPalavra());
        }
        copia.RemoUltima();
    }
}

Indice::Indice(std::string arquivo):Indice(){
    std::ifstream in;
    in.open(arquivo);
    std::string texto;

    while(in >> texto){
        Documento d(texto);
        Adicionar(d);
    }

    in.close();
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
    if(Pertence(texto))
        return vocabulario[texto].size();
    else 
        return 0;
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
            Chaves.push_front(Ind2.UltimChave());
        }
        Ind2.RemoUltim();
    }
}

double Indice::Importancia(std::string texto){
    double N = NumDoc(), nx = Associados(texto);
    if(nx == 0)
        return 0;
    return std::log(N/nx);
}

double Indice::Coordenada(Documento d,std::string texto){
    int frequencia = d.Aparicoes(texto);
    double importancia = Importancia(texto);
    return frequencia*importancia;
}

double Indice::Similaridadedoc(Documento D,Documento q){
    double numerador = 0,denominador1 = 0,denominador2 = 0;
    Documento copia = q;
    for(int i=0;i<q.tamanho();i++){
        numerador = numerador + Coordenada(D,copia.UltimPalavra())*Coordenada(q,copia.UltimPalavra());
        denominador1 = denominador1 + pow(Coordenada(D,copia.UltimPalavra()),2);
        denominador2 = denominador2 + pow(Coordenada(q,copia.UltimPalavra()),2);
        copia.RemoUltima();
    }
    double similaridade = numerador/(sqrt(denominador1)*sqrt(denominador2));
    if(denominador2==0||denominador1==0)
        return 0;
    return similaridade;
}
 
std::list<double> Indice::Similaridade(Documento q){
    std::list<double> sim;
    std::list<Documento> Copia = Documentos;
    for(int i=0;i<Documentos.size();i++){
        Documento d = Copia.front();
        sim.push_back(Similaridadedoc(d,q));
        Copia.pop_front();
    }
    return sim;
}

std::list<std::list<std::string>> Indice::Ranking(Documento q){
    std::list<std::list<std::string>> Ranking;
    std::list<double> similaridades = Similaridade(q);
    std::list<double> copia_sim = similaridades;
    std::map<double,std::list<std::string>> Associativo;
    //Associa a cada valor de similaridade um conjunto de nomes de documentos que a possui
    for(std::list<Documento>::iterator it=Documentos.begin();it!=Documentos.end();++it){
        if(Associativo[copia_sim.front()].empty()){
            std::list<std::string> fontes;
            Associativo.insert(std::pair<double,std::list<std::string>>(copia_sim.front(),fontes));
            Associativo[copia_sim.front()].push_back((*it).Fonte());
            copia_sim.pop_front();
        }else {
            Associativo[copia_sim.front()].push_back((*it).Fonte());
            copia_sim.pop_front();
        }
    }
    //ordena a similaridade em ordem crescente
    similaridades.sort();
    //adiciona ao vetor os nomes do documento no ranking de acordo com a sua posicao em ordem decrescente
    for(std::list<double>::iterator it=similaridades.begin();it!=similaridades.end();++it){
        Ranking.push_front(Associativo[(*it)]);
        //evitar repeticoes no ranking
        if(Associativo[(*it)].size()>1){
            int num = Associativo[(*it)].size()-1;
            for(int i=0;i<num;i++)
                ++it;
        }
    }
    return Ranking;
}
void Indice::Exibir_Ranking(std::ostream& out,Documento q){
    std::list<std::list<std::string>> ranking;

    ranking = Ranking(q);

    out << "\nRANKING :" << "\n" << "\t";

    int size = ranking.size();
    for(int i=0;i<size;i++){
        int tam =ranking.front().size();
        for(int j=0;j<tam;j++){
            out << ranking.front().front()<<" ";
            ranking.front().pop_front();
        }
        out << "\n" << "\t" ;
        ranking.pop_front();
    }
}