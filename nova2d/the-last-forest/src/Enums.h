#pragma once

namespace thelastforest
{
	enum class GridTypes
	{
		Free,
		PTree, // persistent tree
		DeadPTree, // dead persistent tree
		Tree,
		Grass,
		Water,
		Sun,
		Blocked,
		Heart
	};

	enum class Facing
	{
		Up, Down, Right, Left
	};
}