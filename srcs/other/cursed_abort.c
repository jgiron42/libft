#include "libft.h"

// since 42 specifically allow the use of certain external functions but not the other (yeah even exit and raise),
// this function does a good work at exiting the program!
void	cursed_abort(char *str)
{
	ft_fprintf(ft_stderr, "ABORT! %s\n", str);
#ifdef FT_USE_RAISE
	raise(SIGABRT);
#elif defined(FT_USE_EXIT)
	exit(1);
#else
	ft_strlen(NULL);
#endif
	while(true);
}
