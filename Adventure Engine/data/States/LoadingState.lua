local class = require "middleclass"
local i = require "inspect"
local hs = utils.hash.string



LoadingState = class("LoadingState", State)

function LoadingState:initialize(state_to_load)
	self.finished = false
	loadAsync(state_to_load, self) -- Sometime in the future this will be async
	self.toLoad = state_to_load
	self.text = TextRenderComponent.new("Connecting... Please wait", "font.otf", 50)
	b = self.text:getLocalBounds()
	self.t = self.text:getTransformable()
	self.t:setOrigin(b.width * 0.5, b.height * 0.5)
	self.t:setPosition(1920 * 0.5, 1080 * 0.5)
	self.time = 1
	self.up = false
end

function LoadingState:update(dt)
	if self.up then
		if self.time + dt > 1 then
			self.time = 2 - self.time - dt
			self.up = false
		else
			self.time = self.time + dt
		end
	else
		if self.time - dt < 0 then
			self.time = dt - self.time
			self.up = true
		else
			self.time = self.time - dt
		end
	end
	
	self.text:setColor(255, 255, 255, 255 * self.time)

	if self.finished then
		stateStack:replace(self.toLoad)
	end

end

function LoadingState:render(target, states)
	self.text:draw(target, states)
end

function LoadingState:onFinish()
	self.finished = true;
end