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


SRCS    =	ft_atoi.c \
		ft_strspn.c \
		ft_strcspn.c \
		ft_strtok.c \
		ft_strpbrk.c \
		ft_abs.c \
		ft_labs.c \
		ft_llabs.c \
		ft_getenv.c \
		ft_atof.c \
		ft_atol.c \
		ft_atoll.c \
		ft_strtol.c \
		ft_strtoll.c \
		ft_strtod.c \
		ft_strtof.c \
		ft_strtold.c \
		ft_posixly_correct.c \
		ft_getopt.c \
		ft_bzero.c	\
		ft_calloc.c	\
		ft_isspace.c	\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_itoa.c	\
		ft_memchr.c	\
		ft_memcmp.c	\
		ft_memcpy.c	\
		ft_memmove.c	\
		ft_memset.c	\
		ft_putchar_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		ft_putstr_fd.c	\
		ft_split.c	\
		ft_strchr.c	\
		ft_strdup.c	\
		ft_strjoin.c	\
		ft_strlcat.c	\
		ft_strlcpy.c	\
		ft_strlen.c	\
		ft_strmapi.c	\
		ft_strncmp.c	\
		ft_strnstr.c	\
		ft_strncasecmp.c	\
		ft_strcasecmp.c	\
		ft_strrchr.c	\
		ft_strtrim.c	\
		ft_substr.c	\
		ft_tolower.c	\
		ft_striteri.c	\
		ft_toupper.c \
		ft_lstadd_front_bonus.c	\
		ft_lstadd_back_bonus.c	\
		ft_lstclear_bonus.c	\
		ft_lstdelone_bonus.c	\
		ft_lstiter_bonus.c	\
		ft_lstlast_bonus.c	\
		ft_lstmap_bonus.c	\
		ft_lstnew_bonus.c	\
		ft_lstsize_bonus.c	\

OBJS    =	$(SRCS:.c=.o)\

HEADER	=	libft.h

NAME    =	libft.a

CFLAGS  +=	-Wall -Werror -Wextra -g3

all	:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(BONUS)
	gcc -shared -nostartfiles -o libft.so $(OBJS) $(OBJS_BONUS)

clean	:
		rm -f $(OBJS) $(OBJS_BONUS)

fclean	:	clean
	        rm -f $(NAME) libft.so

re	:	fclean all
	
.PHONY	:	clean fclean re all compil_objs compil_lib 
