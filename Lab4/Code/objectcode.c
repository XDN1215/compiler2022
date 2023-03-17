#include "objectcode.h"
//#define DEBUG
//
extern ICLnodep head; 
RegDescp regdescs[REGS_MAX];
char numstr[32];
VarDescp stack=NULL;
int frameSize=20000;
int curReg=0;
int Paramn=0;int paramsumn=0;
int Argn=0;int ArgCount=0;
int spoffset=0;
int regx=-1,regy=-1,regz=-1;
//

bool Generate_begin(char filename[])
{
    Init_Regs();
    Generate_objectcode(filename);
}
bool Generate_objectcode(char filename[])
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
        printf("File Open Failed! \n");
    else
    {
        fprintf(fp, ".data\n");
        fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
        fprintf(fp, "_ret: .asciiz \"\\n\"\n");
        fprintf(fp, ".globl main\n");
        fprintf(fp, ".text\n");
        fprintf(fp, "read:\n");
        fprintf(fp, "\tli $v0, 4\n");
        fprintf(fp, "\tla $a0, _prompt\n");
        fprintf(fp, "\tsyscall\n");
        fprintf(fp, "\tli $v0, 5\n");
        fprintf(fp, "\tsyscall\n");
        fprintf(fp, "\tjr $ra\n\n");
        fprintf(fp, "write:\n");
        fprintf(fp, "\tli $v0, 1\n");
        fprintf(fp, "\tsyscall\n");
        fprintf(fp, "\tli $v0, 4\n");
        fprintf(fp, "\tla $a0, _ret\n");
        fprintf(fp, "\tsyscall\n");
        fprintf(fp, "\tmove $v0, $0\n");
        fprintf(fp, "\tjr $ra\n\n");

        int intercodei=0;char megs[100];
        if (head != NULL)
        {
            ICLnode *cur = head->next;
            while (cur != head)
            {
                intercodei++;
                sprintf(megs, "InterCodei---------------%d----------------%d\n", intercodei, cur->code.kind);
                //pDebug(megs);
                #ifdef DEBUG
                fprintf(fp, "InterCodei---------------%d\n", intercodei);
                #endif
                switch (cur->code.kind)
                {
                case LAB:
                    #ifdef DEBUG
                    fprintf(fp, "\nLAB\n");
                    #endif
                    Generate_LAB(cur, fp);
                    break;
                case FUNC:
                    #ifdef DEBUG
                    fprintf(fp, "\nFUNC\n");
                    #endif
                    Generate_FUNC(cur, fp);
                    break;
                case ASSIGN:
                    #ifdef DEBUG
                    fprintf(fp, "\nASSIGN\n");
                    #endif
                    Generate_ASSIGN(cur, fp);
                    break;
                case ADD:
                    #ifdef DEBUG
                    fprintf(fp, "\nADD\n");
                    #endif
                    Generate_ADD(cur, fp);
                    break;
                case SUB:
                    #ifdef DEBUG
                    fprintf(fp, "\nSUB\n");
                    #endif
                    Generate_SUB(cur, fp);
                    break;
                case MUL:
                    #ifdef DEBUG
                    fprintf(fp, "\nMUL\n");
                    #endif
                    Generate_MUL(cur, fp);
                    break;
                case DIV:
                    #ifdef DEBUG
                    fprintf(fp, "\nDIV\n");
                    #endif
                    Generate_DIV(cur, fp);
                    break;
                case GOTO:
                    #ifdef DEBUG
                    fprintf(fp, "\nGOTO\n");
                    #endif
                    Generate_GOTO(cur, fp);
                    break;
                case IFGOTO:
                    #ifdef DEBUG
                    fprintf(fp, "\nIFGOTO\n");
                    #endif
                    Generate_IFGOTO(cur, fp);
                    break;
                case RETURN:
                    #ifdef DEBUG
                    fprintf(fp, "\nRETURN\n");
                    #endif
                    Generate_RETURN(cur, fp);
                    break;
                case DEC:
                    #ifdef DEBUG
                    fprintf(fp, "\nDEC\n");
                    #endif
                    Generate_DEC(cur, fp);
                    break;
                case ARG:
                    #ifdef DEBUG
                    fprintf(fp, "\nARG\n");
                    #endif
                    Generate_ARG(cur, fp);
                    break;
                case CALL:
                    #ifdef DEBUG
                    fprintf(fp, "\nCALL\n");
                    #endif
                    Generate_CALL(cur, fp);
                    break;
                case PARAM:
                    #ifdef DEBUG
                    fprintf(fp, "\nPARAM\n");
                    #endif
                    Generate_PARAM(cur, fp);
                    break;
                case READ:
                    #ifdef DEBUG
                    fprintf(fp, "\nREAD\n");
                    #endif
                    Generate_READ(cur, fp);
                    break;
                case WRITE:
                    #ifdef DEBUG
                    fprintf(fp, "\nWRITE\n");
                    #endif
                    Generate_WRITE(cur, fp);
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


bool Generate_LAB(ICLnodep cur, FILE* fp)
{
    PrintOprand(fp, cur->code.u.oneop.op);fprintf(fp, ":\n");
    return true;
}
bool Generate_FUNC(ICLnodep cur, FILE* fp)
{
    PrintOprand(fp, cur->code.u.oneop.op);fprintf(fp, ":\n");
    //if(sameStr(cur->code.u.oneop.op->u.funcname, "main")==false)
    //{
        //fprintf(fp, "\tsubu $sp, $sp, 4\n");
        //fprintf(fp, "\tsw $ra, 0($sp)\n");
        fprintf(fp, "\tsubu $sp, $sp, 4\n");
        fprintf(fp, "\tsw $fp, 0($sp)\n");
        fprintf(fp, "\tmove $fp, $sp\n");
        fprintf(fp, "\tsubu $sp, $sp, %d\n", frameSize);
    //}
    spoffset=0;
    Paramn=0;
    return true;
}
bool Generate_ASSIGN(ICLnodep cur, FILE* fp)
{
    if(cur->code.u.assign.left->kind==VARIABLE || cur->code.u.assign.left->kind==TEMPVAR)
        regx=Get_RegForVar(fp, cur->code.u.assign.left);
    if(cur->code.u.assign.right->kind==VARIABLE || cur->code.u.assign.right->kind==TEMPVAR)
        regy=Get_RegForVar(fp, cur->code.u.assign.right);
    if(cur->code.u.assign.assigntype==DEFAULT){
        if(cur->code.u.assign.right->kind==CONSTANT){
            fprintf(fp, "\tli ");
            Print_Reg(fp, regx);fprintf(fp, ", ");
            sprintf(numstr, "%d", cur->code.u.assign.right->u.value);fprintf(fp, "%s\n", numstr);
        }
        else {
            fprintf(fp, "\tmove ");
            Print_Reg(fp, regx);fprintf(fp, ", ");
            Print_Reg(fp, regy);fprintf(fp, "\n");
        }
    }
    else if(cur->code.u.assign.assigntype==GETDATA){
        fprintf(fp, "\tlw ");
        Print_Reg(fp, regx);fprintf(fp, ", 0(");
        Print_Reg(fp, regy);fprintf(fp, ")\n");
        //pDebug("GETDATA: ");
    }
    else if(cur->code.u.assign.assigntype==SETDATA){
        if(cur->code.u.assign.right->kind==CONSTANT){
            fprintf(fp, "\tli $s3, ");
            sprintf(numstr, "%d", cur->code.u.assign.right->u.value);fprintf(fp, "%s\n", numstr);
            fprintf(fp, "\tsw $s3, 0(");
            Print_Reg(fp, regx);fprintf(fp, ")\n");
        }
        else {
            fprintf(fp, "\tsw ");
            Print_Reg(fp, regy);fprintf(fp, ", 0(");
            Print_Reg(fp, regx);fprintf(fp, ")\n");
            //pDebug("SETDATA: ");
        }
    }
    else if(cur->code.u.assign.assigntype==GETADDR){
        VarDescp var = Get_Var(cur->code.u.assign.right->name);
        if(var==NULL)pError("Generate_ADD");
        fprintf(fp, "\tla ");
        Print_Reg(fp, regx);fprintf(fp, ", %d($fp)\n", var->offset);
    }
    SW_Reg(fp, regx);
    return true;
}
bool Generate_ADD(ICLnodep cur, FILE* fp)
{
    if(cur->code.u.binop.assigntype==DEFAULT)
    {
        if(cur->code.u.binop.result->kind==VARIABLE || cur->code.u.binop.result->kind==TEMPVAR)
            regx=Get_RegForVar(fp, cur->code.u.binop.result);
        if(cur->code.u.binop.op1->kind==VARIABLE || cur->code.u.binop.op1->kind==TEMPVAR)
            regy=Get_RegForVar(fp, cur->code.u.binop.op1);
        if(cur->code.u.binop.op2->kind==VARIABLE || cur->code.u.binop.op2->kind==TEMPVAR)
            regz=Get_RegForVar(fp, cur->code.u.binop.op2);
        if(cur->code.u.binop.op1->kind==CONSTANT && (cur->code.u.binop.op2->kind!=CONSTANT)){
            fprintf(fp, "\taddi ");
            Print_Reg(fp, regx);fprintf(fp, ", ");
            Print_Reg(fp, regz);fprintf(fp, ", ");
            sprintf(numstr, "%d", cur->code.u.binop.op1->u.value);fprintf(fp, "%s", numstr);fprintf(fp, "\n");
        }
        else if(cur->code.u.binop.op2->kind==CONSTANT && (cur->code.u.binop.op1->kind!=CONSTANT)){
            fprintf(fp, "\taddi ");
            Print_Reg(fp, regx);fprintf(fp, ", ");
            Print_Reg(fp, regy);fprintf(fp, ", ");
            sprintf(numstr, "%d", cur->code.u.binop.op2->u.value);fprintf(fp, "%s", numstr);fprintf(fp, "\n");
        }
        else{
            fprintf(fp, "\tadd ");
            Print_Reg(fp, regx);fprintf(fp, ", ");
            Print_Reg(fp, regy);fprintf(fp, ", ");
            Print_Reg(fp, regz);fprintf(fp, "\n");
        }
        SW_Reg(fp, regx);
    }
    else if(cur->code.u.binop.assigntype==GETADDR){//x := &y + z
        if(cur->code.u.binop.result->kind==VARIABLE || cur->code.u.binop.result->kind==TEMPVAR)
            regx=Get_RegForVar(fp, cur->code.u.binop.result);
        if(cur->code.u.binop.op1->kind==VARIABLE || cur->code.u.binop.op1->kind==TEMPVAR)
            regy=Get_RegForVar(fp, cur->code.u.binop.op1);
        if(cur->code.u.binop.op2->kind==VARIABLE || cur->code.u.binop.op2->kind==TEMPVAR)
            regz=Get_RegForVar(fp, cur->code.u.binop.op2);
        VarDescp var = Get_Var(cur->code.u.binop.op1->name);
        if(var==NULL)pError("Generate_ADD");
        fprintf(fp, "\tla $s0, %d($fp)\n", var->offset);
        if(cur->code.u.binop.op2->kind==CONSTANT)
        {
            fprintf(fp, "\taddi ");
            Print_Reg(fp, regx);fprintf(fp, ", $s0, ");
            sprintf(numstr, "%d", cur->code.u.binop.op2->u.value);fprintf(fp, "%s", numstr);fprintf(fp, "\n");
        }
        else{
            fprintf(fp, "\tadd ");
            Print_Reg(fp, regx);fprintf(fp, ", $s0, ");
            Print_Reg(fp, regz);fprintf(fp, "\n");
        }
        SW_Reg(fp, regx);
    }
    return true;
}
bool Generate_SUB(ICLnodep cur, FILE* fp)
{
    if(cur->code.u.binop.result->kind==VARIABLE || cur->code.u.binop.result->kind==TEMPVAR)
        regx=Get_RegForVar(fp, cur->code.u.binop.result);
    if(cur->code.u.binop.op1->kind==VARIABLE || cur->code.u.binop.op1->kind==TEMPVAR)
        regy=Get_RegForVar(fp, cur->code.u.binop.op1);
    else {
        regy=16;
        fprintf(fp, "\tli $s0, %d\n", cur->code.u.binop.op1->u.value);
    }
    if(cur->code.u.binop.op2->kind==VARIABLE || cur->code.u.binop.op2->kind==TEMPVAR)
        regz=Get_RegForVar(fp, cur->code.u.binop.op2);
    /*if(cur->code.u.binop.op1->kind==CONSTANT && (cur->code.u.binop.op2->kind!=CONSTANT && cur->code.u.binop.op2->isaddr==0)){
        fprintf(fp, "\taddi ");
        Print_Reg(fp, regx);fprintf(fp, ", ");
        Print_Reg(fp, regz);fprintf(fp, ", -");
        sprintf(numstr, "%d", cur->code.u.binop.op1->u.value);fprintf(fp, "%s", numstr);fprintf(fp, "\n");
    }
    else*/ if(cur->code.u.binop.op2->kind==CONSTANT && (cur->code.u.binop.op1->kind!=CONSTANT)){
        fprintf(fp, "\taddi ");
        Print_Reg(fp, regx);fprintf(fp, ", ");
        Print_Reg(fp, regy);fprintf(fp, ", -");
        sprintf(numstr, "%d", cur->code.u.binop.op2->u.value);fprintf(fp, "%s", numstr);fprintf(fp, "\n");
    }
    else{
        fprintf(fp, "\tsub ");
        Print_Reg(fp, regx);fprintf(fp, ", ");
        Print_Reg(fp, regy);fprintf(fp, ", ");
        Print_Reg(fp, regz);fprintf(fp, "\n");
    }
    SW_Reg(fp, regx);
    return true;
}
bool Generate_MUL(ICLnodep cur, FILE* fp)
{
    /*if(cur->code.u.binop.result->kind==VARIABLE || cur->code.u.binop.result->kind==TEMPVAR)
        regx=Get_Reg(fp, cur->code.u.binop.result);
    if(cur->code.u.binop.op1->kind==VARIABLE || cur->code.u.binop.op1->kind==TEMPVAR)
        regy=Get_Reg(fp, cur->code.u.binop.op1);
    if(cur->code.u.binop.op2->kind==VARIABLE || cur->code.u.binop.op2->kind==TEMPVAR)
        regz=Get_Reg(fp, cur->code.u.binop.op2);
    fprintf(fp, "\tmul ");
    Print_Reg(fp, regx);fprintf(fp, ", ");
    Print_Reg(fp, regy);fprintf(fp, ", ");
    Print_Reg(fp, regz);fprintf(fp, "\n");
    SW_Reg(fp, regx);*/
    if(cur->code.u.binop.result->kind==VARIABLE || cur->code.u.binop.result->kind==TEMPVAR)
        regx=Get_RegForVar(fp, cur->code.u.binop.result);
    else{
        pError("Generate_MUL");
    }
    if(cur->code.u.binop.op1->kind==VARIABLE || cur->code.u.binop.op1->kind==TEMPVAR)
        regy=Get_RegForVar(fp, cur->code.u.binop.op1);
    else {
        regy=16;
        fprintf(fp, "\tli $s0, %d\n", cur->code.u.binop.op1->u.value);
    }
    if(cur->code.u.binop.op2->kind==VARIABLE || cur->code.u.binop.op2->kind==TEMPVAR)
        regz=Get_RegForVar(fp, cur->code.u.binop.op2);
    else {
        regz=17;
        fprintf(fp, "\tli $s1, %d\n", cur->code.u.binop.op2->u.value);
    }
    fprintf(fp, "\tmul ");
    Print_Reg(fp, regx);fprintf(fp, ", ");
    Print_Reg(fp, regy);fprintf(fp, ", ");
    Print_Reg(fp, regz);fprintf(fp, "\n");
    SW_Reg(fp, regx);
    return true;
}
bool Generate_DIV(ICLnodep cur, FILE* fp)
{
    if(cur->code.u.binop.result->kind==VARIABLE || cur->code.u.binop.result->kind==TEMPVAR)
        regx=Get_RegForVar(fp, cur->code.u.binop.result);
    if(cur->code.u.binop.op1->kind==VARIABLE || cur->code.u.binop.op1->kind==TEMPVAR)
        regy=Get_RegForVar(fp, cur->code.u.binop.op1);
    else {
        regy=16;
        fprintf(fp, "\tli $s0, %d\n", cur->code.u.binop.op1->u.value);
    }
    if(cur->code.u.binop.op2->kind==VARIABLE || cur->code.u.binop.op2->kind==TEMPVAR)
        regz=Get_RegForVar(fp, cur->code.u.binop.op2);
    else {
        regz=17;
        fprintf(fp, "\tli $s1, %d\n", cur->code.u.binop.op2->u.value);
    }
    fprintf(fp, "\tdiv ");
    Print_Reg(fp, regy);fprintf(fp, ", ");
    Print_Reg(fp, regz);fprintf(fp, "\n");
    fprintf(fp, "\tmflo ");
    Print_Reg(fp, regx);fprintf(fp, "\n");
    SW_Reg(fp, regx);
    return true;
}
bool Generate_GOTO(ICLnodep cur, FILE* fp)
{
    fprintf(fp, "\tj ");
    PrintOprand(fp, cur->code.u.oneop.op);fprintf(fp, "\n");
    return true;
}
bool Generate_IFGOTO(ICLnodep cur, FILE* fp)
{
    if(cur->code.u.ifgoto.op1->kind==VARIABLE || cur->code.u.ifgoto.op1->kind==TEMPVAR)
        regx=Get_RegForVar(fp, cur->code.u.ifgoto.op1);
    else {
        regx=16;
        fprintf(fp, "\tli $s0, %d\n", cur->code.u.ifgoto.op1->u.value);
    }
    if(cur->code.u.ifgoto.op2->kind==VARIABLE || cur->code.u.ifgoto.op2->kind==TEMPVAR)
        regy=Get_RegForVar(fp, cur->code.u.ifgoto.op2);
    else {
        regy=17;
        fprintf(fp, "\tli $s1, %d\n", cur->code.u.ifgoto.op2->u.value);
    }
    if(sameStr(cur->code.u.ifgoto.relop, "=="))
        fprintf(fp, "\tbeq ");
    else if(sameStr(cur->code.u.ifgoto.relop, "!="))
        fprintf(fp, "\tbne ");
    else if(sameStr(cur->code.u.ifgoto.relop, ">"))
        fprintf(fp, "\tbgt ");
    else if(sameStr(cur->code.u.ifgoto.relop, "<"))
        fprintf(fp, "\tblt ");
    else if(sameStr(cur->code.u.ifgoto.relop, ">="))
        fprintf(fp, "\tbge ");
    else if(sameStr(cur->code.u.ifgoto.relop, "<="))
        fprintf(fp, "\tble ");
    else{
        pError("IFGOTO");
    }
    Print_Reg(fp, regx);fprintf(fp, ", ");
    Print_Reg(fp, regy);fprintf(fp, ", ");
    PrintOprand(fp, cur->code.u.ifgoto.label);fprintf(fp, "\n");
    return true;
}
bool Generate_RETURN(ICLnodep cur, FILE* fp)
{
    if(cur->code.u.oneop.op->kind==CONSTANT){
        fprintf(fp, "\tmove $v0, ");
        sprintf(numstr, "%d", cur->code.u.oneop.op->u.value);fprintf(fp, "%s", numstr);fprintf(fp, "\n");
        fprintf(fp, "\taddi $sp, $sp, %d\n", frameSize);
        fprintf(fp, "\tlw $fp, 0($sp)\n");
        fprintf(fp, "\taddi $sp, $sp, 4\n");
        fprintf(fp, "\tjr $ra");fprintf(fp, "\n");
    }
    else if(cur->code.u.oneop.op->kind==VARIABLE || cur->code.u.oneop.op->kind==TEMPVAR)
    {        
        regx=Get_RegForVar(fp, cur->code.u.oneop.op);
        fprintf(fp, "\tmove $v0, ");
        Print_Reg(fp, regx);fprintf(fp, "\n");
        fprintf(fp, "\taddi $sp, $sp, %d\n", frameSize);
        fprintf(fp, "\tlw $fp, 0($sp)\n");
        fprintf(fp, "\taddi $sp, $sp, 4\n");
        fprintf(fp, "\tjr $ra");fprintf(fp, "\n");
    }
    return true;
}
bool Generate_DEC(ICLnodep cur, FILE* fp)
{
    VarDescp arrayHead = malloc(sizeof(VarDesc));
    //spoffset -= 4;
    spoffset-=cur->code.u.dec.size;
    arrayHead->offset=spoffset;
    strcpy(arrayHead->name, cur->code.u.oneop.op->name);
    Push_Var(arrayHead);
    //fprintf(fp, "\taddi $s1, $fp, %d\n", spoffset);//SUBBU&ADDI
    fprintf(fp, "\tsubu $s0, $fp, %d\n", -spoffset);
    fprintf(fp, "\tsw $s0, %d($fp)\n", arrayHead->offset);
    return true;
}
bool Generate_ARG(ICLnodep cur, FILE* fp)
{
    if(ArgCount==0)
    {
        ICLnodep icarg=cur;ArgCount=1;
        while(icarg->next != NULL && icarg->next->code.kind==ARG){
            ArgCount++;
            icarg=icarg->next;
        }
    }
    VarDescp args=NULL;
    args=Get_Var(cur->code.u.oneop.op->name);
    if(args==NULL){
        pError("Generate_ARG");
    }
    if(Argn<4){
        fprintf(fp, "\tlw $a%d, %d($fp)\n", Argn, args->offset);
    }
    else{
        fprintf(fp, "\tlw $s0, %d($fp)\n", args->offset);
        fprintf(fp, "\tsubu $sp, $sp, 4\n");
        fprintf(fp, "\tsw $s0, 0($sp)\n");
    }
    ++Argn;
    if(Argn==ArgCount){
        Argn=0;ArgCount=0;
    }
    /*if(cur->next == NULL || cur->next->code.kind!=ARG){
        VarDescp args=NULL;
        args=Get_Var(cur->code.u.oneop.op->name);
        if(args==NULL){
            pError("Generate_ARG");
        }
        if(Argn<4){
            fprintf(fp, "\tlw $a%d, %d($fp)\n", Argn, args->offset);
        }
        else{
            fprintf(fp, "\tlw $s0, %d($fp)\n", args->offset);
            fprintf(fp, "\tsubu $sp, $sp, 4\n");
            fprintf(fp, "\tlw $s0, 0($sp)\n");
        }
        ++Argn;
        if(Argn==ArgCount){
            Argn=0;ArgCount=0;
        }
    }
    else{
        Generate_ARG(cur->next, fp);
        VarDescp args=NULL;
        args=Get_Var(cur->code.u.oneop.op->name);
        if(args==NULL){
            pError("Generate_ARG");
        }
        if(Argn<4){
            fprintf(fp, "\tlw $a%d, %d($fp)\n", Argn, args->offset);
        }
        else{
            fprintf(fp, "\tlw $s0, %d($fp)\n", args->offset);
            fprintf(fp, "\tsubu $sp, $sp, 4\n");
            fprintf(fp, "\tsw $s0, 0($sp)\n");
        }
        ++Argn;
        if(Argn==ArgCount){
            Argn=0;ArgCount=0;
        }
    }*/
    return true;
}
bool Generate_CALL(ICLnodep cur, FILE* fp)
{
    fprintf(fp, "\tsubu $sp, $sp, 4\n");
    fprintf(fp, "\tsw $ra, 0($sp)\n");
    if(cur->code.u.assign.left->kind==VARIABLE || cur->code.u.assign.left->kind==TEMPVAR)
        regx=Get_RegForVar(fp, cur->code.u.assign.left);
    fprintf(fp, "\tjal ");
    PrintOprand(fp, cur->code.u.assign.right);fprintf(fp, "\n");
    fprintf(fp, "\tmove ");
    Print_Reg(fp, regx);
    fprintf(fp, ", $v0");fprintf(fp, "\n");
    SW_Reg(fp, regx);
    fprintf(fp, "\tlw $ra, 0($sp)\n");
    fprintf(fp, "\taddi $sp, $sp, 4\n");
    //
    /*fprintf(fp, "\tmove ");
    Print_Reg(fp, regx);
    fprintf(fp, ", $v0");fprintf(fp, "\n");
    SW_Reg(fp, regx);*/
    Argn=0;ArgCount=0;
    return true;
}
bool Generate_PARAM(ICLnodep cur, FILE* fp)
{
    VarDescp params=malloc(sizeof(VarDesc));
    strcpy(params->name, cur->code.u.oneop.op->name);
    spoffset-=4;
    params->offset=spoffset;
    Push_Var(params);

    if(paramsumn==0)
    {
        ICLnodep paramcur=cur;paramsumn=1;
        while(paramcur->next!=NULL && paramcur->next->code.kind==PARAM){
            paramcur=paramcur->next;
            paramsumn++;
        }
        Paramn=paramsumn-1;
    }
    
    int argoffset=paramsumn-Paramn+1;
    if(Paramn<4){
        fprintf(fp, "\tsw $a%d, %d($fp)\n", Paramn, params->offset);
    }
    else{
        fprintf(fp, "\tlw $s0, %d($fp)\n", (argoffset*4));
        fprintf(fp, "\tsw $s0, %d($fp)\n", params->offset);
    }
    Paramn--;

    if(cur->next==NULL||cur->next->code.kind!=PARAM)paramsumn=0;

    return true;
}
bool Generate_READ(ICLnodep cur, FILE* fp)
{
    fprintf(fp, "\tsubu $sp, $sp, 4\n");
    fprintf(fp, "\tsw $ra, 0($sp)\n");
    fprintf(fp, "\tjal read\n");
    if(cur->code.u.oneop.op->kind==VARIABLE || cur->code.u.oneop.op->kind==TEMPVAR)
        regx=Get_RegForVar(fp, cur->code.u.oneop.op);
    fprintf(fp, "\tmove ");
    Print_Reg(fp, regx);
    fprintf(fp, ", $v0");fprintf(fp, "\n");
    SW_Reg(fp, regx);
    fprintf(fp, "\tlw $ra, 0($sp)\n");
    fprintf(fp, "\taddi $sp, $sp, 4\n");
    //
    /*fprintf(fp, "\tmove ");
    Print_Reg(fp, regx);
    fprintf(fp, ", $v0");fprintf(fp, "\n");
    SW_Reg(fp, regx);*/
    return true;
}
bool Generate_WRITE(ICLnodep cur, FILE* fp)
{
    fprintf(fp, "\tsubu $sp, $sp, 4\n");
    fprintf(fp, "\tsw $ra, 0($sp)\n");
    if(cur->code.u.oneop.op->kind==VARIABLE || cur->code.u.oneop.op->kind==TEMPVAR)
        regx=Get_RegForVar(fp, cur->code.u.oneop.op);
    if(cur->code.u.oneop.op->isaddr==0)
    {
        fprintf(fp, "\tmove $a0, ");
        Print_Reg(fp, regx);
        fprintf(fp, "\n");
    }
    else{
        fprintf(fp, "\tlw $a0, 0(");
        Print_Reg(fp, regx);
        fprintf(fp, ")\n");
    }
    fprintf(fp, "\tjal write\n");
    SW_Reg(fp, regx);
    fprintf(fp, "\tlw $ra, 0($sp)\n");
    fprintf(fp, "\taddi $sp, $sp, 4\n");
    return true;
}


RegDescp New_RegDesc(int no)
{
    RegDescp newrdp = (RegDescp)malloc(sizeof(RegDesc));
    newrdp->no=no;
    newrdp->free=1;
    newrdp->var=NULL;
    sprintf(numstr, "%d", newrdp->no);
    strcpy(newrdp->name, "$t");
    strcat(newrdp->name, numstr);
    strcpy(newrdp->alias,"*");
    return newrdp;
}
bool Init_Regs()
{
    for(int i = 0;i<REGS_MAX;i++){
        regdescs[i]=New_RegDesc(i);
    }
    strcpy(regdescs[0]->alias, "$zero");strcpy(regdescs[1]->alias, "$at");strcpy(regdescs[2]->alias, "$v0");strcpy(regdescs[3]->alias, "$v1");
    strcpy(regdescs[4]->alias, "$a0");strcpy(regdescs[5]->alias, "$a1");strcpy(regdescs[6]->alias, "$a2");strcpy(regdescs[7]->alias, "$a3");
    strcpy(regdescs[8]->alias, "$t0");strcpy(regdescs[9]->alias, "$t1");strcpy(regdescs[10]->alias, "$t2");strcpy(regdescs[11]->alias, "$t3");
    strcpy(regdescs[12]->alias, "$t4");strcpy(regdescs[13]->alias, "$t5");strcpy(regdescs[14]->alias, "$t6");strcpy(regdescs[15]->alias, "$t7");
    strcpy(regdescs[16]->alias, "$s0");strcpy(regdescs[17]->alias, "$s1");strcpy(regdescs[18]->alias, "$s2");strcpy(regdescs[19]->alias, "$s3");
    strcpy(regdescs[20]->alias, "$s4");strcpy(regdescs[21]->alias, "$s5");strcpy(regdescs[22]->alias, "$s6");strcpy(regdescs[23]->alias, "$s7");
    strcpy(regdescs[24]->alias, "$t8");strcpy(regdescs[25]->alias, "$t9");strcpy(regdescs[26]->alias, "$k0");strcpy(regdescs[27]->alias, "$k1");
    strcpy(regdescs[28]->alias, "$gp");strcpy(regdescs[29]->alias, "$sp");strcpy(regdescs[30]->alias, "$fp");strcpy(regdescs[31]->alias, "$ra");
    return true;
}
int Get_RegForVar(FILE *fp, Operandp var)
{
    VarDescp vardesc=Get_Var(var->name);
    int i = curReg+8;
    curReg=(++curReg)%8;
    if(vardesc==NULL){
        vardesc=malloc(sizeof(vardesc));
        strcpy(vardesc->name, var->name);
        spoffset-=4;
        vardesc->offset=spoffset;
        Push_Var(vardesc);
        vardesc->reg=i;
        regdescs[i]->var=vardesc;
    }
    else{
        vardesc->reg=i;
        regdescs[i]->var=vardesc;
        LW_Reg(fp, i, vardesc);
    }
    return i;
}
bool SW_Reg(FILE *fp, int regno)
{
    VarDescp vardesc=regdescs[regno]->var;
    fprintf(fp, "\tsw ");
    Print_Reg(fp, regno);
    fprintf(fp, ", %d($fp)\n", vardesc->offset);
    return true;
}
bool LW_Reg(FILE *fp, int regno, VarDescp vardesc)
{
    regdescs[regno]->var=vardesc;
    regdescs[regno]->free=0;
    fprintf(fp, "\tlw ");
    Print_Reg(fp, regno);
    fprintf(fp, ", %d($fp)\n", vardesc->offset);
    return true;
}

bool Push_Var(VarDescp vardesc)
{
    if(vardesc!=NULL){
        vardesc->next=NULL;
        if(stack==NULL){
            stack=vardesc;
        }
        else{
            VarDescp p = stack;
            while(p->next!=NULL){
                p=p->next;
            }
            p->next=vardesc;
        }
    }
    return true;
}

bool Pop_Var()
{
    VarDescp p = stack;
    while (p!=NULL)
    {
        stack=stack->next;
        free(p);
        p=stack;
    }
    return true;
}
VarDescp Get_Var(char name[])
{
    VarDescp p=stack;
    while(p!=NULL){
        if(sameStr(p->name, name)){
            return p;
        }
        p=p->next;
    }
    return p;
}

bool pDebug(char* mesgs)
{
    printf("Debug------------%s\n", mesgs);
}

bool pError(char* mesgs)
{
    printf("Error------------%s\n", mesgs);
    exit(-1);
}

bool Print_Reg(FILE *fp, int regno)
{
    fprintf(fp, "%s", regdescs[regno]->alias);
}