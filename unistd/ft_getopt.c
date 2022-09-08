#include "../libft.h"
char *ft_optarg = NULL;
int ft_optind = 1;
int ft_opterr = 1;
int ft_optopt = 0;

/**
 * GNU getopt (man 3 getopt)
 */
int ft_getopt(int argc, char * const argv[], const char *optstring)
{
	bool plus_enabled = *optstring == '+';
	bool minus_enabled = *optstring == '-';
	bool colon_enabled = optstring[minus_enabled | plus_enabled] == ':';
	static bool	offset = false, has_arg = false;
	static int ft_optwordind;

	/*
	if (ft_optind <= 1) { // reset
		offset = false;
		has_arg = false;
		ft_optwordind = 0;
	}
	 */
	ft_optarg = NULL;
	while (true) {
		if (ft_optind >= argc) // no more argv
			return (-1);
		if (!argv[ft_optind][ft_optwordind]) // end of argv
		{
			if (!(ft_posixly_correct() || plus_enabled)) { // GNU nice args permutations
				int i = ft_optind;
				while ((!offset && i > 1 + has_arg && argv[i - has_arg][0] == '-' && argv[i - 1 - has_arg][0] != '-') ||
					   (offset && i > 2 + has_arg && argv[i - has_arg][0] == '-' && argv[i - 2 - has_arg][0] != '-')) {
					if (!has_arg) {
						register char *tmp = argv[i - 1];
						((char **) argv)[i - 1] = argv[i];
						((char **) argv)[i] = tmp;
					}
					else
					{
						register char *tmp = argv[i - 2];
						((char **) argv)[i - 2] = argv[i - 1];
						((char **) argv)[i - 1] = argv[i];
						((char **) argv)[i] = tmp;
					}
					i--;
				}
				offset = has_arg;
				has_arg = false;
			}
			ft_optind++;
			ft_optwordind = 0;
		}
		else if (ft_optwordind == 0) { // begin of argv
			if (argv[ft_optind][0] == '-') { // is an option string
				if (argv[ft_optind][1] == '-') // end of options
					return (-1);
				else // parse next character
					ft_optwordind++;
			}
			else // is a normal command argument
			{
				if (minus_enabled) // return as an arg for char code 1 option
				{
					ft_optarg = argv[ft_optind];
					ft_optwordind = (int)ft_strlen(argv[ft_optind]);
					return (1);
				}
				else if (ft_posixly_correct() || plus_enabled) // posix version
					return (-1);
				else // GNU version
					ft_optwordind = (int)ft_strlen(argv[ft_optind]);
			}
		}
		else // parsing options
		{
			unsigned char current = argv[ft_optind][ft_optwordind];
			char *pos = ft_strchr(optstring, current); // pos in optstring
			if (!pos) // option is not in optstring
			{
				if (ft_opterr && !colon_enabled)
					ft_fprintf(ft_stderr, "%s: invalid option -- '%c'\n", optstring, current);
				ft_optopt = current;
				ft_optwordind++;
				return('?');
			}
			else if (pos[1] == ':') // the option take an argument
			{
				if (argv[ft_optind][ft_optwordind + 1]) // argument is the rest of the string
				{
					ft_optarg = argv[ft_optind] + ft_optwordind + 1;
					ft_optwordind = (int)ft_strlen(argv[ft_optind]);
					return (current);
				}
				else if (ft_optind + 1 < argc) // the argument is the next argv
				{
					ft_optind++;
					ft_optarg = argv[ft_optind];
					ft_optwordind = (int)ft_strlen(argv[ft_optind]);
					has_arg = true;
					return (current);
				}
				else // no argument
				{
					if (ft_opterr && !colon_enabled) // need to print error
						ft_fprintf(ft_stderr, "%s: option requires an argument -- '%c'\n", optstring, current);
					ft_optwordind = (int)ft_strlen(argv[ft_optind]);
					ft_optopt = current;
					return (colon_enabled ? ':' : '?');
				}
			}
			else // the option don't take arguments
			{
				ft_optwordind++;
				return (current);
			}
		}
	}
}
