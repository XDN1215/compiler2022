#include "treenode.h"

unsigned int unsignedinthash_pjw(char *name)
{
    unsigned int val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i = val & ~SYMBOL_TABLE_SIZE) //符号表的大小
            val = (val ^ (i >> 12)) & 0x3fff;
    }
    return val;
}

void HashTable_Initial(SymbolTable st)
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        st[i] = NULL;
    }

    SymbolNodep readp = SymbolNode_New();
    strcpy(readp->name, "read");
    readp->deepth = 0;
    readp->kind_ = FUNCTIONDEF;
    readp->type->kind = FUNCTIONDEF;
    readp->type->uval.function.paramn = 0;
    readp->type->uval.function.params = NULL;
    readp->type->uval.function.return_type = Type_New();
    readp->type->uval.function.return_type->kind = BASIC;
    readp->type->uval.function.return_type->uval.basic = 0;
    HashTable_Insert(st, readp);

    SymbolNodep writep = SymbolNode_New();
    strcpy(writep->name, "write");
    writep->deepth = 0;
    writep->kind_ = FUNCTIONDEF;
    writep->type->kind = FUNCTIONDEF;
    writep->type->uval.function.paramn = 1;
    writep->type->uval.function.params = Field_New();
    writep->type->uval.function.params->type->kind = BASIC;
    writep->type->uval.function.params->type->uval.basic = 0;
    writep->type->uval.function.return_type = Type_New();
    writep->type->uval.function.return_type->kind = BASIC;
    writep->type->uval.function.return_type->uval.basic = 0;
    HashTable_Insert(st, writep);
}

SymbolNodep HashTable_Search(int para, SymbolTable st, char *name, Kind_ k, int deepth, Kind t)
{ //不同para，对应查找时的不同标准
    unsigned int key = unsignedinthash_pjw(name);
    SymbolNodep snode = st[key];
    switch (para)
    {
    case 0:
        while (snode != NULL)
        {
            if (sameStr(name, snode->name))
            {
                return snode;
            }
            snode = snode->next;
        }
        break;
    case 1:
        while (snode != NULL)
        {
            if (sameStr(name, snode->name) && snode->kind_ == k)
            {
                return snode;
            }
            snode = snode->next;
        }
        break;
    case 2:
        while (snode != NULL)
        {
            if (sameStr(name, snode->name) && snode->kind_ == k && snode->deepth == deepth)
            {
                return snode;
            }
            snode = snode->next;
        }
        break;
    case 3:
        while (snode != NULL)
        {
            if (sameStr(name, snode->name) && snode->kind_ == k && snode->deepth == deepth && snode->type->kind == t)
            {
                return snode;
            }
            snode = snode->next;
        }
        break;
    case 4:
        while (snode != NULL)
        {
            if (sameStr(name, snode->name) && snode->deepth == deepth)
            {
                return snode;
            }
            snode = snode->next;
        }
        break;
    default:
        break;
    }
    return NULL;
}

bool HashTable_Insert(SymbolTable st, SymbolNodep sn)
{
    unsigned int key = unsignedinthash_pjw(sn->name);
    sn->next = st[key];
    if (st[key] != NULL)
    {
        st[key]->prev = sn;
    }
    st[key] = sn;
    //printf("---------------------------------------------------------Insert%s\n", sn->name);
    return true;
}

bool HashTable_Remove(SymbolTable st, SymbolNodep sn)
{
    SymbolNodep snext = sn;
    while (snext != NULL)
    {
        sn = snext;
        snext = snext->snext;
        if (sn->prev != NULL)
            sn->prev->next = sn->next;
        if (sn->next != NULL)
            sn->next->prev = sn->prev;
    }
    return true;
}

Typep Type_New()
{
    Typep p = (Typep)malloc(sizeof(Type));
    p->kind = NOTHING; // NOTHING
    p->uval.structure = NULL;
    p->width = 0;
    return p;
}

Typep Type_Set(Typep t)
{
    if (t != NULL)
    {
        Typep type = (Typep)malloc(sizeof(Type));
        type->kind = t->kind;
        switch (t->kind)
        {
        case BASIC:
            type->uval.basic = t->uval.basic;
            break;
        case ARRAY:
            type->uval.array.elem = Type_Set(t->uval.array.elem);
            type->uval.array.size = t->uval.array.size;
            break;
        case STRUCTURE:
            type->uval.structure = FieldList_Set(t->uval.structure);
            break;
        case FUNCTIONDEC:
            type->uval.function.return_type = Type_Set(t->uval.function.return_type);
            type->uval.function.paramn = t->uval.function.paramn;
            type->uval.function.params = FieldList_Set(t->uval.function.params);
            break;
        case FUNCTIONDEF:
            type->uval.function.return_type = Type_Set(t->uval.function.return_type);
            type->uval.function.paramn = t->uval.function.paramn;
            type->uval.function.params = FieldList_Set(t->uval.function.params);
            break;
        default:
            break;
        }
        return type;
    }
    else
        return NULL;
}

FieldListp Field_New()
{
    FieldListp p = (FieldListp)malloc(sizeof(FieldList));
    strcpy(p->fieldname, "*");
    p->type = Type_New();
    p->tail = NULL;
    return p;
}

FieldListp Field_Set(FieldListp fp)
{
    if (fp != NULL)
    {
        FieldListp p = (FieldListp)malloc(sizeof(FieldList));
        strcpy(p->fieldname, fp->fieldname);
        p->type = Type_Set(fp->type);
        p->tail = NULL;
        return p;
    }
    else
        return NULL;
}

FieldListp FieldList_Set(FieldListp fp)
{
    if (fp != NULL)
    {
        FieldListp p = (FieldListp)malloc(sizeof(FieldList));
        strcpy(p->fieldname, fp->fieldname);
        p->type = Type_Set(fp->type);
        fp = fp->tail;
        p->tail = FieldList_Set(fp);
        return p;
    }
    else
    {
        return NULL;
    }
}
//
int Get_Width(Typep type)
{
    if (type->kind == BASIC)
        return 4;
    else if (type->kind == ARRAY)
    {
        return Get_Width(type->uval.array.elem) * (type->uval.array.size);
    }
    else if (type->kind == STRUCTURE)
    {
        int width = 0;
        FieldListp strfield = type->uval.structure;
        while (strfield != NULL)
        {
            width = width + Get_Width(strfield->type);
            strfield = strfield->tail;
        }
        return width;
    }
    else
        return 0;
}

SymbolNodep SymbolNode_New()
{
    SymbolNodep p = (SymbolNodep)malloc(sizeof(SymbolNode));
    p->kind_ = NOTYPE;
    strcpy(p->name, "*");
    p->type = Type_New();
    p->deepth = 0;
    // lab 3
    p->val_no = 0;
    p->isaddr = 0;
    //
    p->next = NULL;
    p->prev = NULL;
    p->snext = NULL;
    return p;
}

SymbolNodep SymbolNode_Set(char *name, Kind_ k, int deepth, Typep type)
{
    SymbolNodep p = (SymbolNodep)malloc(sizeof(SymbolNode));
    p->kind_ = k;
    strcpy(p->name, name);
    p->type = Type_Set(type);
    p->deepth = deepth;
    p->val_no=0;
    p->isaddr=0;
    p->next = NULL;
    p->prev = NULL;
    p->snext = NULL;
    return p;
}

Stackp Stack_New(int size)
{
    Stackp stack = (Stackp)malloc(sizeof(Stack));
    stack->snps = (SymbolTable)malloc(sizeof(SymbolNodep) * size);
    for (int i = 0; i < size; i++)
    {
        stack->snps[i] = NULL;
    }
    stack->size = size;
    stack->top = 0;
    return stack;
}

bool Stack_Link(Stackp stack, SymbolNodep sn)
{
    sn->snext = stack->snps[stack->top];
    stack->snps[stack->top] = sn;
    return true;
}

bool Stack_Up(Stackp stack)
{
    if (stack->top < stack->size - 1)
    {
        stack->top++;
        return true;
    }
    else
        return false;
}

bool Stack_Down(Stackp stack)
{
    if (stack->top > 0)
    {
        stack->snps[stack->top] = NULL;
        stack->top--;
        return true;
    }
    else
        return false;
}

SymbolNodep Stack_Search(Stackp stack, char *name, int deepth)
{
    if (!Stack_IsEmpty(stack))
    {
        SymbolNodep p = stack->snps[stack->top];
        while (p != NULL)
        {
            if (strcmp(p->name, name) == 0 && p->deepth == deepth)
            {
                return p;
            }
            p = p->snext;
        }
        return NULL;
    }
    else
        return NULL;
}

bool Stack_IsEmpty(Stackp stack)
{
    if (stack->top == -1)
    {
        return true;
    }
    return false;
}

int Stack_GetSize(Stackp stack)
{
    return stack->size;
}

bool sameStr(char str1[], char str2[])
{
    if (strcmp(str1, str2) == 0)
        return true;
    else
        return false;
}