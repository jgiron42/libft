#include "libft.h"
char *ft_optarg = NULL;
int ft_optind = 1;
int ft_opterr = 1;
int ft_optopt = 0;
int ft_optwordind = 0;

void next_word()
{
	ft_optind++;
	ft_optwordind = 0;
}
/**
 * POSIX getopt (man 3 getopt)
 */
int ft_getopt(int argc, char * const argv[], const char *optstring)
{
	bool plus_enabled = *optstring == '+';
	bool minus_enabled = *optstring == '-';
	bool colon_enabled = optstring[minus_enabled | plus_enabled] == ':';

	ft_optarg = NULL;
	while (true) {
		if (ft_optind >= argc) // no more argv
			return (-1);
		if (!argv[ft_optind][ft_optwordind]) // end of argv
			next_word();
		else if (ft_optwordind == 0) { // begin of argv
			if (argv[ft_optind][0] == '-') { // is an option string
				if (argv[ft_optind][1] == '-') // end of options
					return (-1);
				else if (argv[ft_optind][1] == '\0') // no option
					next_word();
				else // parse next character
					ft_optwordind++;
			}
			else // is a normal command argument
			{
				if (minus_enabled) // return as an arg for char code 1 option
				{
					ft_optarg = argv[ft_optind];
					next_word();
					return (1);
				}
				else if (ft_posixly_correct() || plus_enabled) // posix version
					return (-1);
				else // GNU version TODO: permutation
					next_word();
			}
		}
		else // parsing options
		{
			char current = argv[ft_optind][ft_optwordind];
			char *pos = ft_strchr(optstring, current); // pos in optstring
			if (!pos) // option is not in optstring
			{
				if (ft_opterr && !colon_enabled)
				{
					ft_putstr_fd((char *) optstring, 2);
					ft_putstr_fd(": invalid option -- '", 2);
					write(2, &current, 1);
					ft_putstr_fd("'\n", 2);
				}
				ft_optopt = current;
				if (argv[ft_optind][ft_optwordind + 1]) // still characters to parse in arg
					ft_optwordind++;
				else // end of arg
					next_word();
				return('?');
			}
			else if (pos[1] == ':') // the option take an argument
			{
				if (argv[ft_optind][ft_optwordind + 1]) // argument is the rest of the string
				{
					ft_optarg = argv[ft_optind] + ft_optwordind + 1;
					next_word();
					return (current);
				}
				else if (ft_optind + 1 < argc) // the argument is the next argv
				{
					ft_optind++;
					ft_optarg = argv[ft_optind];
					next_word();
					return (current);
				}
				else // no argument
				{
					if (ft_opterr && !colon_enabled) // need to print error
					{
						ft_putstr_fd((char *) optstring, 2);
						ft_putstr_fd(": option requires an argument -- '", 2);
						write(2, &current, 1);
						ft_putstr_fd("'\n", 2);
					}
					next_word();
					ft_optopt = current;
					return (colon_enabled ? ':' : '?');
				}
			}
			else // the option don't take arguments
			{
				if (argv[ft_optind][ft_optwordind + 1]) // still characters to parse in arg
					ft_optwordind++;
				else // end of arg
					next_word();
				return (current);
			}
		}
	}
}
