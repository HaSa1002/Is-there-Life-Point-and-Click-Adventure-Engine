local class = require "middleclass"
local i = require "inspect"
local hs = utils.hash.string

MainMenuState = class("MainMenuState", State)

function MainMenuState:initialize()
	self.input = nil
	-- Create your Mainmenu here, but for now just create a Text, telling us to press Space
	self.text = TextRenderComponent.new("Press Space to continue...", "font.otf", 50)
	b = self.text:getLocalBounds()
	self.t = self.text:getTransformable()
	self.t:setOrigin(b.width * 0.5, b.height * 0.5)
	self.t:setPosition(1920 * 0.5, 1080 * 0.5)
	self.time = 1
	self.up = false
	self.counter = 0
end

function MainMenuState:setInput(inputVector)
	self.input = inputVector
end

function MainMenuState:handleInput()
	local e = self.input
	for v=1, #e do
		local type = e[v].type
		if type == EventType.KeyReleased then
			local key = e[v].key
			if key.code == KeyCode.Space then
				-- Go into a game state
				-- ...but for the purpose of testing we just change the string
				self.counter = self.counter + 1
				self.text:setString("Continued! x"..self.counter)
				local b = self.text:getLocalBounds()
				self.t:setOrigin(b.width * 0.5, b.height * 0.5);
				stateStack:push(LoadingState(TestScene()))
				
			end
		elseif type == EventType.MouseMoved then
			local m = e[v].mouseMove
			if self.text:getGlobalBounds():contains(m.x, m.y) then
				local p = self.t:getPosition()
				self.text:setCharSize(100)
				local b = self.text:getLocalBounds()
				self.t:setOrigin(b.width * 0.5, b.height * 0.5);
				self.t:setPosition(p)
			else
				local p = self.t:getPosition()
				self.text:setCharSize(50)
				local b = self.text:getLocalBounds()
				self.t:setOrigin(b.width * 0.5, b.height * 0.5);
				self.t:setPosition(p)
			end
		end

	end
end

function MainMenuState:update(dt)
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

end

function MainMenuState:render(target, states)
	self.text:draw(target, states)
end