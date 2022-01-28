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

			m_Drawables = new Text("font3", "Dra: 0", "white", Rect(m_Position.x, m_Position.y + 22,
				100, 20), 0);

			m_Updaters = new Text("font3", "Ups: 0", "white", Rect(m_Position.x, m_Position.y + 44,
				100, 20), 0);
			
			m_Deletables = new Text("font3", "Del: 0", "white", Rect(m_Position.x, m_Position.y + 66,
				100, 20), 0);

			m_References = new Text("font3", "Ref: 0", "white", Rect(m_Position.x, m_Position.y + 88,
				100, 20), 0);

			m_Gravers = new Text("font3", "Gra: 0", "white", Rect(m_Position.x, m_Position.y + 110,
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
			m_Drawables->UpdateText("Dra: " + std::to_string(objs));

			auto ups = n2dDebugUpdaterCount();
			m_Updaters->UpdateText("Ups: " + std::to_string(ups));

			auto dels = n2dDebugDeleteableCount();
			m_Deletables->UpdateText("Del: " + std::to_string(dels));

			auto refs = n2dDebugReferencedCount();
			m_References->UpdateText("Refs: " + std::to_string(refs));

			auto gravs = n2dDebugGraverCount();
			m_Gravers->UpdateText("Gra: " + std::to_string(gravs));
		}
		
		void DebugOverlay::Draw()
		{
			
		}

		void DebugOverlay::DestroySelf()
		{
			m_FPS->DestroySelf();
			m_Drawables->DestroySelf();
			m_Updaters->DestroySelf();
			m_Deletables->DestroySelf();
			m_References->DestroySelf();
			m_Gravers->DestroySelf();

			CleanUpdaters();

			n2dRemoveDrawable(m_ID, m_Layer);

			m_DeleteNow = 1;
		}
	}
}