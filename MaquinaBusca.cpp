#include <iostream>
#include <fstream>
#include <cstdio>

#include "Documento.h"
#include "Indice.h"


int main(){
    char continuar;
    std::string pesquisa;
    Indice Index("input.txt");
    std::ofstream out;
    do{
        std::cout << "Digite a chave de pesquisa:" << std::endl;
        out.open("q.txt");
        std::getline(std::cin,pesquisa);
        out << pesquisa;
        out.close();

        Documento q("q.txt");
        Index.Exibir_Ranking(std::cout,q);
        std::remove("q.txt");
        std::cout <<"\n" << "Continuar?(S/N)" << std::endl;
        std::cin >> continuar;
        std::cin.ignore();
        std::system("cls");
    }while(continuar!='n'&&continuar !='N');
    return 0;
}