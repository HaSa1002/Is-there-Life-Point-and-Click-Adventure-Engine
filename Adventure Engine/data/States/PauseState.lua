local class = require "middleclass"
local i = require "inspect"
local hs = utils.hash.string
PauseState = class("PauseState", State)

function PauseState:initialize()
	self.input = nil
end

function PauseState:setInput(inputVector)
	self.input = inputVector
end

function PauseState:handleInput()
	local e = self.input
	for v=1, #e do
		local type = e[v].type
		if type == EventType.KeyReleased then
			local key = e[v].key
			if key.code == KeyCode.Escape then
				print "Game"
				stateStack:pop()
			end
		end
	end
end
function PauseState:update(dt) end
function PauseState:render(target, states) end