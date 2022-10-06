#include "../../includes/libft.h"

// since only allow the use of certain external functions (yeah even exit and raise),
// this function does a good work at exiting the program!
void	cursed_abort(char *str)
{
	ft_fprintf(ft_stderr, "ABORT! %s\n", str);
	(void)*NULL;
	while(true);
}
