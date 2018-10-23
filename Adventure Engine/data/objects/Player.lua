local class = require "middleclass"

Player = class("Player", RenderedObject)

function Player:initialize()
	RenderedObject.initialize(self, "player")
	ecs:subscribe(Subscription{
		listener = self,
		eventType = EventType.MouseMoved,
		callback = Player.onMouseButtonReleased
	})
	self.transform = RenderedObject.getTransformable(self)
	self.sizeX, self.sizeY = RenderedObject.getSize(self)
	self.transform:setOrigin(self.sizeX * 0.5, self.sizeY)
	self.transform:scale((1/6), (1/6))
	self.transform:setPosition(100,100)
end

function Player:onMouseButtonReleased(event)
	local e = event.mouseMove
		RenderedObject.getTransformable(self):setPosition(e.x, e.y)
end

--function Player:onMouseButtonReleased(event)
--	local e = event.mouseButton
--	if e.button == MouseButton.Left then
--		RenderedObject.getTransformable(self):setPosition(e.x, e.y)
--	end
--end
