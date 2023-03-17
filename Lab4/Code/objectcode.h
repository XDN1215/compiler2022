#include "intermediate.h"
#include <stdlib.h>
#define REGS_MAX 32

//变量描述符
typedef struct VarDesc *VarDescp;
typedef struct VarDesc{
    char name[5];
    int reg;//寄存器
    int offset;//在栈中的偏移量
    VarDescp next;//在栈中相邻的下一个变量
}VarDesc;

//寄存器描述符
typedef struct RegDesc *RegDescp;
typedef struct RegDesc{
    char name[5];//名字
    char alias[5];//别名
    int no;//编号
    int free;//是否空闲
    VarDescp var;//保存的变量
}RegDesc;

bool Generate_begin(char filename[]);//进行初始化的准备工作
bool Generate_objectcode(char filename[]);//生成目标代码
//各类中间代码的翻译
bool Generate_LAB(ICLnodep cur, FILE* fp);
bool Generate_FUNC(ICLnodep cur, FILE* fp);
bool Generate_ASSIGN(ICLnodep cur, FILE* fp);
bool Generate_ADD(ICLnodep cur, FILE* fp);
bool Generate_SUB(ICLnodep cur, FILE* fp);
bool Generate_MUL(ICLnodep cur, FILE* fp);
bool Generate_DIV(ICLnodep cur, FILE* fp);
bool Generate_GOTO(ICLnodep cur, FILE* fp);
bool Generate_IFGOTO(ICLnodep cur, FILE* fp);
bool Generate_RETURN(ICLnodep cur, FILE* fp);
bool Generate_DEC(ICLnodep cur, FILE* fp);
bool Generate_ARG(ICLnodep cur, FILE* fp);
bool Generate_CALL(ICLnodep cur, FILE* fp);
bool Generate_PARAM(ICLnodep cur, FILE* fp);
bool Generate_READ(ICLnodep cur, FILE* fp);
bool Generate_WRITE(ICLnodep cur, FILE* fp);

RegDescp New_RegDesc(int no);//初始化寄存器描述符
bool Init_Regs();//初始化32个寄存器的信息，名字、别名、编号、初始空闲、保存变量为NULL
int Get_RegForVar(FILE *fp, Operandp var);//返回变量所在寄存器（没有就分配一个）
bool SW_Reg(FILE *fp, int regno);//将寄存器的值写回栈
bool LW_Reg(FILE *fp, int regno, VarDescp var);//将栈中变量加载到寄存器
bool Print_Reg(FILE *fp, int regno);//打印寄存器别名

bool Push_Var(VarDescp var);//将变量存到活动记录中
bool Pop_Var();//将栈清空
VarDescp Get_Var(char name[]);//在栈中找到变量

bool pDebug(char* mesgs);
bool pError(char* mesgs);//打印异常，并退出程序