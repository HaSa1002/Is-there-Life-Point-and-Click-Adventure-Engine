-- This is a simple object test
-- Work in progress! Some more or less functions might be not included in the engine :D
-- We are using the tablet texture


objects.simple = class(function(o)
	o.pos = {0,0,1}
	o.scale = {4.9, 6}
	o.rotation = 100
	o.texture = "tablet"
	o.actions = {'u', 'l', 'h'}
	o.data = 1
end);
Object = objects.simple;

function Object:onUse()
	-- Default callback maybe nil??
	pc.setSubtitle(local("tabletU"));
end
function Object:onLook()
	-- Default callback maybe nil??
	pc.setSubtitle(local("tabletL"));
end
function Object:onHover()
	-- Default callback maybe nil??
	pc.setSubtitle(local("tablet"));
end

pc.objects.add("simple");