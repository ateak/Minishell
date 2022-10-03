# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 18:33:39 by cpollito          #+#    #+#              #
#    Updated: 2022/08/08 14:05:07 by cpollito         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a

SRCS 	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
			ft_strlcpy.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
			ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strlcat.c ft_strnstr.c\
			ft_atoi.c ft_calloc.c ft_strdup.c ft_putchar_fd.c ft_putstr_fd.c\
			ft_putnbr_fd.c ft_itoa.c ft_putendl_fd.c ft_substr.c ft_strjoin.c\
			ft_strmapi.c ft_striteri.c ft_split.c ft_strtrim.c\
			ft_strcmp.c ft_strchr_int.c\
			ft_lstsize.c ft_lstnew.c ft_lstadd_back.c ft_lstadd_front.c\
			ft_lstclear.c ft_lstlast.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c\
			ft_isspace.c\

# SRCS_B	= ft_lstsize.c ft_lstnew.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstlast.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c

HEADER 	= libft.h 

OBJ		=	$(SRCS:.c=.o)
OBJ_B	= $(SRCS_B:.c=.o)

CC 		= cc
CFLAGS 	= -Wall -Werror -Wextra 
RM 		= rm -f

.PHONY : all clean fclean re bonus

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	ar rcs $(NAME) $?

bonus:	$(OBJ) $(OBJ_B) $(HEADER)
	ar rcs $(NAME) $(OBJ) $(OBJ_B)
	

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJ) $(OBJ_B)

fclean	:	clean
	@$(RM) $(NAME)

re	:	fclean all