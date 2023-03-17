#include "intermediate.h"
#include <stdarg.h>
//
ICLnodep head = NULL;                 //双向循环链表的附加头结点
int VarNum = 0;                       //计数变量，用于编号
int TempVarNum = 0;                   //计数临时变量，用于编号
int LabelNum = 0;                     //计数标号，用于编号
SymbolNodep st_im[SYMBOL_TABLE_SIZE]; //符号表，因为不存在作用域，所以只需要散列表即可，存储函数、变量、形参
ICLnodep newic = NULL;                //指向新构造的中间代码结点
Operandp con0 = NULL;                 //常量0
Operandp con1 = NULL;                 //常量1
Operandp arg_list[20][100];               //实参列表，顺序存储实参，倒序生成中间代码
int functop = -1;
int argn[20];                         //实参列表中的实参个数

//初始化
bool translate_begin(TreeNode *tn, char filename[])
{
    if (tn != NULL)
    {
        con0 = Create_Operand(0, CONSTANT, 0); //构造常量0，便于后续使用
        con1 = Create_Operand(0, CONSTANT, 1); //构造常量1，便于后续使用
        if (tn != NULL)
        {
            bool isright = true;
            for(int i =0;i<20;i++){
                argn[i]=0;
            }
            head = InterCodeList_Initial(); //双向循环链表的初始化
            HashTable_Initial(st_im);       //符号表的初始化
            translate_Program(tn);          //开始翻译语法树
            PrintInterCodes(filename);      //打印中间代码到指定文件
            return isright;
        }
    }
    return true;
}
//翻译函数
bool translate_Program(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        if (tn->childtype == 1) // ExtDefList
        {
            translate_ExtDefList(Child1);
        }
        return isright;
    }
    return true;
}
bool translate_ExtDefList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        if (tn->childtype == 1) // ExtDef ExtDefList
        {
            translate_ExtDef(Childi(tn, 1));
            translate_ExtDefList(Childi(tn, 2));
        }
        return isright;
    }
    return true;
}
bool translate_ExtDef(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 3) // Specifier FunDec CompSt
        {
            translate_FunDec(Child2);
            translate_CompSt(Child3);
        }
        return isright;
    }
    return true;
}
bool translate_FunDec(TreeNode *tn)
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
            SymbolNodep newsn = SymbolNode_Set(tn->syn->fieldname, FUNCTIONDEF, 0, tn->syn->type);
            HashTable_Insert(st_im, newsn);
            Operandp funcx = Create_Operand(0, FUNCTION, Child1->strval);
            InterCodeList_CandI(head, newic, FUNC, funcx);
            if (tn->childtype == 1) // ID LP VarList RP
            {
                translate_VarList(Child3);
            }
        }
        return isright;
    }
    return true;
}
bool translate_VarList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // ParamDec COMMA VarList
        {
            translate_ParamDec(Child1);
            translate_VarList(Child3);
        }
        else if (tn->childtype == 2) // ParamDec
        {
            translate_ParamDec(Child1);
        }
        return isright;
    }
    return true;
}
bool translate_ParamDec(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        if (tn->childtype == 1) // Specifier VarDec
        {
            SymbolNodep newsn = SymbolNode_Set(tn->syn->fieldname, LOCAL, 0, tn->syn->type);
            newsn->val_no = ++VarNum;
            if (tn->syn->type->kind == ARRAY || tn->syn->type->kind == STRUCTURE) //如果是数组或者结构体，参数传递传的是地址
                newsn->isaddr = 1;
            HashTable_Insert(st_im, newsn);
            Operandp varx = Create_Operand(0, VARIABLE, newsn->val_no);
            InterCodeList_CandI(head, newic, PARAM, varx);
        }
        return isright;
    }
    return true;
}

bool translate_CompSt(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // LC DefList StmtList RC
        {
            translate_DefList(Child2);
            translate_StmtList(Child3);
        }
        return isright;
    }
    return true;
}
bool translate_StmtList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        if (tn->childtype == 1) // Stmt StmtList
        {
            translate_Stmt(Child1);
            translate_StmtList(Child2);
        }
        return isright;
    }
    return true;
}
bool translate_Stmt(TreeNode *tn)
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
        switch (tn->childtype)
        {
        case 1: // Exp SEMI
        {
            translate_Exp(Child1, NULL);
            break;
        }
        case 2: // CompSt
        {
            translate_CompSt(Child1);
            break;
        }
        case 3: // RETURN Exp SEMI
        {
            Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
            translate_Exp(Child2, newtemp1);
            InterCodeList_CandI(head, newic, RETURN, newtemp1);
            break;
        }
        case 4: // IF LP Exp RP Stmt1
        {
            Operandp label1 = Create_Operand(0, LABEL, ++LabelNum);
            Operandp label2 = Create_Operand(0, LABEL, ++LabelNum);
            translate_Cond(Child3, label1, label2);
            InterCodeList_CandI(head, newic, LAB, label1);
            translate_Stmt(Child5);
            InterCodeList_CandI(head, newic, LAB, label2);
            break;
        }
        case 5: // IF LP Exp RP Stmt1 ELSE Stmt2
        {
            Operandp label1 = Create_Operand(0, LABEL, ++LabelNum);
            Operandp label2 = Create_Operand(0, LABEL, ++LabelNum);
            Operandp label3 = Create_Operand(0, LABEL, ++LabelNum);
            translate_Cond(Child3, label1, label2);
            InterCodeList_CandI(head, newic, LAB, label1);
            translate_Stmt(Child5);
            InterCodeList_CandI(head, newic, GOTO, label3);
            InterCodeList_CandI(head, newic, LAB, label2);
            translate_Stmt(Child7);
            InterCodeList_CandI(head, newic, LAB, label3);
            break;
        }
        case 6: // WHILE LP Exp RP Stmt1
        {
            Operandp label1 = Create_Operand(0, LABEL, ++LabelNum);
            Operandp label2 = Create_Operand(0, LABEL, ++LabelNum);
            Operandp label3 = Create_Operand(0, LABEL, ++LabelNum);
            InterCodeList_CandI(head, newic, LAB, label1);
            translate_Cond(Child3, label2, label3);
            InterCodeList_CandI(head, newic, LAB, label2);
            translate_Stmt(Child5);
            InterCodeList_CandI(head, newic, GOTO, label1);
            InterCodeList_CandI(head, newic, LAB, label3);
            break;
        }
        default:
            break;
        }
        return isright;
    }
    return true;
}

bool translate_DefList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        if (tn->childtype == 1) // Def DefList
        {
            TreeNode *Child1 = Childi(tn, 1);
            TreeNode *Child2 = Childi(tn, 2);
            translate_Def(Child1);
            translate_DefList(Child2);
        }
        return isright;
    }
    return true;
}
bool translate_Def(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        if (tn->childtype == 1) // Specifier DecList SEMI
        {
            TreeNode *Child2 = Childi(tn, 2);
            translate_DecList(Child2);
        }
        return isright;
    }
    return true;
}
bool translate_DecList(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->childtype == 1) // Dec
        {
            translate_Dec(Child1);
        }
        else if (tn->childtype == 2) // Dec COMMA DecList
        {
            translate_Dec(Child1);
            translate_DecList(Child3);
        }
        return isright;
    }
    return true;
}
bool translate_Dec(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        if (tn->isstrdef == 0) //不属于结构体域的变量定义需要处理
        {
            SymbolNodep newsn = SymbolNode_Set(tn->syn->fieldname, LOCAL, 0, tn->syn->type);
            newsn->val_no = ++VarNum;
            HashTable_Insert(st_im, newsn);
            if (tn->childtype == 1) // VarDec
            {
                Operandp varx = Create_Operand(0, VARIABLE, newsn->val_no);
                if (newsn->type->kind == ARRAY || newsn->type->kind == STRUCTURE)
                    InterCodeList_CandI(head, newic, DEC, varx, Get_Width(newsn->type));
            }
            else if (tn->childtype == 2) // VarDec ASSIGNOP Exp
            {
                Operandp varx = Create_Operand(0, VARIABLE, newsn->val_no);
                if (newsn->type->kind == ARRAY || newsn->type->kind == STRUCTURE)
                    InterCodeList_CandI(head, newic, DEC, varx, Get_Width(newsn->type));
                Operandp place = Create_Operand(0, TEMPVAR, ++TempVarNum);
                translate_Exp(Child3, place);
                if (Child1->syn->type->kind == BASIC)
                {
                    if (place->isaddr == 0)
                        InterCodeList_CandI(head, newic, ASSIGN, varx, place, DEFAULT);
                    else
                        InterCodeList_CandI(head, newic, ASSIGN, varx, place, GETDATA);
                }
            }
        }
        return isright;
    }
    return true;
}

bool translate_Exp(TreeNode *tn, Operandp place)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        switch (tn->childtype)
        {
        case 17: // INT
        {
            Operandp consx = Create_Operand(0, CONSTANT, Child1->val.ival);
            if (place != NULL)
                InterCodeList_CandI(head, newic, ASSIGN, place, consx, DEFAULT);
            break;
        }
        case 16: // ID
        {
            SymbolNodep p = HashTable_Search(0, st_im, Child1->strval, 0, 0, -1);
            if (p != NULL)
            {
                Operandp varx = Create_Operand(0, VARIABLE, p->val_no);
                if (place != NULL)
                {
                    if (p->isaddr == 0)
                    {
                        if (place->isaddr == 0)
                            InterCodeList_CandI(head, newic, ASSIGN, place, varx, DEFAULT);
                        else
                        {
                            if (p->type->kind == ARRAY || p->type->kind == STRUCTURE)
                                InterCodeList_CandI(head, newic, ASSIGN, place, varx, GETADDR);
                            else
                                InterCodeList_CandI(head, newic, ASSIGN, place, varx, SETDATA);
                        }
                    }
                    else
                    {
                        if (place->isaddr == 0)
                            InterCodeList_CandI(head, newic, ASSIGN, place, varx, GETDATA);
                        else
                            InterCodeList_CandI(head, newic, ASSIGN, place, varx, DEFAULT);
                    }
                }
            }
            break;
        }
        case 1: // ASSIGN
        {
            if (Child1->childtype == 16) // ID
            {
                SymbolNodep p = HashTable_Search(0, st_im, Child1->firstchild->strval, 0, 0, -1);
                if (p != NULL)
                {
                    Operandp varx = Create_Operand(0, VARIABLE, p->val_no);
                    Operandp newtemp = Create_Operand(0, TEMPVAR, ++TempVarNum);
                    translate_Exp(Child3, newtemp);
                    InterCodeList_CandI(head, newic, ASSIGN, varx, newtemp, DEFAULT);
                    if (place != NULL)
                        InterCodeList_CandI(head, newic, ASSIGN, place, varx, DEFAULT);
                }
            }
            else if (Child1->childtype == 14)
            { //数组
                Operandp newtemp1 = Create_Operand(1, TEMPVAR, ++TempVarNum);
                translate_Exp(Child1, newtemp1);
                Operandp newtemp2 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                if (Child3->syn->type->kind != BASIC)
                    newtemp2->isaddr = 1;
                translate_Exp(Child3, newtemp2);
                if (newtemp2->isaddr == 0)
                {
                    InterCodeList_CandI(head, newic, ASSIGN, newtemp1, newtemp2, SETDATA);
                }
                if (place != NULL)
                {
                    if (place->isaddr == 0)
                        InterCodeList_CandI(head, newic, ASSIGN, place, newtemp1, GETDATA);
                    else
                        InterCodeList_CandI(head, newic, ASSIGN, place, newtemp1, DEFAULT);
                }
            }
            else if (Child1->childtype == 15)
            { //结构体
                Operandp newtemp1 = Create_Operand(1, TEMPVAR, ++TempVarNum);
                translate_Exp(Child1, newtemp1);
                Operandp newtemp2 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                if (Child3->syn->type->kind != BASIC)
                    newtemp2->isaddr = 1;
                translate_Exp(Child3, newtemp2);
                if (newtemp2->isaddr == 0)
                {
                    InterCodeList_CandI(head, newic, ASSIGN, newtemp1, newtemp2, SETDATA);
                }
                if (place != NULL)
                {
                    if (place->isaddr == 0)
                        InterCodeList_CandI(head, newic, ASSIGN, place, newtemp1, GETDATA);
                    else
                        InterCodeList_CandI(head, newic, ASSIGN, place, newtemp1, DEFAULT);
                }
            }
            break;
        }
        case 5: // PLUS
        case 6: // SUB
        case 7: // MUL
        case 8: // DIV
        {
            Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
            Operandp newtemp2 = Create_Operand(0, TEMPVAR, ++TempVarNum);
            translate_Exp(Child1, newtemp1);
            translate_Exp(Child3, newtemp2);
            if (place != NULL)
            {
                InterCodeList_CandI(head, newic, (icKind)(tn->childtype - 2), place, newtemp1, newtemp2, DEFAULT);
            }
            break;
        }
        case 10: // MINUS Exp
        {
            Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
            translate_Exp(Child2, newtemp1);
            if (place != NULL)
                InterCodeList_CandI(head, newic, SUB, place, con0, newtemp1, DEFAULT);
            break;
        }
        case 4:  // Exp RELOP Exp
        case 11: // NOT Exp
        case 2:  // Exp AND Exp
        case 3:  // Exp OR Exp
        {
            Operandp label1 = Create_Operand(0, LABEL, ++LabelNum);
            Operandp label2 = Create_Operand(0, LABEL, ++LabelNum);
            if (place != NULL)
                InterCodeList_CandI(head, newic, ASSIGN, place, con0, DEFAULT);
            translate_Cond(tn, label1, label2);
            InterCodeList_CandI(head, newic, LAB, label1);
            if (place != NULL)
                InterCodeList_CandI(head, newic, ASSIGN, place, con1, DEFAULT);
            InterCodeList_CandI(head, newic, LAB, label2);
            break;
        }
        case 13: // ID LP RP
        {
            SymbolNodep p = HashTable_Search(1, st_im, Child1->strval, FUNCTIONDEF, 0, -1);
            if (p != NULL)
            {
                if (sameStr(p->name, "read"))
                {
                    if (place != NULL)
                        InterCodeList_CandI(head, newic, READ, place);
                }
                else
                {
                    Operandp funcx = Create_Operand(0, FUNCTION, p->name);
                    if (place != NULL)
                        InterCodeList_CandI(head, newic, CALL, place, funcx);
                    else
                    {
                        Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                        InterCodeList_CandI(head, newic, CALL, newtemp1, funcx);
                    }
                }
            }
            break;
        }
        case 12: // ID LP Args RP
        {
            functop++;
            SymbolNodep p = HashTable_Search(1, st_im, Child1->strval, FUNCTIONDEF, 0, -1);
            if (p != NULL)
            {
                Operandp funcx = Create_Operand(0, FUNCTION, p->name);
                if (sameStr(p->name, "write"))
                {
                    translate_Args(Child3);
                    InterCodeList_CandI(head, newic, WRITE, arg_list[functop][0]);
                    if (place != NULL)
                        InterCodeList_CandI(head, newic, ASSIGN, place, con0, DEFAULT);
                }
                else
                {
                    translate_Args(Child3);
                    for (int i = 0; i < argn[functop]; i++)
                    {
                        InterCodeList_CandI(head, newic, ARG, arg_list[functop][argn[functop] - i - 1]);
                    }
                    if (place != NULL)
                        InterCodeList_CandI(head, newic, CALL, place, funcx);
                    else
                    {
                        Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                        InterCodeList_CandI(head, newic, CALL, newtemp1, funcx);
                    }
                }
                argn[functop] = 0;
                functop--;
            }
            break;
        }
        case 9: // LP Exp RP
        {
            translate_Exp(Child2, place);
            break;
        }
        case 14: // Exp LB Exp RB
        {
            if (Child1->childtype == 16)
            {
                SymbolNodep p = HashTable_Search(0, st_im, Child1->firstchild->strval, LOCAL, 0, -1);
                if (p != NULL)
                {
                    Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                    translate_Exp(Child3, newtemp1);
                    Operandp width = Create_Operand(0, CONSTANT, Get_Width(tn->syn->type));
                    Operandp newtemp2 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                    InterCodeList_CandI(head, newic, MUL, newtemp2, newtemp1, width, DEFAULT);
                    if (place != NULL)
                    {
                        if (place->isaddr == 0)
                        {
                            Operandp varx = Create_Operand(p->isaddr, VARIABLE, p->val_no);
                            Operandp newtemp3 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                            if (varx->isaddr == 0)
                                InterCodeList_CandI(head, newic, ADD, newtemp3, varx, newtemp2, GETADDR);
                            else
                                InterCodeList_CandI(head, newic, ADD, newtemp3, varx, newtemp2, DEFAULT);
                            InterCodeList_CandI(head, newic, ASSIGN, place, newtemp3, GETDATA);
                        }
                        else
                        {
                            Operandp varx = Create_Operand(p->isaddr, VARIABLE, p->val_no);
                            if (varx->isaddr == 0)
                                InterCodeList_CandI(head, newic, ADD, place, varx, newtemp2, GETADDR);
                            else
                                InterCodeList_CandI(head, newic, ADD, place, varx, newtemp2, DEFAULT);
                        }
                    }
                }
            }
            else
            {
                Operandp newtemp1 = Create_Operand(1, TEMPVAR, ++TempVarNum);
                translate_Exp(Child1, newtemp1);
                Operandp newtemp2 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                translate_Exp(Child3, newtemp2);
                TreeNode *arrayname = Child1;
                while (sameStr(arrayname->firstchild->name, "ID") == false)
                {
                    arrayname = arrayname->firstchild;
                }
                SymbolNodep p = HashTable_Search(0, st_im, arrayname->firstchild->strval, LOCAL, 0, -1);
                if (p != NULL)
                {
                    Operandp width = Create_Operand(0, CONSTANT, Get_Width(tn->syn->type));
                    Operandp newtemp3 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                    InterCodeList_CandI(head, newic, MUL, newtemp3, newtemp2, width, DEFAULT);
                    if (place != NULL)
                    {
                        if (tn->syn->type->kind == BASIC)
                        {
                            if (place->isaddr == 0)
                            {
                                Operandp newtemp4 = Create_Operand(0, TEMPVAR, ++TempVarNum);
                                InterCodeList_CandI(head, newic, ADD, newtemp4, newtemp1, newtemp3, DEFAULT);
                                InterCodeList_CandI(head, newic, ASSIGN, place, newtemp4, GETDATA);
                            }
                            else
                                InterCodeList_CandI(head, newic, ADD, place, newtemp1, newtemp3, DEFAULT);
                        }
                        else
                            InterCodeList_CandI(head, newic, ADD, place, newtemp1, newtemp3, DEFAULT);
                    }
                }
            }
            break;
        }
        case 15: // Exp DOT ID
        {
            if (Child1->childtype == 16)
            {
                SymbolNodep p = HashTable_Search(0, st_im, Child1->firstchild->strval, LOCAL, 0, -1);
                if (p != NULL)
                {
                    FieldListp fieldhead = p->type->uval.structure;
                    int addr_toadd = 0;
                    while (fieldhead != NULL && sameStr(fieldhead->fieldname, Child3->strval) == false)
                    {
                        addr_toadd = addr_toadd + Get_Width(fieldhead->type);
                        fieldhead = fieldhead->tail;
                    }
                    Operandp conx = Create_Operand(0, CONSTANT, addr_toadd);
                    if (place != NULL)
                    {
                        if (place->isaddr == 0)
                        {
                            Operandp varx = Create_Operand(p->isaddr, VARIABLE, p->val_no);
                            Operandp newtemp = Create_Operand(0, TEMPVAR, ++TempVarNum);
                            if (varx->isaddr == 0)
                                InterCodeList_CandI(head, newic, ADD, newtemp, varx, conx, GETADDR);
                            else
                                InterCodeList_CandI(head, newic, ADD, newtemp, varx, conx, DEFAULT);
                            InterCodeList_CandI(head, newic, ASSIGN, place, newtemp, GETDATA);
                        }
                        else
                        {
                            Operandp varx = Create_Operand(p->isaddr, VARIABLE, p->val_no);
                            if (varx->isaddr == 0)
                                InterCodeList_CandI(head, newic, ADD, place, varx, conx, GETADDR);
                            else
                                InterCodeList_CandI(head, newic, ADD, place, varx, conx, DEFAULT);
                        }
                    }
                }
                break;
            }
            else
            {
                Operandp newtemp1 = Create_Operand(1, TEMPVAR, ++TempVarNum);
                translate_Exp(Child1, newtemp1);
                if (Child1->syn->type->kind == STRUCTURE)
                {
                    FieldListp fieldhead = Child1->syn->type->uval.structure;
                    int addr_toadd = 0;
                    while (fieldhead != NULL && sameStr(fieldhead->fieldname, Child3->strval) == false)
                    {
                        addr_toadd = addr_toadd + Get_Width(fieldhead->type);
                        fieldhead = fieldhead->tail;
                    }
                    Operandp conx = Create_Operand(0, CONSTANT, addr_toadd);
                    if (place != NULL)
                    {
                        if (tn->syn->type->kind == BASIC)
                        {
                            if (place->isaddr == 0)
                            {
                                Operandp newtemp2 = Create_Operand(1, TEMPVAR, ++TempVarNum);
                                InterCodeList_CandI(head, newic, ADD, newtemp2, newtemp1, conx, DEFAULT);
                                InterCodeList_CandI(head, newic, ASSIGN, place, newtemp2, GETDATA);
                            }
                            else
                                InterCodeList_CandI(head, newic, ADD, place, newtemp1, conx, DEFAULT);
                        }
                        else
                            InterCodeList_CandI(head, newic, ADD, place, newtemp1, conx, DEFAULT);
                    }
                }
            }
            break;
        }
        default:
            break;
        }
        return isright;
    }
    return true;
}
bool translate_Args(TreeNode *tn)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        switch (tn->childtype)
        {
        case 2: // Exp
        {
            Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
            if (Child1->syn->type->kind != BASIC)
                newtemp1->isaddr = 1;
            translate_Exp(Child1, newtemp1);
            arg_list[functop][argn[functop]++] = newtemp1;
            break;
        }
        case 1: // Exp COMMA Args
        {
            Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
            if (Child1->syn->type->kind != BASIC)
                newtemp1->isaddr = 1;
            translate_Exp(Child1, newtemp1);
            arg_list[functop][argn[functop]++] = newtemp1;
            translate_Args(Child3);
            break;
        }
        default:
            break;
        }
        return isright;
    }
    return true;
}
bool translate_Cond(TreeNode *tn, Operandp label_true, Operandp label_false)
{
    if (tn != NULL)
    {
        bool isright = true;
        TreeNode *Child1 = Childi(tn, 1);
        TreeNode *Child2 = Childi(tn, 2);
        TreeNode *Child3 = Childi(tn, 3);
        switch (tn->childtype)
        {
        case 4: // Exp RELOP Exp
        {
            Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
            Operandp newtemp2 = Create_Operand(0, TEMPVAR, ++TempVarNum);
            translate_Exp(Child1, newtemp1);
            translate_Exp(Child3, newtemp2);
            InterCodeList_CandI(head, newic, IFGOTO, newtemp1, newtemp2, label_true, Child2->strval);
            InterCodeList_CandI(head, newic, GOTO, label_false);
            break;
        }
        case 11: // NOT Exp
        {
            translate_Cond(Child2, label_false, label_true);
            break;
        }
        case 2: // Exp AND Exp
        {
            Operandp label1 = Create_Operand(0, LABEL, ++LabelNum);
            translate_Cond(Child1, label1, label_false);
            InterCodeList_CandI(head, newic, LAB, label1);
            translate_Cond(Child3, label_true, label_false);
            break;
        }
        case 3: // Exp OR Exp
        {
            Operandp label1 = Create_Operand(0, LABEL, ++LabelNum);
            translate_Cond(Child1, label_true, label1);
            InterCodeList_CandI(head, newic, LAB, label1);
            translate_Cond(Child3, label_true, label_false);
            break;
        }
        default: // othercases
        {
            Operandp newtemp1 = Create_Operand(0, TEMPVAR, ++TempVarNum);
            translate_Exp(tn, newtemp1);
            InterCodeList_CandI(head, newic, IFGOTO, newtemp1, con0, label_true, "!=");
            InterCodeList_CandI(head, newic, GOTO, label_false);
            break;
        }
        }
        return isright;
    }
    return true;
}

//构造函数
Operandp Create_Operand(int isaddr, opKind kind, ...)
{
    Operandp newp = (Operandp)malloc(sizeof(Operand));
    newp->isaddr = isaddr;
    newp->kind = kind;
    //lab 4
    /*newp->desc= (VarDescp)malloc(sizeof(VarDesc));
    newp->desc->mem=0;
    newp->desc->next=NULL;
    newp->desc->regno=-1;*/
    char noname[32];
    va_list params;
    va_start(params, kind);
    switch (newp->kind)
    {
    case VARIABLE:
        newp->u.var_no = va_arg(params, int);
        strcpy(newp->name, "v");
        break;
    case CONSTANT:
        newp->u.value = va_arg(params, int);
        break;
    case TEMPVAR:
        newp->u.var_no = va_arg(params, int);
        strcpy(newp->name, "t");
        break;
    case LABEL:
        newp->u.var_no = va_arg(params, int);
        break;
    case FUNCTION:
        strcpy(newp->u.funcname, va_arg(params, char *));
        break;
    default:
        break;
    }
    va_end(params);
    if(newp->kind==VARIABLE || newp->kind==TEMPVAR){
        sprintf(noname, "%d", newp->u.var_no);
        strcat(newp->name, noname);
    }
    return newp;
}
bool InterCodeList_CandI(ICLnodep first, ICLnodep toinsert, icKind kind, ...)
{
    bool isright = true;
    ICLnodep newp = (ICLnodep)malloc(sizeof(ICLnode));
    newp->code.kind = kind;
    newp->next = NULL;
    newp->prev = NULL;
    va_list params;
    va_start(params, kind);
    if (newp->code.kind == ASSIGN || newp->code.kind == CALL)
    {
        newp->code.u.assign.left = va_arg(params, Operandp);
        newp->code.u.assign.right = va_arg(params, Operandp);
        newp->code.u.assign.assigntype = va_arg(params, AssignType);
        if (newp->code.u.assign.left != NULL && newp->code.u.assign.right != NULL)
            isright = true;
        else
            isright = false;
    }
    else if (newp->code.kind == ADD || newp->code.kind == SUB || newp->code.kind == MUL || newp->code.kind == DIV)
    {
        newp->code.u.binop.result = va_arg(params, Operandp);
        newp->code.u.binop.op1 = va_arg(params, Operandp);
        newp->code.u.binop.op2 = va_arg(params, Operandp);
        newp->code.u.binop.assigntype = va_arg(params, AssignType);
        if (newp->code.u.binop.result != NULL && newp->code.u.binop.op1 != NULL && newp->code.u.binop.op2 != NULL)
            isright = true;
        else
            isright = false;
    }
    else if (newp->code.kind == IFGOTO)
    {
        newp->code.u.ifgoto.op1 = va_arg(params, Operandp);
        newp->code.u.ifgoto.op2 = va_arg(params, Operandp);
        newp->code.u.ifgoto.label = va_arg(params, Operandp);
        strcpy(newp->code.u.ifgoto.relop, va_arg(params, char *));
        if (newp->code.u.ifgoto.op1 != NULL && newp->code.u.ifgoto.op2 != NULL && newp->code.u.ifgoto.label != NULL)
            isright = true;
        else
            isright = false;
    }
    else if (newp->code.kind == DEC)
    {
        newp->code.u.dec.op = va_arg(params, Operandp);
        newp->code.u.dec.size = va_arg(params, int);
        if (newp->code.u.dec.op != NULL)
            isright = true;
        else
            isright = false;
    }
    else
    {
        newp->code.u.oneop.op = va_arg(params, Operandp);
        if (newp->code.u.oneop.op != NULL)
            isright = true;
        else
            isright = false;
    }
    va_end(params);
    if (isright)
        InterCodeList_Insert(first, newp);
    return true;
}

//
ICLnodep InterCodeList_New()
{
    ICLnodep newp = (ICLnodep)malloc(sizeof(ICLnode));
    newp->next = NULL;
    newp->prev = NULL;
    return newp;
}

//双向链表的建立、结点插入
ICLnodep InterCodeList_Initial()
{
    ICLnodep newp = InterCodeList_New();
    if (newp == NULL)
        return newp;
    newp->next = newp;
    newp->prev = newp;
    return newp;
}
bool InterCodeList_Insert(ICLnodep first, ICLnodep toinsert)
{
    toinsert->next = first;
    toinsert->prev = first->prev;
    first->prev->next = toinsert;
    first->prev = toinsert;
}

//打印函数
void PrintOprand(FILE *fp, Operandp op)
{
    switch (op->kind)
    {
    case VARIABLE:
        fprintf(fp, "v%d", op->u.var_no);
        break;
    case CONSTANT:
        fprintf(fp, "#%d", op->u.value);
        break;
    case TEMPVAR:
        fprintf(fp, "t%d", op->u.var_no);
        break;
    case LABEL:
        fprintf(fp, "label%d", op->u.var_no);
        break;
    case FUNCTION:
        fprintf(fp, "%s", op->u.funcname);
        break;
    default:
        break;
    }
}
void PrintInterCodes(char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
        printf("Error! \n");
    else
    {
        if (head != NULL)
        {
            ICLnode *cur = head->next;
            while (cur != head)
            {
                switch (cur->code.kind)
                {
                case LAB:
                    fprintf(fp, "LABEL ");
                    PrintOprand(fp, cur->code.u.oneop.op);
                    fprintf(fp, " :\n");
                    break;
                case FUNC:
                    fprintf(fp, "FUNCTION ");
                    PrintOprand(fp, cur->code.u.oneop.op);
                    fprintf(fp, " :\n");
                    break;
                case ASSIGN:
                    switch (cur->code.u.assign.assigntype)
                    {
                    case DEFAULT:
                        PrintOprand(fp, cur->code.u.assign.left);
                        fprintf(fp, " := ");
                        PrintOprand(fp, cur->code.u.assign.right);
                        fprintf(fp, "\n");
                        break;
                    case GETADDR:
                        PrintOprand(fp, cur->code.u.assign.left);
                        fprintf(fp, " := &");
                        PrintOprand(fp, cur->code.u.assign.right);
                        fprintf(fp, "\n");
                        break;
                    case GETDATA:
                        PrintOprand(fp, cur->code.u.assign.left);
                        fprintf(fp, " := *");
                        PrintOprand(fp, cur->code.u.assign.right);
                        fprintf(fp, "\n");
                        break;
                    case SETDATA:
                        fprintf(fp, "*");
                        PrintOprand(fp, cur->code.u.assign.left);
                        fprintf(fp, " := ");
                        PrintOprand(fp, cur->code.u.assign.right);
                        fprintf(fp, "\n");
                        break;
                    default:
                        break;
                    }
                    break;
                case ADD:
                    if (cur->code.u.binop.assigntype == GETADDR)
                    {
                        PrintOprand(fp, cur->code.u.binop.result);
                        fprintf(fp, " := &");
                        PrintOprand(fp, cur->code.u.binop.op1);
                        fprintf(fp, " + ");
                        PrintOprand(fp, cur->code.u.binop.op2);
                        fprintf(fp, "\n");
                    }
                    else
                    {
                        PrintOprand(fp, cur->code.u.binop.result);
                        fprintf(fp, " := ");
                        PrintOprand(fp, cur->code.u.binop.op1);
                        fprintf(fp, " + ");
                        PrintOprand(fp, cur->code.u.binop.op2);
                        fprintf(fp, "\n");
                    }
                    break;
                case SUB:
                    PrintOprand(fp, cur->code.u.binop.result);
                    fprintf(fp, " := ");
                    PrintOprand(fp, cur->code.u.binop.op1);
                    fprintf(fp, " - ");
                    PrintOprand(fp, cur->code.u.binop.op2);
                    fprintf(fp, "\n");
                    break;
                case MUL:
                    PrintOprand(fp, cur->code.u.binop.result);
                    fprintf(fp, " := ");
                    PrintOprand(fp, cur->code.u.binop.op1);
                    fprintf(fp, " * ");
                    PrintOprand(fp, cur->code.u.binop.op2);
                    fprintf(fp, "\n");
                    break;
                case DIV:
                    PrintOprand(fp, cur->code.u.binop.result);
                    fprintf(fp, " := ");
                    PrintOprand(fp, cur->code.u.binop.op1);
                    fprintf(fp, " / ");
                    PrintOprand(fp, cur->code.u.binop.op2);
                    fprintf(fp, "\n");
                    break;
                case GOTO:
                    fprintf(fp, "GOTO ");
                    PrintOprand(fp, cur->code.u.oneop.op);
                    fprintf(fp, "\n");
                    break;
                case IFGOTO:
                    fprintf(fp, "IF ");
                    PrintOprand(fp, cur->code.u.ifgoto.op1);
                    fprintf(fp, " %s ", cur->code.u.ifgoto.relop);
                    PrintOprand(fp, cur->code.u.ifgoto.op2);
                    fprintf(fp, " GOTO ");
                    PrintOprand(fp, cur->code.u.ifgoto.label);
                    fprintf(fp, "\n");
                    break;
                case RETURN:
                    fprintf(fp, "RETURN ");
                    PrintOprand(fp, cur->code.u.oneop.op);
                    fprintf(fp, "\n");
                    break;
                case DEC:
                    fprintf(fp, "DEC ");
                    PrintOprand(fp, cur->code.u.dec.op);
                    fprintf(fp, " %d\n", cur->code.u.dec.size);
                    break;
                case ARG:
                    fprintf(fp, "ARG ");
                    PrintOprand(fp, cur->code.u.oneop.op);
                    fprintf(fp, "\n");
                    break;
                case CALL:
                    PrintOprand(fp, cur->code.u.assign.left);
                    fprintf(fp, " := CALL ");
                    PrintOprand(fp, cur->code.u.assign.right);
                    fprintf(fp, "\n");
                    break;
                case PARAM:
                    fprintf(fp, "PARAM ");
                    PrintOprand(fp, cur->code.u.oneop.op);
                    fprintf(fp, "\n");
                    break;
                case READ:
                    fprintf(fp, "READ ");
                    PrintOprand(fp, cur->code.u.oneop.op);
                    fprintf(fp, "\n");
                    break;
                case WRITE:
                    fprintf(fp, "WRITE ");
                    PrintOprand(fp, cur->code.u.oneop.op);
                    fprintf(fp, "\n");
                    break;
                default:
                    break;
                }
                cur = cur->next;
            }
        }
        fclose(fp);
    }
}