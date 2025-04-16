NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = Minishell_42/pars/parsing.c Minishell_42/src/main.c

OBJS = $(SRCS:.c=.o)

all  : $(NAME)

$(LIB):
	$(MAKE) -C libft/

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(CFLAGS) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C libft/

fclean: clean
	$(MAKE) fclean -C libft/ 
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)