set p1=../nova-zero/src
set p2=../Dependencies/mysql/Release/include
set p3=../Dependencies/box2d/include
set p4=../Dependencies/sdl2_ttf/include

emcc .\src\main.cpp -O2 -s USE_SDL=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -I%p1% -I%p2% -I%p3% -I%p4% --preload-file res -o test-project.html