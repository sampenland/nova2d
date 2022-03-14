![nova2d-logo](https://user-images.githubusercontent.com/49030884/157763854-97bc29ea-1284-43d3-b474-6535abd98ee3.svg)


Doxygen Docs: https://n2d.dev/
Check out the [Wiki](https://github.com/sampenland/nova2d/wiki) for a helpful CHEATSHEET and beginning work on some Docs. Also, to get involved in the development by suggesting ideas and features, check out the [Forums](https://n2d.dev/forums/) to follow DevLogs and also join the community.

---
!!Currently in development!! -> 2d SDL2 based game engine specifically made for Arcade Games to target the Steam Deck.

---
**Feature Set**
 
 Graphics
 - Simple 2D sprites with Animations, if desired
 - Draw Collections which can be used for Screen animations, possibily 2D cameras later on
 - Simple TextInput and Text Displays
 - 4 built in fonts: "font1", "font2", "font3", "font4"
 - Debug Draw shapes: Circle and Rectangle
 
 Prefabs/Components
 - Basic StatBar (main use is Health Bars)
 - HitDisplay (pre-made tweened text)
 
 Controllers:
 - Basic ArrowKeys/Joysticks controller with built-in movement bounds, acceleration, Graver, Time Effected, etc.
 
 Managment
 - Ease of use Color Managament, Referencer and Asset(sprite/texutre) Managament
 - Simple 2D Collision Manager
 - Timelines - easily create an array of events to happen on an varying interval or on referenced condition function
 - Simple 2D Renderering with 20 layers for PhotoShop like layer rendering
 - Gravers : Component type gravity objects that apply forces to attached objects
 - Tweens : Ability to Tween an object's X, Y, etc. from startValue to endValue in N amount of milliseconds (all implemented curves shown here: www.easings.net )
 - TimeEffectors : aka: Time Bubbles. A circluar or rectangular area in which Time slows or speeds up. Works similar to Gravers.
	- All 'TimeEffected' objects are effected by such Effectors.
 
 AI
 - Simple WeakAI with easy to use programmable Patrol Points which move along a functional equation
 - Simple Bullet holder for shooting from point A to point B
 - Simple Follower holder for target seeking behavior
 
 Debugging
 - Director - add in any variable to the Director so that you can change it in realtime during gameplay
	- also one key opening and altering Time Scale of game (such as speeding it up or down to see what works best)
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
	- Great example use of following features:
		- Sprites
		- Animations
		- Director
		- Timelines
		- Tweens
		- Asset Management
		- Debug Overlay
		- SimpleWeak AI
		- SimpleFollower AI
		- SimpleBullet AI
 
