#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Documento.h"
#include "doctest.h"

using std::string;

class Teste {
    public: 
        static std::list<std::string> valor_dados(Documento d1){
            return d1.dados;
        }
        static int valor_palavras(Documento d1){
            return d1.palavras;
        }
        static string valor_arquivo(Documento d1){
            return d1.arquivo;
        }
};

TEST_SUITE("Documento") {
    TEST_CASE("Documento()"){
        Documento d1;
        CHECK(Teste::valor_palavras(d1) == 0);
    }

}