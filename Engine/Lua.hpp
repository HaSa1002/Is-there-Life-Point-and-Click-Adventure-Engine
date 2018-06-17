////////////////////////////////////////////////////////////
// 
// ITLengine - Is there Life? Point and Click Adventure Engine
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

#ifndef PC_LUA
#define PC_LUA

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#define SOL_CHECK_ARGUMENTS 1
#include "ScriptEngine.hpp"
#include "sol.hpp"

namespace pc {
	class Lua : public ScriptEngine {
	public:
		sol::state lua;
		
		void init();

		void setScene(const std::string& scene);

		void call(pc::Scene& scene, const std::string& object, const char action);
		
		EditorValues getEditorConfig();

		SubtitleValue getSubtitleSettings();

		void bindFunctions();

		const std::string getSceneToBeLoaded();

		const std::wstring getSubtitleToBeLoaded();

		void loadScene(Scene& scene, bool addToRenderer);

		void playAnimatedMove(const std::string& obj, const std::string& point, const float sec);

		void readObject(std::pair<sol::object, sol::object> o);

		void readWalkbox(std::pair<sol::object, sol::object> o);

		void readZoomline(std::pair<sol::object, sol::object> o);
	private:
		Scene* scene_temp;
		
	};
}


#endif // !PC_LUA