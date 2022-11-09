#include "internal_ft_regex.h"
#include "ft_stdio.h"

static const char *error_array[] =
{
	"Success",
	"No match",
	"Invalid regular expression",
	"Invalid collation character",
	"Invalid character class name",
	"Trailing backslash",
	"Invalid back reference",
	"Unmatched [ or [^",
	"Unmatched ( or \\(",
	"Unmatched \\{",
	"Invalid content of \\{\\}",
	"Invalid range end",
	"Memory exhausted",
	"Invalid preceding regular expression",
	"Premature end of regular expression",
	"Regular expression too big",
	"Unmatched ) or \\)",
};

size_t ft_regerror(int code, const ft_regex_t *restrict r, char *restrict buf, size_t size)
{
	const char *s;
	(void)r;
	if (code >= (int)(sizeof(error_array) / sizeof(*error_array)) || code < 0)
		s = "Unknown error";
	else
		s = error_array[code];
//	if (buf && size > 0)
//		ft_strncpy(buf, s, size);
	return ft_snprintf(buf, size, "%s", s);
}