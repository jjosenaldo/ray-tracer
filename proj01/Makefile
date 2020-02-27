# Paths
SRC = ./src
BIN = ./bin
OBJ = ./obj
PARSER = $(SRC)/parser
TINYXML = $(PARSER)/tinyxml

# Other
FLAGS = -g -std=c++11
INC := -I $(TINYXML) -I $(PARSER)
OBJS = $(OBJ)/tinyxml.o $(OBJ)/tinystr.o $(OBJ)/tinyxmlerror.o $(OBJ)/tinyxmlparser.o $(OBJ)/parser.o

all: $(BIN)/rt.out

$(BIN)/rt.out: $(OBJS) $(SRC)/main.cpp
	g++ $(SRC)/main.cpp $(OBJS) -o $(BIN)/rt.out $(INC) $(FLAGS)

$(OBJ)/parser.o: $(PARSER)/parser.hpp $(PARSER)/parser.cpp
	g++ -c -o $(OBJ)/parser.o $(PARSER)/parser.cpp $(INC) $(FLAGS)

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