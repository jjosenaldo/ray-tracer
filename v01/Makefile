# Paths
SRC = ./src
BIN = ./bin
OBJ = ./obj
CORE = $(SRC)/core
UTILS = $(SRC)/utils
MAIN = $(SRC)/main
TINYXML = $(CORE)/tinyxml2
CXXOPTS = $(CORE)/cxxopts

WARNS = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
-Winit-self -Wlogical-op -Wmissing-declarations \
-Wmissing-include-dirs -Wnoexcept -Wold-style-cast \
-Woverloaded-virtual -Wredundant-decls -Wsign-conversion \
-Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
-Wswitch-default -Wundef -Wno-unused-variable

# Other
FLAGS = $(NO_WARNS_FLAGS) $(WARNS)
NO_WARNS_FLAGS = -g -std=c++17
INC := -I $(UTILS) -I $(CORE) -isystem $(TINYXML) -isystem $(CXXOPTS)
OBJS = $(OBJ)/image.o $(OBJ)/math.o $(OBJ)/api.o $(OBJ)/background.o $(OBJ)/camera.o $(OBJ)/film.o $(OBJ)/parser.o $(OBJ)/tinyxml2.o

all: $(BIN)/rt3.out

$(BIN)/rt3.out: $(OBJS) $(MAIN)/rt3.cpp | $(BIN)
	g++ $(MAIN)/rt3.cpp $(OBJS) -o $(BIN)/rt3.out $(INC) $(FLAGS)

$(OBJ)/image.o: $(UTILS)/image.h $(UTILS)/image.cpp | $(OBJ)
	g++ -c -o $(OBJ)/image.o $(UTILS)/image.cpp $(INC) $(FLAGS)

$(OBJ)/math.o: $(UTILS)/math.h $(UTILS)/math.cpp | $(OBJ)
	g++ -c -o $(OBJ)/math.o $(UTILS)/math.cpp $(INC) $(FLAGS)

$(OBJ)/api.o: $(CORE)/api.h $(CORE)/api.cpp | $(OBJ)
	g++ -c -o $(OBJ)/api.o $(CORE)/api.cpp $(INC) $(FLAGS)

$(OBJ)/background.o: $(CORE)/background.h $(CORE)/background.cpp | $(OBJ)
	g++ -c -o $(OBJ)/background.o $(CORE)/background.cpp $(INC) $(FLAGS)

$(OBJ)/camera.o: $(CORE)/camera.h $(CORE)/camera.cpp | $(OBJ)
	g++ -c -o $(OBJ)/camera.o $(CORE)/camera.cpp $(INC) $(FLAGS)

$(OBJ)/film.o: $(CORE)/film.h $(CORE)/film.cpp | $(OBJ)
	g++ -c -o $(OBJ)/film.o $(CORE)/film.cpp $(INC) $(FLAGS)

$(OBJ)/parser.o: $(CORE)/parser.h $(CORE)/parser.cpp | $(OBJ)
	g++ -c -o $(OBJ)/parser.o $(CORE)/parser.cpp $(INC) $(FLAGS)

$(OBJ)/tinyxml2.o: $(TINYXML)/tinyxml2.h $(TINYXML)/tinyxml2.cpp | $(OBJ)
	g++ -c -o $(OBJ)/tinyxml2.o $(TINYXML)/tinyxml2.cpp $(NO_WARNS_FLAGS)

$(OBJ):
	mkdir -p $(OBJ)

$(BIN):
	mkdir -p $(BIN)

# Clean project
clean:
	@# @ symbol at beginning indicates that it will not be printed
	@if [ "$$(ls -A $(OBJ))" ]; then \
		rm -rf $(OBJ); \
	fi
	@if [ "$$(ls -A $(BIN))" ]; then \
		rm -rf $(BIN); \
	fi
