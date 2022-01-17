#pragma once
#include <functional>
#include "SDL.h"

// Game pads
#define MAX_JOYSTICKS 8

// Draw layers
#define MAX_LAYERS 20

// Random Int between min and max
#define randomi(min, max) (int)(rand() % min + max)

// Random float between min and max
#define randomf(min, max) min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)))

enum JoystickAxis
{
	JOY_STICK_AXIS_X = 0,
	JOY_STICK_AXIS_Y = 1
};

typedef std::function<void()> f_VoidFunction;
typedef std::function<void(float)> f_FloatPassFunction;

typedef std::function<bool(SDL_Keycode)> f_ConditionalFunction;
typedef std::function<bool(int, int)> f_JoyStickConditionalFunction;
typedef std::function<float(char, JoystickAxis)> f_JoyStickAxisConditionalFunction;
