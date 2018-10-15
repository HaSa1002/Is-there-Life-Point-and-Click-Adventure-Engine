local class = require "middleclass"


local EventHandler = class('EventHandler');

function EventHandler:initialize()
	self.events = nil
end

function EventHandler:setEvents(eventVector)
	self.events = eventVector
end

function EventHandler:handleEvents()
	for ()
end