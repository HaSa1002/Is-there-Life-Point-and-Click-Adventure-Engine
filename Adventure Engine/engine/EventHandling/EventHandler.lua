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
	local e = self.events
	for v=1, #e do
		local type = e[v].type
		for num, s in pairs(self.subscribers[type]) do
			s:call(e[v])
		end
	end
	
end

function EventHandler:update(dt)
	for num, s in pairs(self.subscribers.update) do
		s:call(dt)
	end
end

function EventHandler:render(target_, states_)
	local event = {
		states = states_,
		target = target_}
		local drawlist = self.subscribers.draw
		--print(#drawlist)
	for i, v in pairs(drawlist) do
		for num, s in pairs(drawlist[i]) do
			s:call(event)
		end
	end
end

function EventHandler:subscribe(subscription)
	if subscription.eventType == "draw" then
		if subscription.layer == nil or subscription.layer < 1 then
			subscription.layer = 1
		end
		local d = self.subscribers.draw[subscription.layer]
		if  d == nil then
			self.subscribers.draw[subscription.layer] = {subscription}
		else 
			self.subscribers.draw[subscription.layer][#d+1] = subscription
		end
	else
		local t = self.subscribers[subscription.eventType]
		if t == nil then
			self.subscribers[subscription.eventType] = {subscription}
		else 
			self.subscribers[subscription.eventType][#t+1] = subscription
		end
	end
end

function EventHandler:clearSubscriptions()
	self.subscribers.draw = {}
	self.subscribers.update = {}
	for type, v in pairs(getmetatable(EventType).__index) do
		self.subscribers[v] = {}
	end
end

