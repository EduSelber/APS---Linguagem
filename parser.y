%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

using Statement = function<void()>;
using StatementList = vector<Statement>;

unordered_map<string, float> symbols;

extern int yylex();
extern FILE* yyin;
void yyerror(const char* msg);
%}

%union {
    char* str;
    float fval;
    void* generic;
}

%token <str> STRING ID
%token <fval> NUM
%token CIRCULO RETANGULO LINHA COR GRUPO MOVER SE REPETIR VEZES
%token X Y X1 Y1 X2 Y2 RAIO LARGURA ALTURA
%token IGUAL DIFERENTE MAIORIGUAL MENORIGUAL MAIOR MENOR
%token ATRIB MAISIGUAL MENOSIGUAL MAIS MENOS VEZES_OP DIV
%token ABRECHAVE FECHACHAVE ABREPAR FECHAPAR

%type <fval> expr term factor condition
%type <generic> statement statements

%%

program:
    {
        printf("<svg xmlns='http://www.w3.org/2000/svg' width='800' height='600'>\n");
    }
    statements {
        auto* stmts = static_cast<StatementList*>($2);
        for (auto& stmt : *stmts) stmt();
        delete stmts;
        printf("</svg>\n");
    }
;

statements:
    /* vazio */ {
        $$ = new StatementList();
    }
    | statements statement {
        auto* list = static_cast<StatementList*>($1);
        auto* stmt = static_cast<Statement*>($2);
        list->push_back(*stmt);
        delete stmt;
        $$ = list;
    }
;

statement:
    CIRCULO X expr Y expr RAIO expr {
        $$ = new Statement([=]() {
            printf("<circle cx='%.2f' cy='%.2f' r='%.2f' stroke='black' fill='none'/>\n", $3, $5, $7);
        });
    }
  | RETANGULO X expr Y expr LARGURA expr ALTURA expr {
        $$ = new Statement([=]() {
            printf("<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' stroke='black' fill='none'/>\n", $3, $5, $7, $9);
        });
    }
  | LINHA X1 expr Y1 expr X2 expr Y2 expr {
        $$ = new Statement([=]() {
            printf("<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='black'/>\n", $3, $5, $7, $9);
        });
    }
  | COR expr {
        $$ = new Statement([=]() {
            printf("<!-- Cor atual: %.2f -->\n", $2);
        });
    }
  | ID ATRIB expr {
        char* raw = strdup($1);
        $$ = new Statement([=]() {
            symbols[string(raw)] = $3;
            free(raw);
        });
    }
  | ID MAISIGUAL expr {
        char* raw = strdup($1);
        $$ = new Statement([=]() {
            symbols[string(raw)] += $3;
            free(raw);
        });
    }
  | ID MENOSIGUAL expr {
        char* raw = strdup($1);
        $$ = new Statement([=]() {
            symbols[string(raw)] -= $3;
            free(raw);
        });
    }
  | SE condition ABRECHAVE statements FECHACHAVE {
        auto* block = static_cast<StatementList*>($4);
        $$ = new Statement([=]() {
            if ($2) {
                for (auto& s : *block) s();
            }
            delete block;
        });
    }
  | REPETIR expr VEZES ABRECHAVE statements FECHACHAVE {
        auto* block = static_cast<StatementList*>($5);
        $$ = new Statement([=]() {
            for (int i = 0; i < (int)$2; i++) {
                for (auto& s : *block) s();
            }
            delete block;
        });
    }
;

condition:
    ID IGUAL expr {
        std::string var($1);
        $$ = symbols[var] == $3;
    }
  | ID DIFERENTE expr {
        std::string var($1);
        $$ = symbols[var] != $3;
    }
  | ID MAIOR expr {
        std::string var($1);
        $$ = symbols[var] > $3;
    }
  | ID MENOR expr {
        std::string var($1);
        $$ = symbols[var] < $3;
    }
  | ID MAIORIGUAL expr {
        std::string var($1);
        $$ = symbols[var] >= $3;
    }
  | ID MENORIGUAL expr {
        std::string var($1);
        $$ = symbols[var] <= $3;
    }
;

expr:
    term
    | expr MAIS term { $$ = $1 + $3; }
    | expr MENOS term { $$ = $1 - $3; }
;

term:
    factor
    | term VEZES_OP factor { $$ = $1 * $3; }
    | term DIV factor { $$ = $1 / $3; }
;

factor:
    NUM { $$ = $1; }
  | ID {
        std::string var($1);
        if (!symbols.count(var)) {
            std::cerr << "Aviso: variável '" << var << "' não inicializada, assumindo 0.\n";
            symbols[var] = 0;
        }
        $$ = symbols[var];
    }
  | ABREPAR expr FECHAPAR { $$ = $2; }
  | STRING { $$ = 0; }
;

%%

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s arquivo.txt\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    yyin = file;
    yyparse();
    fclose(file);
    return 0;
}

void yyerror(const char* msg) {
    fprintf(stderr, "Erro: %s\n", msg);
}