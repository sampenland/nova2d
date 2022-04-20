CPP := em++ -std=c++14
CPPFLAGS := -s LLD_REPORT_UNDEFINED -DNOVA_EMSCRIPTEN ..\..\box2d\box2d.a ..\..\nova-zero\src\novalib.a -O2 -s USE_WEBGL2=1 -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s SDL2_MIXER_FORMATS=[ogg,mp3] -s USE_SDL_MIXER=2 -s USE_OGG=1 -s USE_VORBIS=1 -s USE_MPG123=1 -s USE_MODPLUG=1 --preload-file res

I1 = -I..\..\box2d
I2 = -I..\..\nova-zero\src

SRCS := $(wildcard *.cpp) $(wildcard scenes/*.cpp) $(wildcard actors/*.cpp)

all: 
	$(CPP) $(CPPFLAGS) $(I1) $(I2) $(SRCS) -o index.html