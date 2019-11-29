# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vronchin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/17 13:49:12 by vronchin          #+#    #+#              #
#    Updated: 2019/11/28 14:05:23 by jgiron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    =	ft_atoi.c	\
		ft_bzero.c	\
		ft_calloc.c	\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_itoa.c	\
		ft_memccpy.c	\
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
		ft_strrchr.c	\
		ft_strtrim.c	\
		ft_substr.c	\
		ft_tolower.c	\
		ft_toupper.c

OBJS    =	$(SRCS:.c=.o)

HEADER	=	libft.h

NAME    =	libft.a

CFLAGS  +=	-Wall -Werror -Wextra

all	:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER)
		gcc -c $(SRCS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

clean	:
		rm -f $(OBJS)

fclean	:	clean
	        rm -f $(NAME)

re	:	fclean all

.PHONY	:	clean fclean re all compil_objs compil_lib 
