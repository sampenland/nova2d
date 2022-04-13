set p1=src
set p2=../Dependencies/mysql/Release/include
set p3=../Dependencies/box2d/include

emcc -DNOVA_EMSCRIPTEN -s WASM=1 -I%p1% -I%p2% -I%p3% src/core/Game.cpp -O2 -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file res -o web-dist/nova2d-lib.a