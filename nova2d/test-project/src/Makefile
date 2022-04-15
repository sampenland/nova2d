CC := em++ -std=c++14
CFLAGS := -DNOVA_EMSCRIPTEN -s LLD_REPORT_UNDEFINED ..\..\box2d\box2d.a ..\..\nova-zero\src\novalib.a -O2 -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file ..\res

I1 = -I..\..\box2d
I2 = -I..\..\nova-zero\src

SRCS := $(wildcard *.cpp) $(wildcard scenes/*.cpp)

objects := $(SRCS:.cpp=.o)

all: $(objects)
	$(CC) $(CFLAGS) $(I1) $(I2) main.cpp -o index.html

$(objects): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(I1) $(I2) $<