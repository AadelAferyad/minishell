CC = cc
CFLAGS = -Werror -Wall -Wextra -ggdb3 #-fsanitize=address

NAME = minishell

SRCS = main.c \
	parser/lexer.c \
	parser/char_check.c \
	parser/char_check2.c \
	parser/str_funcs.c \
	parser/list_funcs.c \
	parser/cleaning.c \
	parser/lexer_handlers.c \
	parser/lexer_segments.c \
	parser/lexer_quotes.c \
	parser/lexer_utils.c \
	parser/parser.c \
	parser/parser_checks.c \
	parser/herdoc.c \
	parser/herdoc_read.c \
	parser/herdoc_func.c \
	parser/herdoc_utils.c \
	parser/expand.c \
	parser/env_funcs.c \
	parser/field_split.c \
	execution/builtins/builtins.c \
	execution/builtins/builtins_1.c \
	execution/builtins/builtins_2.c \
	execution/builtins/builtins_3.c \
	execution/builtins/builtins_4.c \
	execution/normal_func.c \
	execution/execution.c \
	execution/env.c \
	execution/execute_cmd.c \
	execution/execute_multiple_cmd.c \
	execution/pipeline.c \
	execution/execution_func.c \
	execution/execution_path.c \
	execution/redirection.c \
	safe_allocation/memory_system.c \

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -I include -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I include -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all fclean clean re
