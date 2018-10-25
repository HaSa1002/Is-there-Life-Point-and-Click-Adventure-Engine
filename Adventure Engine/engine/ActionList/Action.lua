local class = require "middleclass"
local i = require "inspect"

Action = class("Action")
ActionList = class("ActionList")

DelayAction = class("DelayAction", Action)
GoToAction = class("GoToAction", Action)
MoveToAction = class("MoveToAction", Action)


function Action:launch()
	--self:init()

	while not self.finished do
		local dt = coroutine.yield()
		self:update(dt)
	end

	--self:exit()
end

function ActionList:initialize()
	self.functions = {}
end

function ActionList:add(func)
	table.insert(self.functions, coroutine.create(func))
	return self.functions[#self.functions]
end

function ActionList:update(dt)
	local finished = true
	for k,v in pairs(self.functions) do
		if coroutine.status(v) == 'dead' then
			k = nil
		else
			ok, msg = coroutine.resume(v, dt)
			if not ok then
				print("Coroutine failed!", msg)
			end
			finished = false
		end
	end
	return finished
end

function MoveToAction:initialize(params)
	self.t = params.t
	self.time = params.time
	self.dest = params.dest
	self.finished = false
	self.currentTime = 0
	
	local pos = self.t:getPosition()
	local toGoX = self.dest.x - pos.x
	local toGoY = self.dest.y - pos.y

	-- Calc movement per second
	self.moveX = toGoX / self.time
	self.moveY = toGoY / self.time

end

function MoveToAction:update(dt)
	self.currentTime = self.currentTime + dt
	if self.currentTime >= self.time then
		self.t:setPosition(self.dest.x, self.dest.y)
		self.finished = true
	else
		self.t:move(self.moveX * dt, self.moveY * dt)
	end

end

function moveTo(t, time, dest)
	action = GoToAction{
		t = t,
		time = time,
		dest = dest
	}
	action:launch()
end


function GoToAction:initialize(params)
	self.t = params.t
	self.walkspeed = params.walkspeed
	self.dest = params.dest
	self.finished = false
	self.currentTime = 0
	
	local pos = self.t:getPosition()
	local toGoX = self.dest.x - pos.x
	local toGoY = self.dest.y - pos.y



	-- Calc time
	local a = math.sqrt((toGoX * toGoX) + (toGoY * toGoY))
	self.time = a / self.walkspeed
	print (self.time)

	self.moveX = toGoX / self.time
	self.moveY = toGoY / self.time

end

function GoToAction:update(dt)
	self.currentTime = self.currentTime + dt
	if self.currentTime >= self.time then
		self.t:setPosition(self.dest.x, self.dest.y)
		self.finished = true
	else
		self.t:move(self.moveX * dt, self.moveY * dt)
	end

end

function goTo(t, walkspeed, dest)
	action = GoToAction{
		t = t,
		walkspeed = walkspeed,
		dest = dest
	}
	action:launch()
end




function DelayAction:initialize(params)
	self.delay = params.delay
	self.currentTime = 0
	self.finished = false
end

function DelayAction:update(dt)
	self.currentTime = self.currentTime + dt
	if self.currentTime >= self.delay then
		self.finished = true
	end
end

function delay(time)
	action = DelayAction{delay = time}
	action:launch()
end

AppearAction = class("AppearAction", Action)

function AppearAction:initialize(params)
	self.obj = params.obj
	self.colorR = params.r
	self.colorG = params.g
	self.colorB = params.b
	self.time = params.time
	self.currentTime = 0
	self.finished = false
end

function AppearAction:update(dt)
	if self.currentTime + dt >= self.time then
		self.obj:setColor(self.colorR, self.colorG, self.colorB, 255)
		self.finished = true
	else
		self.currentTime = self.currentTime + dt
		local factor = self.currentTime / self.time
		self.obj:setColor(self.colorR, self.colorG, self.colorB, 255 * factor)
	end
end

function appear(time, r, g, b, setColor)
	action = AppearAction{
		obj = setColor,
		r = r,
		g = g,
		b = b,
		time = time
	}
	action:launch()
end

DisappearAction = class("DisappearAction", Action)

function DisappearAction:initialize(params)
	self.obj = params.obj
	self.colorR = params.r
	self.colorG = params.g
	self.colorB = params.b
	self.time = params.time
	self.currentTime = params.time
	self.finished = false
end

function DisappearAction:update(dt)
	if self.currentTime - dt <= 0 then
		self.obj:setColor(self.colorR, self.colorG, self.colorB, 0)
		self.finished = true
	else
		self.currentTime = self.currentTime - dt
		local factor = self.currentTime / self.time
		self.obj:setColor(self.colorR, self.colorG, self.colorB, 255 * factor)
	end
end

function disappear(time, r, g, b, setColor)
	action = DisappearAction{
		obj = setColor,
		r = r,
		g = g,
		b = b,
		time = time
	}
	action:launch()
end