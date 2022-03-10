#pragma once
#include "core/Scene.h"
#include "maps/TiledMap.h"
#include "graphics/Image.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::maps;
	using namespace novazero::graphics;

	class Level2 :
		public Scene
	{

	private:

		TiledMap* m_Map = nullptr;

	public:

		Level2(const std::string& sceneName)
			: Scene(sceneName)
		{

		};

		void Update() override
		{
		}

		void Start() override
		{
			m_Map = n2dAssetsGetMap("level2");
						
		}

		void OnEscape()
		{
			
		}

		void End() override
		{
			
		}

	};
}