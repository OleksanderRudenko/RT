NAME = libtfd.a
FLAGS = -Wall -Wextra -Werror
ODIR = bin/
OBJ = $(SRC:.c=.o)

SRC = tinyfiledialogs.c

O = $(addprefix $(ODIR), $(OBJ))

all: $(NAME)

$(NAME): $(O) $(EXT)
	@ar rc $(NAME) $(O)
	@ranlib $(NAME)

$(ODIR)%.o: %.c $(EXT)
	@gcc $(FLAGS) -c $< -o $@

$(O): | ./bin

./bin:
	@mkdir $(ODIR)

clean:
	@rm -rf $(ODIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
