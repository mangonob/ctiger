#include "tiles.h"

static T_stm _jump_to_name = NULL;
T_stm jump_to_name()
{
  if (!_jump_to_name)
    _jump_to_name = T_Jump(T_Name(NULL), NULL);
  return _jump_to_name;
}

static T_stm _move_const_to_temp = NULL;
T_stm move_const_to_temp()
{
  if (!_move_const_to_temp)
    _move_const_to_temp = T_Move(T_Temp(NULL), T_Const(0));
  return _move_const_to_temp;
}

static T_stm _move_binop_temp_const_to_temp = NULL;
T_stm move_binop_temp_const_to_temp()
{
  if (!_move_binop_temp_const_to_temp)
    _move_binop_temp_const_to_temp = T_Move(T_Temp(NULL), T_Binop(ANY_ENUM, T_Temp(NULL), T_Const(0)));
  return _move_binop_temp_const_to_temp;
}

static T_stm _move_temp_to_temp = NULL;
T_stm move_temp_to_temp()
{
  if (!_move_temp_to_temp)
    _move_temp_to_temp = T_Move(T_Temp(NULL), T_Temp(NULL));
  return _move_temp_to_temp;
}

static T_exp _binop_x_const = NULL;
T_exp binop_x_const()
{
  if (!_binop_x_const)
    _binop_x_const = T_Binop(ANY_ENUM, NULL, T_Const(0));
  return _binop_x_const;
}

static T_exp _binop_const_const = NULL;
T_exp binop_const_const()
{
  if (!_binop_const_const)
    _binop_const_const = T_Binop(ANY_ENUM, T_Const(0), T_Const(0));
  return _binop_const_const;
}

static T_stm _move_from_binop_x_const = NULL;
T_stm move_from_binop_x_const()
{
  if (!_move_from_binop_x_const)
    _move_from_binop_x_const = T_Move(NULL, binop_x_const());
  return _move_from_binop_x_const;
}

static T_exp _binop_temp_temp = NULL;
T_exp binop_temp_temp()
{
  if (!_binop_temp_temp)
    _binop_temp_temp = T_Binop(ANY_ENUM, T_Temp(NULL), T_Temp(NULL));
  return _binop_temp_temp;
}
