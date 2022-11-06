//
// Created by joachim on 11/2/22.
//

#ifndef LIBFT_MACRO_H
#define LIBFT_MACRO_H
#include "libft.h"

// quick way to switch on a program_status variable
# define SWITCH_STATUS(status, ok, ko, fatal) switch (status) {case OK:ok;break;case KO:ko;;break;case FATAL:fatal;break;default:break;}

// size of a static array
# define ARRAY_SIZE(array) (sizeof(array) / sizeof (*(array)))

// give a pointer to the value (even if the value is temporary)
#define ref_of(v) ((__typeof__(v)[1]){(v)})

#endif //LIBFT_MACRO_H
