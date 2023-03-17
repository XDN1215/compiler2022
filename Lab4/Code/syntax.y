%locations
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

void yyerror(char* msg, ...);
#include "lex.yy.c"

int syntaxerror=0;
struct TreeNode* root = NULL;
%}

/* declared types */
%union {
    struct TreeNode* nodep;
}

/* declared tokens */
%token <nodep> ID
%token <nodep> SEMI COMMA
%token <nodep> LC RC
%token <nodep> INT OCTAL HEXAL illegal_INT illegal_OCTAL illegal_HEXAL
%token <nodep> FLOAT expFLOAT illegal_FLOAT illegal_expFLOAT
%token <nodep> TYPE
%token <nodep> STRUCT RETURN IF ELSE WHILE

%token <nodep> ASSIGNOP
%token <nodep> OR
%token <nodep> AND 
%token <nodep> RELOP
%token <nodep> PLUS MINUS
%token <nodep> STAR DIV
%token <nodep> NOT
%token <nodep> DOT LP RP LB RB


%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS 
%left STAR DIV
%right NOT HIGHER_THAN_MINUS
%left DOT LP RP LB RB

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* declared non-terminals */
%type <nodep> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args 

%%
//High-level Definitions
Program : ExtDefList { $$=TreeNodeSet(0, @$.first_line, "Program", "null", (Value)0, 1);TreeNodeInsert($$, 1, $1);root=$$;}
    ;

ExtDefList : ExtDef ExtDefList { $$=TreeNodeSet(0, @$.first_line, "ExtDefList" , "null", (Value)0, 1);TreeNodeInsert($$, 2, $1, $2);}
    | { $$=TreeNodeSet(0, @$.first_line, "ExtDefList", "null", (Value)0, 2);}
    ;

ExtDef : Specifier ExtDecList SEMI { $$=TreeNodeSet(0, @$.first_line, "ExtDef", "null", (Value)0, 1);TreeNodeInsert($$, 3, $1, $2, $3);}
    | Specifier SEMI { $$=TreeNodeSet(0, @$.first_line, "ExtDef", "null", (Value)0, 2);TreeNodeInsert($$, 2, $1, $2);}
    | Specifier FunDec CompSt { $$=TreeNodeSet(0, @$.first_line, "ExtDef", "null", (Value)0, 3);TreeNodeInsert($$, 3, $1, $2, $3);}
    | Specifier FunDec SEMI { $$=TreeNodeSet(0, @$.first_line, "ExtDef", "null", (Value)0, 4);TreeNodeInsert($$, 3, $1, $2, $3);}
//error
    | Specifier error SEMI {yyerror("Error", 0, @2.first_line, "Syntax error1");}
    | error Specifier SEMI {yyerror("Error", 0, @1.first_line, "Syntax error2");}
    | error SEMI {yyerror("Error", 0, @1.first_line, "Syntax error3");}
    //| Specifier error CompSt {yyerror("Error", 0, @$.first_line, "Syntax error before compst: ");}
    | Specifier FunDec error SEMI {yyerror("Error", 0, @3.first_line, "Syntax error4");}
    //| Specifier FunDec error {yyerror("Error", 0, @3.first_line, "Syntax error4");}
    | Specifier error CompSt {yyerror("Error", 0, @2.first_line, "Syntax error5");}
    | error RP {yyerror("Error", 0, @1.first_line, "Syntax error6");}//
    | error RC {yyerror("Error", 0, @1.first_line, "Syntax error7");}
    //| error Specifier error CompSt {yyerror("Error", 0, @1.first_line, "Syntax error8");}//}
    ;

ExtDecList : VarDec { $$=TreeNodeSet(0, @$.first_line, "ExtDecList", "null", (Value)0, 1);TreeNodeInsert($$, 1, $1);}
    | VarDec COMMA ExtDecList { $$=TreeNodeSet(0, @$.first_line, "ExtDecList", "null", (Value)0, 2);TreeNodeInsert($$, 3, $1, $2, $3);}
//error
    | VarDec ExtDecList {yyerror("Error", 0, @2.first_line, "Syntax error9");}
    //| VarDec COMMA error {yyerror("Error", 0, @$.first_line, "Syntax error after \",\": ");}
    //| error COMMA ExtDecList {yyerror("Error", 0, @$.first_line, "Syntax error before \",\": ");}
    ;

//Specifiers
Specifier : TYPE { $$=TreeNodeSet(0, @$.first_line, "Specifier", "null", (Value)0, 1);TreeNodeInsert($$, 1, $1);}
    | StructSpecifier { $$=TreeNodeSet(0, @$.first_line, "Specifier", "null", (Value)0, 2);TreeNodeInsert($$, 1, $1);}
    ;

StructSpecifier : STRUCT OptTag LC DefList RC { $$=TreeNodeSet(0, @$.first_line, "StructSpecifier", "null", (Value)0, 1);TreeNodeInsert($$,5,$1,$2,$3,$4,$5);}
    | STRUCT Tag { $$=TreeNodeSet(0, @$.first_line, "StructSpecifier", "null", (Value)0, 2);TreeNodeInsert($$, 2, $1, $2);}
//error
    //| STRUCT error ID LC DefList RC{yyerror("Error", 0, @$.first_line, "Syntax error after struct: ");}
    | STRUCT OptTag LC error RC {yyerror("Error", 0, @4.first_line, "Syntax error10");}
    //| error Tag {yyerror("Error", 0, @1.first_line, "gSyntax error");}
    //| STRUCT error %prec LOWER_THAN_ID {yyerror("Error", 0, @$.first_line, "Syntax error after struct: ");}
    ;

OptTag : ID { $$=TreeNodeSet(0, @$.first_line, "OptTag", "null", (Value)0, 1);TreeNodeInsert($$, 1, $1);}
    | { $$=TreeNodeSet(0, @$.first_line, "OptTag", "null", (Value)0, 2);}
    ;

Tag : ID { $$=TreeNodeSet(0, @$.first_line, "Tag", "null", (Value)0, 1);TreeNodeInsert($$, 1, $1);}
    ;

//Declarators
VarDec : ID { $$=TreeNodeSet(0, @$.first_line, "VarDec", "null", (Value)0, 1);TreeNodeInsert($$, 1, $1);}
    | VarDec LB INT RB { $$=TreeNodeSet(0, @$.first_line, "VarDec", "null", (Value)0, 2);TreeNodeInsert($$,4,$1,$2,$3,$4);}
//error
    | VarDec LB error RB {yyerror("Error", 1, @3.first_line, "Syntax error after \"(\": ", @2.first_line);}
    //| VarDec LB error %prec LOWER_THAN_RB {yyerror("Error", 1, @$.first_line, "Syntax error after \"(\": ", @2.first_line);}
    ;

FunDec : ID LP VarList RP { $$=TreeNodeSet(0, @$.first_line, "FunDec", "null", (Value)0, 1);TreeNodeInsert($$,4,$1,$2,$3,$4);}
    | ID LP RP { $$=TreeNodeSet(0, @$.first_line, "FunDec", "null", (Value)0, 2);TreeNodeInsert($$,3,$1,$2,$3);}
//error
    | ID LP error RP {yyerror("Error", 0, @3.first_line, "Syntax error11");}
    | error LP VarList RP {}{yyerror("Error", 0, @1.first_line, "Syntax error12");}
    //| ID error RP {yyerror("Error", 0, @1.first_line, "Illegal VarList");}
    ;

VarList : ParamDec COMMA VarList { $$=TreeNodeSet(0, @$.first_line, "VarList", "null", (Value)0, 1);TreeNodeInsert($$,3,$1,$2,$3);}
    | ParamDec { $$=TreeNodeSet(0, @$.first_line, "VarList", "null", (Value)0, 2);TreeNodeInsert($$, 1, $1);}
    ;

ParamDec : Specifier VarDec { $$=TreeNodeSet(0, @$.first_line, "ParamDec", "null", (Value)0, 1);TreeNodeInsert($$, 2, $1, $2);}
    ;

//Statements
CompSt : LC DefList StmtList RC { $$=TreeNodeSet(0, @$.first_line, "CompSt", "null", (Value)0, 1);TreeNodeInsert($$,4,$1,$2,$3,$4);}
//error
    //| LC error RC {yyerror("Error", 0, @2.first_line, "Syntax error");}
    | error RC {yyerror("Error", 0, @1.first_line, "Syntax error13");}
    ;

StmtList : Stmt StmtList { $$=TreeNodeSet(0, @$.first_line, "StmtList", "null", (Value)0, 1);TreeNodeInsert($$,2,$1,$2);}
    | { $$=TreeNodeSet(0, @$.first_line, "StmtList", "null", (Value)0, 2);}
    ;

Stmt : Exp SEMI { $$=TreeNodeSet(0, @$.first_line, "Stmt", "null", (Value)0, 1);TreeNodeInsert($$,2,$1,$2);}
    | CompSt { $$=TreeNodeSet(0, @$.first_line, "Stmt", "null", (Value)0, 2);TreeNodeInsert($$, 1, $1);}
    | RETURN Exp SEMI { $$=TreeNodeSet(0, @$.first_line, "Stmt", "null", (Value)0, 3);TreeNodeInsert($$,3,$1,$2,$3);}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE { $$=TreeNodeSet(0, @$.first_line, "Stmt", "null", (Value)0, 4);TreeNodeInsert($$,5,$1,$2,$3,$4,$5);}
    | IF LP Exp RP Stmt ELSE Stmt { $$=TreeNodeSet(0, @$.first_line, "Stmt", "null", (Value)0, 5);TreeNodeInsert($$,7,$1,$2,$3,$4,$5,$6,$7);}
    | WHILE LP Exp RP Stmt { $$=TreeNodeSet(0, @$.first_line, "Stmt", "null", (Value)0, 6);TreeNodeInsert($$,5,$1,$2,$3,$4,$5);}
//error
    //| error WHILE LP Exp RP {yyerror("Error", 0, @$.first_line, "MIssing \";\"");}
    //| Exp WHILE LP Exp RP {yyerror("Error", 0, @2.first_line, "MIssing \";\"");}
    | Exp error {yyerror("Error", 0, @1.first_line, "Syntax error14");}
    | error SEMI {yyerror("Error", 0, @1.first_line, "Syntax error15");}
    | Exp error SEMI {yyerror("Error", 0, @2.first_line, "Syntax error16");}
    | RETURN error SEMI {yyerror("Error", 0, @2.first_line, "Syntax error17");}
    | RETURN Exp error {yyerror("Error", 0, @3.first_line, "Syntax error18");}
    //| error LP Exp RP Stmt %prec LOWER_THAN_ELSE {yyerror("Error", 0, @$.first_line, "\"IF\" should be entered");}
    //| error LP Exp RP Stmt ELSE Stmt {yyerror("Error", 0, @$.first_line, "\"IF\" should be entered");}
    //| WHILE LP Exp RP error {yyerror("Error", 0, @$.first_line, "MIssing Statement");}
    | IF LP error RP Stmt %prec LOWER_THAN_ELSE {yyerror("Error", 0, @3.first_line, "Syntax error19");}
    | IF LP error RP Stmt ELSE Stmt {yyerror("Error", 0, @3.first_line, "Syntax error20");}
    | IF error Stmt %prec LOWER_THAN_ELSE {yyerror("Error", 0, @2.first_line, "Syntax error21");}
    | IF error ELSE Stmt {yyerror("Error", 0, @2.first_line, "Syntax error22");}
    | WHILE LP error RP Stmt {yyerror("Error", 0, @2.first_line, "Syntax error23");}
    | WHILE error RP Stmt {yyerror("Error", 0, @2.first_line, "Syntax error24");}
    | WHILE error RC {yyerror("Error", 0, @2.first_line, "Syntax error25");}
    ;

//Local Definitions
DefList : Def DefList { $$=TreeNodeSet(0, @$.first_line, "DefList", "null", (Value)0, 1);TreeNodeInsert($$,2,$1,$2);}
    | { $$=TreeNodeSet(0, @$.first_line, "DefList", "null", (Value)0, 2);}
    ;

Def : Specifier DecList SEMI { $$=TreeNodeSet(0, @$.first_line, "Def", "null", (Value)0, 1);TreeNodeInsert($$,3,$1,$2,$3);}
//error
    //| error DecList SEMI %prec Defab {yyerror("Error", 0, @1.first_line, "fSyntax error");}
    | Specifier error SEMI {yyerror("Error", 0, @2.first_line, "Syntax error26");}
    | Specifier DecList error {yyerror("Error", 0, @3.first_line, "Syntax error27");}
    //| Specifier DecList %prec LOWER_THAN_SEMI {yyerror("Error", 0, @2.first_line, "dMissing \";\"");}
    ;

DecList : Dec { $$=TreeNodeSet(0, @$.first_line, "DecList", "null", (Value)0, 1);TreeNodeInsert($$, 1, $1);}
    | Dec COMMA DecList { $$=TreeNodeSet(0, @$.first_line, "DecList", "null", (Value)0, 2);TreeNodeInsert($$,3,$1,$2,$3);}
//error  
    //| Dec COMMA error {yyerror("Error", 0, @3.first_line, "Syntax error");}
    //| Dec error DecList{yyerror("Error", 0, @2.first_line, "Missing \",\"");}
    | error COMMA DecList {yyerror("Error", 0, @1.first_line, "Syntax error28");}
    ;

Dec : VarDec { $$=TreeNodeSet(0, @$.first_line, "Dec", "null", (Value)0, 1);TreeNodeInsert($$, 1, $1);}
    | VarDec ASSIGNOP Exp { $$=TreeNodeSet(0, @$.first_line, "Dec", "null", (Value)0, 2);TreeNodeInsert($$,3,$1,$2,$3);}
//error
    //| VarDec ASSIGNOP error {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    //| VarDec error Exp {yyerror("Error", 0, @2.first_line, "Missing \"=\"");}
    | error ASSIGNOP Exp {yyerror("Error", 0, @1.first_line, "Syntax error29");}
    ;

//Expressions
Exp : Exp ASSIGNOP Exp { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 1);TreeNodeInsert($$,3,$1,$2,$3);}
    | Exp AND Exp { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 2);TreeNodeInsert($$,3,$1,$2,$3);}
    | Exp OR Exp { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 3);TreeNodeInsert($$,3,$1,$2,$3);}
    | Exp RELOP Exp { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 4);TreeNodeInsert($$,3,$1,$2,$3);}
    | Exp PLUS Exp { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 5);TreeNodeInsert($$,3,$1,$2,$3);}
    | Exp MINUS Exp { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 6);TreeNodeInsert($$,3,$1,$2,$3);}
    | Exp STAR Exp { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 7);TreeNodeInsert($$,3,$1,$2,$3);}
    | Exp DIV Exp { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 8);TreeNodeInsert($$,3,$1,$2,$3);}
    | LP Exp RP { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 9);TreeNodeInsert($$,3,$1,$2,$3);}
    | MINUS Exp %prec HIGHER_THAN_MINUS { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 10);TreeNodeInsert($$,2,$1,$2);}
    | NOT Exp { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 11);TreeNodeInsert($$,2,$1,$2);}
    | ID LP Args RP { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 12);TreeNodeInsert($$,4,$1,$2,$3,$4);}
    | ID LP RP { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 13);TreeNodeInsert($$,3,$1,$2,$3);}
    | Exp LB Exp RB { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 14);TreeNodeInsert($$,4,$1,$2,$3,$4);}
    | Exp DOT ID { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 15);TreeNodeInsert($$,3,$1,$2,$3);}
    | ID { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 16);TreeNodeInsert($$, 1, $1);}
    | INT { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 17);TreeNodeInsert($$, 1, $1);}
    | FLOAT { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 18);TreeNodeInsert($$, 1, $1);}
    | OCTAL { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 19);TreeNodeInsert($$, 1, $1);}
    | HEXAL { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 20);TreeNodeInsert($$, 1, $1);}
    | expFLOAT { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 21);TreeNodeInsert($$, 1, $1);}
    | illegal_OCTAL { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 22);TreeNodeInsert($$, 1, $1);}
    | illegal_HEXAL { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 23);TreeNodeInsert($$, 1, $1);}
    | illegal_INT { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 24);TreeNodeInsert($$, 1, $1);}
    | illegal_FLOAT { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 25);TreeNodeInsert($$, 1, $1);}
    | illegal_expFLOAT { $$=TreeNodeSet(0, @$.first_line, "Exp", "null", (Value)0, 26);TreeNodeInsert($$, 1, $1);}
//error
    | Exp ASSIGNOP error {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | Exp AND error {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | Exp OR error {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | Exp RELOP error {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | Exp PLUS error {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | Exp MINUS error {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | Exp STAR error {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | Exp DIV error {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | LP error RP {yyerror("Error", 0, @2.first_line, "Illegal expression");}
    | MINUS error {yyerror("Error", 0, @2.first_line, "Illegal expression");}
    | NOT error {yyerror("Error", 0, @2.first_line, "Illegal expression");}
    | ID LP error RP {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | ID LP error SEMI {yyerror("Error", 0, @3.first_line, "Missing \")\"");}
    | Exp LB error RB {yyerror("Error", 0, @3.first_line, "Illegal expression");}
    | Exp LB error SEMI {yyerror("Error", 0, @3.first_line, "Missing \"]\"");}
    ;

Args : Exp COMMA Args {$$=TreeNodeSet(0, @$.first_line, "Args", "null", (Value)0, 1); TreeNodeInsert($$,3,$1,$2,$3);}
    | Exp {$$=TreeNodeSet(0, @$.first_line, "Args", "null", (Value)0, 2); TreeNodeInsert($$, 1, $1);}
    ;
%%

void yyerror(char* msg, ...) {
    syntaxerror=1;
    if(strcmp(msg, "Error")==0){
        va_list msgs;
        va_start(msgs, msg);
        int type = (int)(va_arg(msgs, int));
        int line=(int)(va_arg(msgs, int));
        if(type==0){
            char* msg1=(char*)(va_arg(msgs, char*));
            printf("Error type B at Line %d: %s.\n", line, msg1);
        }
        else if (type==1){
            char* msg1=(char*)(va_arg(msgs, char*));
            int line2=(int)va_arg(msgs, int);
            printf("Error type B at Line %d: %s %d.\n", line, msg1, line2);
        }
        va_end(msgs);
    }
    else if(strcmp(msg, "syntax error")!=0){
        printf("%s\n", msg);
    }
}