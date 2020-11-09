FLAG = -Wall -Wextra -Werror

NAME = ft_traceroute

all: $(NAME)

$(NAME):
	gcc *.c utils/* libft/libft.a -o $(NAME)

clean:
	@rm -f $(OBJ)
	@echo "OBJ deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all

