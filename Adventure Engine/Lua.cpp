////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Engine
// Copyright (c) 2017-2018 Johannes Witt (johawitt@outlook.de)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

#include "Lua.hpp"

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "LuaBindings.hpp"
#include <SFML/Window/Event.hpp>


namespace itl {
	void Lua::init() {
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::io, sol::lib::math, sol::lib::os, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::utf8);
		lua.script(R"(package.path = package.path .. ";engine/3rdParty/?.lua")");
		LuaBindings { lua }; // Create a septerate object file to save compile time

	}

	void Lua::postinit() {
		this->reqisterEventHandling();
		this->registerObjects();
		this->registerUserObjects();
		lua.script_file("engine/engine.lua");
	}

	void Lua::registerUserObjects() {
		std::filesystem::directory_iterator p{"data/objects"};
		for (auto i : p) {
			if (i.path().extension() == ".lua")
				lua.script_file(i.path().generic_string());
		}
	}

	void Lua::registerObjects() {
		lua.script_file("engine/EventHandling/GameObject.lua");
		lua.script_file("engine/EventHandling/RenderedObject.lua");
	}


	void Lua::reqisterEventHandling() {
		lua.script_file("engine/EventHandling/Subscription.lua");
		auto ret = lua.script_file("engine/EventHandling/EventHandler.lua");
		if (ret.valid()) {
			eventHandler = ret.get<sol::table>();
			lua["ecs"] = eventHandler;
		} else std::cout << "Scheiße"; // Try to create new EventHandler else throw error

	}

}