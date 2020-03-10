CC=g++
target = DinguxCommander

RESDIR:=res

SRCS=$(wildcard src/*.cpp)
#SRCS+=$(wildcard JvGame/*.cpp)
OBJS=$(patsubst %cpp,%o,$(SRCS))

INCLUDE = -I/usr/include/SDL2
#LIB = -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_ttf 
LIB = -lSDL2 -lSDL2_image -lSDL2_ttf 

all:$(OBJS)
	$(CC) $(OBJS) -o $(target) $(LIB)

%.o:%.cpp
	$(CC) -DRESDIR="\"$(RESDIR)\""  -c $< -o $@  $(INCLUDE)

clean:
	rm $(OBJS) $(target) -f

