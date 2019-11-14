#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

#include "Documento.h"
#include "Indice.h"


int main(){
    char continuar;
    std::string pesquisa;
    do{
        std::cout << "Digite a chave de pesquisa:" << std::endl;
        std::ofstream out;
        out.open("q.txt");
        std::getline(std::cin,pesquisa);
        out << pesquisa;
        out.close();

        Indice Index("input.txt");
        Documento q("q.txt");
        std::list<std::list<std::string>> Ranking;

        Ranking = Index.Ranking(q);

        std::cout << "\nRANKING :" << std::endl << "\t";

        int size = Ranking.size();
        for(int i=0;i<size;i++){
            int tam =Ranking.front().size();
            for(int j=0;j<tam;j++){
                std::cout << Ranking.front().front()<<" ";
                Ranking.front().pop_front();
            }
            std::cout << std::endl<< "\t" ;
            Ranking.pop_front();
        }
        std::cout <<"\n" << "Continuar?(S/N)" << std::endl;
        std::cin >> continuar;
        std::cin.ignore();
    }while(continuar!='n'&&continuar !='N');
    return 0;
}