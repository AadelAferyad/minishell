NAME := minishell

CC := cc

FLAGS := -Wextra -Werror -Wall -I include

src_libft := libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_memchr.c\
	 libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c\
	 libft/ft_strchr.c libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c\
	 libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_puts.c libft/ft_putchar.c libft/ft_putnbr.c libft/ft_reverse.c

src_collector := safe_allocation/memory_system.c

src_builtins := execution/env.c execution/builtins/builtins.c

all: $(NAME)

$(NAME): $(src_libft) $(src_collector) $(src_builtins)
	$(CC) $(FLAGS) main.c -lreadline $(src_collector) $(src_libft) $(src_builtins) -o $(NAME)

fclean:
	rm -rf minishell

