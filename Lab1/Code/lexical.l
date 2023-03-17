%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "syntax.tab.h"
int yycolumn = 1;
#define YY_USER_ACTION \
yylloc.first_line = yylloc.last_line = yylineno; \
yylloc.first_column = yycolumn; \
yylloc.last_column = yycolumn + yyleng - 1; \
yycolumn += yyleng;

int lexicalerror=0;//0-没有词法错误；1-有词法错误
extern int syntaxerror;//0-没有语法错误；1-有语法错误

typedef union Value{
    int ival;
    double dval;
}Value;//数值
typedef struct TreeNode{
    int type;//1-词法单元/0-语法单元
    int column;//行号
    char name[32];//名称
    char strval[32];//内容
    union Value val;
    struct TreeNode* firstchild, * nextsibling;
    struct TreeNode* parent;
}TreeNode;

//语法树结点的初始化
struct TreeNode* TreeNodeSet(int type, int column, char* name, char* str, Value val) {
    struct TreeNode* r=(struct TreeNode*)malloc(sizeof(TreeNode));
    r->type = type;
    r->column = column;
    strcpy(r->name, name);
    strcpy(r->strval, str);
    if (strcmp(name, "INT") == 0) {
        r->val.ival = val.ival;
    }
    else if (strcmp(name, "FLOAT") == 0) {
        r->val.dval = val.dval;
    }
    else if (strcmp(name, "OCTAL") == 0) {
        r->val.ival = val.ival;
    }
    else if (strcmp(name, "HEXAL") == 0) {
        r->val.ival = val.ival;
    }
    else if (strcmp(name, "expFLOAT") == 0) {
        r->val.dval = val.dval;
    }
    r->firstchild = NULL;
    r->nextsibling = NULL;
    r->parent = NULL;
    return r;
}
%}
%option yylineno
blank [ \t\r]
BLANK {blank}+
digit [0-9]
digits [0-9]+
letter_ [a-zA-Z_]
INT 0|[1-9]({digit}*)
illegal_INT ([0+][0-7]*[8-9]+[0-9]*)
OCTAL 0([0-7]+)
illegal_OCTAL 0([0-7]*[8-9a-fA-F]+[0-9a-fA-F]*)
HEXAL 0[xX]([0-9a-fA-F]+)
illegal_HEXAL 0[xX]([0-9a-fA-F]*[g-zG-Z]+[0-9a-fA-F]*)
FLOAT {digits}\.{digits}
illegal_FLOAT {digit}*\.{digit}[\.0-9]*
expFLOAT (({digit}+\.{digit}*)|({digit}*\.{digit}+))[eE][+-]?{digit}+
illegal_expFLOAT ({digits}\.{digits}|\.{digits}|{digits}\.|{digits})([eE][+-]?)|({digits}\.{digits}*[eE][+-]?{digits}\.{digits})|{illegal_FLOAT}([eE][+-]?){digit}*
ID {letter_}({letter_}|{digit})*
SEMI ";"
COMMA ","
ASSIGNOP "="
RELOP ">"|"<"|">="|"<="|"=="|"!="
PLUS "+"
MINUS "-"
STAR "*"
DIV "/"
AND "&&"
OR "||"
DOT "."
NOT "!"
TYPE "int"|"float"
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT "struct"
RETURN "return"
IF "if"
ELSE "else"
WHILE "while"
ANNO "//"
l_ANNO "/*"
%%
{BLANK} {}
{INT} { 
    yylval.nodep=TreeNodeSet(1, yycolumn, "INT", yytext, (Value)(Value)atoi(yytext)); return INT; }
{OCTAL} { 
    char* endstr;
    int value=(int)strtol(yytext, &endstr, 8);
    yylval.nodep=TreeNodeSet(1, yycolumn, "OCTAL", yytext, (Value)value); return OCTAL; }
{HEXAL} { 
    char* endstr;
    int value=(int)strtol(yytext, &endstr, 16);
    yylval.nodep=TreeNodeSet(1, yycolumn, "HEXAL", yytext, (Value)value); return HEXAL; }
{FLOAT} {
    yylval.nodep=TreeNodeSet(1, yycolumn, "FLOAT", yytext, (Value)atof(yytext)); return FLOAT; }
{expFLOAT} {
    yylval.nodep=TreeNodeSet(1, yycolumn, "FLOAT", yytext, (Value)atof(yytext)); return expFLOAT; }
{TYPE} { yylval.nodep=TreeNodeSet(1, yycolumn, "TYPE", yytext, (Value)0); return TYPE; }
{STRUCT} { yylval.nodep=TreeNodeSet(1, yycolumn, "STRUCT", yytext, (Value)0); return STRUCT; }
{RETURN} { yylval.nodep=TreeNodeSet(1, yycolumn, "RETURN", yytext, (Value)0); return RETURN; }
{IF} { yylval.nodep=TreeNodeSet(1, yycolumn, "IF", yytext, (Value)0); return IF; }
{ELSE} { yylval.nodep=TreeNodeSet(1, yycolumn, "ELSE", yytext, (Value)0); return ELSE; }
{WHILE} { yylval.nodep=TreeNodeSet(1, yycolumn, "WHILE", yytext, (Value)0); return WHILE; }
{ID} { yylval.nodep=TreeNodeSet(1, yycolumn, "ID", yytext, (Value)0); return ID; }
{SEMI} { yylval.nodep=TreeNodeSet(1, yycolumn, "SEMI", yytext, (Value)0); return SEMI; }
{COMMA} { yylval.nodep=TreeNodeSet(1, yycolumn, "COMMA", yytext, (Value)0); return COMMA; }
{ASSIGNOP} { yylval.nodep=TreeNodeSet(1, yycolumn, "ASSIGNOP", yytext, (Value)0); return ASSIGNOP; }
{RELOP} { yylval.nodep=TreeNodeSet(1, yycolumn, "RELOP", yytext, (Value)0); return RELOP; }
{PLUS} { yylval.nodep=TreeNodeSet(1, yycolumn, "PLUS", yytext, (Value)0); return PLUS; }
{MINUS} { yylval.nodep=TreeNodeSet(1, yycolumn, "MINUS", yytext, (Value)0); return MINUS; }
{STAR} { yylval.nodep=TreeNodeSet(1, yycolumn, "STAR", yytext, (Value)0); return STAR; }
{DIV} { yylval.nodep=TreeNodeSet(1, yycolumn, "DIV", yytext, (Value)0); return DIV; }
{AND} { yylval.nodep=TreeNodeSet(1, yycolumn, "AND", yytext, (Value)0); return AND; }
{OR} { yylval.nodep=TreeNodeSet(1, yycolumn, "OR", yytext, (Value)0); return OR; }
{DOT} { yylval.nodep=TreeNodeSet(1, yycolumn, "DOT", yytext, (Value)0); return DOT; }
{NOT} { yylval.nodep=TreeNodeSet(1, yycolumn, "NOT", yytext, (Value)0); return NOT; }
{LP} { yylval.nodep=TreeNodeSet(1, yycolumn, "LP", yytext, (Value)0); return LP; }
{RP} { yylval.nodep=TreeNodeSet(1, yycolumn, "RP", yytext, (Value)0); return RP; }
{LB} { yylval.nodep=TreeNodeSet(1, yycolumn, "LB", yytext, (Value)0); return LB; }
{RB} { yylval.nodep=TreeNodeSet(1, yycolumn, "RB", yytext, (Value)0); return RB; }
{LC} { yylval.nodep=TreeNodeSet(1, yycolumn, "LC", yytext, (Value)0); return LC; }
{RC} { yylval.nodep=TreeNodeSet(1, yycolumn, "RC", yytext, (Value)0); return RC; }
{ANNO} { 
    char c = input();while (c != '\n') c = input(); }
{l_ANNO} { 
    char seek1 = input();
    char seek2 = input();
    while(!((seek1=='*') && (seek2== '/'))){
        seek1 = seek2;
        seek2 = input();
        if(seek2=='\0'){
            printf("Error type B at Line %d: No match annotator \"/*\".\n", yylineno);
            syntaxerror=1;
            break;
        }
    } }
{illegal_INT} { 
    lexicalerror=1; printf("Error type A at Line %d: Illegal INT \'%s\'.\n", yylineno, yytext);
    yylval.nodep=TreeNodeSet(1, yycolumn, "illegal_INT", yytext, (Value)0); return illegal_INT; }
{illegal_OCTAL} { 
    lexicalerror=1; printf("Error type A at Line %d: Illegal OCTAL \'%s\'.\n", yylineno, yytext);
    yylval.nodep=TreeNodeSet(1, yycolumn, "illegal_OCTAL", yytext, (Value)0); return illegal_OCTAL; }
{illegal_HEXAL} { 
    lexicalerror=1; printf("Error type A at Line %d: Illegal HEXAL \'%s\'.\n", yylineno, yytext); 
    yylval.nodep=TreeNodeSet(1, yycolumn, "illegal_HEXAL", yytext, (Value)0); return illegal_HEXAL; }
{illegal_expFLOAT} { 
    lexicalerror=1; printf("Error type A at Line %d: Illegal expFLOAT \'%s\'.\n", yylineno, yytext);
    yylval.nodep=TreeNodeSet(1, yycolumn, "illegal_expFLOAT", yytext, (Value)0); return illegal_expFLOAT; }
{illegal_FLOAT} { 
    lexicalerror=1; printf("Error type A at Line %d: Illegal FLOAT \'%s\'.\n", yylineno, yytext);
    yylval.nodep=TreeNodeSet(1, yycolumn, "illegal_FLOAT", yytext, (Value)0); return illegal_FLOAT; }
\n { yycolumn = 1; }
. { lexicalerror=1; printf("Error type A at Line %d: Mysterious characters \'%s\'.\n", yylineno, yytext); }
%%