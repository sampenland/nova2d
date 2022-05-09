#include "core/Scene.h"
#include <string>
#include "particles/ParticleSystem.h"
#include "debug/DrawRect.h"
#include "core/Timer.h"
#include "graphics/Text.h"
#include "input/ScrollInput.h"

namespace particleeditor
{
	using namespace novazero::core;
	using namespace novazero::particles;
	using namespace novazero::debug;
	using namespace novazero::input;

	class EditorScene
		: public Scene
	{

	private:

		ParticleSystem* m_ParticleSystem = nullptr;
		Sprite* m_Asset = nullptr;
		Text* m_AssetName = nullptr;
		DrawRect* m_AssetBackground = nullptr;
		Vec2 m_AssetPosition = Vec2(0, 0);
		Vec2Int m_AssetSize = Vec2Int(0, 0);
		
		bool* m_SystemOn;

		float* m_MinAngle;
		float* m_MaxAngle;

		float* m_EmitterSpeed;
		int32* m_MaxParticles;
		float* m_ParticleRadius;
		float* m_EmitterVelocity;
		
		float* m_MinLifetime;
		float* m_MaxLifetime;
		
		int* m_StartAlpha;
		int* m_StartAlphaRnd;
		int* m_EndAlpha;
		int* m_EndAlphaRnd;
		float* m_AlphaChangeSpeed;
		bool* m_UsingAlphaTransition;

		bool* m_UsingColorTransition;
		ParticleColorTransition* m_ColorTransition;
		float* m_ColorTransSpeed;
		float* m_StartColor;
		float* m_MidColor;
		float* m_EndColor;

		ScrollInput* m_MinAngleInput = nullptr;
		ScrollInput* m_MaxAngleInput = nullptr;

		ScrollInput* m_EmitterSpeedInput = nullptr;
		ScrollInput* m_EmitterVelocityInput = nullptr;
		
		ScrollInput* m_MaxParticleInput = nullptr;
		ScrollInput* m_ParticleRadiusInput = nullptr;
		
		ScrollInput* m_MinLifetimeInput = nullptr;
		ScrollInput* m_MaxLifetimeInput = nullptr;
		
		ScrollInput* m_StartAlphaInput = nullptr;
		ScrollInput* m_StartAlphaRndInput = nullptr;
		ScrollInput* m_EndAlphaInput = nullptr;
		ScrollInput* m_EndAlphaRndInput = nullptr;
		ScrollInput* m_AlphaChangeSpeedInput = nullptr;
		
		ScrollInput* m_ColorTransSpeedInput = nullptr;

	public:

		EditorScene(const std::string& sceneName);

		void Start();

		void GUI();
		void Update();

		void End();
	};
}