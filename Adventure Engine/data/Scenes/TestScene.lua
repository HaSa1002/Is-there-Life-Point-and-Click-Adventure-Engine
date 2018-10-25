local hs = utils.hash.string;
local class = require "middleclass"
local i = require "inspect"


TestScene = class("TestScene", State)

function TestScene:initialize()
	self.ecs = EventHandler()
	self.al = ActionList()
end

function TestScene:load()
	tm:add("test.png", hs("sirene"))
	tm:add("t2.png", hs("t2"))
	tm:add("eolas.png", utils.hash.string("player"))
	tm:build()
	self.t2 = Player(self.ecs, self.al)
	self.test = Sirene(self.ecs, self.al)
	self.t = self.test:getTransformable()
	self.t:setPosition(500, 500)

	self.string = TextRenderedObject("Das funktioniert! Mit Ü!", "font.otf", 30, 2, self.ecs, self.al)
	self.string:getTransformable():setPosition(10, 300)


	self.ecs:subscribe(Subscription{
		listener = self,
		eventType = EventType.KeyReleased,
		callback = TestScene.onKeyReleased
	})


	return true
end


function TestScene:setInput(inputVector) 
	self.ecs:setEvents(inputVector)
end

function TestScene:onKeyReleased(KeyEvent)
	local key = KeyEvent.key
	if key.code == KeyCode.Escape then
		stateStack:push(PauseState())
	end
end

function TestScene:handleInput() 
	self.ecs:handleEvents()
end


function TestScene:update(dt) 
	self.ecs:update(dt)
	self.al:update(dt)
end


function TestScene:render(target, states)
	self.ecs:render(target, states)
end








