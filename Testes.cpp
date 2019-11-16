// FUNCOES A SER DECIDIDO SE MANTIDAS OU NAO:


//DOcumento.cpp

/*
    void Documento::Exibir(){
        for(std::list<std::string>::iterator it=dados.begin();it!=dados.end();++it){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
*/

// Documento.h

/*        
    //exibe o documento
    //PRE-CONDICAO = O documento nao esta vazio
    void Exibir();
        
*/

//TESTE_DOC.cpp

/*
    TEST_CASE("Exibir()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e unica";
        out.close();
        Documento d1("teste.txt");
        std::list<std::string> copia = Teste::valor_dados(d1), copia2 = copia;
        for(std::list<std::string>::iterator it=copia.begin();it!=copia.end();++it){
            CHECK(*it == copia2.front());
            copia2.pop_front();
        }
    }
*/

//Indice.cpp

/*
void Indice::Exibir(){
    for(std::list<std::string>::iterator it=Chaves.begin();it!=Chaves.end();++it){
        std::cout <<"\"" << *it << "\" ={";
        for(std::list<std::string>::iterator it2=vocabulario[*it].begin();it2!=vocabulario[*it].end();++it2){
            std::cout << *it2 << " ";
        } 
        std::cout << "};"<< "   ";
    }
}
*/

//Indice.h

/*  
    //Exibe o Indice
    void Exibir();
*/
