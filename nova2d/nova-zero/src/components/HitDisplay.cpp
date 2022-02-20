#include "HitDisplay.h"
#include "../core/Game.h"

namespace novazero 
{
	namespace components
	{
		HitDisplay::HitDisplay(const std::string& startText, const std::string& fontName, const std::string& colorName, 
				Rect drawRect, Vec2 endPos, float startToEndTimeMS, char layer) :
					Deleteable("hitDisplay_")
		{
			m_DeleteName = "hitDisplay_" + std::to_string(m_ID);
			m_Display = new Text(fontName, startText, colorName, drawRect, layer, false);
			m_Display->SetPosition(Vec2(drawRect.x, drawRect.y));

			n2dAddDrawable(this, layer);

			m_YTweenID = n2dTweenAdd(false, m_Display->GetYRef(), drawRect.y, endPos.y, startToEndTimeMS, false, true, TweenTypes::EaseOutSine);
			Game::s_SceneManager->s_TweenManager->RemoveOffset(m_YTweenID);

			Timer* t = new Timer(startToEndTimeMS + 500, false, std::bind(&HitDisplay::DestroySelf, this)); // clean

		}

		void HitDisplay::Draw(float oX, float oY)
		{
			m_Display->Draw();
		}

		void HitDisplay::DestroySelf()
		{
			CleanUpdaters();

			if (m_Display)
				m_Display->DestroySelf();

			n2dRemoveDrawable(m_ID, m_Layer);
			n2dTweenRemove(m_YTweenID);

			SetDeleted(true);
		}
	}
}