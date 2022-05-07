CLEAN_BIN= $(wildcard bin/*)
OBJ= $(wildcard bin/*.o)
SRC= $(wildcard bin/*.c)
INC= -Iglad -IKHR

build_app: build_obj build_lib main.c
	gcc -g -Wall -Lbin main.c -lSDL2 -llib -lGL -ldl -o bin/app

build_obj: $(SRC)
	gcc -c -g -Wall $(INC) glad.c -o bin/glad.o
	gcc -c -g -Wall $(INC) shader.c -o bin/shader.o

build_lib: $(OBJ)
	ar -rcs -o bin/liblib.a $(OBJ)

run:
	./bin/app

clean:
ifeq ($(CLEAN_BIN),)
else
	rm $(CLEAN_BIN)
endif
