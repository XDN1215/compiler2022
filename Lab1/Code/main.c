#include <stdio.h>

extern int lexicalerror;
extern int syntaxerror;

extern struct TreeNode* root;
extern void TreePrint(struct TreeNode* r, int retra_n);

extern int yyrestart();
extern int yyparse();

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    if(lexicalerror==0 && syntaxerror==0)TreePrint(root,0);//既没有词法错误也没有语法错误，就打印语法树
    return 0;
}