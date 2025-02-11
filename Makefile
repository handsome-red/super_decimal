EXECUTABLE = decimal
CC = gcc
CFLAGS = -Wall -Wextra -Wextra -I.
SRC_DIR = core
OBJ_DIR = obj
TEST_DIR = tests


$(shell mkdir -p $(OBJ_DIR))
CORE_SRC = $(wildcard $(SRC_DIR)/*.c)
CORE_OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CORE_SRC))

TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRC))


OBJ = $(CORE_OBJ) $(TEST_OBJ)


$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) -o $(EXECUTABLE) -lcheck -lm -lsubunit


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@



test: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) $(OBJ_DIR)/*.o