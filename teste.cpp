#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

#include "Documento.h"
#include "Indice.h"


int main(){
    Documento doc1("d1.txt");
    Documento doc2("d2.txt");
    Documento doc3("d3.txt");
    Documento doc4("d4.txt");
    Documento q("q.txt");


    Indice Index(doc1);
    Index.Adicionar(doc2);
    std::cout << "12" << std::endl;
    Index.Adicionar(doc3);
    Index.Adicionar(doc4);

    double sim1,sim2,sim3,sim4;
    sim1 = Index.Similaridade(doc1,q);
    sim2 = Index.Similaridade(doc2,q);
    sim3 = Index.Similaridade(doc3,q);
    sim4 = Index.Similaridade(doc4,q);

    std::cout << sim1 << " " << sim2 << " " << sim3 << " " <<sim4 << std::endl;

    return 0;
}