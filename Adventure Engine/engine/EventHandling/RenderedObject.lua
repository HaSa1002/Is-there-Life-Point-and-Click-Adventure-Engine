local class = require "middleclass"

RenderedObject = class("RenderedObject", GameObject)

function RenderedObject:initialize(texture, layer, ecs)
	self.renderComponent = RenderComponent.new(tm, utils.hash.string(texture))
	print ("Init:", layer)
	ecs:subscribe(Subscription{
		listener = self,
		eventType = "draw",
		callback = RenderedObject.onRender,
		layer = layer
	})
end

function RenderedObject:onRender(event)
	self.renderComponent:draw(event.target, event.states);
end

function RenderedObject:getTransformable()
	return self.renderComponent:getTransformable()
end

function RenderedObject:getSize()
	local fr = self.renderComponent:getLocalBounds()
	return fr.width, fr.height
end