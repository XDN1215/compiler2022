#include "treenode.h"

bool Analyse_Program(TreeNode* tn);
bool Analyse_ExtDefList(TreeNode* tn);
bool Analyse_ExtDef(TreeNode* tn);
bool Analyse_ExtDecList(TreeNode* tn);

bool Analyse_Specifier(TreeNode* tn);
bool Analyse_StructSpecifier(TreeNode* tn);
bool Analyse_OptTag(TreeNode* tn);
bool Analyse_Tag(TreeNode* tn);

bool Analyse_VarDec(TreeNode* tn);
bool Analyse_FunDec(TreeNode* tn);
bool Analyse_VarList(TreeNode* tn);
bool Analyse_ParamDec(TreeNode* tn);

bool Analyse_CompSt(TreeNode* tn);
bool Analyse_StmtList(TreeNode* tn);
bool Analyse_Stmt(TreeNode* tn);

bool Analyse_DefList(TreeNode* tn);
bool Analyse_Def(TreeNode* tn);
bool Analyse_DecList(TreeNode* tn);
bool Analyse_Dec(TreeNode* tn);

bool Analyse_Exp(TreeNode* tn);
bool Analyse_Args(TreeNode* tn);

//类型检查
bool TypeCheck_type(Typep type1, Typep type2);
bool TypeCheck_Field(FieldListp f1, FieldListp f2);
bool TypeCheck_FieldList(FieldListp f1, FieldListp f2);
bool TypeCheck_TreeNode(TreeNode* tn1, TreeNode* tn2);

bool begin_semanalysis();
bool PrintError(char megs[], int errortype, int column);//打印错误类型信息