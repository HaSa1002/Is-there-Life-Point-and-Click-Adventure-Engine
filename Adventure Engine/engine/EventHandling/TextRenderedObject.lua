local class = require "middleclass"

TextRenderedObject = class("TextRenderedObject")

function TextRenderedObject:initialize(string, font, size, layer, ecs, al)
	self.renderComponent = TextRenderComponent.new(string, font, size)
	ecs:subscribe(Subscription{
		listener = self,
		eventType = "draw",
		callback = TextRenderedObject.onRender,
		layer = layer
	})
end

function TextRenderedObject:onRender(event)
	self.renderComponent:draw(event.target, event.states);
end

function TextRenderedObject:getTransformable()
	return self.renderComponent:getTransformable()
end

function TextRenderedObject:getSize()
	local fr = self.renderComponent:getLocalBounds()
	return fr.width, fr.height
end