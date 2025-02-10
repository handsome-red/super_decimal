EXECUTABLE = decimal
CC = gcc
CFLAGS = -Wall -Wextra -Wextra -I.
SRC_DIR = core
OBJ_DIR = obj


$(shell mkdir -p $(OBJ_DIR))
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) -o $(EXECUTABLE) -lcheck -lm -lsubunit

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(EXECUTABLE) $(OBJ_DIR)/*.o