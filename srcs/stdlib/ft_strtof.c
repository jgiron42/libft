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

static double lazy_pow(double n, int e)
{
	double ret = 1;
	if (e < 0)
		return 1 / lazy_pow(n, -e);
	while (e > 0)
	{
		ret *= n;
		e--;
	}
	return (ret);
}

static double	ft_strtod_base(char *nptr, char **endptr, int base)
{
	float ret = 0;
	int c;
	bool overflow = false;
	// integer part
	while ((c = from_hex(*nptr)) >= 0 && c < base)
	{
		if ((ret > HUGE_VALF / base || ret * base > HUGE_VALF - c))
		{
			errno = ERANGE;
			overflow = true;
			ret = HUGE_VALF;
		}
		else
			ret = ret * base + c;
		nptr++;
	}
	if (*nptr == '.' && from_hex(nptr[1]) < base) // decimal part
	{
		nptr++;
		float tmp = 1 / (float)base;
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
		if (exponent > 0 && (errno == ERANGE || exponent > FLT_MAX_10_EXP || ret > HUGE_VALF / lazy_pow(base == 16 ? 2 : 10, exponent)))
		{
			errno = ERANGE;
			ret = HUGE_VALF;
		}
		else if (exponent < 0 && (errno == ERANGE || exponent < FLT_MIN_10_EXP || ret < FLT_MIN * lazy_pow(base == 16 ? 2 : 10, exponent)))
		{
			errno = ERANGE;
			ret = FLT_MIN;
		}
		else
			ret *= lazy_pow(base == 16 ? 2 : 10, exponent);
	}
	if (endptr)
		*endptr = (char*)nptr;
	return (ret);
}

float	ft_strtof(const char *nptr, char **endptr)
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
		return (sign * ft_strtod_base((char *) nptr, endptr, 16));
	}
	else if (ft_isdigit(*nptr))
		return (sign * ft_strtod_base((char *)nptr, endptr, 10));
	else
		return (0);
}