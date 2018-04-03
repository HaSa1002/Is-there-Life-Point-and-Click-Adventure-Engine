#include "Lua.hpp"
#include <fstream>

namespace pc {
	bool Lua::init() {
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::io, sol::lib::math, sol::lib::os, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::utf8);
		try {
			lua.script_file("Engine.lua");
		}
		catch (sol::error err) {
			printf("%s\n", err.what());
			return false;
		}
		if (lua["rooms"].valid() && lua["localisations"].valid() && lua["game"].valid())
			return true;
		return false;
	}


	bool Lua::editorConfig() {
		//See the Editor.conf.lua to get an overview of what is possible
		// Create the variables first, so that we don't run into errors with the file nor with our Engine.cpp
		lua.script(R"(
			editor = {
				solution = {1600, 900},
				title = "Is there Life? | Engine",
				fullscreen = false,
				open_menues = { "mainmenue" },
			}
			print "Config variables set.\n"
			)");


		//Load the Config File
		try {
			lua.script_file("Editor.conf.lua");
		}
		catch (sol::error err) {
			printf("%s\n", err.what());
			
			try {
				//Create a new file...
				std::fstream file("Editor.conf.lua", std::fstream::out);
				file << std::flush;
				file.close();
				//...and try again
				lua.script_file("Editor.conf.lua");
			}
			catch (sol::error err) {
				//if we are here. Something went terribly wrong
				printf("%s\n", err.what());
				return false;
			}
		}
		return true;
	}


}


