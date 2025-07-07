CC = cc
CFLAGS = -Werror -Wall -Wextra -ggdb3

NAME = minishell

SRCS = main.c \
	parser/lexer.c \
	parser/char_check.c \
	parser/str_funcs.c \
	parser/list_funcs.c \
	parser/lexer_handlers.c \
	parser/lexer_quotes.c \
	parser/parser.c \
	parser/parser_checks.c \
	parser/lexer_segments.c \
	parser/expand.c \
	parser/env_funcs.c \
	parser/field_split.c \
	execution/builtins/builtins.c \
	execution/execution.c \
	execution/env.c \
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