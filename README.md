![image](https://user-images.githubusercontent.com/49030884/151238809-8672aba8-410b-42de-84c0-c1407d83caf0.png)

Simple Win32 experimental 2d SDL2 based game engine specifically made for Arcade Games.
TODO: Plan to target Steam Deck

**Feature Set**
 
 Graphics
 - Simple 2D sprites with Animations, if desired
 - Draw Collections which can be used for Screen animations, possibily 2D cameras later on
 - Simple TextInput and Text Displays
 - 4 built in fonts: "font1", "font2", "font3", "font4"
 - Debug Draw shapes: Circle and Rectangle
 
 Prefabs
 - Basic WSAD/ArrowKeys controller with built-in movement bounds, acceleration, Graver, Time Effected, etc.
 
 Managment
 - Ease of use Color Managament, Referencer and Asset(sprite/texutre) Managament
 - Simple 2D Collision Manager
 - Simple 2D Renderering with 20 layers for PhotoShop like layer rendering
 - Gravers : Component type gravity objects that apply forces to attached objects
 - Tweens : Ability to Tween an object's X, Y, etc. from startValue to endValue in N amount of milliseconds
 - TimeEffectors : aka: Time Bubbles. A circluar or rectangular area in which Time slows or speeds up. Works similar to Gravers.
	- All 'TimeEffected' objects are effected by such Effectors.
 
 AI
 - Simple WeakAI with easy to use programmable Patrol Points which move along a functional equation
 - Simple Bullet holder for shooting from point A to point B
 - Simple Follower holder for target seeking behavior
 
 Debugging
 - Simple DebugOverlay (enabled with one line of code) which displays:
	- FPS
	- Drawables
	- Updaters
	- Deleteables counts
	- Graver counts
	- Tween counts
	- Time Effectors
	- Time Effected
 - Simple Logging system with several LOG_Levels
 
 Misc
 - Automatic MACROs for simple score keeping
 - SQL Integration
 - SQL High Score table built-in, if desired simply enable it
 
 n2dMacros
 - Easy to use MACROs to simplify use of complex functions / lenghtly functions
 
 **Samples**
 - Space shooter : Simple shooter like Dragon Spirit for NES. Project used for testing, game not really polished in any way.
 
