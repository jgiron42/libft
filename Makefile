# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgiron <jgiron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 07:10:46 by jgiron            #+#    #+#              #
#    Updated: 2022/04/19 07:11:04 by jgiron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS    =	stdlib/ft_atoi.c \
		string/ft_strspn.c \
		string/ft_strcspn.c \
		string/ft_strtok.c \
		string/ft_strpbrk.c \
		stdlib/ft_abs.c \
		stdlib/ft_labs.c \
		stdlib/ft_llabs.c \
		stdlib/ft_getenv.c \
		stdlib/ft_atof.c \
		stdlib/ft_atol.c \
		stdlib/ft_atoll.c \
		stdlib/ft_strtol.c \
		stdlib/ft_strtoll.c \
		stdlib/ft_strtod.c \
		stdlib/ft_strtof.c \
		stdlib/ft_strtold.c \
		other/ft_posixly_correct.c \
		unistd/ft_getopt.c \
		strings/ft_bzero.c	\
		stdlib/ft_calloc.c	\
		ctype/ft_isspace.c	\
		ctype/ft_isalnum.c	\
		ctype/ft_isalpha.c	\
		ctype/ft_isascii.c	\
		ctype/ft_isdigit.c	\
		ctype/ft_isprint.c	\
		other/ft_itoa.c	\
		string/ft_memccpy.c	\
		string/ft_memchr.c	\
		string/ft_memcmp.c	\
		string/ft_memcpy.c	\
		string/ft_memmove.c	\
		string/ft_memset.c	\
		string/ft_strcmp.c	\
		other/ft_putendl_fd.c	\
		other/ft_putnbr_fd.c	\
		other/ft_putstr_fd.c	\
		other/ft_split.c	\
		string/ft_strcat.c	\
		string/ft_strchr.c	\
		string/ft_strcpy.c	\
		string/ft_strdup.c	\
		string/ft_strndup.c	\
		string/ft_strstr.c	\
		other/ft_strjoin.c	\
		other/ft_append.c	\
		other/ft_strlcat.c	\
		other/ft_strlcpy.c	\
		string/ft_strncpy.c	\
		string/ft_strlen.c	\
		other/ft_strmapi.c	\
		string/ft_strncmp.c	\
		other/ft_strnstr.c	\
		strings/ft_strncasecmp.c	\
		strings/ft_strcasecmp.c	\
		string/ft_strrchr.c	\
		other/ft_strtrim.c	\
		other/cursed_abort.c	\
		other/ft_substr.c	\
		ctype/ft_tolower.c	\
		ctype/ft_toupper.c \
		other/ft_striteri.c	\
		other/ft_lstadd_front_bonus.c	\
		other/ft_lstadd_back_bonus.c	\
		other/ft_lstclear_bonus.c	\
		other/ft_lstdelone_bonus.c	\
		other/ft_lstiter_bonus.c	\
		other/ft_lstlast_bonus.c	\
		other/ft_lstmap_bonus.c	\
		other/ft_lstnew_bonus.c	\
		other/ft_lstsize_bonus.c	\
		stdio/ft_clearerr.c \
        stdio/ft_expand_buf.c \
        stdio/ft_fclose.c \
        stdio/ft_feof.c \
        stdio/ft_ferror.c \
        stdio/ft_fflush.c \
        stdio/ft_fgetc.c \
        stdio/ft_fgetpos.c \
        stdio/ft_fgets.c \
        stdio/ft_fileno.c \
        stdio/ft_fopen.c \
        stdio/ft_fputc.c \
        stdio/ft_fputs.c \
        stdio/ft_fread.c \
        stdio/ft_fseek.c \
        stdio/ft_fsetpos.c \
        stdio/ft_ftell.c \
        stdio/ft_fwrite.c \
        stdio/ft_getc.c \
        stdio/ft_getchar.c \
        stdio/ft_get_delim_buffered.c \
        stdio/ft_getdelim.c \
        stdio/ft_getline.c \
        stdio/ft_gets.c \
        stdio/ft_perror.c \
        stdio/ft_putc.c \
        stdio/ft_putchar.c \
        stdio/ft_puts.c \
        stdio/ft_remove.c \
        stdio/ft_rename.c \
        stdio/ft_rewind.c \
        stdio/ft_setbuf.c \
        stdio/ft_setvbuf.c \
        stdio/ft_ungetc.c \
        stdio/ft_ungets.c \
        stdio/globals.c \
		stdio/printf/ft_vfprintf.c \
		stdio/printf/ft_fprintf.c \
		stdio/printf/ft_vsprintf.c \
		stdio/printf/ft_sprintf.c \
		stdio/printf/ft_vsnprintf.c \
		stdio/printf/ft_snprintf.c \
		stdio/printf/ft_vprintf.c \
		stdio/printf/ft_printf.c \
		stdio/printf/handle_i.c \
		stdio/printf/handle_integer.c \
		stdio/printf/handle_char.c \
		stdio/printf/handle_percent.c \
		stdio/printf/handle_string.c \
		stdio/printf/handle_m.c \
		stdio/printf/handle_n.c \
		stdio/printf/parsing.c \
		stdio/printf/utils.c \
		containers/list.c \
		containers/btree.c \
		containers/vector.c \
		containers/string.c \
		containers/buffer.c \
		containers/bheap.c \
		containers/iterator.c \
		containers/oo_utils.c \
		regex/ft_regcomp.c \
		regex/ft_regexec.c \
		regex/ft_regerror.c \
		regex/ft_regfree.c
#		containers/generic_interface.c \

NAME    =	libft.a

CFLAGS  +=	-Wall -Werror -Wextra -g3 -D ENABLE_STRERROR # -fsanitize=address

SRCS_DIR = srcs

OBJS_DIR = .objs

INCLUDE_DIR = .

CFLAGS = -Wall -Werror -Wextra -g3

include makefile-template/lib.mk