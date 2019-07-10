%{
    #include <stdlib.h>
    #include <string.h>
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
"mientras" {ECHO; return(MIENTRAS);}
"lista de" {ECHO; yylval.type = LIST; return(LISTA_DE);}
"leer" {ECHO; return(LEER);}
"escribir" {ECHO; return(ESCRIBIR);}
"=" {ECHO; return(ASIGNACION);}

"||" {
  ECHO;
  return(OP_OR_LOGICO);
  yylval.n = 0;
}

"&&" {
  ECHO;
  return(OP_AND_LOGICO);
  yylval.n = 0;
}

"|" {
  ECHO;
  yylval.n = 0;
  return(OP_OR_BIT);
}

"^" {
  ECHO;
  yylval.n = 0;
  return(OP_EXC_OR);
}

"&" {
  ECHO;
  yylval.n = 0;
  return(OP_UNARIO);
}

"!" {
  ECHO;
  yylval.n = 1;
  return(OP_UNARIO);
}

"==" {
  ECHO;
  yylval.n = 0;
  return(OP_IGUALDAD);
}

"!=" {
  ECHO;
  yylval.n = 1;
  return(OP_IGUALDAD);
}

"<" {
  ECHO;
  yylval.n = 0;
  return(OP_RELACION);
}

">" {
  ECHO;
  yylval.n = 1;
  return(OP_RELACION);
}

"<=" {
  ECHO;
  yylval.n = 2;
  return(OP_RELACION);
}

">=" {
  ECHO;
  yylval.n = 3;
  return(OP_RELACION);
}

"+" {
  ECHO;
  yylval.n = 0;
  return(SIGNO);
}

"-" {
  ECHO;
  yylval.n = 1;
  return(SIGNO);
}

"*" {
  ECHO;
  yylval.n = 0;
  return(OP_MULTIPLICATIVO);
}

"/" {
  ECHO;
  yylval.n = 1;
  return(OP_MULTIPLICATIVO);
}

"%" {
  ECHO;
  yylval.n = 2;
  return(OP_MULTIPLICATIVO);
}

"++" {
  ECHO;
  yylval.n = 0;
  return(OP_MAS_MAS);
}

"--" {
  ECHO;
  yylval.n = 0;
  return(OP_MENOS_MENOS);
}

"**" {
  ECHO;
  yylval.n = 0;
  return(OP_CONCATENAR);
}

"@" {
  ECHO;
  yylval.n = 0;
  return(OP_ARR);
}

"<<" {
  ECHO;
  yylval.n = 0;
  return(OP_ES);
}

">>" {
  ECHO;
  yylval.n = 1;
  return(OP_ES);
}

"$" {ECHO; return(OP_INICIO_LISTA);}
"#" {ECHO; return(OP_LONGITUD_LISTA);}
"?" {ECHO; return(OP_ELEMENTO_LISTA);}

"entero" {
  ECHO;
  yylval.type = INT;
  return(TIPO_BASICO);
}

"real" {
  ECHO;
  yylval.type = REAL;
  return(TIPO_BASICO);
}

"booleano" {
  ECHO;
  yylval.type = BOOL;
  return(TIPO_BASICO);
}

"caracter" {
  ECHO;
  yylval.type = CHAR;
  return(TIPO_BASICO);
}

"verdadero" {
  ECHO;
  yylval.n = 0;
  yylval.lex = strdup(yytext);
  return(CONST_BOOLEANO);
}

"falso" {
  ECHO;
  yylval.n = 1;
  yylval.lex = strdup(yytext);
  return(CONST_BOOLEANO);
}

[0-9]+\.[0-9]+ {
  ECHO;
  yylval.n = 2;
  yylval.lex = strdup(yytext);
  return(CONST_REAL);
}

[0-9]+ {
  ECHO;
  yylval.n = 3;
  yylval.lex = strdup(yytext);
  return(CONST_ENTERO);
}

[a-zA-Z]([a-zA-Z]|[0-9]|_)* {
  ECHO;
  yylval.lex = strdup(yytext);
  return(IDENTIFICADOR);
}

\'.*?\' {
  ECHO;
  yylval.n = 4;
  yylval.lex = strdup(yytext);
  return(CONST_CARACTER);
}

\".*?\" {
  ECHO;
  yylval.n = 5;
  yylval.lex = strdup(yytext);
  return(CADENA);
}

[ \t] {
  ECHO;
}

[\n\r] {
  ECHO;
  line++;
}


. {
  printf("\nError léxico, línea: %d. No se reconoce ‘%s’. \n", yylineno, yytext);
};

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
//        printf ("\nError: no se puede abrir el archivo %s\n", argv[1]);
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
