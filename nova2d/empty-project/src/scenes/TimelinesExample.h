#include "core/Scene.h"
#include "graphics/Text.h"
#include "../Executor.h"

namespace emptyproject
{
	using namespace novazero::core;
	using namespace novazero::graphics;

	class TimelinesExample : public Scene
	{

	private:

		Text* m_Title = nullptr;
		int m_PlayerHealth = 100;
		Executor* m_Executor = nullptr;

	public:

		TimelinesExample(const std::string& sceneName);

		void SetLowHealth();

		void TriggeredOn();

		void TriggeredOff();

		bool PlayerHealthLow();

		void Start() override;

		void Update() override;

		void End() override;

		void DestroySelf();


	};

}