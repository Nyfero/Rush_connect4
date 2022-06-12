#    Colors
GREY = \e[90m
RED = \e[91m
GREEN = \e[92m
YELLOW = \e[93m
BLUE = \e[34m
PURPLE = \e[95m
CYAN = \e[96m
END = \e[39m

#    Showing command
DISP = FALSE

ifeq ($(DISP),TRUE)
    HIDE =
else
    HIDE = @
endif

#    Includes
INC = inc/

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

MLX_PATH = ./minilibx-linux

MLX = $(addprefix $(MLX_PATH)/,libmlx_Linux.a libmlx.a)

#    Folders
SRCS_PATH = srcs

SRCS_PATH_BONUS = srcs_bonus

#    Files
FILES = main.c init.c error.c display.c game.c player.c checkWin.c ia.c

FILES_BONUS = main_bonus.c init.c error.c display.c game.c player.c checkWin.c ia.c mlx.c

#    Compilation
NAME = connect4

BONUS = connect4_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

MLX_FLAG = -Lmlx_linux -Lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm

RM = rm -rf

SRCS = $(addprefix $(SRCS_PATH)/,	$(FILES))

SRCS_BONUS = $(addprefix $(SRCS_PATH_BONUS)/,	$(FILES_BONUS))

OBJS_PATH = objs/

OBJS_PATH_BONUS = objs_bonus/

OBJS = $(patsubst $(SRCS_PATH)%.c,	$(OBJS_PATH)%.o,	$(SRCS))

OBJS_BONUS = $(patsubst $(SRCS_PATH_BONUS)%.c,	$(OBJS_PATH_BONUS)%.o,	$(SRCS_BONUS))

#    Rules
all: $(NAME)

bonus: $(BONUS)

$(NAME): $(LIBFT) $(OBJS_PATH) $(OBJS) $(INC)/$(NAME).h
	@ echo "$(BLUE)\n         ***Make $(NAME) ***\n$(END)"
	$(HIDE) $(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)
	@ echo "$(GREEN)\n        ---$(NAME) created ---\n$(END)"
	
$(BONUS): $(LIBFT) $(MLX) $(OBJS_PATH_BONUS) $(OBJS_BONUS) $(INC)/$(NAME).h
	@ echo "$(BLUE)\n         ***Make $(BONUS) ***\n$(END)"
	$(HIDE) $(CC) $(CFLAGS) $(MLX_FLAG) $(OBJS_BONUS) -o $(BONUS) $(LIBFT) $(MLX)
	@ echo "$(GREEN)\n        ---$(BONUS) created ---\n$(END)"

$(LIBFT): libft/Makefile
	@ echo "$(BLUE)\n        ***Make Libft ***\n$(END)"
	$(HIDE) make -C $(LIBFT_DIR)

$(MLX):
	@ echo "$(BLUE)\n		***Make MinilibX ***\n$(END)"
	$(HIDE) make -C $(MLX_PATH)
	@ echo "$(GREEN)\n        ---MinilibX created ---\n$(END)"

$(OBJS_PATH):
	$(HIDE) mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INC)/$(NAME).h Makefile
	$(HIDE) $(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@ echo "$(GREEN)[ OK ]$(END) $(CYAN)${<:.s=.o}$(END)"
	
$(OBJS_PATH_BONUS):
	$(HIDE) mkdir -p $(OBJS_PATH_BONUS)

$(OBJS_PATH_BONUS)%.o: $(SRCS_PATH_BONUS)%.c $(INC)/$(NAME).h Makefile
	$(HIDE) $(CC) $(CFLAGS) -I $(INC) -c $< -o $@
	@ echo "$(GREEN)[ OK ]$(END) $(CYAN)${<:.s=.o}$(END)"

clean:
	$(HIDE) $(RM) $(OBJS_PATH)
	$(HIDE) $(RM) $(OBJS_PATH_BONUS)
	$(HIDE) make clean -C $(LIBFT_DIR)
	@ echo "$(PURPLE)\n        *** Clean objects ***\n$(END)"

fclean: clean
	$(HIDE) $(RM) $(NAME)
	$(HIDE) $(RM) $(BONUS)
	$(HIDE) make fclean -C $(LIBFT_DIR)
	$(HIDE) make fclean -C $(MLX_PATH)
	@ echo "$(RED)\n        *** Remove $(NAME) ***\n$(END)"

re: fclean all

.PHONY: all clean fclean re bonus
