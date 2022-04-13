
emcc .\src\main.cpp ..\nova-zero\web-dist\nova2d-lib.a -O2 -s USE_SDL=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file res -o test-project.html