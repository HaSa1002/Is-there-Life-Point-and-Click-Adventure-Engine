local class = require "middleclass"



EventHandler = class('EventHandler');

function EventHandler:initialize()
	self.events = nil
	self.subscribers = {}
	self.subscribers["update"] = {}
	self.subscribers["draw"] = {}
	for type in pairs(getmetatable(EventType).__index) do
		self.subscribers[type] = {}
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

function EventHandler:render(target_, states_)
	local event = {
		states = states_,
		target = target_}
	for n, s in pairs(self.subscribers.draw) do
		s:call(event)
	end
end

function EventHandler:subscribe(subscription)
	local t = self.subscribers[subscription.eventType]
	if self.subscribers[subscription.eventType] == nil then
		self.subscribers[subscription.eventType] = {subscription}
	else self.subscribers[subscription.eventType][#t+1] = subscription
	end
end

function EventHandler:clearSubscriptions()
	self.subscribers.draw = {}
	self.subscribers.update = {}
	for type in pairs(getmetatable(EventType).__index) do
		self.subscribers[type] = {}
	end
end

return EventHandler()