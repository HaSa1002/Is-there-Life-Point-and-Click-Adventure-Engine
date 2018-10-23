local class = require "middleclass"

Action = class("Action")

function Action:launch()
	self:init()

	while not self.finished do
		local dt = coroutine.yield()
		self.update(dt)
	end

	self:exit()
end