# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abutok <abutok@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/22 16:24:00 by abutok            #+#    #+#              #
#    Updated: 2018/03/22 20:16:18 by abutok           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
PARSON = ./parson/libparson.a
#	C compiler and his default flags
GCC = gcc -Wall -Wextra
#-Werror
#	Libft linking
LINKLIBFT = -L ./libft -lft
LINKPARSON = -L ./parson -lparson

# Lib SDL
LIBSDLINCLUDE = -I ./frameworks/SDL2.framework/Versions/A/Headers \
				-I ./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I ./frameworks/SDL2_image.framework/Versions/A/Headers \
				-F ./frameworks/ 
LIBSDLFRAMES = -F ./frameworks \
				-rpath ./frameworks \
				-framework SDL2 \
				-framework SDL2_ttf -framework SDL2_image\


#	Libs linking
LINKLIB = -framework OpenGL -framework AppKit -lmlx $(LINKLIBFT) $(LINKPARSON) $(LIBSDLFRAMES)
#	Sources directories
SRCDIR = ./src/
COLORDIR = ./src/color/
FIGUREDIR = ./src/figure/
LIGHTDIR = ./src/light/
VECTORDIR = ./src/vector/
PARSEDIR = ./src/parse/
#	Source files
SRCFILES = do_rt.c main.c space.c sdl_errors.c sdl_init.c init_buttons.c \
			button_functions.c create_text.c print_list_obj.c list_properties.c \
			utils1.c
COLORFILES = color.c
FIGUREFILES = fsphere.c fplane.c fcylinder.c fcone.c ftriangle.c figure.c
LIGHTFILES = light.c
VECTORFILES = vector.c vector2.c rotate.c
PARSEFILES = pcam.c pcone.c pcylinder.c perror.c ft_hexatoi.c plight.c parse.c \
				pplane.c psphere.c ptriangle.c pelipsoid.c preflection.c pvector.c \
#	Header folder
INCLUDE = ./includes $(LIBSDLINCLUDE)
#	Binaries folder
BINDIR = ./obj/
#	Binaries list
BIN = $(addprefix $(BINDIR), $(SRCFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(COLORFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(FIGUREFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(LIGHTFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(VECTORFILES:.c=.o)) \
		$(addprefix $(BINDIR), $(PARSEFILES:.c=.o))
#	Libft
LIBFT = ./libft/libft.a
#	Libft header
LIBFTINCLUDE = ./libft/includes
#	Parson header
PARSONINCLUDE = ./parson

.NOTPARALLEL = all fclean clean re $(NAME)

all: $(LIBFT) $(PARSON) $(NAME)

$(NAME): $(BINDIR) $(BIN)
	$(GCC) $(LINKLIB) -o $(NAME) $(BIN) -I $(LIBFTINCLUDE) -I $(INCLUDE) \
		-I $(PARSONINCLUDE) 

$(BINDIR):
	@if [ ! -d "$(BINDIR)" ]; then mkdir $(BINDIR); fi

$(BINDIR)%.o: $(PARSEDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(SRCDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(COLORDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(FIGUREDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

$(BINDIR)%.o: $(LIGHTDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE)  $< -o $@

$(BINDIR)%.o: $(VECTORDIR)%.c
	$(GCC) -c -I $(INCLUDE) -I $(LIBFTINCLUDE) -I $(PARSONINCLUDE) $< -o $@

clean:
	make -C ./libft/ clean
	make -C ./parson/ clean
	if [ -d "$(BINDIR)" ]; then rm -rf $(BINDIR); fi

fclean: clean
	make -C ./libft/ fclean
	make -C ./parson/ fclean
	if [ -f "$(NAME)" ]; then rm -rf $(NAME); fi

re: fclean all

$(LIBFT):
	make -C ./libft/

$(PARSON):
	make -C ./parson/
