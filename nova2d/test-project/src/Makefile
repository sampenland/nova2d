CC := em++ -std=c++14
CFLAGS := -DNOVA_EMSCRIPTEN -s WASM=1 -O2 -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file ..\res

I1 :=-I..\..\Dependencies\mysql\Release\include
I2 :=-I..\..\Dependencies\box2d\include

SRCS := main.cpp $(wildcard scenes/*.cpp)

objects := $(SRCS:.cpp=.o)

testproject:
	$(CC) $(CFLAGS) $(I1) $(I2) main.cpp -o index.html
	
	# TODO
	# - create and link nova2dlib.a lib