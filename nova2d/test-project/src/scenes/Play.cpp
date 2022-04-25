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

		n2dAssetsLoadAndAddTexture("player", "res/lander-TX518.png");
		n2dAssetsLoadAndAddTexture("alien", "res/Ralph-TX18.png");
		n2dAssetsLoadAndAddTexture("planet", "res/planet.png");
		n2dAssetsLoadAndAddTexture("bullet", "res/bullet.png");
		n2dAssetsLoadAndAddTexture("fuel", "res/fuel.png");

		planetDisplay = new Image("planet", Vec2(Game::s_Width - 256, Game::s_Height - 256),
			Vec2Int(256, 256), 2);
		planet = new PhySensor("planet", true, Vec2(Game::s_Width - 32, Game::s_Height - 32), 256);
		n2dReferenceAdd("planet", planet);

		player1 = new Player("player1", Game::GetCenterScreen(), Vec2(32, 32),
			10);
		player1->EnableArrowKeys(true);
		player1->EnabledJoystickController(true, 0);
		n2dReferenceAdd("player1", player1);

		player2 = new Player("player2", Vec2(Game::GetCenterScreen().x, Game::GetCenterScreen().y + 250), Vec2(32, 32),
			10);
		player2->EnableWASD(true);
		player2->EnabledJoystickController(true, 1);
		n2dReferenceAdd("player2", player2);

		alien = new Alien("alien", Vec2(200, 200), Vec2Int(32, 32), 2);

		ParticleSystem* ps = n2dAddParticleSystem("fuel", Vec2Int(16, 16), "ps", 50, 10, 10);
		ps->SetLifetime(5, 10);

	}

	void Play::Update()
	{
		if (n2dMouseJustDown())
		{
			n2dGetParticleSystem("ps")->BurstParticles(25, n2dGetMousePosition(SDL_BUTTON_LEFT), 50, 0, 90, false);
		}
	}

	void Play::End()
	{

	}

	void Play::DestroySelf()
	{

	}
}