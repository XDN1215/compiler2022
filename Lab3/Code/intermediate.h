#include <stdio.h>
#include <stdbool.h>
#include "semantic.h"

//单条中间代码的数据结构
typedef struct Operand *Operandp;
typedef enum
{
    VARIABLE, //变量
    CONSTANT, //常量
    TEMPVAR,  //临时变量
    LABEL,    //标号
    FUNCTION  //函数
} opKind;
typedef struct Operand
{
    opKind kind; //操作数的类型
    union
    {
        int var_no;        //变量、临时变量、标号的数字编号
        int value;         //常量的值
        char funcname[32]; //函数的名字
    } u;
    int isaddr; //变量、临时变量代表的是地址还是值
} Operand;

typedef enum
{
    LAB,
    FUNC,
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    GOTO,
    IFGOTO,
    RETURN,
    DEC,
    ARG,
    CALL,
    PARAM,
    READ,
    WRITE
} icKind;
typedef enum AssignType // 便于打印函数根据AssignType分类打印
{
    DEFAULT, // x := y
    GETADDR, // x := &y
    GETDATA, // x := *y
    SETDATA, //*x := y
} AssignType;
typedef struct InterCode
{
    icKind kind; // 中间代码的类型
    union
    {
        struct
        {
            Operandp op;
        } oneop; // LAB,FUNC,GOTO,RETURN,ARG,PARAM,READ,WRITE
        struct
        {
            Operandp right, left;
            AssignType assigntype;
        } assign; // ASSIGN,CALL
        struct
        {
            Operandp result, op1, op2;
            AssignType assigntype;
        } binop; // ADD,SUB,MUL,DIV
        struct
        {
            Operandp op1, op2, label;
            char relop[5];
        } ifgoto; // IFGOTO
        struct
        {
            Operandp op;
            int size;
        } dec; // DEC
    } u;
} InterCode;

// 双向链表
typedef struct ICLnode *ICLnodep;
typedef struct ICLnode
{
    InterCode code;
    struct ICLnode *prev, *next;
} ICLnode;

// 构造函数
Operandp Create_Operand(int isaddr, opKind kind, ...);
// 简化中间代码结点的构造与插入，合并成一个函数Create and Insert
bool InterCodeList_CandI(ICLnodep first, ICLnodep toinsert, icKind kind, ...);

ICLnodep InterCodeList_New();
// 双向链表的建立、结点插入
ICLnodep InterCodeList_Initial();
bool InterCodeList_Insert(ICLnodep first, ICLnodep toinsert);

// 初始化，main函数调用
bool translate_begin(TreeNode *tn, char filename[]);
// 翻译函数
bool translate_Program(TreeNode *tn);
bool translate_ExtDefList(TreeNode *tn);
bool translate_ExtDef(TreeNode *tn);

bool translate_FunDec(TreeNode *tn);
bool translate_VarList(TreeNode *tn);
bool translate_ParamDec(TreeNode *tn);

bool translate_CompSt(TreeNode *tn);
bool translate_StmtList(TreeNode *tn);
bool translate_Stmt(TreeNode *tn);

bool translate_DefList(TreeNode *tn);
bool translate_Def(TreeNode *tn);
bool translate_DecList(TreeNode *tn);
bool translate_Dec(TreeNode *tn);

bool translate_Exp(TreeNode *tn, Operandp place);
bool translate_Args(TreeNode *tn);

bool translate_Cond(TreeNode *tn, Operandp op1, Operandp op2);

// 打印函数
void PrintOprand(FILE *fp, Operandp op);
void PrintInterCodes(char *fname);