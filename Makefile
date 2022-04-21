# Paths
SRC = ./src
BIN = ./bin
OBJ = ./obj
MATH = $(SRC)/math
IMAGE = $(SRC)/image

# Other
FLAGS = -g -std=c++14
INC := -I $(MATH) -I $(IMAGE)
OBJS = $(OBJ)/image.o $(OBJ)/math.o

all: $(BIN)/rt3.out

$(BIN)/rt3.out: $(OBJS) $(SRC)/rt3.cpp | $(BIN)
	g++ $(SRC)/rt3.cpp $(OBJS) -o $(BIN)/rt3.out $(INC) $(FLAGS)

$(OBJ)/image.o: $(IMAGE)/image.h $(IMAGE)/image.cpp | $(OBJ)
	g++ -c -o $(OBJ)/image.o $(IMAGE)/image.cpp $(INC) $(FLAGS)

$(OBJ)/math.o: $(MATH)/math.h $(MATH)/math.cpp | $(OBJ)
	g++ -c -o $(OBJ)/math.o $(MATH)/math.cpp $(INC) $(FLAGS)

$(OBJ):
	mkdir -p $(OBJ)

$(BIN):
	mkdir -p $(BIN)

# Clean project
clean:
	@# @ symbol at beginning indicates that it will not be printed
	@if [ "$$(ls -A $(OBJ))" ]; then \
		rm $(OBJ)/*; \
	fi
	@if [ "$$(ls -A $(BIN))" ]; then \
		rm $(BIN)/*; \
	fi