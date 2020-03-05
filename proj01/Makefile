# Paths
SRC = ./src
BIN = ./bin
OBJ = ./obj
PARSER = $(SRC)/parser
TINYXML = $(PARSER)/tinyxml
UTILS = $(SRC)/utils
SCENE = $(SRC)/scene

# Other
FLAGS = -g -std=c++14
INC := -I $(TINYXML) -I $(PARSER) -I $(UTILS) -I $(SCENE)
OBJS = $(OBJ)/tinyxml.o $(OBJ)/tinystr.o $(OBJ)/tinyxmlerror.o $(OBJ)/tinyxmlparser.o \
	   $(OBJ)/background.o $(OBJ)/camera.o $(OBJ)/film.o $(OBJ)/parser.o \
	   $(OBJ)/linearalgebra.o $(OBJ)/rt3.o

all: $(BIN)/rt.out

$(BIN)/rt.out: $(OBJS) $(SRC)/main.cpp
	g++ $(SRC)/main.cpp $(OBJS) -o $(BIN)/rt.out $(INC) $(FLAGS)

$(OBJ)/background.o: $(SCENE)/background.hpp $(SCENE)/background.cpp $(UTILS)/paramset.hpp
	g++ -c -o $(OBJ)/background.o $(SCENE)/background.cpp $(INC) $(FLAGS)

$(OBJ)/camera.o: $(SCENE)/camera.hpp $(SCENE)/camera.cpp $(UTILS)/paramset.hpp
	g++ -c -o $(OBJ)/camera.o $(SCENE)/camera.cpp $(INC) $(FLAGS)

$(OBJ)/film.o: $(SCENE)/film.hpp $(SCENE)/film.cpp $(UTILS)/paramset.hpp
	g++ -c -o $(OBJ)/film.o $(SCENE)/film.cpp $(INC) $(FLAGS)

$(OBJ)/linearalgebra.o: $(UTILS)/linearalgebra.hpp $(UTILS)/linearalgebra.cpp
	g++ -c -o $(OBJ)/linearalgebra.o $(UTILS)/linearalgebra.cpp $(INC) $(FLAGS)

$(OBJ)/parser.o: $(PARSER)/parser.hpp $(PARSER)/parser.cpp
	g++ -c -o $(OBJ)/parser.o $(PARSER)/parser.cpp $(INC) $(FLAGS)

$(OBJ)/rt3.o: $(SCENE)/rt3.hpp $(SCENE)/rt3.cpp
	g++ -c -o $(OBJ)/rt3.o $(SCENE)/rt3.cpp $(INC) $(FLAGS)

$(OBJ)/tinystr.o: $(TINYXML)/tinystr.h $(TINYXML)/tinystr.cpp
	g++ -c -o $(OBJ)/tinystr.o $(TINYXML)/tinystr.cpp $(INC) $(FLAGS)

$(OBJ)/tinyxml.o: $(TINYXML)/tinyxml.h $(TINYXML)/tinyxml.cpp
	g++ -c -o $(OBJ)/tinyxml.o $(TINYXML)/tinyxml.cpp $(INC) $(FLAGS)

$(OBJ)/tinyxmlerror.o: $(TINYXML)/tinyxmlerror.cpp
	g++ -c -o $(OBJ)/tinyxmlerror.o $(TINYXML)/tinyxmlerror.cpp $(INC) $(FLAGS)

$(OBJ)/tinyxmlparser.o: $(TINYXML)/tinyxmlparser.cpp
	g++ -c -o $(OBJ)/tinyxmlparser.o $(TINYXML)/tinyxmlparser.cpp $(INC) $(FLAGS)

# Clean project
clean:
	@# @ symbol at beginning indicates that it will not be printed
	@if [ "$$(ls -A $(OBJ))" ]; then \
		rm $(OBJ)/*; \
	fi
	@if [ "$$(ls -A $(BIN))" ]; then \
		rm $(BIN)/*; \
	fi