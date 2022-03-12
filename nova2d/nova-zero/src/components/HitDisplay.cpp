#include "HitDisplay.h"
#include "../core/Game.h"

namespace novazero 
{
	namespace components
	{
		HitDisplay::HitDisplay(const std::string& startText, const std::string& fontName, const std::string& colorName, 
				Rect drawRect, Vec2 endPos, float startToEndTimeMS, unsigned char layer) :
					Deleteable("hitDisplay_")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "hitDisplay_" + std::to_string(m_ID);
			
			m_Display = new Text(fontName, startText, colorName, drawRect, layer);
			m_Display->SetPosition(Vec2(drawRect.x, drawRect.y));
			
			int* textY = m_Display->GetYRef();
			m_YTweenID = n2dTweenAdd(false, textY, drawRect.y, endPos.y, startToEndTimeMS, false, true, TweenTypes::EaseOutSine);
			Game::s_SceneManager->s_TweenManager->RemoveOffset(m_YTweenID); // TODO: what does this do??

			Timer* t = new Timer(startToEndTimeMS + 500, false, std::bind(&HitDisplay::DestroySelf, this)); // clean

		}

		void HitDisplay::DestroySelf()
		{
			CleanUpdaters();

			if (m_Display)
				m_Display->DestroySelf();

			n2dTweenRemove(m_YTweenID);

			SetDeleted(true);
		}
	}
}