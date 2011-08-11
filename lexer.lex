%{
  #include <iostream>
  #include <node.hpp>
  #include <parser.hpp>

  int yyline = 0;
  int yyposs = 0;

#ifdef DEBUG
#define yyposs_inc yyposs += strlen(yytext); std::cout << yytext;
#else
#define yyposs_inc yyposs += strlen(yytext);
#endif

%}

num [0-9]
id  [a-zA-Z_]+[a-zA-Z0-9_]*
eol (\n|\r|\r\n)
ws  ([ \t])+

nonstar [^*]
nonstarslash [^*/]

c_comment "/*"{nonstar}*("*"({nonstarslash}{nonstar}*)?)*"*/"
c_com "//".*$

%%

"if"       { yyposs_inc; return IF;       }
"else"     { yyposs_inc; return ELSE;     }
"while"    { yyposs_inc; return WHILE;    }
"in"       { yyposs_inc; return IN;       }
"for"      { yyposs_inc; return FOR;      }
"var"      { yyposs_inc; return VAR;      }
"constvar" { yyposs_inc; return CONSTVAR; }
"func"     { yyposs_inc; return FUNC;     }
"return"   { yyposs_inc; return RETURN;   }

"union"      { yyposs_inc; return UNION;      }
"complement" { yyposs_inc; return COMPLEMENT; }
"intersect"  { yyposs_inc; return INTERSECT;  }
"explode"    { yyposs_inc; return EXPLODE;    }
"desplode"   { yyposs_inc; return DESPLODE;   }
"rollagain"  { yyposs_inc; return ROLLAGAIN;  }

"="  { yyposs_inc; return ASN;   }
"==" { yyposs_inc; return EQ;    }
"!=" { yyposs_inc; return NEQ;   }
">"  { yyposs_inc; return GT;    }
"<"  { yyposs_inc; return LT;    }
">=" { yyposs_inc; return EQGT;  }
"<=" { yyposs_inc; return EQLT;  }
"->" { yyposs_inc; return TO;    }
"!"  { yyposs_inc; return BANG;  }

"("  { yyposs_inc; return LPAR;  }
")"  { yyposs_inc; return RPAR;  }
"["  { yyposs_inc; return LBRA;  }
"]"  { yyposs_inc; return RBRA;  }
"{"  { yyposs_inc; return LCUR;  }
"}"  { yyposs_inc; return RCUR;  }
","  { yyposs_inc; return COMMA; }
";"  { yyposs_inc; return SEMI;  }
":"  { yyposs_inc; return COLO;  }

"+"  { yyposs_inc; return PLUS;  }
"-"  { yyposs_inc; return MINUS; }
"*"  { yyposs_inc; return MULT;  }
"/"  { yyposs_inc; return DIV;   }
"%"  { yyposs_inc; return MOD;   }

{num}+ { yyposs_inc; yylval.token_t = token::get(yytext, yyline, yyposs); return INTLIT; }
{id}   { yyposs_inc; yylval.token_t = token::get(yytext, yyline, yyposs); return ID;     }

{c_comment} { yyposs_inc; }
{c_com}     { yyposs_inc; }
{ws}        { yyposs_inc; }
{eol}       {
  std::cout << "... " << std::flush;
#ifdef DEBUG
  std::cout << std::endl;
#endif 
  yyposs = 0; yyline++;
}
. { std::cout << "Illegal character: " << yytext << std::endl; }

%%

int yywrap(void) {
  return 1;
}

