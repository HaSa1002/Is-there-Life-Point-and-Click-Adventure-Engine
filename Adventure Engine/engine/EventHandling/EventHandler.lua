local class = require "middleclass"



EventHandler = class('EventHandler');

function EventHandler:initialize()
	self.events = nil
	self.subscribers = {}
	self.subscribers["update"] = {}
	self.subscribers["draw"] = {}
	for type, v in pairs(getmetatable(EventType).__index) do
		self.subscribers[v] = {}
	end
	
end

function EventHandler:setEvents(eventVector)
	self.events = eventVector
end

function EventHandler:handleEvents()
	local i = require "inspect"
	--print(i(#self.events))
	local e = self.events
	for v=1, #e do
		local type = e[v].type
		--print(i(type))
		for n, s in pairs(self.subscribers[type]) do
			s:call(e[v])
		end
	end
	
end

function EventHandler:update(dt)
	for n, s in pairs(self.subscribers.update) do
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