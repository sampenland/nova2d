#include "DebugOverlay.h"
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

		DebugOverlay::DebugOverlay(Vec2Int position) : Drawable(Vec2Int(0,0)), Deleteable("debugoverlay")
		{
			m_ID = n2dGameGetID();

			m_Position = position;

			int x = m_Position.x;
			int y = m_Position.y;

			m_FPS = new Text("font3", "FPS: 60", "white", Rect(x, y,
				100, 20), 0);
			m_FPS->SetFixedAndNonScale(true);

			m_Drawables = new Text("font3", "Dra: 0", "white", Rect(x, y + 22,
				100, 20), 0);
			m_Drawables->SetFixedAndNonScale(true);

			m_Updaters = new Text("font3", "Ups: 0", "white", Rect(x, y + 44,
				100, 20), 0);
			m_Updaters->SetFixedAndNonScale(true);

			m_Deletables = new Text("font3", "Del: 0", "white", Rect(x, y + 66,
				100, 20), 0);
			m_Deletables->SetFixedAndNonScale(true);

			m_References = new Text("font3", "Ref: 0", "white", Rect(x, y + 88,
				100, 20), 0);
			m_References->SetFixedAndNonScale(true);

			m_Gravers = new Text("font3", "Gra: 0", "white", Rect(x, y + 110,
				100, 20), 0);
			m_Gravers->SetFixedAndNonScale(true);

			m_Tweens = new Text("font3", "Twa: 0", "white", Rect(x, y + 132,
				100, 20), 0);
			m_Tweens->SetFixedAndNonScale(true);
			
			m_TimeEffects = new Text("font3", "TimE: 0", "white", Rect(x, y + 154,
				100, 20), 0);
			m_TimeEffects->SetFixedAndNonScale(true);

			m_TimeEffecteds = new Text("font3", "TiEmd: 0", "white", Rect(x, y + 176,
				100, 20), 0);
			m_TimeEffecteds->SetFixedAndNonScale(true);

			n2dAddDrawable(this, 0);
			SetFixedAndNonScale(true);

			auto cleanID = n2dAddUpdater(DebugOverlay::Update, this);
			m_CleanUpdaters.push_back(cleanID);

		}

		void DebugOverlay::Update()
		{
			if (m_Destroyed) return;

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

			auto tweens = n2dDebugTweenCount();
			m_Tweens->UpdateText("Twa: " + std::to_string(tweens));

			auto timeEffectors = n2dDebugTimeEffectorsCount();
			m_TimeEffects->UpdateText("TimE: " + std::to_string(timeEffectors));

			auto timeEffecteds = n2dDebugTimeEffectedCount();
			m_TimeEffecteds->UpdateText("TimD: " + std::to_string(timeEffecteds));

		}

		void DebugOverlay::Toggle()
		{
			// TODO: doesn't work
			m_Visible = !m_Visible;

			m_FPS->SetVisible(m_Visible);
			m_Drawables->SetVisible(m_Visible);
			m_Updaters->SetVisible(m_Visible);
			m_Deletables->SetVisible(m_Visible);
			m_References->SetVisible(m_Visible);
			m_Gravers->SetVisible(m_Visible);
			m_Tweens->SetVisible(m_Visible);
		}
		
		void DebugOverlay::Draw(float oX, float oY, float scale)
		{
			
		}

		void DebugOverlay::DestroySelf()
		{
			if (m_Destroyed) return;
			m_Destroyed = true;

			m_FPS->DestroySelf();
			m_Drawables->DestroySelf();
			m_Updaters->DestroySelf();
			m_Deletables->DestroySelf();
			m_References->DestroySelf();
			m_Gravers->DestroySelf();
			m_Tweens->DestroySelf();

			CleanUpdaters();

			n2dRemoveDrawable(m_ID, m_Layer);

			SetDeleted(true);
		}
	}
}