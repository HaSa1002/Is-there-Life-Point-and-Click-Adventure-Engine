local class = require "middleclass"


local EventHandler = class('EventHandler');

function EventHandler:initialize()
	self.events = nil
	self.subscribers = {}
	for type in eventTypes do
		self.subscribers[type] = {}
	end
end

function EventHandler:setEvents(eventVector)
	self.events = eventVector
end

function EventHandler:handleEvents()
	for e in self.events do
		for s in self.subscribers[e.type] do
			s.call(e)
		end
	end
end

function EventHandler:subscribe(subscription)
	self.subscribers[subscription.eventType].insert(subscription)
end

