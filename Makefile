NAME = minishell

CC = cc
CFLGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/main.c src/minishell.c src/init.c src/builtins/cd.c src/builtins/pwd.c src/builtins/env.c src/builtins/echo.c src/builtins/export.c src/builtins/export_2.c src/builtins/unset.c src/token.c src/check.c src/expend.c src/frees.c src/signals.c src/redirections.c src/splits.c src/splits_2.c src/find_path.c src/builtins/exit.c src/heredoc.c src/utils.c src/expend_2.c src/builtins/builtins.c src/builtins/export_3.c src/execve.c src/heredoc_2.c 
OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(LIBFT) $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

