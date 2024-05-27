NAME          = libasm.a
CFLAGS        = -Wall -Wextra -Werror

OBJ_DIR       = obj
SRC_DIR       = src/assembly/core
BONUS_DIR     = src/assembly/bonus

SRC           = $(SRC_DIR)/ft_write.s $(SRC_DIR)/ft_read.s $(SRC_DIR)/ft_strlen.s $(SRC_DIR)/ft_strcmp.s $(SRC_DIR)/ft_strdup.s $(SRC_DIR)/ft_strcpy.s
BONUS					= $(BONUS_DIR)/ft_atoi_base.s

OBJ           = $(SRC:.s=.o)
OBJ_BONUS     = $(BONUS:.s=.o)

HEADERS       = src/libasm.h

NASM          = nasm
NASMFLAGS     = -f elf64 -F dwarf -g -w+all

GREEN           = \033[1;32m
BLUE            = \033[1;36m
RED             = \033[0;31m
NC              = \033[0m # No Color

START           = "$(BLUE)---\nStarting...!\n---$(NC)"
MESSAGE         = "$(BLUE)---\nCompiling done! Run ./$(NAME)\n---$(NC)"
COMP_MESSAGE    = "$(GREEN)Building C object... $(NC)%-33.33s\r\n"
REM_MESSAGE     = "$(RED)Removing files...$(NC)"

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking..."
	ar rcs $@ $(OBJ)
	@echo "Build complete."

bonus: $(OBJ) $(OBJ_BONUS)
	@echo "Linking..."
	ar rcs $(NAME) $(OBJ) $(OBJ_BONUS) 
	@echo "Build complete."

%.o: %.s
	@echo "Assembling $<..."
	@mkdir -p $(OBJ_DIR)
	$(NASM) ${NASMFLAGS} -o $@ $<

$(OBJ_DIR):
	@mkdir -p $@

test: $(NAME)  
	@$(CC) src/main.c $(NAME) -I$(HEADERS)} $(CFLAGS)

test_bonus: $(NAME) bonus 
	@$(CC) src/bonus.c $(NAME) -I$(HEADERS)} $(CFLAGS) -DBONUS=1

clean:
	@echo "\n"
	@echo $(OBJECTS)
	@rm -rf $(OBJ_DIR)
	@printf $(REM_MESSAGE)
	@echo "\n"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
