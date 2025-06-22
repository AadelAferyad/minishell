NAME := builtin

CC := cc
FLAGS := -Wall -Wextra -Werror

main := $(ARG)
src := ../../execution/builtins/builtins.c
libft := ~/minishell/libft/libft.a

all: $(NAME)

builtin: $(src) $(main) $(libft)
	${CC} $(FLAGS) $(main) $(src) $(libft) -I ~/minishell/include -o builtin



fclean: 
	rm -rf builtin 
