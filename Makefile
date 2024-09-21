
TARGET = t

all: $(TARGET)

INC = -I. -I/Users/celes/Work/include -I/opt/homebrew/include 
LIB = -L.  -L/opt/homebrew/lib

CPP = CC
#CPPFLAGS = -Wall -O2 -std=c++17 -DGL_SILENCE_DEPRECATION 
CPPFLAGS = -g -Wall -std=c++17 -DGL_SILENCE_DEPRECATION 

SRC = \
  main.cpp \
	error.cpp \
	shader.cpp \
	triangle.cpp \

OBJ = $(addsuffix .o, $(basename $(SRC))) 

.cpp.o:
	$(CPP) $(INC) $(CPPFLAGS) -c $< -o $@ 

$(TARGET): $(OBJ) Makefile 
	$(CXX) $(LIB) -o $@ $(OBJ) -lglfw -framework OpenGL

clean:
	rm -f $(TARGET) $(OBJ)


