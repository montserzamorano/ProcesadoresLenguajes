%{
    #include <stdlib.h>
%}

%option yylineno
%option noyywrap

%%

\/\*.*?\*\/ {}

"principal" {ECHO; return(PRINCIPAL);}
"inicio_variables" {ECHO; return(INI_VARIABLES);}
"fin_variables" {ECHO; return(FIN_VARIABLES);}
"procedimiento" {ECHO; return(PROCEDIMIENTO);}

"," {ECHO; return(COMA);}
";" {ECHO; return(PUNTO_Y_COMA);}
"(" {ECHO; return(INI_PARENTESIS);}
")" {ECHO; return(FIN_PARENTESIS);}
"{" {ECHO; return(INI_LLAVES);}
"}" {ECHO; return(FIN_LLAVES);}
"[" {ECHO; return(INI_CORCHETE);}
"]" {ECHO; return(FIN_CORCHETE);}

"si" {ECHO; return(SI);}
"si_no" {ECHO; return(SINO);}
"hacer" {ECHO; return(HACER);}
"hasta" {ECHO; return(HASTA);}
"mientras" {ECHO; return(MIENTRAS); }
"lista de" {ECHO; return(LISTA_DE);}
"leer" {ECHO; return(LEER);}
"escribir" {ECHO; return(ESCRIBIR);}
"=" {ECHO; return(ASIGNACION);}

"||" {ECHO; return(OP_OR_LOGICO);}
"&&" {ECHO; return(OP_AND_LOGICO);}
"|" {ECHO; return(OP_OR_BIT);}
"^" {ECHO; return(OP_EXC_OR);}
"&" {ECHO; return(OP_UNARIO);}
"!" {ECHO; return(OP_UNARIO);}
"==" {ECHO; return(OP_IGUALDAD);}
"!=" {ECHO; return(OP_IGUALDAD);}
"<" {ECHO; return(OP_RELACION);}
">" {ECHO; return(OP_RELACION);}
"<=" {ECHO; return(OP_RELACION);}
">=" {ECHO; return(OP_RELACION);}
"+" {ECHO; return(SIGNO);}
"-" {ECHO; return(SIGNO);}
"*" {ECHO; return(OP_MULTIPLICATIVO);}
"/" {ECHO; return(OP_MULTIPLICATIVO);}
"%" {ECHO; return(OP_MULTIPLICATIVO);}

"++" {ECHO; return(OP_MAS_MAS);}
"--" {ECHO; return(OP_MENOS_MENOS);}

"**" {ECHO; return(OP_CONCATENAR);}
"@" {ECHO; return(OP_ARR);}
"<<" {ECHO; return(OP_ES);}
">>" {ECHO; return(OP_ES);}
"$" {ECHO; return(OP_INICIO_LISTA);}
"#" {ECHO; return(OP_LONGITUD_LISTA);}
"?" {ECHO; return(OP_ELEMENTO_LISTA);}

"entero" {ECHO; return(TIPO_BASICO);}
"real" {ECHO; return(TIPO_BASICO);}
"booleano" {ECHO; return(TIPO_BASICO);}
"caracter" {ECHO; return(TIPO_BASICO);}

"verdadero" {ECHO; return(CONST_BOOLEANO);}
"falso" {ECHO; return(CONST_BOOLEANO);}


[0-9]+\.[0-9]+ {ECHO; return(CONST_REAL);}
[0-9]+ {ECHO; return(CONST_ENTERO);}
[a-zA-Z]([a-zA-Z]|[0-9]|_)* {ECHO; return(IDENTIFICADOR);}
\'.*?\' {ECHO; return(CONST_CARACTER);}
\".*?\" {ECHO; return(CADENA);}

[ \t] {ECHO;}
[\n\r] {ECHO;}


. { printf("\nError en linea: %d. No se reconoce ‘%s’. \n", yylineno, yytext);};

%%

//int main (int argc, char** argv){
//
//    if (argc != 2) {
//        printf("\nError al ejecutar la aplicación...\n");
//        printf("Uso: %s nombre_fichero_fuente\n", argv[0]);
//        exit(-1);
//    }
//
//    yyin = fopen(argv[1], "r");
//
//    if (yyin == NULL){
//        printf ("\nError no se puede abrir el archivo %s\n", argv[1]);
//        exit(-2);
//    }
//
//    int an = yylex();
//
//    while (an != 0) {
//        printf("__%d__ ", an);
//        an = yylex();
//    }
//
//    exit(1);
//}
