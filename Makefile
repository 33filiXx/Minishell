NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = Minishell_42/pars/parsing.c Minishell_42/pars/parser.c Minishell_42/src/main.c  \
Minishell_42/pars/lexer_h.c  Minishell_42/exec/builtin/echo.c  Minishell_42/exec/free/free.c \
Minishell_42/exec/builtin/cd.c Minishell_42/exec/builtin/pwd.c Minishell_42/exec/env/env.c Minishell_42/exec/env/extract_path.c \
Minishell_42/exec/builtin/export.c Minishell_42/exec/builtin/unset.c Minishell_42/exec/exc/init_ex.c \

OBJS = $(SRCS:.c=.o)
LIB = ./ft_libft/libft.a

all  : $(NAME)


$(LIB):
	$(MAKE) -C ft_libft/

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(CFLAGS) $(LIB) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C ft_libft/

fclean: clean
	$(MAKE) fclean -C ft_libft/ 
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)