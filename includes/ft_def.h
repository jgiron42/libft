//
// Created by joachim on 11/2/22.
//

#ifndef LIBFT_FT_DEF_H
# define LIBFT_FT_DEF_H
#include <malloc.h>
# include <stddef.h>
# include <limits.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/types.h>
# include <stdint.h>

typedef enum {
	OK,
	KO,
	FATAL,
}		status;

// quick way to switch on a status variable
# define SWITCH_STATUS(status, ok, ko, fatal) switch (status) {case OK:ok;break;case KO:ko;;break;case FATAL:fatal;break;default:break;}

// size of a static array
# define ARRAY_SIZE(array) (sizeof(array) / sizeof (*(array)))

// give a pointer to the value (even if the value is temporary)
# define ref_of(v) ((__typeof__(v)[1]){(v)})

# define ft_align_backward(v, align) ((v) - (v) % (align))
# define ft_align_forward(v, align) (ft_align_backward((v) + (align) - 1, (align)))

//# define authorized_function(FUNCTION_NAME) (defined(WHITELIST) && defined(FUNCTION_NAME)) || (!defined(WHITELIST) && !defined(FUNCTION_NAME))

#endif //LIBFT_FT_DEF_H
