![nova2d-logo](https://user-images.githubusercontent.com/49030884/165163135-45d789a7-1ddb-4b72-9d30-55cf3b6dd62f.png)

IMPORTANT! If you clone/download this repo, you will need to follow a few steps to get your MSVS Solution working. Here's the [Getting Started Page](https://github.com/sampenland/nova2d/wiki/Getting-Started) which describes those steps.

For full API overview, check out the [Doxygen Docs](https://n2d.dev/). For an intro to nova2d, check out the [Wiki](https://github.com/sampenland/nova2d/wiki) for a helpful CHEATSHEET and beginning work on some Docs. 

Also, to get involved in the development by suggesting ideas and features, check out the [Forums](https://n2d.dev/forums/index.php/community-forums/). Visit the [DevLogs](https://n2d.dev/forums/) site for How To video tutorials and a development blog of nova2d's progress. and and also join the community.

---
!!Currently in development!! -> 2d SDL2 based game engine specifically made for Arcade Games and rapid development. AS OF NOW, nova2d will be solely targetting Windows and Web (js and WebAssembly).

---
**Feature Set as of 4/25/22**
 
 Graphics
 - Simple 2D sprites with Animations with Box2D bodies if desired
 - Draw Collections which can be used for Screen animations
 - Integration with full Dear ImGUI library but nova2d abstractions are not complete
 - 4 built in fonts: "font1", "font2", "font3", "font4" for Pixel basced Text
 - Debug Draw shapes: Circle and Rectangle
 - Debug drawing of Box2D bodies if turned on
 - Integration with Tiled for TileMaps (level creation)
 
 Prefabs/Components
 - Basic StatBar (main use is Health Bars)
 - HitDisplay (pre-made tweened text)
 
 Controllers:
 - Basic ArrowKeys/Joysticks controller with built-in movement bounds which uses a Box2D body.
 - More controllers to come, such as Mouse controllers
 
 Managment
 - Ease of use Color Managament, Referencer and Asset(sprite/texutre) Managament
 - Most Managers std::map<string, class> structures which allow easy lookups like: n2dGetParticleSystem("myParticleSystem");
 - Fully integrated Box2D physics engine and Liquid Fun as the Particle engine - working on abstracting for simpler uses
 - Timelines - easily create an array of events to happen on an varying interval or on referenced condition function
 - Simple 2D Renderering with 20 layers for PhotoShop like layer rendering
 - Tweens : Ability to Tween an object's X, Y, alpha, etc. from startValue to endValue in N amount of milliseconds (all implemented curves shown here: www.easings.net )
 
 AI
 - Simple WeakAI with easy to use programmable Patrol Points which move along a functional equation
 - Simple Bullet holder for shooting from point A to point B
 - Simple Follower holder for target seeking behavior
 - More to come, such as A Star path finding 
 
 Debugging
 - Simple Director (enabled with one line of code) which displays:
	- FPS
	- Drawables
	- Updaters
	- Deleteables counts
	- Graver counts
	- Tween counts
	..etc.
 - Simple Logging system with several LOG_Levels
  
 Misc
 - Automatic MACROs for simple score keeping
 - SQL Integration
 - SQL High Score table built-in, if desired simply enable it
 
 n2dMacros
 - Easy to use MACROs to simplify use of complex functions / lenghtly functions
