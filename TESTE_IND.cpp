#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Indice.h"
#include "doctest.h"
#include <cstdio>

class Teste {
    public: 
        static std::list<std::string> valor_Chaves(Indice i1){
            return i1.Chaves;
        }
        static int valor_palavras(Indice i1){
            return i1.palavras;
        }
        static int valor_docs(Indice i1){
            return i1.docs;
        }
        static std::list<Documento> valor_Documentos(Indice i1){
            return i1.Documentos;
        }
        static std::map<std::string,std::list<std::string>> valor_vocabulario(Indice i1){
            return i1.vocabulario;
        }
};

TEST_SUITE("Indice"){
    TEST_CASE("Indice()"){
        Indice i1;
        CHECK(Teste::valor_palavras(i1) == 0);
        CHECK(Teste::valor_docs(i1) == 0);
    }

    TEST_CASE("Indice(Documento)"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e Unica";
        out.close();
        Documento d1("teste.txt");
        Indice i1(d1);
        CHECK(Teste::valor_docs(i1) == 1);
        CHECK(Teste::valor_palavras(i1) == 4);
        CHECK(Teste::valor_Chaves(i1) == std::list<std::string> {"a","palavra","e","unica"});
        CHECK((Teste::valor_Documentos(i1).size() == 1));
        CHECK((Teste::valor_Documentos(i1).front() == d1));
        std::list<std::string> documents {"teste.txt"};
        CHECK(Teste::valor_vocabulario(i1) == std::map<std::string,std::list<std::string>> {make_pair("a",documents),make_pair("palavra",documents),make_pair("e",documents),make_pair("unica",documents)});
        std::remove("teste.txt");    
    }

    TEST_CASE("Indice(vazio)"){
        Documento d1;
        Indice i1(d1);
        CHECK(Teste::valor_docs(i1) == 1);
        CHECK(Teste::valor_palavras(i1) == 0);
        CHECK(Teste::valor_Chaves(i1).empty());
        CHECK((Teste::valor_Documentos(i1).size() == 1));
        CHECK((Teste::valor_Documentos(i1).front() == d1));
        std::list<std::string> documents {"teste.txt"};
        CHECK(Teste::valor_vocabulario(i1).empty());
    }                                                              

    TEST_CASE("Indice(Arquivo)"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e unica";
        out.close();
        Documento d1("teste.txt");
        out.open("teste1.txt");
        out << "Queijo e bacon";
        out.close();
        Documento d2("teste1.txt");
        out.open("input1.txt");
        out << "teste.txt ";
        out << "teste1.txt";
        out.close();
        Indice i2("input1.txt");
        CHECK(Teste::valor_docs(i2) == 2);
        CHECK(Teste::valor_palavras(i2) == 6);
        CHECK(Teste::valor_Documentos(i2).size() == 2);
        CHECK((Teste::valor_Documentos(i2).front() == d1));
        CHECK((Teste::valor_Documentos(i2).back() == d2));
        CHECK(Teste::valor_Chaves(i2).size() == 6);
        CHECK(Teste::valor_Chaves(i2) == std::list<std::string> {"queijo","bacon","a","palavra","e","unica"});
        std::list<std::string> documents {"teste.txt"};
        std::list<std::string> documents1 {"teste1.txt"};
        std::list<std::string> documents2 {"teste.txt","teste1.txt"};
        CHECK(Teste::valor_vocabulario(i2) == std::map<std::string,std::list<std::string>> {make_pair("bacon",documents1),make_pair("queijo",documents1),make_pair("a",documents),make_pair("palavra",documents),make_pair("e",documents2),make_pair("unica",documents)});
        std::remove("teste.txt");
        std::remove("teste1.txt");
        std::remove("input1.txt");
    }

    TEST_CASE("Indice(Arquivo(com documento vazio))"){
        std::ofstream out;
        out.open("teste.txt");
        out.close();
        Documento d1("teste.txt");
        out.open("teste1.txt");
        out.close();
        Documento d2("teste1.txt");
        out.open("input1.txt");
        out << "teste.txt ";
        out << "teste1.txt";
        out.close();
        Indice i2("input1.txt");
        CHECK(Teste::valor_docs(i2) == 2);
        CHECK(Teste::valor_palavras(i2) == 0);
        CHECK(Teste::valor_Documentos(i2).size() == 2);
        CHECK((Teste::valor_Documentos(i2).front() == d1));
        CHECK((Teste::valor_Documentos(i2).back() == d2));
        CHECK(Teste::valor_Chaves(i2).empty());
        CHECK(Teste::valor_vocabulario(i2).empty());
        std::remove("teste.txt");
        std::remove("teste1.txt");
        std::remove("input1.txt");
    }

    TEST_CASE("Adicionar(vazio)"){
        Documento d1;
        Indice i1;
        i1.Adicionar(d1);
        CHECK(Teste::valor_palavras(i1) == 0);
        CHECK(Teste::valor_docs(i1) == 1);
        CHECK(Teste::valor_Documentos(i1).size() == 1);
        CHECK((Teste::valor_Documentos(i1).front() == d1));
        CHECK(Teste::valor_Chaves(i1).empty());
        CHECK(Teste::valor_vocabulario(i1).empty());
    }

    TEST_CASE("vazio.Adicionar()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e Unica ANTA";
        out.close();
        Documento d1("teste.txt");
        Indice i1;
        i1.Adicionar(d1);
        CHECK(Teste::valor_palavras(i1) == 5);
        CHECK(Teste::valor_docs(i1) == 1);
        CHECK(Teste::valor_Documentos(i1).size() == 1);
        CHECK((Teste::valor_Documentos(i1).front() == d1));
        CHECK(Teste::valor_Chaves(i1) == std::list<std::string> {"a","palavra","e","unica","anta"});
        std::list<std::string> documents {"teste.txt"};
        CHECK(Teste::valor_vocabulario(i1) == std::map<std::string,std::list<std::string>> {make_pair("a",documents),make_pair("unica",documents),make_pair("palavra",documents),make_pair("anta",documents),make_pair("e",documents)});
        std::remove("teste.txt");
    }

    TEST_CASE("Adicionar()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palma e e unica";
        out.close();
        Documento d1("teste.txt");
        out.open("teste1.txt");
        out << "Queijo e bacon";
        out.close();
        Documento d2("teste1.txt");
        Indice i1(d1);
        i1.Adicionar(d2);
        CHECK(Teste::valor_docs(i1) == 2);
        CHECK(Teste::valor_palavras(i1) == 6);
        CHECK(Teste::valor_Documentos(i1).size() == 2);
        CHECK((Teste::valor_Documentos(i1).front() == d1));
        CHECK((Teste::valor_Documentos(i1).back() == d2));
        CHECK(Teste::valor_Chaves(i1).size() == 6);
        CHECK(Teste::valor_Chaves(i1) == std::list<std::string> {"queijo","bacon","a","palma","e","unica"});
        std::list<std::string> documents {"teste.txt"};
        std::list<std::string> documents1 {"teste1.txt"};
        std::list<std::string> documents2 {"teste.txt","teste1.txt"};
        CHECK(Teste::valor_vocabulario(i1) == std::map<std::string,std::list<std::string>> {make_pair("bacon",documents1),make_pair("queijo",documents1),make_pair("a",documents),make_pair("palma",documents),make_pair("e",documents2),make_pair("unica",documents)});
        std::remove("teste.txt");
        std::remove("teste1.txt");    
    }

    TEST_CASE("Pertence()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e Unica ANTA";
        out.close();
        Documento d1("teste.txt");
        Indice i1(d1);
        CHECK(i1.Pertence("a"));
        CHECK(i1.Pertence("palavra"));
        CHECK(i1.Pertence("e"));
        CHECK(!i1.Pertence(""));
        CHECK(!i1.Pertence(" "));
        std::remove("teste.txt");
    }

    TEST_CASE("Indice(vazio).Pertence()"){
        Documento d1;
        Indice i1(d1);
        CHECK(!i1.Pertence("a"));
        CHECK(!i1.Pertence("palavra"));
        CHECK(!i1.Pertence(""));
        CHECK(!i1.Pertence(" "));
    }

    TEST_CASE("vazio.Pertence()"){
        Indice i1;
        CHECK(!i1.Pertence("a"));
        CHECK(!i1.Pertence("palavra"));
        CHECK(!i1.Pertence(""));
        CHECK(!i1.Pertence(" "));
    }

    TEST_CASE("Remoultim()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palma e e unica";
        out.close();
        Documento d1("teste.txt");
        Indice i1(d1);
        i1.RemoUltim();
        CHECK(Teste::valor_Chaves(i1).back() == "e");
        CHECK(Teste::valor_vocabulario(i1).count("unica") == 0);
        CHECK(Teste::valor_palavras(i1) == 3);
        i1.RemoUltim();
        CHECK(Teste::valor_Chaves(i1).back() == "palma");
        CHECK(Teste::valor_vocabulario(i1).count("e") == 0);
        CHECK(Teste::valor_palavras(i1) == 2);
        i1.RemoUltim();
        CHECK(Teste::valor_Chaves(i1).back() == "a");
        CHECK(Teste::valor_vocabulario(i1).count("palma") == 0);
        CHECK(Teste::valor_palavras(i1) == 1);
        i1.RemoUltim();
        CHECK(Teste::valor_Chaves(i1).empty());
        CHECK(Teste::valor_vocabulario(i1).count("a") == 0);
        CHECK(Teste::valor_palavras(i1) == 0);
        std::remove("teste.txt");
    }

    TEST_CASE("UltimChave()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palma e e unica";
        out.close();
        Documento d1("teste.txt");
        Indice i1(d1);
        CHECK(i1.UltimChave() == "unica");
        i1.RemoUltim();
        CHECK(i1.UltimChave() == "e");
        i1.RemoUltim();
        CHECK(i1.UltimChave() == "palma");
        i1.RemoUltim();
        CHECK(i1.UltimChave() == "a");
        out.open("teste1.txt");
        out << "Queijo e bacon";
        out.close();
        Documento d2("teste1.txt");
        i1.Adicionar(d2);
        CHECK(i1.UltimChave() == "a");
        i1.RemoUltim();
        CHECK(i1.UltimChave() == "bacon");
        std::remove("teste.txt");
    }

    TEST_CASE("Elementos()"){
        Indice i;
        CHECK(i.Elementos() == 0);

        Documento d;
        Indice i1(d);
        CHECK(i1.Elementos() == 0);

        std::ofstream out;
        out.open("teste.txt");
        out << "A palma e e unica";
        out.close();
        Documento d1("teste.txt");
        Indice i2(d1);
        CHECK(i2.Elementos() == 4);
        std::remove("teste.txt");
    }

    TEST_CASE("NumDoc()"){
        Indice i1;
        CHECK(i1.NumDoc() == 0);
        Documento d1, d2;
        Indice i2(d1);
        CHECK(i2.NumDoc() == 1);
        i2.Adicionar(d2);
        CHECK(i2.NumDoc() == 2);
    }

    TEST_CASE("Associados()"){
        Indice i2;
        CHECK(i2.Associados("a") == 0);
        CHECK(i2.Associados("") == 0);
        CHECK(i2.Associados(" ") == 0);

        std::ofstream out;
        out.open("teste.txt");
        out << "A palma e e unica";
        out.close();
        Documento d1("teste.txt");
        Indice i1(d1);
        CHECK(i1.Associados("e") == 1);

        out.open("teste1.txt");
        out << "Queijo e bacon";
        out.close();
        Documento d2("teste1.txt");
        i1.Adicionar(d2);
        CHECK(i1.Associados("a palma") == 0);
        CHECK(i1.Associados("e") == 2);
        CHECK(i1.Associados("a") == 1);

        std::remove("teste.txt");
        std::remove("teste1.txt");
    }

    TEST_CASE("Importancia()"){
        Indice i1;
        CHECK(i1.Importancia("a") == 0);

        Documento d;
        i1.Adicionar(d);
        CHECK(i1.Importancia("a") == 0);

        std::ofstream out;
        out.open("teste.txt");
        out << "A palma e e unica";
        out.close();
        Documento d1("teste.txt");
        out.open("teste1.txt");
        out << "Queijo e bacon";
        out.close();
        Documento d2("teste1.txt");
        Indice i2(d1);
        i1.Adicionar(d1);
        CHECK(i1.Importancia("a") == std::log(2));
        CHECK(i2.Importancia("a") == std::log(1));
        CHECK(i1.Importancia("e") == std::log(2));
        CHECK(i2.Importancia("e") == std::log(1));
        i1.Adicionar(d2);
        i2.Adicionar(d2);
        CHECK(i1.Importancia("a") == std::log(3));
        CHECK(i2.Importancia("a") == std::log(2));
        CHECK(i1.Importancia("e") == std::log(3.0/2.0));
        CHECK(i2.Importancia("e") == std::log(1));
        std::remove("teste.txt");
        std::remove("teste1.txt");
    }

    TEST_CASE("Coordenada()"){
        Documento d;
        Indice i(d);
        CHECK(i.Coordenada(d,"") == 0);

        std::ofstream out;
        out.open("teste.txt");
        out << "A palma e e unica";
        out.close();
        Documento d1("teste.txt");
        out.open("teste1.txt");
        out << "Queijo e bacon";
        out.close();
        Documento d2("teste1.txt");
        Indice i1(d1);
        CHECK(i1.Coordenada(d1,"a") == std::log(1)*1);
        CHECK(i1.Coordenada(d1,"e") == std::log(1)*2);
        i1.Adicionar(d2);
        CHECK(i1.Coordenada(d1,"a") == std::log(2)*1);
        CHECK(i1.Coordenada(d1,"e") == std::log(1)*2);
        CHECK(i1.Coordenada(d2,"a") == std::log(2)*0);
        CHECK(i1.Coordenada(d2,"e") == std::log(1)*1);
        std::remove("teste.txt");
        std::remove("teste1.txt");
    }

    TEST_CASE("Similaridadedoc()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A B";
        out.close();
        Documento q("teste.txt"),d;
        Indice i(d);
        CHECK(i.Similaridadedoc(d,q) == 0);

        out.open("teste1.txt");
        out << "A A A B";
        out.close();
        Documento d1("teste1.txt");
        out.open("teste2.txt");
        out << "A A C";
        out.close();
        Documento d2("teste2.txt");
        out.open("teste3.txt");
        out << "A A";
        out.close();
        Documento d3("teste3.txt");
        out.open("teste4.txt");
        out << "B B";
        out.close();
        Documento d4("teste4.txt");
        Indice i1(d1);
        CHECK(i1.Similaridadedoc(d1,q) == 0.0);

        i1.Adicionar(d2);
        i1.Adicionar(d3);
        i1.Adicionar(d4);
        CHECK((int)(i1.Similaridadedoc(d1,q)*1000) == 877);
        CHECK((int)(i1.Similaridadedoc(d2,q)*1000) == 383);
        CHECK((int)(i1.Similaridadedoc(d3,q)*1000) == 383);
        CHECK((int)(i1.Similaridadedoc(d4,q)*1000) == 923);

        out.open("teste4.txt");
        out.close();
        Documento q2("teste4.txt");
        CHECK(i1.Similaridadedoc(d1,q2) == 0.0);
        CHECK(i1.Similaridadedoc(d2,q2) == 0.0);
        CHECK(i1.Similaridadedoc(d3,q2) == 0.0);
        CHECK(i1.Similaridadedoc(d4,q2) == 0.0);

        out.open("teste4.txt");
        out << "D";
        out.close();
        Documento q3("teste4.txt");
        CHECK(i1.Similaridadedoc(d1,q3) == 0.0);
        CHECK(i1.Similaridadedoc(d2,q3) == 0.0);
        CHECK(i1.Similaridadedoc(d3,q3) == 0.0);
        CHECK(i1.Similaridadedoc(d4,q3) == 0.0);
        std::remove("teste.txt");
        std::remove("teste1.txt");
        std::remove("teste2.txt");
        std::remove("teste3.txt");
        std::remove("teste4.txt");
    }

    TEST_CASE("Similaridade()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A B";
        out.close();
        Documento q("teste.txt");

        out.open("teste1.txt");
        out << "A A A B";
        out.close();
        Documento d1("teste1.txt");
        out.open("teste2.txt");
        out << "A A C";
        out.close();
        Documento d2("teste2.txt");
        out.open("teste3.txt");
        out << "A A";
        out.close();
        Documento d3("teste3.txt");
        out.open("teste4.txt");
        out << "B B";
        out.close();
        Documento d4("teste4.txt");
        Indice i1(d1);
        i1.Adicionar(d2);
        i1.Adicionar(d3);
        i1.Adicionar(d4);
        std::list<double> sim = i1.Similaridade(q);
        CHECK((int)(sim.front()*1000) == 877);
        sim.pop_front();
        CHECK((int)(sim.front()*1000) == 383);
        sim.pop_front();
        CHECK((int)(sim.front()*1000) == 383);
        sim.pop_front();
        CHECK((int)(sim.front()*1000) == 923);

        out.open("teste4.txt");
        out.close();
        Documento q2("teste4.txt");
        CHECK(i1.Similaridade(q2) == std::list<double> {0.0,0.0,0.0,0.0});

        out.open("teste4.txt");
        out << "D";
        out.close();
        Documento q3("teste4.txt");
        CHECK(i1.Similaridade(q3) == std::list<double> {0.0,0.0,0.0,0.0});
        std::remove("teste.txt");
        std::remove("teste1.txt");
        std::remove("teste2.txt");
        std::remove("teste3.txt");
        std::remove("teste4.txt");
    }

    TEST_CASE("Ranking()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A B";
        out.close();
        Documento q("teste.txt");

        out.open("teste1.txt");
        out << "A A A B";
        out.close();
        Documento d1("teste1.txt");
        out.open("teste2.txt");
        out << "A A C";
        out.close();
        Documento d2("teste2.txt");
        out.open("teste3.txt");
        out << "A A";
        out.close();
        Documento d3("teste3.txt");
        out.open("teste4.txt");
        out << "B B";
        out.close();
        Documento d4("teste4.txt");
        Indice i1(d1);
        i1.Adicionar(d2);
        i1.Adicionar(d3);
        i1.Adicionar(d4);
        std::list<std::list<std::string>> ranking = i1.Ranking(q);
        std::list<std::string> lista1 {d4.Fonte()};
        std::list<std::string> lista2 {d1.Fonte()};
        std::list<std::string> lista3 {d2.Fonte(),d3.Fonte()};
        CHECK(ranking == std::list<std::list<std::string>> {lista1,lista2,lista3});

        out.open("teste4.txt");
        out << "D";
        out.close();
        Documento q2("teste4.txt");
        std::list<std::list<std::string>> ranking2 = i1.Ranking(q2);
        std::list<std::string> lista4 {d1.Fonte(),d2.Fonte(),d3.Fonte(),d4.Fonte()};
        CHECK(ranking2 == std::list<std::list<std::string>> {lista4});

        out.open("teste4.txt");
        out.close();
        Documento q3("teste4.txt");
        std::list<std::list<std::string>> ranking3 = i1.Ranking(q3);
        std::list<std::string> lista5 {d1.Fonte(),d2.Fonte(),d3.Fonte(),d4.Fonte()};
        CHECK(ranking3 == std::list<std::list<std::string>> {lista5});
        std::remove("teste.txt");
        std::remove("teste1.txt");
        std::remove("teste2.txt");
        std::remove("teste3.txt");
        std::remove("teste4.txt");
    }

    TEST_CASE("Exibir_Ranking(ofstream,Documento)"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A B";
        out.close();
        Documento q("teste.txt");

        out.open("teste1.txt");
        out << "A A A B";
        out.close();
        Documento d1("teste1.txt");
        out.open("teste2.txt");
        out << "A A C";
        out.close();
        Documento d2("teste2.txt");
        out.open("teste3.txt");
        out << "A A";
        out.close();
        Documento d3("teste3.txt");
        out.open("teste4.txt");
        out << "B B";
        out.close();
        Documento d4("teste4.txt");
        Indice i1(d1);
        i1.Adicionar(d2);
        i1.Adicionar(d3);
        i1.Adicionar(d4);
        out.open("saida.txt");
        i1.Exibir_Ranking(out,q);
        out.close();

        std::ifstream in;
        in.open("saida.txt");
        std::string s;
        in >> s;
        CHECK(s == "RANKING");
        in >> s;
        CHECK(s == ":");
        in >> s;
        CHECK(s == "teste4.txt");
        in >> s;
        CHECK(s == "teste1.txt");
        in >> s;
        CHECK(s == "teste2.txt");
        in >> s;
        CHECK(s == "teste3.txt");

        std::remove("saida.txt");
        std::remove("teste.txt");
        std::remove("teste1.txt");
        std::remove("teste2.txt");
        std::remove("teste3.txt");
        std::remove("teste4.txt");
    }
}