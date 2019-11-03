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

    doc1.Exibir();
    std::cout << std::endl;
    doc2.Exibir();
    std::cout << std::endl;


    Indice Ind1(doc1);
    Ind1.Exibir();
    std::cout << std::endl;

    Ind1.Adicionar(doc2);
    Ind1.Exibir();

    return 0;
}