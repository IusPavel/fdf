NAME   :=	fdf
SRC    :=	fdf.c draw_line.c map_handle.c \
			get_next_line.c get_next_line_utils.c \
			count_align.c isometric_projection.c utils.c
OBJ    :=	$(SRC:.c=.o)
HDR    :=	fdf.h
SRC_   :=	get_next_line.c get_next_line_utils.c \
			fdf_bonus.c draw_line_bonus.c map_handle_bonus.c \
			count_align_bonus.c show_projection_bonus.c utils_bonus.c \
			parallel_projection_bonus.c plan_projection_bonus.c
OBJ_   :=	$(SRC_:.c=.o)
HDR_   :=	fdf_bonus.h
CC     :=	gcc
CFLAGS :=	-Wall -Wextra -Werror -MMD
VPATH  :=	src include
all:		$(NAME)

$(NAME):	$(OBJ)
			$(MAKE) -C libft
			$(CC) $(CFLAGS) -Lmlx -lmlx -Llibft -lft $(OBJ) \
			-framework OpenGL -framework AppKit -o $(NAME)

bonus:		$(OBJ_)
			$(MAKE) -C libft
			$(CC) $(CFLAGS) -Lmlx -lmlx -Llibft -lft $(OBJ_) \
			-framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -Imlx -Iinclude -Ilibft -c $< -o $@

include		$(wildcard *.d)

clean:
			rm -rf *.o *.d
			$(MAKE) clean -C libft

fclean:		clean
			rm -rf $(NAME)
			$(MAKE) fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re bonus
