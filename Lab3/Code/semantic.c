#include "semantic.h"
//符号表
SymbolNodep st[SYMBOL_TABLE_SIZE];
Stackp stack_sn;
//结构体定义
Stackp strdef;
//记录函数形参
FieldListp funpara[100];
int funparan = -1;
//函数声明
FieldListp fundec_st[100];
int fundecn = -1;
int fundec_co[100]; // 函数声明所在位置，便于打印错误信息
int fundec_con = -1;
//
// lab 3
// SymbolNodep st_im[SYMBOL_TABLE_SIZE];
//

bool begin_semanalysis(TreeNode *root)
{
    HashTable_Initial(st);
    stack_sn = Stack_New(100);
    strdef = Stack_New(100);
    strdef->top = -1; //初始化数据结构
    // lab 3
    // HashTable_Initial(st_im);
    //
    Analyse_Program(root); //开始对语法树进行语义分析

    int fundecj = 0;
    for (; fundecj <= fundecn; fundecj++)
    {
        if (HashTable_Search(1, st, fundec_st[fundecj]->fieldname, FUNCTIONDEF, 0, 0) == NULL)
        {
            PrintError("*", 18, fundec_co[fundecj]); // error 18 函数进行了声明，但没有被定义
        }
    }
    return true;
}

bool Analyse_Program(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        if (tn->childtype == 1)
        { // ExtDefList
            Analyse_ExtDefList(Child1);
        }
        return isright;
    }
    return true;
}

bool Analyse_ExtDefList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        if (tn->childtype == 1)
        { // ExtDef ExtDefList
            Analyse_ExtDef(Childi(tn, 1));
            Analyse_ExtDefList(Childi(tn, 2));
        }
        return isright;
    }
    return true;
}

bool Analyse_ExtDef(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // Specifier ExtDecList SEMI
        {
            Child1->inh = Field_New();
            Analyse_Specifier(Child1);
            Child2->inh = Child1->syn;
            Analyse_ExtDecList(Child2);
        }
        else if (tn->childtype == 2) // Specifier SEMI
        {
            Child1->inh = Field_New();
            Analyse_Specifier(Child1);
        }
        else if (tn->childtype == 3) // Specifier FunDec CompSt
        {
            Child1->inh = Field_New();
            Analyse_Specifier(Child1);
            Child2->inh = Child1->syn;
            Analyse_FunDec(Child2);
            Child3->inh = Child2->syn; //传递返回类型
            Analyse_CompSt(Child3);
        }
        else if (tn->childtype == 4) // Specifier FunDec SEMI 函数声明
        {
            Child1->inh = Field_New();
            Analyse_Specifier(Child1);
            Child2->inh = Child1->syn;
            Child2->isfundec = 1; // 指示标志
            Analyse_FunDec(Child2);
        }
        return isright;
    }
    return true;
}

bool Analyse_ExtDecList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // VarDec
        {
            Child1->inh = tn->inh;
            Analyse_VarDec(Child1);
            tn->syn = Child1->syn;

            //填表
            if (HashTable_Search(1, st, Child1->strval, GLOBAL, -1, 0) == NULL)
            {
                SymbolNodep newsn = SymbolNode_Set(Child1->syn->fieldname, GLOBAL, 0, Child1->syn->type);
                HashTable_Insert(st, newsn);
                Stack_Link(stack_sn, newsn);
            }
            else
            {
                PrintError("*", 3, tn->column); // error 3 变量出现重复定义，或变量与前面定义过的结构体名字重复
                isright = false;
            }
        }
        else if (tn->childtype == 2) // VarDec COMMA ExtDecList
        {
            Child1->inh = tn->inh;
            Analyse_VarDec(Child1);

            //填表
            if (HashTable_Search(1, st, Child1->strval, GLOBAL, -1, 0) == NULL)
            {
                SymbolNodep newsn = SymbolNode_Set(Child1->syn->fieldname, GLOBAL, 0, Child1->syn->type);
                HashTable_Insert(st, newsn);
                Stack_Link(stack_sn, newsn);
            }
            else
            {
                PrintError("*", 3, tn->column); // error 3 变量出现重复定义，或变量与前面定义过的结构体名字重复
                isright = false;
            }

            Child3->inh = tn->inh;
            Analyse_ExtDecList(Child3);

            Child1->syn->tail = Child3->syn;
            tn->syn = Child1->syn;
        }
        return isright;
    }
    return true;
}

bool Analyse_Specifier(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        if (tn->childtype == 1) // TYPE
        {
            strcpy(Child1->syn->fieldname, Child1->strval);
            Child1->syn->type->kind = BASIC;
            if (sameStr(Child1->syn->fieldname, "int"))
                Child1->syn->type->uval.basic = 0;
            else if (sameStr(Child1->syn->fieldname, "float"))
                Child1->syn->type->uval.basic = 1;
            Child1->syn->type->width = 4;
            tn->syn = Child1->syn;
        }
        else if (tn->childtype == 2) // StructSpecifier
        {
            strcpy(Child1->inh->fieldname, "STRUCTSpecifier");
            Child1->isstrdef = 1;
            Child1->inh->type->kind = STRUCTURE;
            Analyse_StructSpecifier(Child1);
            tn->syn = Child1->syn;
        }
        return isright;
    }
    return true;
}

bool Analyse_StructSpecifier(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child4 = Childi(tn, 4);
        if (tn->childtype == 1) // STRUCT OptTag LC DefList RC
        {
            Child2->inh = tn->inh;
            isright = Analyse_OptTag(Child2);
            Child4->isstrdef = 1;
            Child4->inh = tn->inh;
            Stack_Up(strdef); //结构体定义深度加一
            Analyse_DefList(Child4);
            Stack_Down(strdef); //结构体定义深度减一
            if (Child2->childtype == 1)
            { // OptTag-->ID
                //先判断此名称是否已经被定义过或者使用过
                if (isright == true)
                { //没有被使用过
                    // StructSpecifier->syn=OptTag+DefList
                    strcpy(tn->syn->fieldname, Child2->syn->fieldname);
                    tn->syn->type->uval.structure = Child4->syn;
                    tn->syn->type->kind = STRUCTURE;

                    //填表
                    SymbolNodep newsn = SymbolNode_Set(tn->syn->fieldname, GLOBAL, 0, tn->syn->type);
                    HashTable_Insert(st, newsn);
                    Stack_Link(stack_sn, newsn);
                }
                else
                {
                    strcpy(tn->syn->fieldname, "STRUCT*unnamed");
                    tn->syn->type->uval.structure = Child4->syn;
                    tn->syn->type->kind = STRUCTURE;
                    isright = false;
                }
            }
            else
            { // OptTag-->ε
                strcpy(tn->syn->fieldname, "STRUCT*unnamed");
                tn->syn->type->uval.structure = Child4->syn;
                tn->syn->type->kind = STRUCTURE;
            }
        }
        else if (tn->childtype == 2) // STRUCT Tag
        {
            Child2->inh = tn->inh;
            Analyse_Tag(Child2);
            tn->syn = Child2->syn;
        }
        return isright;
    }
    return true;
}

bool Analyse_OptTag(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        if (tn->childtype == 1) // ID
        {
            if (HashTable_Search(1, st, Child1->strval, GLOBAL, -1, 0) != NULL)
            {
                PrintError("*", 16, tn->column); // error 16 结构体的名字与前面定义过的结构体或变量的名字重复
                isright = false;
            }
            //获得一个ID值，传给OptTag，（传给DefList），再传给StructSpecifier
            Child1->syn = tn->inh;
            strcpy(Child1->syn->fieldname, Child1->strval);
            tn->syn = Child1->syn;
        }
        return isright;
    }
    return true;
}

bool Analyse_Tag(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        if (tn->childtype == 1) // ID
        {
            TreeNode *Child1 = Childi(tn, 1);
            // ID应该是已经定义过的结构体名称，首先查表，找不到说明错误
            if (HashTable_Search(3, st, Child1->strval, GLOBAL, 0, STRUCTURE) != NULL)
            {
                SymbolNodep p = HashTable_Search(3, st, Child1->strval, GLOBAL, 0, STRUCTURE);
                //找到了ID对应的相关STRUCTURE表项，赋给tag，tag再赋给structSpecifier
                strcpy(Child1->syn->fieldname, Child1->strval);
                Child1->syn->type = p->type;
                tn->syn = Child1->syn;
            }
            else
            {
                PrintError("*", 17, tn->column); // error 17 直接使用未定义过的结构体来定义变量
                isright = false;
                strcpy(tn->syn->fieldname, "invalidSTRUCTUE");
                Child1->syn->type->kind = STRUCTURE;
            }
        }
        return isright;
    }
    return true;
}

bool Analyse_VarDec(TreeNode *tn)
{ //分类讨论，变量类型-BASIC/ARRAY/STRUCTVAR/
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // ID
        {
            Child1->inh = tn->inh;
            switch (tn->inh->type->kind) // Specifier为BASIC或者STRUCTURE或者ARRAY
            {
            case BASIC:
                strcpy(Child1->syn->fieldname, Child1->strval);
                Child1->syn->type = Child1->inh->type;
                break;
            case STRUCTURE:
                strcpy(Child1->syn->fieldname, Child1->strval);
                Child1->syn->type->kind = STRUCTURE;
                Child1->syn->type->uval.structure = Child1->inh->type->uval.structure;
                break;
            // lab 3
            case ARRAY:
                strcpy(Child1->syn->fieldname, Child1->strval);
                Child1->syn->type = Child1->inh->type;
            //
            default:
                break;
            }
            tn->syn = Child1->syn;
        }
        else if (tn->childtype == 2) // VarDec LB INT RB 数组
        {
            // lab 2
            /*Child1->inh = tn->inh;
            isright = Analyse_VarDec(Child1);
            strcpy(tn->syn->fieldname, Child1->syn->fieldname);
            tn->syn->type->kind = ARRAY;
            tn->syn->type->uval.array.elem = Child1->syn->type;
            tn->syn->type->uval.array.size = Child3->val.ival;*/

            // lab 3
            /*if (Child1->childtype == 1)
            {
                
                Child1->syn->type->kind = ARRAY;
                Child1->syn->type->uval.array.elem = tn->inh->type;
                Child1->syn->type->uval.array.size = Child3->val.ival;
                tn->syn = tn->inh;
            }
            else
            {*/
                tn->syn = tn->inh;
                Child1->inh->type->kind = ARRAY;
                Child1->inh->type->uval.array.elem = tn->inh->type;
                Child1->inh->type->uval.array.size = Child3->val.ival;
                isright = Analyse_VarDec(Child1);
                strcpy(tn->syn->fieldname, Child1->syn->fieldname);
            //}
            //
        }
        return isright;
    }
    return true;
}

bool Analyse_FunDec(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        TreeNode *Child4 = Childi(tn, 4);
        if (tn->isfundec == 0) //函数定义
        {
            if (tn->childtype == 1) // ID LP VarList RP
            {
                Analyse_VarList(Child3);
                strcpy(tn->syn->fieldname, Child1->strval);
                tn->syn->type->kind = FUNCTIONDEF;
                tn->syn->type->uval.function.return_type = tn->inh->type;
                tn->syn->type->uval.function.paramn = funparan + 1;
                funparan = -1;
                tn->syn->type->uval.function.params = Child3->syn;

                if (HashTable_Search(1, st, Child1->strval, FUNCTIONDEF, -1, 0) != NULL)
                {
                    PrintError("*", 4, tn->column); // error 4 函数出现重复定义
                    isright = false;
                }
                else
                { //填表
                    SymbolNodep newsn = SymbolNode_Set(tn->syn->fieldname, FUNCTIONDEF, 0, tn->syn->type);
                    HashTable_Insert(st, newsn);
                    // lab 3
                    // HashTable_Insert(st_im, newsn);
                    //
                    Stack_Link(stack_sn, newsn);
                    //检查是否与声明匹配
                    SymbolNodep p = HashTable_Search(1, st, Child1->strval, FUNCTIONDEC, -1, 0);
                    if (p != NULL)
                    {
                        if (TypeCheck_type(p->type, tn->syn->type) == false)
                        {
                            PrintError("*", 19, tn->column); // error 19 函数定义与声明冲突
                            isright = false;
                        }
                    }
                }
            }
            else if (tn->childtype == 2) // ID LP RP
            {
                strcpy(tn->syn->fieldname, Child1->strval);
                tn->syn->type->kind = FUNCTIONDEF;
                tn->syn->type->uval.function.return_type = tn->inh->type;
                tn->syn->type->uval.function.paramn = 0;
                tn->syn->type->uval.function.params = NULL;

                if (HashTable_Search(1, st, Child1->strval, FUNCTIONDEF, -1, 0) != NULL)
                {
                    PrintError("*", 4, tn->column); // error 4 函数出现重复定义
                    isright = false;
                }
                else
                { //填表
                    SymbolNodep newsn = SymbolNode_Set(tn->syn->fieldname, FUNCTIONDEF, 0, tn->syn->type);
                    HashTable_Insert(st, newsn);
                    // lab 3
                    // HashTable_Insert(st_im, newsn);
                    //
                    Stack_Link(stack_sn, newsn);
                    //检查是否与声明匹配
                    SymbolNodep p = HashTable_Search(1, st, Child1->strval, FUNCTIONDEC, -1, 0);
                    if (p != NULL)
                    {
                        if (TypeCheck_type(p->type, tn->syn->type) == false)
                        {
                            PrintError("*", 19, tn->column); // error 19 函数定义与声明冲突
                            isright = false;
                        }
                    }
                }
            }
        }
        else
        {                           //函数声明
            if (tn->childtype == 1) // ID LP VarList RP
            {
                Analyse_VarList(Child3);
                strcpy(tn->syn->fieldname, Child1->strval);
                tn->syn->type->kind = FUNCTIONDEF;
                tn->syn->type->uval.function.return_type = tn->inh->type;
                tn->syn->type->uval.function.paramn = funparan + 1;
                funparan = -1;
                tn->syn->type->uval.function.params = Child3->syn;

                SymbolNodep p = HashTable_Search(1, st, Child1->strval, FUNCTIONDEC, -1, 0);
                if (p != NULL)
                {
                    if (TypeCheck_type(p->type, tn->syn->type) == false)
                    {
                        PrintError("*", 19, tn->column); // error 19 函数声明与声明冲突
                        isright = false;
                    }
                }
                p = HashTable_Search(1, st, Child1->strval, FUNCTIONDEF, -1, 0);
                if (p != NULL)
                {
                    if (TypeCheck_type(p->type, tn->syn->type) == false)
                    {
                        PrintError("*", 19, tn->column); // error 19 函数声明与声明冲突
                        isright = false;
                    }
                }
                if (isright)
                { //填表
                    SymbolNodep newsn = SymbolNode_Set(tn->syn->fieldname, FUNCTIONDEC, 0, tn->syn->type);
                    HashTable_Insert(st, newsn);
                    Stack_Link(stack_sn, newsn);

                    fundec_st[++fundecn] = tn->syn;
                    fundec_co[++fundec_con] = tn->column;
                }
            }
            else if (tn->childtype == 2) // ID LP RP
            {
                strcpy(tn->syn->fieldname, Child1->strval);
                tn->syn->type->kind = FUNCTIONDEF;
                tn->syn->type->uval.function.return_type = tn->inh->type;
                tn->syn->type->uval.function.paramn = 0;
                tn->syn->type->uval.function.params = NULL;

                SymbolNodep p = HashTable_Search(1, st, Child1->strval, FUNCTIONDEC, -1, 0);
                if (p != NULL)
                {
                    if (TypeCheck_type(p->type, tn->syn->type) == false)
                    {
                        PrintError("*", 19, tn->column); // error 19 函数声明与声明冲突
                        isright = false;
                    }
                }
                p = HashTable_Search(1, st, Child1->strval, FUNCTIONDEF, -1, 0);
                if (p != NULL)
                {
                    if (TypeCheck_type(p->type, tn->syn->type) == false)
                    {
                        PrintError("*", 19, tn->column); // error 19 函数声明与声明冲突
                        isright = false;
                    }
                }
                if (isright)
                { //填表
                    SymbolNodep newsn = SymbolNode_Set(tn->syn->fieldname, FUNCTIONDEC, 0, tn->syn->type);
                    HashTable_Insert(st, newsn);
                    Stack_Link(stack_sn, newsn);

                    fundec_st[++fundecn] = tn->syn;
                    fundec_co[++fundec_con] = tn->column;
                }
            }
        }
        return isright;
    }
    return true;
}

bool Analyse_VarList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // ParamDec COMMA VarList
        {
            Analyse_ParamDec(Child1);
            Analyse_VarList(Child3);
            Child1->syn->tail = Child3->syn;
            tn->syn = Child1->syn;

            int funparaj = 0;
            for (; funparaj <= funparan; funparaj++)
                if (sameStr(Child1->syn->fieldname, funpara[funparaj]->fieldname))
                    break;
            if (funparaj > funparan)
                funpara[++funparan] = Child1->syn;
        }
        else if (tn->childtype == 2) // ParamDec
        {
            Analyse_ParamDec(Child1);
            tn->syn = Child1->syn;

            int funparaj = 0;
            for (; funparaj <= funparan; funparaj++)
                if (sameStr(Child1->syn->fieldname, funpara[funparaj]->fieldname))
                    break;
            if (funparaj > funparan)
                funpara[++funparan] = Child1->syn;
        }
        return isright;
    }
    return true;
}

bool Analyse_ParamDec(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        if (tn->childtype == 1) // Specifier VarDec
        {
            Analyse_Specifier(Child1);
            Child2->inh = Child1->syn;
            isright = Analyse_VarDec(Child2);
            // lab 3
            TreeNode * vardec = Child2;
            while(sameStr(vardec->firstchild->name, "ID") == false){
                vardec = vardec->firstchild;
            }
            tn->syn = vardec->firstchild->syn;
            //
            // lab 2
            //tn->syn = Child2->syn;
        }
        return isright;
    }
    return true;
}

bool Analyse_CompSt(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // LC DefList StmtList RC
        {
            Stack_Up(stack_sn);                                              //进入语句块
            if (tn->inh->type != NULL && tn->inh->type->kind == FUNCTIONDEF) //如果是函数，就向当前栈顶传递函数的参数
            {
                FieldListp params = tn->inh->type->uval.function.params;
                while (params != NULL)
                {
                    SymbolNodep newsn = SymbolNode_Set(params->fieldname, LOCAL, stack_sn->top, params->type);
                    HashTable_Insert(st, newsn);
                    // lab 3
                    // HashTable_Insert(st_im, newsn);
                    //
                    Stack_Link(stack_sn, newsn);
                    params = params->tail;
                }
            }
            Child2->inh = tn->inh;
            Analyse_DefList(Child2);
            Child3->inh = tn->inh;
            Analyse_StmtList(Child3);
            if (stack_sn->snps[stack_sn->top] != NULL)
            {
                SymbolNodep p = stack_sn->snps[stack_sn->top];
                HashTable_Remove(st, p);
            }
            Stack_Down(stack_sn); //退出语句块
        }
        return isright;
    }
    return true;
}

bool Analyse_StmtList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        if (tn->childtype == 1) // Stmt StmtList
        {
            Child1->inh = tn->inh;
            Analyse_Stmt(Child1);
            Child2->inh = tn->inh;
            Analyse_StmtList(Child2);
        }
        return isright;
    }
    return true;
}

bool Analyse_Stmt(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        TreeNode *Child4 = Childi(tn, 4);
        TreeNode *Child5 = Childi(tn, 5);
        TreeNode *Child6 = Childi(tn, 6);
        TreeNode *Child7 = Childi(tn, 7);
        if (tn->childtype == 1) // Exp SEMI
        {
            Child1->inh = tn->inh;
            Analyse_Exp(Child1);
        }
        else if (tn->childtype == 2) // CompSt
        {
            Child1->inh = tn->inh;
            Analyse_CompSt(Child1);
        }
        else if (tn->childtype == 3) // RETURN Exp SEMI
        {
            Child2->inh = tn->inh;
            Analyse_Exp(Child2);
            //检查返回类型
            if (TypeCheck_type(Child2->inh->type->uval.function.return_type, Child2->syn->type) == false)
            {
                PrintError("*", 8, tn->column); //  error 8 ：return语句的返回类型与函数定义的返回类型不匹配
                isright = false;
            }
        }
        else if (tn->childtype == 4) // IF LP Exp RP Stmt
        {
            Child3->inh = tn->inh;
            Analyse_Exp(Child3);
            Child5->inh = tn->inh;
            Analyse_Stmt(Child5);
        }
        else if (tn->childtype == 5) // IF LP Exp RP Stmt ELSE Stmt
        {
            Child3->inh = tn->inh;
            Analyse_Exp(Child3);
            Child5->inh = tn->inh;
            Analyse_Stmt(Child5);
            Child7->inh = tn->inh;
            Analyse_Stmt(Child7);
        }
        else if (tn->childtype == 6) //  WHILE LP Exp RP Stmt
        {
            Child3->inh = tn->inh;
            Analyse_Exp(Child3);
            Child5->inh = tn->inh;
            Analyse_Stmt(Child5);
        }
        return isright;
    }
    return true;
}

bool Analyse_DefList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        if (tn->childtype == 1) // Def DefList 考虑DefList为空
        {
            TreeNode *Child1 = Childi(tn, 1);
            TreeNode *Child2 = Childi(tn, 2);
            Child1->isstrdef = tn->isstrdef;
            Child2->isstrdef = tn->isstrdef;
            Child1->inh = tn->inh;
            Child2->inh = tn->inh;
            Analyse_Def(Child1);
            Analyse_DefList(Child2);
            if (Child2->childtype == 1)
            {
                if (Child1->syn->tail == NULL)
                {
                    Child1->syn->tail = Child2->syn;
                }
                else
                { // Def是一串变量，即不止一个Dec
                    FieldListp tail = Field_New();
                    tail = Child1->syn;
                    while (tail->tail != NULL)
                        tail = tail->tail;
                    tail->tail = Child2->syn;
                }
                tn->syn = Child1->syn;
            }
            else
            { // Def ε即只有一个Def
                tn->syn = Child1->syn;
            }
        }
        return isright;
    }
    return true;
}

bool Analyse_Def(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        if (tn->childtype == 1) // Specifier DecList SEMI
        {
            TreeNode *Child1 = Childi(tn, 1);
            TreeNode *Child2 = Childi(tn, 2);
            Child1->isstrdef = tn->isstrdef;
            Child2->isstrdef = tn->isstrdef;
            Child1->inh = tn->inh;
            Child2->inh = tn->inh;
            Analyse_Specifier(Child1);
            Child2->inh = Child1->syn; //将Specifier->syn类型传给变量
            Analyse_DecList(Child2);
            tn->syn = Child2->syn;
        }
        return isright;
    }
    return true;
}

bool Analyse_DecList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // Dec
        {
            Child1->isstrdef = tn->isstrdef;
            Child1->inh = tn->inh;
            isright = Analyse_Dec(Child1);
            tn->syn = Child1->syn;
        }
        else if (tn->childtype == 2) // Dec COMMA DecList
        {
            Child1->isstrdef = tn->isstrdef;
            Child1->inh = tn->inh;
            if (Analyse_Dec(Child1) == false)
                isright = false;
            Child3->isstrdef = tn->isstrdef;
            Child3->inh = tn->inh;
            if (Analyse_DecList(Child3) == false)
                isright = false;
            Child1->syn->tail = Child3->syn;
            tn->syn = Child1->syn;
        }
        return isright;
    }
    return true;
}

bool Analyse_Dec(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // VarDec
        {
            Child1->isstrdef = tn->isstrdef;
            Child1->inh = tn->inh;
            isright = Analyse_VarDec(Child1);
            // lab 3
            TreeNode * vardec = Child1;
            while(sameStr(vardec->firstchild->name, "ID") == false){
                vardec = vardec->firstchild;
            }
            tn->syn = vardec->firstchild->syn;
            //
            // lab 2
            //tn->syn = Child1->syn;
        }
        else if (tn->childtype == 2) // VarDec ASSIGNOP Exp
        {
            Child1->isstrdef = tn->isstrdef;
            Child1->inh = tn->inh;
            isright = Analyse_VarDec(Child1);
            // lab 3
            TreeNode * vardec = Child1;
            while(sameStr(vardec->firstchild->name, "ID") == false){
                vardec = vardec->firstchild;
            }
            tn->syn = vardec->firstchild->syn;
            //
            // lab 2
            //tn->syn = Child1->syn;
            Analyse_Exp(Child3);

            //检查Exp与VarDec的类型
            if (TypeCheck_Field(Child1->syn, Child3->syn) == false)
            {
                PrintError("*", 5, tn->column); // error 5 赋值号两边的表达式类型不匹配
                isright = false;
            }
            if (tn->isstrdef == 1)
            {
                PrintError("*", 15, tn->column); // error 15 在定义时对域进行初始化
                isright = false;
            }
        }
        //printf("+++++++++++++++++++++++++++++++++++++++++%s\n", tn->syn->fieldname);
        if (tn->isstrdef == 0) //不属于结构体定义的变量需要填表
        {
            SymbolNodep p = stack_sn->snps[stack_sn->top];
            while (p != NULL)
            {
                if (sameStr(p->name, tn->syn->fieldname))
                {
                    PrintError("*", 3, tn->column); // error 3 变量出现重复定义，或变量与前面定义过的结构体名字重复
                    isright = false;
                    break;
                }
                p = p->snext;
            }
            p = stack_sn->snps[0];
            while (p != NULL)
            {
                if (sameStr(p->name, tn->syn->fieldname) && p->type->kind == STRUCTURE)
                {
                    PrintError("*", 3, tn->column); // error 3 变量出现重复定义，或变量与前面定义过的结构体名字重复
                    isright = false;
                    break;
                }
                p = p->snext;
            }
            if (p == NULL)
            {
                SymbolNodep newsn = SymbolNode_Set(tn->syn->fieldname, LOCAL, 0, tn->syn->type);
                HashTable_Insert(st, newsn);
                // lab 3
                // HashTable_Insert(st_im, newsn);
                //
                Stack_Link(stack_sn, newsn);
            }
        }
        else
        {
            SymbolNodep p = Stack_Search(strdef, Child1->syn->fieldname, strdef->top);
            if (p == NULL)
            {
                p = SymbolNode_Set(Child1->syn->fieldname, 0, strdef->top, 0);
                Stack_Link(strdef, p);
            }
            else
            {
                PrintError("*", 15, tn->column); // error 15 结构体中域名重复定义（指同一结构体中）
                isright = false;
            }
        }
        return isright;
    }
    return true;
}

bool Analyse_Exp(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        bool isright1 = true;
        bool isright2 = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        switch (tn->childtype)
        {
        case 1: // Exp ASSIGNOP Exp
            isright1 = Analyse_Exp(Child1);
            isright2 = Analyse_Exp(Child3);
            if (isright1 && isright2)
            { //赋值号左边出现一个只有右值的表达式
                if (Child1->childtype != 14 && Child1->childtype != 15 && Child1->childtype != 16)
                {
                    PrintError("*", 6, tn->column); // error 6 赋值号左边出现一个只有右值的表达式
                    isright = false;
                }
                isright = TypeCheck_TreeNode(Child1, Child3);
                if (isright == false)
                    PrintError("*99", 5, tn->column); // error 5 赋值号两边的表达式类型不匹配
                tn->syn = Child1->syn;
            }
            else
            {
                if (isright1)
                {
                    if (Child1->childtype != 14 && Child1->childtype != 15 && Child1->childtype != 16)
                    {
                        PrintError("*", 6, tn->column); // error 6 赋值号左边出现一个只有右值的表达式
                        isright = false;
                    }
                    PrintError("*99", 5, tn->column); // error 5 赋值号两边的表达式类型不匹配
                }
            }
            break;
        case 2: // Exp AND Exp
            isright1 = Analyse_Exp(Child1);
            isright2 = Analyse_Exp(Child3);
            if (isright1 && isright2)
            {
                if (Child1->syn->type->kind == BASIC && Child3->syn->type->kind == BASIC && Child1->syn->type->uval.basic == 0)
                {
                    if (TypeCheck_Field(Child1->syn, Child3->syn))
                    {
                        tn->syn->type->kind = BASIC;
                        tn->syn->type->uval.basic = 0;
                    }
                    else
                    {
                        PrintError("&&", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                        isright = false;
                    }
                }
                else
                {
                    PrintError("&&", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                    isright = false;
                }
            }
            break;
        case 3: // Exp OR Exp
            isright1 = Analyse_Exp(Child1);
            isright2 = Analyse_Exp(Child3);
            if (isright1 && isright2)
            {
                if (Child1->syn->type->kind == BASIC && Child3->syn->type->kind == BASIC && Child1->syn->type->uval.basic == 0)
                {
                    if (TypeCheck_Field(Child1->syn, Child3->syn))
                    {
                        tn->syn->type->kind = BASIC;
                        tn->syn->type->uval.basic = 0;
                    }
                    else
                    {
                        PrintError("||", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                        isright = false;
                    }
                }
                else
                {
                    PrintError("||", 7, Child1->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                    isright = false;
                }
            }
            else
            {
                PrintError("||", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                isright = false;
            }
            break;
        case 4: // Exp RELOP Exp
            isright1 = Analyse_Exp(Child1);
            isright2 = Analyse_Exp(Child3);
            if (isright1 && isright2)
            {
                if (Child1->syn->type->kind == BASIC && Child3->syn->type->kind == BASIC)
                {
                    if (TypeCheck_Field(Child1->syn, Child3->syn))
                    {
                        tn->syn->type->kind = BASIC;
                        tn->syn->type->uval.basic = 0;
                    }
                    else
                    {
                        PrintError("<>", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                        isright = false;
                    }
                }
                else
                {
                    PrintError("<>", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                    isright = false;
                }
            }
            break;
        case 5: // Exp PLUS Exp
            isright1 = Analyse_Exp(Child1);
            isright2 = Analyse_Exp(Child3);
            if (isright1 && isright2)
            {
                if (Child1->syn->type->kind == BASIC && Child3->syn->type->kind == BASIC)
                {
                    if (TypeCheck_Field(Child1->syn, Child3->syn))
                    {
                        tn->syn = Child1->syn;
                    }
                    else
                    {
                        PrintError("+", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                        isright = false;
                    }
                }
                else
                {
                    PrintError("+", 7, Child1->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                    isright = false;
                }
            }
            break;
        case 6: // Exp MINUS Exp
            isright1 = Analyse_Exp(Child1);
            isright2 = Analyse_Exp(Child3);
            if (isright1 && isright2)
            {
                if (Child1->syn->type->kind == BASIC && Child3->syn->type->kind == BASIC)
                {
                    if (TypeCheck_Field(Child1->syn, Child3->syn))
                    {
                        tn->syn = Child1->syn;
                    }
                    else
                    {
                        PrintError("-", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                        isright = false;
                    }
                }
                else
                {
                    PrintError("-", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                    isright = false;
                }
            }
            break;
        case 7: // Exp STAR Exp
            isright1 = Analyse_Exp(Child1);
            isright2 = Analyse_Exp(Child3);
            if (isright1 && isright2)
            {
                if (Child1->syn->type->kind == BASIC && Child3->syn->type->kind == BASIC)
                {
                    if (TypeCheck_Field(Child1->syn, Child3->syn))
                    {
                        tn->syn = Child1->syn;
                    }
                    else
                    {
                        PrintError("*", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                        isright = false;
                    }
                }
                else
                {
                    PrintError("*", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                    isright = false;
                }
            }
            break;
        case 8: // Exp DIV Exp
            isright1 = Analyse_Exp(Child1);
            isright2 = Analyse_Exp(Child3);
            if (isright1 && isright2)
            {
                if (Child1->syn->type->kind == BASIC && Child3->syn->type->kind == BASIC)
                {
                    if (TypeCheck_Field(Child1->syn, Child3->syn))
                    {
                        tn->syn = Child1->syn;
                    }
                    else
                    {
                        PrintError("/", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                        isright = false;
                    }
                }
                else
                {
                    PrintError("/", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                    isright = false;
                }
            }
            break;
        case 9: // LP Exp RP
            Analyse_Exp(Child2);
            tn->syn = Child2->syn;
            break;
        case 10: // MINUS Exp
            Analyse_Exp(Child2);
            if (Child2->syn->type->kind == BASIC)
                tn->syn = Child2->syn;
            else
            {
                PrintError("--", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                isright = false;
            }
            break;
        case 11: // NOT Exp
            Analyse_Exp(Child2);
            if (Child2->syn->type->kind == BASIC && Child2->syn->type->uval.basic == 0)
                tn->syn = Child2->syn;
            else
            {
                PrintError("~", 7, tn->column); // error 7 操作数类型不匹配或操作数类型与操作符不匹配
                isright = false;
            }
            break;
        case 12: // ID LP Args RP
        {
            strcpy(Child1->syn->fieldname, Child1->strval);
            SymbolNodep p = HashTable_Search(3, st, Child1->syn->fieldname, FUNCTIONDEF, 0, FUNCTIONDEF);
            if (p != NULL)
            {
                Child1->syn->type = p->type;
                isright2 = Analyse_Args(Child3);
                if (isright2)
                {
                    if (TypeCheck_FieldList(Child3->syn, p->type->uval.function.params) == false)
                    {
                        PrintError("*", 9, tn->column); // error 9 函数调用时实参与形参的数目或类型不匹配
                        isright = false;
                    }
                }
                strcpy(tn->syn->fieldname, Child1->strval);
                tn->syn->type = p->type->uval.function.return_type;
            }
            else
            {
                p = HashTable_Search(0, st, Child1->syn->fieldname, 0, 0, 0);
                if (p != NULL && p->kind_ != FUNCTIONDEC)
                {
                    PrintError("*", 11, tn->column); // error 11 对普通变量使用“(…)”或“()”（函数调用）操作符
                    isright = false;
                }
                else
                {
                    PrintError("*", 2, tn->column); // error 2 函数在调用时未经定义
                    isright = false;
                }
            }
            break;
        }
        case 13: // ID LP RP
            strcpy(Child1->syn->fieldname, Child1->strval);
            SymbolNodep p = HashTable_Search(3, st, Child1->syn->fieldname, FUNCTIONDEF, 0, FUNCTIONDEF);
            if (p != NULL)
            {

                Child1->syn->type = p->type;
                strcpy(tn->syn->fieldname, Child1->strval);
                tn->syn->type = p->type->uval.function.return_type;
            }
            else
            {
                p = HashTable_Search(0, st, Child1->syn->fieldname, 0, 0, 0);
                if (p != NULL && p->kind_ != FUNCTIONDEC)
                {
                    PrintError("*", 11, tn->column); // error 11 对普通变量使用“(…)”或“()”（函数调用）操作符
                    isright = false;
                }
                else
                {
                    PrintError("*", 2, tn->column); // error 2 函数在调用时未经定义
                    isright = false;
                }
            }
            break;
        case 14: // Exp LB Exp RB
            Analyse_Exp(Child1);
            Analyse_Exp(Child3);
            if (Child1->syn->type->kind == ARRAY)
            {
                if (Child3->syn->type->kind == BASIC && Child3->syn->type->uval.basic == 0)
                {
                    tn->syn->type = Child1->syn->type->uval.array.elem;
                }
                else
                {
                    PrintError("*", 12, tn->column); // error 12 数组访问操作符“[…]”中出现非整数（例如a[1.5]）
                    isright = false;
                }
            }
            else
            {
                PrintError("*", 10, tn->column); // error 10 对非数组型变量使用“[…]”（数组访问）操作符
                isright = false;
            }
            break;
        case 15: // Exp DOT ID
            isright1 = Analyse_Exp(Child1);
            if (isright1 && Child1->syn->type->kind == STRUCTURE)
            {
                FieldListp fp = Child1->syn->type->uval.structure;
                while (fp != NULL)
                {
                    if (sameStr(fp->fieldname, Child3->strval))
                    {
                        strcpy(tn->syn->fieldname, fp->fieldname);
                        tn->syn->type = Type_Set(fp->type);
                        tn->syn->tail = NULL;
                        break;
                    }
                    fp = fp->tail;
                }
                if (fp == NULL)
                {
                    PrintError("*", 14, tn->column); // error 14 访问结构体中未定义过的域
                    isright = false;
                }
            }
            else
            {
                PrintError("*", 13, tn->column); // error 13 对非结构体型变量使用“.”操作符
                isright = false;
            }
            break;
        case 16: // ID
        {
            strcpy(Child1->syn->fieldname, Child1->strval);
            SymbolNodep p = HashTable_Search(0, st, Child1->syn->fieldname, LOCAL, stack_sn->top, -1);
            if (p != NULL)
            {
                Child1->syn->type->kind = p->type->kind;
                Child1->syn->type->uval = p->type->uval;
                tn->syn = Child1->syn;
            }
            else
            {
                PrintError("*", 1, tn->column); // error 1 变量在使用时未经定义
                isright = false;
            }
            break;
        }
        case 17: // INT
            strcpy(Child1->syn->fieldname, Child1->name);
            Child1->syn->type->kind = BASIC;
            Child1->syn->type->uval.basic = 0;
            tn->syn = Child1->syn;
            break;
        case 18: // FLOAT
            strcpy(Child1->syn->fieldname, Child1->name);
            Child1->syn->type->kind = BASIC;
            Child1->syn->type->uval.basic = 1;
            tn->syn = Child1->syn;
            break;
        default:
            break;
        }
        return isright;
    }
    return true;
}

bool Analyse_Args(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // Exp COMMA Args
        {
            Child1->inh = tn->inh;
            Child3->inh = tn->inh;
            if (Analyse_Exp(Child1) == false)
                isright = false;
            if (Analyse_Args(Child3) == false)
                isright = false;
            Child1->syn->tail = Child3->syn;
            tn->syn = Child1->syn;
        }
        else if (tn->childtype == 2) // Exp
        {
            Child1->inh = tn->inh;
            if (Analyse_Exp(Child1) == false)
                isright = false;
            tn->syn = Child1->syn;
        }
        return isright;
    }
    return true;
}

bool PrintError(char megs[], int errortype, int column)
{
    printf("Error type %d at Line %d: ", errortype, column);
    switch (errortype)
    {
    case 1:
        printf("Variables are used without definition");
        break;
    case 2:
        printf("The function is called without the defined");
        break;
    case 3:
        printf("Variables appear to be defined repeatedly");
        break;
    case 4:
        printf("Functions appear to be defined repeatedly");
        break;
    case 5:
        printf("The types of expressions do not match");
        break;
    case 6:
        printf("An expression with only the right value appears to the left");
        break;
    case 7:
        printf("The operand types do not match");
        break;
    case 8:
        printf("The return type does not match");
        break;
    case 9:
        printf("A mismatch between real and formal parameters");
        break;
    case 10:
        printf("Incorrect operator for non-array variables");
        break;
    case 11:
        printf("Incorrect operator for ordinary variables");
        break;
    case 12:
        printf("The array access operator \"[...]\" appears as a non-integer");
        break;
    case 13:
        printf("Incorrect operator for non-structural variables");
        break;
    case 14:
        printf("Access to undefined domains in structs");
        break;
    case 15:
        printf("Duplicate definition in a structure or Initialize the domain in the structure");
        break;
    case 16:
        printf("The name of a structure duplicates");
        break;
    case 17:
        printf("Define variables directly using undefined structs");
        break;
    case 18:
        printf("The function is declared, but not defined");
        break;
    case 19:
        printf("Multiple declarations of functions or Declarations and definitions conflict with each other");
        break;
    default:
        break;
    }
    if (strcmp(megs, "*") != 0)
    {
        printf("----------%s", megs);
    }
    printf(".\n");
    return true;
}

bool TypeCheck_type(Typep type1, Typep type2)
{
    if (type1->kind == type2->kind && type1->kind > 0)
    {
        switch (type1->kind)
        {
        case BASIC:
            if (type1->uval.basic == type2->uval.basic)
                return true;
            break;
        case ARRAY:
            if (type1->uval.array.size == type2->uval.array.size)
                if (TypeCheck_type(type1->uval.array.elem, type2->uval.array.elem))
                    return true;
            break;
        case STRUCTURE:
            if (TypeCheck_FieldList(type1->uval.structure, type2->uval.structure))
                return true;
            break;
        case FUNCTIONDEC:
            if (TypeCheck_type(type1->uval.function.return_type, type2->uval.function.return_type))
                if (type1->uval.function.paramn == type2->uval.function.paramn)
                    if (TypeCheck_FieldList(type1->uval.function.params, type2->uval.function.params))
                        return true;
            break;
        case FUNCTIONDEF:
            if (TypeCheck_type(type1->uval.function.return_type, type2->uval.function.return_type))
                if (type1->uval.function.paramn == type2->uval.function.paramn)
                    if (TypeCheck_FieldList(type1->uval.function.params, type2->uval.function.params))
                        return true;
            break;
        default:
            break;
        }
        return false;
    }
    else if ((type1->kind == FUNCTIONDEC && type2->kind == FUNCTIONDEF) || (type1->kind == FUNCTIONDEF && type2->kind == FUNCTIONDEC))
    {
        if (TypeCheck_type(type1->uval.function.return_type, type2->uval.function.return_type))
        {
            if (type1->uval.function.paramn == type2->uval.function.paramn)
            {
                if (TypeCheck_FieldList(type1->uval.function.params, type2->uval.function.params))
                {
                    return true;
                }
            }
        }
    }
    else
        return false;
}

bool TypeCheck_Field(FieldListp f1, FieldListp f2)
{
    return TypeCheck_type(f1->type, f2->type);
}

bool TypeCheck_FieldList(FieldListp f1, FieldListp f2)
{
    bool isright = true;
    while (f1 != NULL && f2 != NULL)
    {
        if (TypeCheck_Field(f1, f2) == false)
        {
            isright = false;
            break;
        }
        f1 = f1->tail;
        f2 = f2->tail;
    }
    if (f1 != NULL || f2 != NULL)
        isright = false;
    return isright;
}

bool TypeCheck_TreeNode(TreeNode *tn1, TreeNode *tn2)
{
    return TypeCheck_Field(tn1->syn, tn2->syn);
}