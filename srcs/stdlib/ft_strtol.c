#include "../../includes/libft.h"

static int	from_hex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

/**
 * POSIX compliant strtol (see: man 3 strtol)
 */
long ft_strtol(const char *nptr, char **endptr, int base)
{
	int sign = 1;
	if (endptr)
		*endptr = (char *)nptr; // no digit case

	// truncating spaces
	while(ft_isspace(*nptr))
		nptr++;

	// sign management
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;

	if (!ft_isdigit(*nptr)) // no digit case
		return (0);

	// base detection
	if (*nptr == '0')
	{
		nptr++;
		if (*nptr == 'x' || *nptr == 'X')
		{
			if (base != 16 && base != 0)
			{
				if (endptr)
					*endptr = (char *)nptr;
				return (0);
			}
			base = 16;
			nptr++;
		}
#ifdef NON_POSIX_FEATURE
		else if (*nptr == 'b' || *nptr == 'B')
		{
			if (base != 2 && base != 0)
			{
				if (endptr)
					*endptr = (char *)nptr;
				return (0);
			}
			base = 2;
			nptr++;
		}
#endif
		else if (ft_isdigit(*nptr) && base == 0)
			base = 8;
		else
		{
			if (endptr)
				*endptr = (char *)nptr;
			return (0);
		}
	}
	else if (base == 0)
		base = 10;

	// parsing
	long int ret = 0;
	int c;
	while ((c = from_hex(*nptr)) >= 0 && c < base)
	{
		if (sign == 1 && (ret > LONG_MAX / base || ret * base > LONG_MAX - c))
		{
			errno = ERANGE;
			ret = LONG_MAX;
		}
		else if (sign == -1 && (ret < LONG_MIN / base || ret * base < LONG_MIN + c))
		{
			errno = ERANGE;
			ret = LONG_MIN;
		}
		else
			ret = ret * base + sign * c;
		nptr++;
	}
	if (endptr)
		*endptr = (char*)nptr;
	return (ret);
}