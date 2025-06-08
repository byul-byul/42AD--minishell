# Compiler & flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iincludes -Ilibft

# Generic build rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
