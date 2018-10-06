-- This is a simple object test
-- Work in progress! Some more or less functions might be not included in the engine :D
-- We are using the tablet texture


simple = class(function(o)
	o.pos = {0,0,1}
	o.scale = {4.9, 6}
	o.rotation = 100
	o.texture = "tablet"
	o.actions = {'u', 'l', 'h'}
	o.data = 1
end);

o = simple();
o2 = simple();


function simple:onUse()
	-- Default callback maybe nil??
	print("use")
end
function simple:onLook()
	-- Default callback maybe nil??
	print("look")
end
function simple:onHover()
	-- Default callback maybe nil??
	print("hover")
end

function o.update(dt, actions)
	print("Hello")
end