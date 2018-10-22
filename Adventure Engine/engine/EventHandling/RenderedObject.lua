local class = require "middleclass"

RenderedObject = class("RenderedObject", GameObject)

function RenderedObject:initialize(texture)
	self.renderComponent = RenderComponent.new(tm, utils.hash.string(texture))

	ecs:subscribe(Subscription{
		listener = self,
		eventType = "draw",
		callback = RenderedObject.onRender
	})
end

function RenderedObject:onRender(event)
	self.renderComponent:draw(event.target, event.states);
end

function RenderedObject:getTransformable()
	return self.renderComponent:getTransformable()
end