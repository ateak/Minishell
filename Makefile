# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 12:14:22 by cpollito          #+#    #+#              #
#    Updated: 2022/09/09 13:42:08 by cpollito         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell 

PARS_DIR := parser
BUILT_DIR := builtin
LIBFT_DIR := my_libft

LIBFT = $(LIBFT_DIR)/libft.a

PARS_F := check_syntax_main.c\
				check_syntax.c\
				lexer_main.c\
				lexer_list_utils.c\
				lexer_pipe_redir_tokens.c\
				parser_main.c\
				parser_create_cmd_args.c\
				parser_redir_handler.c\
				parser_tokens_handler.c\
				parser_dollar_handler_main.c\
				parser_dollar_handler_prt1.c\
				parser_dollar_handler_prt2.c\
				parser_utils.c\

PARSER := $(addprefix $(PARS_DIR)/, $(PARS_F))
BUILT_F := builtin_pwd_echo.c\
				builtin_export_prt1.c\
				builtin_export_prt2.c\
				builtin_env_exit.c\
				builtin_unset.c\
				builtin_cd.c\

BUILTIN := $(addprefix $(BUILT_DIR)/, $(BUILT_F))			

SRCS_F := main.c utils.c executor.c errors.c\
				parsing_env_into_list.c parsing_env_into_arr.c\
				shlvl.c\
				just_do_it.c\
				redirects.c heredoc.c\
				get_next_line/get_next_line.c\
				get_next_line/get_next_line_utils.c\
				signals.c\
				free_functions.c\

SRCS := $(SRCS_F) $(BUILTIN) $(PARSER)
OBJ := $(SRCS:.c=.o)

HEADER := minishell.h\
	get_next_line/get_next_line.h

CC := cc
CFLAGS := -Wall -Wextra -Werror -g
# CFLAGS := -Wall -Wextra -Werror -g -fsanitize=address

RDLN	:= 	-lreadline -L ~/.brew/Cellar/readline/8.1.2/lib\
			  	-I~/.brew/Cellar/readline/8.1.2/include

RM := rm -rf

.PHONY:	all clean fclean re libft
	
all :  libft $(NAME)

$(NAME): $(OBJ) Makefile
	$(CC) $(CFLAGS) $(RDLN) $(OBJ) -I$(LIBFT_DIR) $(LIBFT) -o $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@ 

libft: 
	@make -C $(LIBFT_DIR)

clean :
	@$(RM) $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR) 

fclean : clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all
