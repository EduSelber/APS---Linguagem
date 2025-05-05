# 🎨 Selber_Sketches

Selber_Sketches é uma linguagem de programação focada na criação de elementos gráficos simples, como círculos, linhas e retângulos, por meio de comandos textuais. A linguagem foi projetada para ser intuitiva, permitindo o uso de variáveis, condições, laços de repetição e agrupamento de formas.

## Sintaxe da Linguagem – EBNF

A linguagem definida abaixo permite a criação de formas geométricas, grupos, estruturas condicionais e repetições, além do uso de variáveis com atribuições e expressões. A gramática está descrita na notação EBNF (Extended Backus-Naur Form), que facilita a visualização da estrutura e regras da linguagem.

```ebnf
program      = { statement } ;

statement    = shape | color | group | conditional | loop | assignment ;

shape        = circle | rect | line ;

circle       = "circulo" "x" expr "y" expr "raio" expr ;

rect         = "retangulo" "x" expr "y" expr "largura" expr "altura" expr ;

line         = "linha" "x1" expr "y1" expr "x2" expr "y2" expr ;

color        = "cor" expr ;

group        = "grupo" "{" { statement } "}" [ transform ] ;

transform    = "mover" "x" expr "y" expr ;

conditional  = "se" condition "{" { statement } "}" ;

loop         = "repetir" expr "vezes" "{" { statement } "}" ;

assignment   = identifier assign_op expr ;

assign_op    = "=" | "+=" | "-=" ;

condition    = ( "x" | "y" | "cor_atual" | identifier ) comparator expr ;

expr         = term { ("+" | "-") term } ;

term         = factor { ("*" | "/") factor } ;

factor       = number | string | identifier | "(" expr ")" ;

comparator   = "==" | ">" | "<" | ">=" | "<=" | "!=" ;

string       = '"' { letter | digit } '"' ;

identifier   = letter { letter | digit | "_" } ;

number       = digit { digit } [ "." digit { digit } ] ;

digit        = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;

letter       = "a" | "b" | "c" | ... | "z" | "A" | "B" | ... | "Z" ;
```

## Características

- **Formas básicas**: `circulo`, `retangulo`, `linha`
- **Manipulação de cores**: comando `cor`
- **Grupos**: agrupar múltiplas formas com `grupo { ... }`
- **Movimentação**: aplicar transformações de movimento com `mover`
- **Variáveis**: atribuição e operações como `=`, `+=`, `-=`
- **Condicionais**: blocos `se { ... }` baseados em comparações
- **Laços de repetição**: `repetir { ... }` com controle baseado em variáveis ou números
- **Expressões aritméticas**: uso de `+`, `-`, `*`, `/` em valores

## Exemplo de código

```plaintext
cor "azul"

posicao = 10

circulo x posicao y 50 raio (posicao + 5)

posicao += 20

se posicao > 15 {
    retangulo x 0 y 0 largura posicao altura 30
}

repetir 5 vezes {
    linha x1 0 y1 0 x2 posicao y2 100
}
