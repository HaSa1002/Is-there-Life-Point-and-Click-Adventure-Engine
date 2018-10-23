local class = require "middleclass"
local i = require "inspect"

Sirene = class("Sirene", RenderedObject)

function Sirene:initialize()
	 RenderedObject.initialize(self, "sirene")
	ecs:subscribe(Subscription{
		listener = self,
		eventType = "update",
		callback = Sirene.update
	})

	self.transform = RenderedObject.getTransformable(self)
	self.sizeX, self.sizeY = RenderedObject.getSize(self)
	self.transform:setOrigin(self.sizeX * 0.5, self.sizeY * 0.5)
	self.transform:setScale(6,6)
end


function Sirene:update(dt)
	self.transform:rotate(36 * dt)
end