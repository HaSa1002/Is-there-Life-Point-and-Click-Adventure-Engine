local class = require "middleclass"
local i = require "inspect"
local hs = utils.hash.string

SplashScreenState = class("SplashScreenState", State)

function SplashScreenState:initialize()
	-- Add the splash images
	tm:add("splash/sfml.png", hs("sfml"))
	tm:build()
	self.actionList = ActionList()
	

	-- Set the SFML Splash
	self.sfmlSplash = RenderComponent.new(tm, hs("sfml"))
	local b = self.sfmlSplash:getLocalBounds()
	self.t = self.sfmlSplash:getTransformable()
	self.t:setOrigin(b.width * 0.5, b.height * 0.5)
	self.t:setPosition(1920 * 0.5, 1080 * 0.5) -- Get the Viewport width
	self.sfmlSplash:setColor(255, 255, 255, 125)
	self.time = 9;
	coroutine.resume(self.actionList:add(function (splash)
		appear(0.5, 255, 255, 255, splash)
		delay(4)
		disappear(2, 255, 255, 255, splash)
	end), self.sfmlSplash)

	-- coroutine.resume(self.actionList:add(goTo), self.t, 7, Vector2f.new(1920 * 0.5, 1080))
end

function SplashScreenState:update(dt)
	if self.actionList:update(dt) then
		stateStack:replace(MainMenuState())
	end
end

function SplashScreenState:render(target, states)
	self.sfmlSplash:draw(target, states)
end