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
    _move_binop_temp_const_to_temp = T_Move(T_Temp(NULL), T_Binop(INVALID_ENUM, T_Temp(NULL), T_Const(0)));
  return _move_binop_temp_const_to_temp;
}
