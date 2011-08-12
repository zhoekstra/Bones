
%{

#include <iostream> 
#include <vector>
#include <node.hpp>

extern int yylex();
extern _i_stmt*    stmt;
extern funcdecl_b* func;
extern bool        closing;
extern bool        quiet;

void yyerror(const char* msg) {
  std::cout << msg << std::endl;
}

%}

%union {
  token*              token_t;
  _i_expr*            expr_t;
  _i_stmt*            stmt_t;
  funcdecl_b*         func_t;
  param_b*            param_t;
  __node*             default_t;
  
  std::vector<param_b*>* paramlist_t;
  std::vector<_i_expr*>* exprlist_t;
  std::vector<_i_stmt*>* stmtlist_t;
}

%token            LPAR RPAR LCUR RCUR LBRA RBRA COMMA SEMI COLO
%token            IF ELSE WHILE IN FOR VAR CONSTVAR FUNC RETURN
%token            ASN EQ NEQ GT LT EQGT EQLT TO BANG
%token            PLUS MINUS MULT DIV MOD
%token            UNION COMPLEMENT INTERSECT
%token            EXPLODE DESPLODE ROLLAGAIN
%token <token_t>  INTLIT
%token <token_t>  ID

%type <stmt_t>      script
%type <func_t>      funcdecl
%type <expr_t>      callexpr

%type <param_t>     param
%type <paramlist_t> paramlist

%type <expr_t>      expr
%type <exprlist_t>  exprlist

%type <stmt_t>      stmt
%type <stmtlist_t>  stmtlist

%type <stmt_t>      elseif
%type <stmtlist_t>  elseiflist

%type <expr_t>      rollmod
%type <exprlist_t>  rollmodlist

%right  ASN
%left   UNION
%left   INTERSECT
%left   PRODUCT
%right  COMPLEMENT
%left   NEQ
%left   EQ 
%left   GT EQGT
%left   LT EQLT
%left   PLUS MINUS
%left   MULT DIV MOD
%right  BANG
%left   DOT
%left   LPAR RPAR
%left   LBRA RBRA

%expect 3

%start base

%% /* Grammar rules and actions */

base:
    script
;

script:
    stmt
    { stmt = $1; func = NULL; YYACCEPT; }
  | funcdecl
    { stmt = NULL; func = $1; YYACCEPT; }
  | /* epsilon */
    { stmt = NULL; func = NULL; closing = true; YYACCEPT; }
;

elseiflist:
    elseif elseiflist
    { $2->push_back($1); $$ = $2; }
  | /* epsilon */
    { $$ = new std::vector<_i_stmt*>(); }
;

elseif:
    ELSE IF LPAR expr RPAR stmt
    { $$ = new elseif_s($4, $6); }
;

stmtlist:
    stmt stmtlist
    { $2->push_back($1); $$ = $2; }
  | /* epsilon */
    { $$ = new std::vector<_i_stmt*>(); }
;

stmt:
    LCUR stmtlist RCUR
    { $$ = new block_s($2); }
  | IF LPAR expr RPAR stmt elseiflist ELSE stmt
    { $$ = new if_s($3, $5, $6, $8); }
  | IF LPAR expr RPAR stmt elseiflist
    { $$ = new if_s($3, $5, $6, NULL); }
  | FOR LPAR ID IN expr RPAR stmt
    { $$ = new for_s($3, $5, $7); }
  | WHILE LPAR expr RPAR stmt
    { $$ = new while_s($3, $5); }
  | VAR ID ASN expr SEMI
    { $$ = new vardecl_s($2, $4); }
  | CONSTVAR ID ASN expr SEMI
    { $$ = new constvardecl_s($2, $4); }
;

rollmodlist:
    rollmodlist COMMA rollmod
    { $1->push_back($3); $$ = $1; }
  | rollmod
    { $$ = new std::vector<_i_expr*>(1, $1); }
;

rollmod:
    EXPLODE expr
    { $$ = new explode_e($2); }
  | DESPLODE expr
    { $$ = new desplode_e($2); }
  | ROLLAGAIN expr
    { $$ = new rollagain_e($2); }
;

funcdecl:
    FUNC ID LPAR paramlist RPAR LCUR stmtlist RETURN expr SEMI RCUR
    { $$ = new funcdecl_b($2, $4, $7, $9); }
  | FUNC ID LPAR           RPAR LCUR stmtlist RETURN expr SEMI RCUR
    { $$ = new funcdecl_b($2, NULL, $6, $8); }
;

callexpr:
    ID LPAR exprlist RPAR
    { $$ = new call_e($1, $3); }
  | ID LPAR          RPAR
    { $$ = new call_e($1, NULL); }
;

paramlist:
    paramlist COMMA param
    { $1->push_back($3); $$ = $1; }
  | param
    { $$ = new std::vector<param_b*>(1, $1); }
;

param:
    ID
    { $$ = new param_b($1); }
;

exprlist:
    exprlist COMMA expr
    { $1->push_back($3); $$ = $1; }
  | expr
    { $$ = new std::vector<_i_expr*>(1, $1); }
;

expr:
    ID
    { $$ = new id_e($1); }
  | INTLIT
    { $$ = new int_e($1); }
  | callexpr
    { $$ = $1; }
  
  | expr UNION      expr
    { $$ = new union_e($1, $3); }
  | expr COMPLEMENT expr
    { $$ = new complement_e($1, $3); }
  | expr INTERSECT  expr
    { $$ = new intersect_e($1, $3); }
    
  | expr PLUS expr
    { $$ = new plus_e($1, $3); }
  | expr MINUS expr
    { $$ = new minus_e($1, $3); }
  | expr MULT expr
    { $$ = new mult_e($1, $3); }
  | expr DIV expr
    { $$ = new div_e($1, $3); }
  | expr MOD expr
    { $$ = new mod_e($1, $3); }
  | LPAR expr RPAR
    { $$ = $2; }
    
  | expr GT expr
    { $$ = new gt_e($1, $3); }
  | expr EQGT expr
    { $$ = new eqgt_e($1, $3); }
  | expr LT expr
    { $$ = new lt_e($1, $3); }
  | expr EQLT expr
    { $$ = new eqlt_e($1, $3); }
  | expr EQ expr
    { $$ = new eq_e($1, $3); }
  | expr NEQ expr
    { $$ = new neq_e($1, $3); }
  | BANG expr
    { $$ = new not_e($2); }
    
  | LBRA expr TO expr RBRA
    { $$ = new to_e($2, $4); }
  | LBRA expr COLO expr COLO rollmodlist RBRA
    { $$ = new roll_e($2, $4, $6); }
  | LBRA expr COLO expr RBRA
    { $$ = new roll_e($2, $4, NULL); }
  | LBRA          RBRA
    { $$ = new pool_e(new std::vector<_i_expr*>()); }
  | LBRA exprlist RBRA
    { $$ = new pool_e($2); }
;

%%




