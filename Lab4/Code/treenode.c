#include "treenode.h"

struct TreeNode *TreeNodeSet(int type, int column, char *name, char *str, Value val, int childtype)
{
    struct TreeNode *r = (struct TreeNode *)malloc(sizeof(TreeNode));
    r->type = type;
    r->column = column;
    strcpy(r->name, name);
    strcpy(r->strval, str);
    if (strcmp(name, "INT") == 0)
    {
        r->val.ival = val.ival;
    }
    else if (strcmp(name, "FLOAT") == 0)
    {
        r->val.dval = val.dval;
    }
    else if (strcmp(name, "OCTAL") == 0)
    {
        r->val.ival = val.ival;
    }
    else if (strcmp(name, "HEXAL") == 0)
    {
        r->val.ival = val.ival;
    }
    else if (strcmp(name, "expFLOAT") == 0)
    {
        r->val.dval = val.dval;
    }
    r->childtype = childtype;
    r->isstrdef = 0;
    r->isfundec = 0;
    r->inh = Field_New();
    r->syn = Field_New();
    r->firstchild = NULL;
    r->nextsibling = NULL;
    r->parent = NULL;
    return r;
}

void TreeNodeInsert(struct TreeNode *r, int childnum, ...)
{
    if (childnum >= 1)
    {
        struct TreeNode *next = NULL;
        va_list children;
        va_start(children, childnum);
        for (int i = 0; i < childnum; i++)
        {
            next = (struct TreeNode *)(va_arg(children, TreeNode *));
            if (r->firstchild == NULL)
            {
                r->firstchild = next;
                next->parent = r;
            }
            else
            {
                struct TreeNode *fc = r->firstchild;
                while (fc->nextsibling != NULL)
                    fc = fc->nextsibling;
                fc->nextsibling = next;
                next->parent = r;
            }
        }
        va_end(children);
    }
}

void TreePrint(struct TreeNode *r, int retra_n)
{
    if (r->type == 0)
    {
        if (r->firstchild != NULL)
        {
            for (int i = 0; i < retra_n; i++)
            {
                printf("  ");
            }
            printf("%s (%d)\n", r->name, r->column);
            retra_n++;
            struct TreeNode *sub = r->firstchild;
            for (; sub != NULL; sub = sub->nextsibling)
            {
                TreePrint(sub, retra_n);
            }
            retra_n--;
        }
    }
    else if (r->type == 1)
    {
        for (int i = 0; i < retra_n; i++)
        {
            printf("  ");
        }
        if (strcmp(r->name, "ID") == 0)
        {
            printf("ID: %s\n", r->strval);
        }
        else if (strcmp(r->name, "TYPE") == 0)
        {
            printf("TYPE: %s\n", r->strval);
        }
        else if (strcmp(r->name, "INT") == 0)
        {
            printf("INT: %d\n", r->val.ival);
        }
        else if (strcmp(r->name, "FLOAT") == 0)
        {
            printf("FLOAT: %f\n", r->val.dval);
        }
        else if (strcmp(r->name, "OCTAL") == 0)
        {
            printf("INT: %d\n", r->val.ival);
        }
        else if (strcmp(r->name, "HEXAL") == 0)
        {
            printf("INT: %d\n", r->val.ival);
        }
        else if (strcmp(r->name, "expFLOAT") == 0)
        {
            printf("FLOAT: %f\n", r->val.dval);
        }
        else
        {
            printf("%s\n", r->name);
        }
    }
}

TreeNode *Childi(struct TreeNode *r, int i)
{
    if (r != NULL)
    {
        TreeNode *first = r->firstchild;
        if (i == 1)
        {
            return first;
        }
        else
        {
            while (i > 1 && first != NULL)
            {
                first = first->nextsibling;
                i--;
            }
            return first;
        }
    }
    else
        return NULL;
}