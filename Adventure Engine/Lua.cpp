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

namespace itl {
	void Lua::init() { 
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::io, sol::lib::math, sol::lib::os, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::utf8);
		bindClassMetatableHelper();
		
	}

	void Lua::postinit() {
		lua.script_file("engine/engine.lua");
	}


	////////////////////////////////////////////////////////////
	void Lua::bindClassMetatableHelper() {
		/*lua.script(R"(
function class(base, init)
	local c = {}    -- a new class instance
	if not init and type(base) == 'function' then
	   init = base
	   base = nil
	elseif type(base) == 'table' then
	 -- our new class is a shallow copy of the base class!
	   for i,v in pairs(base) do
		  c[i] = v
	   end
	   c._base = base
	end
	-- the class will be the metatable for all its objects,
	-- and they will look up their methods in it.
	c.__index = c
 
	-- expose a constructor which can be called by <classname>(<args>)
	local mt = {}
	mt.__call = function(class_tbl, ...)
	local obj = {}
	setmetatable(obj,c)
	if init then
	   init(obj,...)
	else 
	   -- make sure that any stuff from the base class is initialized!
	   if base and base.init then
	   base.init(obj, ...)
	   end
	end
	return obj
	end
	c.init = init
	c.is_a = function(self, klass)
	   local m = getmetatable(self)
	   while m do 
		  if m == klass then return true end
		  m = m._base
	   end
	   return false
	end
	setmetatable(c, mt)
	return c
 end)");*/
	}
}