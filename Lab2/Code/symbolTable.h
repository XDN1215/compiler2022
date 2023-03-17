#include <stdbool.h>
//类型表示
typedef struct Type *Typep;
typedef struct FieldList *FieldListp;
typedef enum
{
    NOTHING,//用于初始化，不是任何类型
    BASIC,//基本类型
    ARRAY,//数组类型
    STRUCTURE,//结构体类型
    FUNCTIONDEF,//函数定义
    FUNCTIONDEC//函数声明
} Kind;
typedef union uval Uval;
typedef struct Type
{
    Kind kind;
    union uval
    {
        // 基本类型
        int basic;
        // 数组类型信息，由元素类型与数组大小构成
        struct
        {
            Typep elem;
            int size;
        } array;
        // 结构体类型
        FieldListp structure;
        //函数类型
        struct
        {
            Typep return_type;
            int argn;
            FieldListp args;
        } function;
    } uval;
} Type;

typedef struct FieldList
{
    char fieldname[32]; // 域的名字
    Typep type;      // 域的类型
    FieldListp tail; // 下一个域
} FieldList;

Typep Type_New();//新建并初始化一个Type节点
Typep Type_Set(Typep t);//新建一个Type节点并复制t指向的Type节点的值
FieldListp Field_New();//新建并初始化一个FiledList节点
FieldListp Field_Set(FieldListp fp);//新建一个FiledList节点并复制fp指向的FiledList节点的值
FieldListp FieldList_Set(FieldListp fp);//复制fp指向的FiledList节点的值，且递归复制fp->tail，直到fp为NULL


//符号表大小
#define SYMBOL_TABLE_SIZE 0x3fff
//符号表--散列表+open hashing
#define TABLE_SIZE SYMBOL_TABLE_SIZE
#define STACK_SIZE SYMBOL_TABLE_SIZE

//基于十字链表和open hashing散列表的符号表
typedef struct SymbolNode *SymbolNodep;
typedef struct SymbolNode **SymbolTable;
typedef enum
{
    NOTYPE,//用于初始化
    GLOBAL,//全局变量
    LOCAL,//局部变量
    FUNDEC,//函数声明
    FUNDEF,//函数定义
} Kind_;
typedef struct SymbolNode
{
    char name[32];
    Kind_ kind_;//类型
    Typep type;//类型信息
    int deepth;//深度信息，便于查找
    SymbolNodep next;//十字链表中的横向下一个
    SymbolNodep prev;//十字链表中的横向上一个
    SymbolNodep snext;//十字链表中的竖向下一个，是位于同一作用域中的节点
} SymbolNode;

unsigned int unsignedinthash_pjw(char *name); // hash函数
void HashTable_Initial(SymbolTable st);       //建立散列表
SymbolNodep HashTable_Search(int para, SymbolTable st, char *name, Kind_ k, int deepth, Kind t);//查表
bool HashTable_Insert(SymbolTable st, SymbolNodep sn); //填表
bool HashTable_Remove(SymbolTable st, SymbolNodep sn); //删除

SymbolNodep SymbolNode_New();//新建并初始化一个符号表节点
SymbolNodep SymbolNode_Set(char *name, Kind_ k, int deepth, Typep type);//新建一个符号表节点，且将此节点的值设置为对应参数

// Stack
typedef struct Stack *Stackp;
typedef struct Stack Stack;
struct Stack
{
    SymbolNodep* snps;
    int top;
    int size;
};
Stackp Stack_New(int size);//新建并初始化一个stack
bool Stack_Up(Stackp stack);//进入一个语句块，栈深度加一
bool Stack_Down(Stackp stack);//退出一个语句块，栈深度减一
bool Stack_Link(Stackp stack, SymbolNodep sn);//将节点连接到深度为栈顶的链表上
SymbolNodep Stack_Search(Stackp stack, char *name, int deepth);//查找符号表中深度为deepth且名字是name的节点
bool Stack_IsEmpty(Stackp stack);
int Stack_GetSize(Stackp stack);

bool sameStr(char *str1, char *str2);//判断两个字符串是否相同