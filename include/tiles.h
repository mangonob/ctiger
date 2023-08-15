#ifndef TILES_H_
#define TILES_H_
#include <stdbool.h>
#include "tree.h"
/// As a wildcard of enumuration value, ANY_ENUM compare with any enum will treat as same value.
#define ANY_ENUM (-1)
#define match_enum(a, b) ((a) == ANY_ENUM || (b) == ANY_ENUM || (a) == (b))

T_stm jump_to_name();

T_stm move_const_to_temp();

T_stm move_binop_temp_const_to_temp();

T_stm move_from_binop_x_const();

T_exp binop_x_const();

#endif
