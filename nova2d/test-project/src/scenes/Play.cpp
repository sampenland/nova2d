#include "Play.h"
#include "logging/logging.h"
#include "core/Game.h"

namespace testproject
{
	using namespace novazero::physics;

	Play::Play(const std::string& sceneName)
		: Scene(sceneName)
	{
		
	}

	void Play::Start()
	{
		EnablePhysics(true);
		PhysicsEnableDebug(false);

		n2dAssetsLoadAndAddTexture("player1", "res/lander-TX518.png");
		n2dAssetsLoadAndAddTexture("player2", "res/lander-TX618.png");

		n2dAssetsLoadAndAddTexture("alien", "res/Ralph-TX18.png");
		n2dAssetsLoadAndAddTexture("planet", "res/planet.png");
		n2dAssetsLoadAndAddTexture("bullet", "res/bullet.png");
		n2dAssetsLoadAndAddTexture("fuel", "res/fuel.png");
		n2dAssetsLoadAndAddTexture("mini-alien", "res/miniAlien.png");
		n2dAssetsLoadAndAddTexture("jetfire", "res/jetfire.png");
		n2dAssetsLoadAndAddTexture("human", "res/human.png");
		n2dAssetsLoadAndAddTexture("mini-alien-bullet", "res/mini-alien-bullet.png");

		planetDisplay = new Image("planet", Vec2(Game::s_Width - 256, Game::s_Height - 256),
			Vec2Int(256, 256), 0);
		planet = new PhySensor("planet", true, Vec2(Game::s_Width - 32, Game::s_Height - 32), 256);
		n2dReferenceAdd("planet", planet);

		player1 = new Player("player1", Vec2(Game::s_Width - 64, Game::s_Height - 64), Vec2(32, 32),
			10);
		player1->EnableArrowKeys(true);
		player1->EnabledJoystickController(true, 0);
		n2dReferenceAdd("player1", player1);

		player2 = new Player("player2", Vec2(Game::s_Width - 64, Game::s_Height - 128), Vec2(32, 32),
			10);
		player2->EnableWASD(true);
		player2->EnabledJoystickController(true, 1);
		n2dReferenceAdd("player2", player2);

		alien = new Alien("alien", Vec2(200, 200), Vec2Int(32, 32), 2);
		n2dReferenceAdd("alien", alien);

		m_HumanCreator = new Timer(1000.f, false, n2dMakeFunc(Play::CreateHuman, this), 10000, 14000);

	}

	void Play::CreateHuman()
	{
		int humanSkill = n2dRandomInt(3, 8);
		Human* human = new Human(Vec2(32, 32), humanSkill);
		m_Humans.push_back(human);

		float x = alien->GetX() + 16;
		float y = alien->GetY() - 16;

		MiniAlien* lastMini = nullptr;
		for (int i = 0; i < 2; i++)
		{
			Positional* target = nullptr;
			
			if (i == 0)
			{
				target = human;
			}
			else
			{
				target = lastMini;
			}

			lastMini = alien->CreateMiniAlien(target, Vec2(x, y + (i * 16)));
		}

		
	}

	void Play::Update()
	{
		
	}

	void Play::End()
	{

	}

	void Play::DestroySelf()
	{

	}
}