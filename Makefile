UNAME_S = $(shell uname -s)

CPPFLAGS = --std=c++17 
LDFLAGS =  -lSDL2 -lSDL2_image  -lm

# GLFW required frameworks on OSX
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

ifeq ($(UNAME_S), Linux)
	LDFLAGS += -ldl -lpthread
endif

SRC  = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) $(wildcard src/**/**/*.cpp) $(wildcard src/**/**/**/*.cpp)
OBJ  = $(SRC:.cpp=.o)
BIN = bin

all: clean dirs build

clean:
	rm -rf $(BIN) $(OBJ)

dirs:
	mkdir -p ./$(BIN)

install:
	git submodule deinit -f . && git submodule update --init
	git update-index --assume-unchanged lib/sdl
	git update-index --assume-unchanged lib/sdl-image

	cd lib/sdl && git checkout SDL2 && ./configure && make && make install
	cd lib/sdl-image && ./configure && make && make install
	cp lib/sdl-image/SDL_image.h lib/sdl/include/SDL_image.h

build: $(OBJ)
	clang++ -o $(BIN)/game $^ $(LDFLAGS) -v

start: all
	$(BIN)/game


