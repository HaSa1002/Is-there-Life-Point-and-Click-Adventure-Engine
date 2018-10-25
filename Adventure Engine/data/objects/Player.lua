local class = require "middleclass"

Player = class("Player", RenderedObject)

function Player:initialize(ecs, al)
	RenderedObject.initialize(self, "player", 5, ecs)
	ecs:subscribe(Subscription{
		listener = self,
		eventType = EventType.MouseButtonReleased,
		callback = Player.onMouseButtonReleased
	})
	self.t = RenderedObject.getTransformable(self)
	self.sizeX, self.sizeY = RenderedObject.getSize(self)
	self.t:setOrigin(self.sizeX * 0.5, self.sizeY)
	self.t:scale((1/6), (1/6))
	self.t:setPosition(100,100)
	self.walkboxes = {}
	self.al = al
	self.ecs = ecs
	self.WALKSPEED = 400
end

function Player:addWalkbox(t, l, w, h)
	self.walkboxes[#self.walkboxes + 1] = IntRect(t, l, w, h)
end

function Player:onMouseButtonReleased(event)
	local e = event.mouseButton
	if e.button == MouseButton.Left then
		coroutine.resume(self.al:add(goTo), self.t, self.WALKSPEED, Vector2f.new(e.x, e.y))
	end
end
