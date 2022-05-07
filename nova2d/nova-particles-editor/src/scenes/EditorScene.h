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

		float* m_MinAngle;
		float* m_MaxAngle;
		bool* m_SystemOn;
		float* m_EmitterSpeed;
		float* m_MinLifetime;
		float* m_MaxLifetime;
		int32* m_MaxParticles;

		ScrollInput* m_MinAngleInput = nullptr;
		ScrollInput* m_MaxAngleInput = nullptr;
		ScrollInput* m_EmitterSpeedInput = nullptr;
		ScrollInput* m_MinLifetimeInput = nullptr;
		ScrollInput* m_MaxLifetimeInput = nullptr;
		ScrollInput* m_MaxParticleInput = nullptr;

	public:

		EditorScene(const std::string& sceneName);

		void Start();

		void GUI();
		void Update();

		void End();
	};
}