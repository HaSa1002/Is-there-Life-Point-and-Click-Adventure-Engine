local class = require "middleclass"


EventHandler = class('EventHandler');

function EventHandler:initialize()
	self.events = nil
	self.subscribers = {}
	for type, v in pairs(EventType) do
		self.subscribers[type] = {}
		print(type .. " | " .. v);
	end
end

function EventHandler:setEvents(eventVector)
	self.events = eventVector
end

function EventHandler:handleEvents()
	for e in self.events do
		for s in self.subscribers[e.type] do
			s:call(e)
		end
	end
end

function EventHandler:update(dt)
	for s in self.subscribers["update"] do
		s:call(dt)
	end
end

function EventHandler:render(target, states)
	for s in self.subscribers["draw"] do
		s:call{event.target = target, event.states = states}
	end
end

function EventHandler:subscribe(subscription)
	self.subscribers[subscription.eventType].insert(subscription)
end

return EventHandler()