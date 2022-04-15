CPP := em++ -std=c++14
CPPFLAGS := -DNOVA_EMSCRIPTEN -s WASM=1 -O2 -s USE_SDL_MIXER=2 -s USE_SDL_TTF=2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file ..\res

CC := emcc
CFLAGS = -s WASM=1 -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]'

I1 :=-I..\..\Dependencies\box2d\include
I2 :=-Igraphics\gfx

cpp_src := $(wildcard ai/*.cpp) $(wildcard audio/*.cpp) $(wildcard components/*.cpp) $(wildcard controllers/*.cpp) $(wildcard core/*.cpp) $(wildcard debug/*.cpp) $(wildcard graphics/*.cpp) $(wildcard gui/imgui/*.cpp) $(wildcard input/*.cpp) $(wildcard logging/*.cpp) $(wildcard maps/*.cpp) $(wildcard maths/*.cpp) $(wildcard particles/*.cpp) $(wildcard physics/*.cpp) $(wildcard thirdparty/jsonparser/*.cpp) $(wildcard utils/*.cpp) $(wildcard utils/timeline/*.cpp) $(wildcard utils/timeline/events/*.cpp)

c_src := $(wildcard graphics/gdx/*.c)

cpp_objects := $(cpp_src:.cpp=.o)
c_objects := $(c_src:.c=.o)

objectsInOut := $(addprefix ../web-dist/out/,$(objects))

all: $(c_objects)

$(cpp_objects):	%.o: %.cpp
	$(CPP) -c $(CPPFLAGS) $(I1) $< -o ../web-dist/out/$@
	
$(c_objects):	%.o: %.c
	$(CC) -c $(CFLAGS) $(I1) $< -o ../web-dist/out/$@
	
library:
	emar -crs novalib.a $(objectsInOut)