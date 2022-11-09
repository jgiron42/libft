#ifndef LIBFT_FT_UNISTD_H
#define LIBFT_FT_UNISTD_H
# include "ft_def.h"

extern char *ft_optarg;
extern int ft_optind, ft_opterr, ft_optopt;

int		ft_getopt(int argc, char * const argv[], const char *optstring);

#endif
