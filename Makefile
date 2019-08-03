# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/10 17:38:22 by dmorgil           #+#    #+#              #
#    Updated: 2019/08/03 19:06:19 by ggwin-go         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=21sh
FLAGS=-Wall -Wextra -Werror -g
HEADER=includes/sh.h

SRCS_DIR=sources/
OBJS_DIR=objects/

LIBFT_DIR=libft

LEXER_DIR=lexer/

SRCS_LEXER=\
	lexer.c\
	lexer_and_or.c\
	lexer_check_redir.c\
	lexer_get_token.c\
	lexer_bang.c

PARSER_DIR=parser/

SRCS_PARSER=\
	parser.c\
	parser_and_or.c\
	parser_cmd.c\
	parser_cmd_prefix.c\
	parser_cmd_suffix.c\
	parser_io_redirect.c\
	parser_pipe_sequence.c\
	parser_pipeline.c\
	parser_print_error.c\
	parser_free_tree.c\
	parser_free_cmd.c

AST_ITER_DIR=ast_iter/

SRCS_AST_ITER=\
	ast_exec.c\
	ast_print_in_order.c

EXEC_DIR=exec/

SRCS_EXEC=\
	exec.c\
	exec_fill_fifo.c\
	exec_open.c\
	exec_print_error.c\
	exec_redir_right.c\
	ft_pipe.c

HASH_DIR=hash_table/

SRCS_HASH=\
	create_bin.c\
	create_hash.c\
	del_hash.c\
	fill_hash_table.c\
	get_bin.c\
	null_hash.c\
	paste_path.c\
	search_env_str.c

DIR_LIB_WTALEA=lib_wtalea/

SRCS_LIB_WTALEA=die_log.c

SRCS_WITHOUT_DIR=\
	main.c

SOURCES=$(SRCS_WITHOUT_DIR)\
	$(addprefix $(AST_ITER_DIR), $(SRCS_AST_ITER))\
	$(addprefix $(LEXER_DIR), $(SRCS_LEXER))\
	$(addprefix $(PARSER_DIR), $(SRCS_PARSER))\
	$(addprefix $(HASH_DIR), $(SRCS_HASH))\
	$(addprefix $(DIR_LIB_WTALEA), $(SRCS_LIB_WTALEA))

SRCS=$(addprefix $(SRCS_DIR), $(SOURCES))
OBJS=$(addprefix $(OBJS_DIR), $(SOURCES:.c=.o))

OBJS_CLEAN=$(strip $(foreach f,$(OBJS),$(wildcard $(f))))
NAME_CLEAN=$(strip $(NAME))

LIBFT_A=$(LIBFT_DIR)/libft.a
INCLUDES:=-I includes -I libft/includes

RED=\033[0;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
NC=\033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(OBJS_DIR):
	@echo "$(BLUE)Compiling $(NAME_CLEAN) objects files...$(NC)"
	@mkdir -p $(OBJS_DIR)$(AST_ITER_DIR)
	@mkdir -p $(OBJS_DIR)$(LEXER_DIR)
	@mkdir -p $(OBJS_DIR)$(PARSER_DIR)
	@mkdir -p $(OBJS_DIR)$(HASH_DIR)
	@mkdir -p $(OBJS_DIR)$(DIR_LIB_WTALEA)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@gcc $(INCLUDES) $(FLAGS) -o $@ -c $<

$(LIBFT_A):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A) $(OBJS_DIR) $(OBJS)
	@echo "$(BLUE)Compiling executable...$(NC)"
	@gcc $(OBJS) $(LIBFT_A) $(INCLUDES) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)Bin $(NAME) is ready to use!$(NC)"

clean:
ifneq ($(OBJS_CLEAN),)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)$(NAME_CLEAN) objects files removed.$(NC)"
else
	@echo "$(RED)$(NAME_CLEAN) objects already cleaned$(NC)"
endif

fclean: clean
ifneq ($(NAME_CLEAN),)
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME)
	@echo "$(RED)Bin $(NAME_CLEAN) removed.$(NC)"
else
	@echo "$(RED)Objects and bin $(NAME_CLEAN) already cleaned$(NC)"
endif

test:
	gcc $(FLAGS) -g $(SRCS) -o $(NAME) $(INCLUDES) $(LIBFT_A)

re: fclean all
