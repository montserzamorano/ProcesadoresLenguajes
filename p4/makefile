##################################################
#
# 	AUTORES:
#		Marina Hurtado Rosales
# 		Antonio Miguel Morillo Chica
# 		Montserrat Rodríguez Zamorano
# 		Alfonso Soto López
#
# 	GRADO EN INGENIERIA INFORMATICA - UGR
# 	PROCESADORES DE LENGUAJES
#
###################################################

SRC = src
BIN = bin
OBJ = obj
LIB = lib
INC = include
DATA = data

CXX = gcc -O3
CPPFLAGS = -g -I$(INC)
#LIBS = -L $(LIB)  -Wl,-rpath=./lib

LEX_FILE = $(wildcard $(SRC)/*.l)
SOURCE_LEX = $(patsubst %.l,%,$(LEX_FILE))
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJETS = $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SOURCES))

PROGRAM = $(BIN)/yacc_semantic

#============================================================
#=====================   COMPILACION   ======================
#============================================================

all: $(PROGRAM)

$(PROGRAM): $(OBJ)/main.o $(OBJ)/y.tab.o $(OBJ)/semantic.o
	@printf "\n\t\t································\n"
	@printf "\t\t·· COMPILANDO [${@}] ··\n"
	@printf "\t\t································\n"
	$(CXX) $(CPPFLAGS) -o $@ $(OBJ)/main.o $(OBJ)/y.tab.o $(OBJ)/semantic.o

$(OBJ)/main.o: $(SRC)/main.c
	$(CXX) $(CPPFLAGS) -o $@ -c $^

$(OBJ)/semantic.o: $(SRC)/semantic.c
	$(CXX) $(CPPFLAGS) -o $@ -c $^

$(OBJ)/y.tab.o: $(SRC)/y.tab.c
	$(CXX) $(CPPFLAGS) -o $@ -c $^

$(SRC)/y.tab.c: $(SRC)/syntactic.y $(SRC)/lex.yy.c
	bison -v -d -o $@ $(SRC)/syntactic.y

$(SRC)/lex.yy.c: $(SRC)/lex.l
	lex -o $(SOURCE_LEX).yy.c $^

#============================================================
#======================   LIMPIEZA  =========================
#============================================================

clean:
	-@rm $(BIN)/* $(OBJ)/*.o

#============================================================
#========================   PACK  ===========================
#============================================================

pack: clean
	tar cvf pl_practica3.tar makefile $(SRC)/*.cpp $(OBJ)/ $(BIN)/ $(INC)/ $(DATA)/
