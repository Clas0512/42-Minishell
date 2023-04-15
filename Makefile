NAME = minishell
LIBFT = libft/libft.a

# Colors

GREEN = \033[0;32m
RESET = \033[0m

# Directories


SRC_DIR = src
OBJ_DIR = cop
LIB 	= /lib/.minishell


# Variables

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INCS = -I include -I libft
LFT = -L libft -lft  
# Flags

CC = gcc

CFLAGS = -Wall -Wextra -Werror
READLINE_FLAGS = -lreadline 
RL_FLAGS = -L./lib/readline/lib
RL_INCS = -I./lib/readline/include

# Rules

all: ${LIB} ${LIBFT} $(NAME)

$(NAME): ${LIB} $(OBJ_DIR) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFT) ${INCS}  $(RL_FLAGS) $(READLINE_FLAGS) 
	@echo "$(GREEN)$(NAME) created$(RESET)"

$(LIBFT) :
	@make -C libft/

$(LIB) :
	@make -C lib/


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCS) $(RL_INCS)  -c $< -o $@ 

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJS)
	
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJ_DIR)
	@make -C libft/ fclean
	@make -C lib/ fclean

re: fclean all

.PHONY: all clean fclean re