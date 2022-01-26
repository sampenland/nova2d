#include "DebugOverlay.h"
#include "../core/Defines.h"
#include "../core/Game.h"
#include <sstream>
#include <iomanip>

namespace novazero
{
	namespace debug
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;

		DebugOverlay::DebugOverlay(Vec2Int position) : Drawable(), Deleteable("debugoverlay")
		{
			m_ID = n2dGameGetID();

			m_Position = position;

			m_FPS = new Text("font3", "FPS: 60", "white", Rect(m_Position.x, m_Position.y,
				100, 20), 0);

			m_Instances = new Text("font3", "I: 0", "white", Rect(m_Position.x, m_Position.y + 22,
				100, 20), 0);

			m_Updaters = new Text("font3", "U: 0", "white", Rect(m_Position.x, m_Position.y + 44,
				100, 20), 0);

			n2dAddDrawable(this, 0);

			auto cleanID = n2dAddUpdater(DebugOverlay::Update, this);
			m_CleanUpdaters.push_back(cleanID);

		}

		DebugOverlay::~DebugOverlay()
		{

		}

		void DebugOverlay::Update()
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << Game::s_FPS;
			std::string fps = ss.str();

			std::string color = "red";
			if (Game::s_FPS > 60)
			{
				color = "green";
			}
			else if (Game::s_FPS > 30)
			{
				color = "yellow";
			}

			m_FPS->UpdateTextColor(color);
			m_FPS->UpdateText("FPS: " + fps);

			auto objs = n2dDebugDrawableCount();
			m_Instances->UpdateText("Objs: " + std::to_string(objs));

			auto ups = n2dDebugUpdaterCount();
			m_Updaters->UpdateText("Objs: " + std::to_string(ups));
		}
		
		void DebugOverlay::Draw()
		{
			
		}

		void DebugOverlay::DestroySelf()
		{
			CleanUpdaters();

			n2dRemoveDrawable(m_ID, m_Layer);

			m_DeleteNow = 1;
		}
	}
}