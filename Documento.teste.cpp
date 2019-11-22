#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Documento.h"
#include "doctest.h"
#include <cstdio>

class Teste {
    public: 
        static std::list<std::string> valor_dados(const Documento d1){
            return d1.dados;
        }
        static int valor_palavras(const Documento d1){
            return d1.palavras;
        }
        static std::string valor_arquivo(const Documento d1){
            return d1.arquivo;
        }
};

TEST_SUITE("Documento") {
    TEST_CASE("Documento()"){
        Documento d1;
        CHECK(Teste::valor_palavras(d1) == 0);
    }

    TEST_CASE("Documento(string)"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e unica";
        out.close();
        Documento d1("teste.txt");
        CHECK(Teste::valor_palavras(d1) == 4);
        CHECK(Teste::valor_arquivo(d1) == "teste.txt");
        CHECK(Teste::valor_dados(d1) == std::list<std::string> {"a","palavra","e","unica"});
        std::remove("teste.txt");
    }

    TEST_CASE("tamanho()-Documento vazio"){
        Documento d;
        CHECK(d.tamanho() == 0);
    }

    TEST_CASE("tamanho()-Documento nao vazio"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e unica";
        out.close();
        Documento d1("teste.txt");
        CHECK(d1.tamanho() == 4);
        std::remove("teste.txt");
    }

    TEST_CASE("Aparicoes()-Documento vazio"){
        Documento d;
        CHECK(d.Aparicoes("a") == 0);
    }

    TEST_CASE("Aparicoes()-Documento nao vazio"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A A E E  e unicA unica";
        out.close();
        Documento d1("teste.txt");
        CHECK(d1.Aparicoes("a") == 2);
        CHECK(d1.Aparicoes("e") == 3);
        CHECK(d1.Aparicoes("unica") == 2);
        CHECK(d1.Aparicoes("um") == 0);
        std::remove("teste.txt");
    }

    TEST_CASE("Pertence()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A A E E  e unicA unica";
        out.close();
        Documento d1("teste.txt");
        CHECK(d1.Pertence("a") == true);
        CHECK(d1.Pertence("e") == true);
        CHECK(d1.Pertence("unica") == true);
        CHECK(d1.Pertence("ai") == false);
        std::remove("teste.txt");
    }

    TEST_CASE("RemoUltima()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e unica";
        out.close();
        Documento d1("teste.txt");
        d1.RemoUltima();
        CHECK(Teste::valor_palavras(d1) == 4);
        CHECK(Teste::valor_dados(d1).back() == "e");
        d1.RemoUltima();
        CHECK(Teste::valor_palavras(d1) == 3);
        CHECK(Teste::valor_dados(d1).back() == "e");
        d1.RemoUltima();
        CHECK(Teste::valor_palavras(d1) == 2);
        CHECK(Teste::valor_dados(d1).back() == "palavra");
        d1.RemoUltima();
        CHECK(Teste::valor_palavras(d1) == 1);
        CHECK(Teste::valor_dados(d1).back() == "a");
        d1.RemoUltima();
        CHECK(Teste::valor_palavras(d1) == 0);
        CHECK(Teste::valor_dados(d1).empty());
        std::remove("teste.txt");
    }

    TEST_CASE("UltimPalavra()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e unica";
        out.close();
        Documento d1("teste.txt");
        CHECK(d1.UltimPalavra() == "unica");
        d1.RemoUltima();
        CHECK(d1.UltimPalavra() == "e");
        d1.RemoUltima();
        CHECK(d1.UltimPalavra() == "e");
        d1.RemoUltima();
        CHECK(d1.UltimPalavra() == "palavra");
        d1.RemoUltima();
        CHECK(d1.UltimPalavra() == "a");
        std::remove("teste.txt");        
    }

    TEST_CASE("Apagar()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e unica";
        out.close();
        Documento d1("teste.txt");
        d1.Apagar();
        CHECK(Teste::valor_palavras(d1) == 0);
        CHECK(Teste::valor_dados(d1).empty());
        std::remove("teste.txt");
    }

    TEST_CASE("Documento = vazio"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e unica";
        out.close();
        Documento d1("teste.txt"), d2;
        d1 = d2;
        CHECK(Teste::valor_palavras(d1) == Teste::valor_palavras(d2));
        CHECK(Teste::valor_arquivo(d1) == Teste::valor_arquivo(d2));
        CHECK(Teste::valor_dados(d1).empty());
        std::remove("teste.txt");
    }

    TEST_CASE("Vazio = Documento"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e unica";
        out.close();
        Documento d1("teste.txt"), d2 = d1;
        CHECK(Teste::valor_palavras(d1) == 5);
        CHECK(Teste::valor_arquivo(d1) == "teste.txt");
        CHECK(Teste::valor_dados(d1) == std::list<std::string> {"a","palavra","e","e","unica"});
        std::remove("teste.txt");
    }

    TEST_CASE("Documento = Documento"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e unica";
        out.close();
        Documento d1("teste.txt");
        out.open("teste1.txt");
        out << "Queijo e bacon";
        out.close();
        Documento d2("teste1.txt");
        d1 = d2;
        CHECK(Teste::valor_palavras(d1) == 3);
        CHECK(Teste::valor_arquivo(d1) == "teste1.txt");
        CHECK(Teste::valor_dados(d1) == std::list<std::string> {"queijo","e","bacon"});
        std::remove("teste.txt");
    }

    TEST_CASE("Fonte()"){
        std::ofstream out;
        out.open("teste.txt");
        out << "A palavra e e unica";
        out.close();
        Documento d1("teste.txt");
        CHECK(d1.Fonte() == Teste::valor_arquivo(d1));
        std::remove("teste.txt");
    }
}