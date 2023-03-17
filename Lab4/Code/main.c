#include <stdio.h>
//#include "semantic.h"
//#include "intermediate.h"
#include "objectcode.h"
extern int lexicalerror;
extern int syntaxerror;

extern struct TreeNode *root;
extern void TreePrint(struct TreeNode *r, int retra_n);

extern int yyrestart();
extern int yyparse();

int main(int argc, char **argv)
{
    if (argc <= 1)
        return 1;
    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    if (lexicalerror == 0 && syntaxerror == 0)
    {
        begin_semanalysis(root);
        translate_begin(root, "out1.ir");
        Generate_begin(argv[2]);
    }
    return 0;
}