CC = cc
CFLAGS = -Werror -Wall -Wextra -ggdb3
NAME = minishell

SRCS = main.c lexer.c char_check.c str_funcs.c list_funcs.c lexer_handlers.c lexer_quotes.c ../safe_allocation/memory_system.c parser.c parser_checks.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -I ../include -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I ../include -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all fclean clean re
