#ifndef TILES_H_
#define TILES_H_
#include <limits.h>
#include <stdbool.h>
#include "tree.h"
/// As a wildcard of enumuration value, INVALID_ENUM compare with any enum will trade as same value.
#define INVALID_ENUM (INT_MAX)
#define invalid_enum(a) ((a) == INVALID_ENUM)

T_stm jump_to_name();

T_stm move_const_to_temp();

T_stm move_binop_temp_const_to_temp();

#endif
