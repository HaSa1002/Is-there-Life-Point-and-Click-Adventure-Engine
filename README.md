# Is there Life? Engine (2D Point&Click Adventures)
This project is not finished. It is under active development. The mission is to have an engine were you can easily create Point and Click Adventures, and make them interactive, as well as animated. This engine is developed for an own project, but in a general approach. It beneficts heavily from Lua and most features are going to be implemented itself in Lua. If you are interested in insights in the development, follow my [blog](https://hasa1002.github.io/). It may take some time, since I experiment a lot at the moment.

# Features #
-	Scripting as the main part of interacting with the engine
-	Designed for 2D Point and Click Adventure
- Deliverd Lua support
-	Animations
- New Update Cirlce (Message/Event driven)

## In Development ##
- Entity Component System (Lua, but with heavy impact for the Engine)
- Player
- TextObjects


## Planned ##
- Editor mode [see](https://hasa1002.github.io/blog/2018/04/04/Basic-Engine/)
-	Savegames
-	Cutscenes
- Action Lists [see](https://eliasdaler.github.io/how-to-implement-action-sequences-and-cutscenes/)
-	Scriptable GUI
-	Doc
-	Multiple Platforms

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
For the detailed Guide, please visit the [Wiki Page](https://github.com/HaSa1002/SFML-Point-and-Click-Adventure-Engine/wiki/Code-Style-Guide).
