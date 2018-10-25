local class = require "middleclass"

Subscription = class("Subscription")

-- we need the params listener, eventType, and Callback
function Subscription:initialize(params)
	self.listener = params.listener
	self.eventType = params.eventType
	self.callback = params.callback
	self.layer = params.layer
end


-- Call the Eventhandler
function Subscription:call(event)
	self.callback(self.listener, event)
end

