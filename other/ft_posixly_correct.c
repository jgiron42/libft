#include "../libft.h"

/**
 * check if the program is needed to be posixly correct with the POSIXLY_CORRECT and POSIX_ME_HARDER environment variables
 * @return true if one of the posix variables is set otherwise false
 */
bool	ft_posixly_correct()
{
	return (ft_getenv("POSIXLY_CORRECT") || ft_getenv("POSIX_ME_HARDER"));
}