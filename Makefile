NAME          = libasm.a
CFLAGS        = -Wall # -Wextra -Werror
OBJ_DIR       = obj
SRC_DIR       = src/assembly
SRC           = $(SRC_DIR)/ft_write.s $(SRC_DIR)/ft_read.s
OBJ           = $(SRC:$(SRC_DIR)/%.s=$(OBJ_DIR)/%.o)
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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s $(HEADERS)
	@echo "Assembling $<..."
	@mkdir -p $(OBJ_DIR)
	$(NASM) ${NASMFLAGS} -o $@ $<

$(OBJ_DIR):
	@mkdir -p $@

test: $(NAME)
	@$(CC) src/main.c $(NAME) -I$(HEADERS)} $(CFLAGS)

clean:
	@echo "\n"
	@echo $(OBJECTS)
	@rm -rf $(OBJ_DIR)
	@printf $(REM_MESSAGE)
	@echo "\n"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
