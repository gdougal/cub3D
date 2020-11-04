# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdougal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 21:58:00 by gdougal           #+#    #+#              #
#    Updated: 2020/11/04 11:55:53 by gdougal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D

CC				=	gcc

LIBFT_DIR		=	./libs/libft/

MLX_DIR			=	./libs/minilibx/

SRCS_DIR		=	./srcs/

HEADERS_DIR		=	$(SRCS_DIR)include/

INCLUDES		=	-I$(HEADERS_DIR) -I$(MLX_DIR) -I./$(LIBFT_DIR)

FLAGS			=	$(INCLUDES) -Wall -Wextra -Werror -MD

LFLAGS			=	-L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

PARS_DIR		=	Parser/
SRCS_PARS		=  $(addprefix $(PARS_DIR), check_type_first_arg.c \
											color_check_f_c.c \
											create_rgb.c \
											cub3D.c \
											glob_error.c \
											init_pars_struct.c \
											map_proc.c \
											map_reproc.c \
											map_validation.c \
											proc_path_to_tex.c \
											proc_r_f_c.c)
GNL_DIR			=	gnl/
SRCS_GNL		=	$(addprefix $(GNL_DIR), get_next_line.c \
											 get_next_line_utils.c)

TRIG_DIR		=	Trigonometry/
SRCS_TRIG		=	$(addprefix $(TRIG_DIR), dist_between.c \
											 distantion.c \
											 null_x_y.c \
											 vector_vision.c \
											 what_a_wall.c)

MV_DIR			=	Move_and_pos/
SRC_MV			=	$(addprefix $(MV_DIR), move_rotate.c \
											 pers_sprites_pos.c \
											 spawn_add.c)

INIT_DIR		=	init_struct/
SRC_INIT		=	$(addprefix $(INIT_DIR), init_struct.c)

RDR_DIR			=	Render/
SRC_RDR			=	$(addprefix $(RDR_DIR), pix_color_txtrs.c \
											pixel_put.c \
											render.c \
											screenshoot.c \
											window.c)
SPRT_DIR		=	Sprites/
SRC_SPRT		=	$(addprefix $(SPRT_DIR), buble_sort_list.c \
											 sprite_color.c \
											 sprites_first.c \
											 sprites_two.c)

SRCS_ALL		=	$(addprefix $(SRCS_DIR), \
									$(SRCS_PARS) \
									$(SRCS_GNL) \
									$(SRCS_TRIG) \
									$(SRC_MV) \
									$(SRC_INIT) \
									$(SRC_RDR) \
									$(SRC_SPRT))

OBJ_DIR			=	./obj/

O_FILE			=	$(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS_ALL))
D_FILE 			=	$(patsubst %.c,%.d,$(SRCS_ALL))

ALL_O_DIRS		=	$(addprefix $(OBJ_DIR), $(GNL_DIR) $(PARS_DIR) $(TRIG_DIR) $(MV_DIR) $(INIT_DIR) $(RDR_DIR) $(SPRT_DIR))

.PHONY: all
all: $(NAME)

$(NAME): $(ALL_O_DIRS) $(O_FILE)
	$(MAKE) -C libs/libft all
	$(MAKE) -C libs/libft bonus
	$(MAKE) -C libs/minilibx all
	gcc $(FLAGS) $(O_FILE) $(LFLAGS) -o $(NAME)

$(O_FILE): $(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	gcc -c $(FLAGS) $(INCLUDES) -c $< -o $@ -MD

$(ALL_O_DIRS):
		@mkdir -p $(ALL_O_DIRS)

.PHONY: clean
clean:
	$(MAKE) -C libs/libft clean
	$(MAKE) -C libs/minilibx clean
	rm -rf $(OBJ_DIR)
	rm -f $(O_FILE)
	rm -f $(D_FILE)

PHONY: fclean
fclean: clean
	$(MAKE) -C libs/libft fclean
	rm -f $(NAME)

.PHONY: re
re:		fclean all
	-include $(wildcards $(D_FILE))

