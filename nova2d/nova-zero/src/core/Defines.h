#pragma once

// Max gamepads
#define MAX_JOYSTICKS 8

// Max draw layers
#define MAX_LAYERS 20

// Random int between min-max
#define randomi(min, max) (int)(rand() % min + max)

// Random float between min-max
#define randomf(min, max) min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max - min)))

