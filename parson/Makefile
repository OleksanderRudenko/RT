NAME = libparson.a
GCC = gcc -Wall -Wextra -Werror -c
SRC = parson.c
OBJ = parson.o
HEADER = parson.h

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib libparson.a

$(OBJ):
	@$(GCC) $(SRC)

clean:
	@if [ -f "parson.o" ]; then rm -rf parson.o; fi

fclean: clean
	@if [ -f "libparson.a" ]; then rm -rf libparson.a; fi

re: fclean all