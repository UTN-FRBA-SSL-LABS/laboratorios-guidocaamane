%{
#include <stdio.h>
#include <stdlib.h>

int  yylex(void);
void yyerror(const char *msg) {}/*Se elimino el print al acceder a yyerror*/
%}

%token NUM

%left '+' '-'
%left '*' '/'

%%

input:
    /* vacío */
  | input linea
  ;

/*
 * Sin manejo de errores, el primer token inesperado hace que yyparse()
 * retorne con fallo y el resto de la entrada nunca se procesa.
 *
 * El token especial 'error' le permite a Bison intentar recuperarse:
 * descarta tokens hasta encontrar el símbolo de sincronización (acá '\n')
 * y continúa parseando la siguiente línea.
 * Llamar a yyerrok dentro de la acción resetea el estado de error interno.
 */
linea:
    exp '\n'    { printf("= %d\n", $1); }
    | error '\n'  { yyerrok; printf("Error: sintaxis invalida\n"); }
    /*Se agrego la regla de recuperacion de errores cuando encuentre un salto de linea*/
  ;

exp:
    exp '+' exp   { $$ = $1 + $3; }
  | exp '-' exp   { $$ = $1 - $3; }
  | exp '*' exp   { $$ = $1 * $3; }
  | exp '/' exp   { $$ = $1 / $3; }
  | '(' exp ')'   { $$ = $2; }
  | NUM           { $$ = $1; }
  ;

%%

int main(void) {
    return yyparse();
}
