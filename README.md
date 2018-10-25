# Is there Life? Engine (2D Point&Click Adventures)
This project is not finished. It is under active development. The mission is to have an engine were you can easily create Point and Click Adventures, and make them interactive, as well as animated. This engine is developed for an own project, but in a general approach. It beneficts heavily from Lua and most features are going to be implemented itself in Lua. If you are interested in insights in the development, follow my [blog](https://hasa1002.github.io/). It may take some time, since I experiment a lot at the moment.

# Features #
-	Scripting as the main part of interacting with the engine
-	Designed for 2D Point and Click Adventure
- Deliverd Lua support
-	Animations
- New Update Cirlce (Message/Event driven)
- Entity Component System (Lua, but with heavy impact for the Engine)
- Player
- TextObjects
- States
- StateStack
- Coroutined ActionLists
- Texture manager
-	Cutscenes (scripted)

## In Development ##
- Pathfinding
- More Rendercomponents
-	Scriptable GUI
- HUD

## Planned ##
- Editor mode [see](https://hasa1002.github.io/blog/2018/04/04/Basic-Engine/)
-	Savegames
- Clear-Up
- Convineance functions
- Audio Integration (perhaps Fmod. Not sure yet)
- Dynamic Audio
- Optimizations (Performance, usage, ...)
- Shaders
-	Doc
-	Multiple Platforms

## Ideas ##
- sfeMovie Integration for rendered cutscenes and the splashscreen (would be an object, so that you can do whatever you want with it)
- fmod (If I understood correctly, we would have massive control about the audio source as such (i.e channels))
- Scene "description" pos, size, texture, etc. as JSON or XML and then functionality via Lua

## Installation ##
You need to have Visual Studio 2017 installed (however I am sure, that you can get this on every Platform running, since I am not using any Windows specific librarys, but somebody has to make a makefile for the project)
1. Clone the project
2. Install SFML version 2.5 (https://www.sfml-dev.org/tutorials/2.5/start-vc.php)

## Libraries ##
This Software uses the following libraries:
- [SFML](https://www.sfml-dev.org/) (zlib/png license) (**not** included)
- [ImGui](https://github.com/ocornut/imgui) (MIT license) (included)
- [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml) (MIT license) (included)
- [Lua](https://lua.org) (MIT license) (included)
- [solv2](https://github.com/ThePhD/sol2) (MIT license) (included)
- [middleclass](https://github.com/kikito/middleclass) (MIT license) (included)

## Help Wanted ##
Since this is my hobby project I update here as I have time. I made this open, so that everyone can use and modify it and to let people influence this project.

# Code Style Guide #
For the detailed Guide, please visit the [Wiki Page](https://github.com/HaSa1002/SFML-Point-and-Click-Adventure-Engine/wiki/Code-Style-Guide). However, currently I'm not going for it strictly, since I am hurring to implement new features to start my game development.
