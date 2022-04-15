CC := em++ -std=c++14
CFLAGS := -DNOVA_EMSCRIPTEN -s WASM=1 -O2 -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file ..\res

I1 :=-I..\..\Dependencies\mysql\Release\include
I2 :=-I..\..\Dependencies\box2d\include

SRCS := $(wildcard ai/*.cpp) $(wildcard audio/*.cpp) $(wildcard components/*.cpp) $(wildcard controllers/*.cpp) $(wildcard core/*.cpp) $(wildcard debug/*.cpp) $(wildcard graphics/*.cpp) $(wildcard graphics/gdx/*.c) $(wildcard gui/imgui/*.cpp) $(wildcard input/*.cpp) $(wildcard logging/*.cpp) $(wildcard maps/*.cpp) $(wildcard maths/*.cpp) $(wildcard particles/*.cpp) $(wildcard physics/*.cpp) $(wildcard thirdparty/jsonparser/*.cpp) $(wildcard utils/*.cpp) $(wildcard utils/timeline/*.cpp) $(wildcard utils/timeline/events/*.cpp)

objects := $(SRCS:.cpp=.o)

all: $(objects)

$(objects): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(I1) $(I2) $< -o ../web-dist/out/$@
	
testproject:
	$(CC) $(CFLAGS) $(I1) $(I2)