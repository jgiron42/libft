#include "libft.h"

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

static long double lazy_pow(long double n, int e)
{
	long double ret = 1;
	if (e < 0)
		return 1 / lazy_pow(n, -e);
	while (e > 0)
	{
		ret *= n;
		e--;
	}
	return (ret);
}

long double	ft_strtold_base(char *nptr, char **endptr, int base)
{
	long double ret = 0;
	int c;
	bool overflow = false;
	// integer part
	while ((c = from_hex(*nptr)) >= 0 && c < base)
	{
		if ((ret > HUGE_VALL / base || ret * base > HUGE_VALL - c))
		{
			errno = ERANGE;
			overflow = true;
			ret = HUGE_VALL;
		}
		else
			ret = ret * base + c;
		nptr++;
	}
	if (*nptr == '.' && from_hex(nptr[1]) < base) // decimal part
	{
		nptr++;
		long double tmp = 1 / (long double)base;
		while ((c = from_hex(*nptr)) >= 0 && c < base) {
			ret += c * tmp;
			nptr++;
			tmp /= base;
		}
	}
	if (!overflow && ((base == 10 && ft_tolower(*nptr) == 'e') || (base == 16 && ft_tolower(*nptr) == 'p')) && (ft_isdigit(nptr[1]) ||
	((nptr[1] == '-' || nptr[1] == '+') && ft_isdigit(nptr[2])))) // exponent
	{
		nptr++;
		errno = 0;
		long int exponent = ft_strtol(nptr, &nptr, 10);
		if (exponent > 0 && (errno == ERANGE || exponent > LDBL_MAX_10_EXP || ret > HUGE_VALL / lazy_pow(base == 16 ? 2 : 10, exponent)))
		{
			errno = ERANGE;
			ret = HUGE_VALL;
		}
		else if (exponent < 0 && (errno == ERANGE || exponent < LDBL_MIN_10_EXP || ret < LDBL_MIN * lazy_pow(base == 16 ? 2 : 10, exponent)))
		{
			errno = ERANGE;
			ret = LDBL_MIN;
		}
		else
			ret *= lazy_pow(base == 16 ? 2 : 10, exponent);
	}
	if (endptr)
		*endptr = (char*)nptr;
	return (ret);
}

long double	ft_strtold(const char *nptr, char **endptr)
{
	int sign = 1;
	if (endptr)
		*endptr = (char *)nptr;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (!ft_strncasecmp(nptr, "nan", 3))
	{
		if (endptr)
			*endptr = (char *)nptr + 3;
		if (sign == 1)
			return (NAN);
		return (-NAN);
	}
	else if (!ft_strncasecmp(nptr, "infinity", 8))
	{
		if (endptr)
			*endptr = (char *)nptr + 8;
		return (sign * INFINITY);
	}
	else if (!ft_strncasecmp(nptr, "inf", 3))
	{
		if (endptr)
			*endptr = (char *)nptr + 3;
		return (sign * INFINITY);
	}
	if (*nptr == '0' && ft_tolower(nptr[1]) == 'x') {
		nptr += 2;
		if (from_hex(*nptr) < 0 || from_hex(*nptr) >= 16)
		{
			if (endptr)
				*endptr = (char *)nptr - 1;
			return(0);
		}
		return (sign * ft_strtold_base((char *) nptr, endptr, 16));
	}
	else if (ft_isdigit(*nptr))
		return (sign * ft_strtold_base((char *)nptr, endptr, 10));
	else
		return (0);
}