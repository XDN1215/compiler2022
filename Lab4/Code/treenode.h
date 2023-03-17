#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "symbolTable.h"

typedef union Value
{
    int ival;
    double dval;
} Value;
typedef struct TreeNode
{
    int type;
    int column;
    char name[32];
    char strval[32];
    union Value val;
    int childtype;
    bool isstrdef;
    bool isfundec;
    FieldListp syn;
    FieldListp inh;
    struct TreeNode *firstchild, *nextsibling;
    struct TreeNode *parent;
} TreeNode;

struct TreeNode *TreeNodeSet(int type, int column, char *name, char *str, Value val, int childtype);

void TreeNodeInsert(struct TreeNode *r, int childnum, ...);

void TreePrint(struct TreeNode *r, int retra_n);

TreeNode *Childi(struct TreeNode *r, int i);