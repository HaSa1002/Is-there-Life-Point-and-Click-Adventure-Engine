local class = require "middleclass"
local i = require "inspect"
local hs = utils.hash.string

StateStack = class("StateStack")

function StateStack:initialize() 
	self.stack = {SplashScreenState()}
	state = self.stack[#self.stack]
end

function StateStack:pop()
	self.stack[#self.stack] = nil
	state = self.stack[#self.stack]
end

function StateStack:push(state_)
	self.stack[#self.stack + 1] = state_
	state = state_
end

function StateStack:replace(state_)
	self.stack[#self.stack] = state_
	state = state_
end


stateStack = StateStack()
return state