#ifndef ABSYNC_HEADER__
#define ABSYNC_HEADER__
#include <stdlib.h>

/* row number and line number in source code */
typedef struct
{
  int column;
  int row;
} A_Pos;

typedef struct A_exp_ *A_exp;
typedef struct A_var_ *A_var;
typedef struct A_expseq_ *A_expseq;
typedef struct A_record_ *A_record;
typedef struct A_record_list_ *A_record_list;
typedef struct A_dec_ *A_dec;
typedef struct A_decs_ *A_decs;
typedef struct A_ty_ *A_ty;
typedef struct A_tyfield_ *A_tyfield;
typedef struct A_tyfields_ *A_tyfields;
typedef struct A_id_ *A_id;

typedef enum
{
  A_plusOp,
  A_minusOp,
  A_timesOp,
  A_divideOp,
  A_eqOp,
  A_neqOp,
  A_ltOp,
  A_leOp,
  A_gtOp,
  A_geOp,
  A_andOp,
  A_orOp,
} A_oper;

struct A_exp_
{
  enum
  {
    A_intExp,
    A_strExp,
    A_nilExp,
    A_varExp,
    A_assignExp,
    A_seqExp,
    A_callExp,
    A_opExp,
    A_recordExp,
    A_ifExp,
    A_whileExp,
    A_forExp,
    A_breakExp,
    A_letExp,
  } type;
  A_Pos pos;
  union
  {
    A_id str;
    int int_value;
    A_var var;
    struct
    {
      A_var var;
      A_exp exp;
    } assign;
    A_expseq seq;
    struct
    {
      A_id func;
      A_expseq args;
    } call;
    struct
    {
      A_oper oper;
      A_exp lhs;
      A_exp rhs;
    } op;
    struct
    {
      A_id name;
      A_record_list record_list;
    } record;
    struct
    {
      A_exp condition;
      A_exp body;
      A_exp els;
    } if_exp;
    struct
    {
      A_exp condition;
      A_exp body;
    } whil;
    struct
    {
      A_id var;
      A_exp from;
      A_exp to;
      A_exp body;
    } forr;
    struct
    {
      A_decs decs;
      A_expseq body;
    } let;
  };
};

struct A_var_
{
  enum
  {
    A_simpleVar,
    A_fieldVar,
    A_subscriptVar
  } type;
  A_Pos pos;
  union
  {
    A_id simple;
    struct
    {
      A_var var;
      A_id sym;
    } field;
    struct
    {
      A_var var;
      A_exp exp;
    } subscript;
  };
};

struct A_expseq_
{
  A_exp head;
  A_expseq tail;
};

struct A_record_
{
  A_id name;
  A_exp value;
};

struct A_record_list_
{
  A_record head;
  A_record_list tail;
};

struct A_dec_
{
  enum
  {
    A_typeDec,
    A_varDec,
    A_funcDec
  } type;
  A_Pos pos;
  union
  {
    struct
    {
      A_id type_id;
      A_ty ty;
    } typedec;
    struct
    {
      A_id var;
      A_id type_id;
      A_exp exp;
    } vardec;
    struct
    {
      A_id funcname;
      A_tyfields parameters;
      A_id return_type;
      A_exp init;
    } funcdec;
  };
};

struct A_ty_
{
  enum
  {
    A_namedTy,
    A_arrayTy,
    A_recordTy
  } type;
  A_Pos pos;
  union
  {
    A_id named;
    A_id array;
    A_tyfields fields;
  };
};

struct A_decs_
{
  A_dec head;
  A_decs tail;
};

struct A_tyfiled_
{
  A_id name;
  A_id type;
  A_Pos pos;
};

struct A_tyfields_
{
  A_tyfield head;
  A_tyfields tail;
};

struct A_id_
{
  char *id;
  A_Pos pos;
};

void *_malloc(size_t byte);

A_exp A_IntExp(A_Pos pos, int i);
A_exp A_StrExp(A_Pos pos, A_id str);
A_exp A_NilExp(A_Pos pos);
A_exp A_VarExp(A_Pos pos, A_var var);
A_exp A_AssignExp(A_Pos pos, A_var var, A_exp exp);
A_exp A_SeqExp(A_Pos pos, A_expseq seq);
A_exp A_CallExp(A_Pos pos, A_id func, A_expseq args);
A_exp A_OpExp(A_Pos pos, A_oper oper, A_exp lhs, A_exp rhs);
A_exp A_RecordExp(A_Pos pos, A_id name, A_record_list record_list);
A_exp A_IfExp(A_Pos pos, A_exp condition, A_exp body, A_exp els);
A_exp A_WhileExp(A_Pos pos, A_exp condition, A_exp body);
A_exp A_ForExp(A_Pos pos, A_id var, A_exp lo, A_exp hi, A_exp body);
A_exp A_BreakExp(A_Pos pos);
A_exp A_LetExp(A_Pos pos, A_decs decs, A_expseq body);
A_var A_SimpleVar(A_Pos pos, A_id name);
A_var A_FieldVar(A_Pos pos, A_var var, A_id name);
A_var A_SubscriptVar(A_Pos pos, A_var var, A_exp exp);
A_expseq A_ExpSeq(A_exp head, A_expseq tail);
A_record_list A_RecordList(A_record head, A_record_list tail);
A_decs A_Decs(A_dec head, A_decs tail);
A_tyfields A_TyFields(A_tyfield head, A_tyfields tail);
A_id A_Id(A_Pos pos, char *id);

#endif