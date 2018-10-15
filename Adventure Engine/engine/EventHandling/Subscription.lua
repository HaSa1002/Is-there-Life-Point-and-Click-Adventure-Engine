local class = require "middleclass"

Subscription = class("Subscription")

function Subscription:initialize(params)
	self.listener = params.listener
	self.eventType = params.eventType
	self.callback = params.callback
	self.event = nil
end

function Subscription:call()
	self.callback(self.listener, self.event)
end

function Subscription:wantsCall(event, eventType)
	if (eventType == self.eventType) then
		self.event = event
		return true
	else return false
	end
end