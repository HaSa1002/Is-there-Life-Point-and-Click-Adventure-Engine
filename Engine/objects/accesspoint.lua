-- This is a simple object test
-- Work in progress! Some more or less functions might be not included in the engine :D

-- Accesspoint

require 'class';

objects.accesspoint = class(function(o)
	o.pos = nil;
	o.scale = {5,5};
	o.rotation = 0;
	o.texture = "accesspoint";
	o.actions = {'u'};
end);
Object = objects.accesspoint;
function Object:onUse()
	pc.setSubtitle(locals("accesspointU"));
end

pc.objects.add("accesspoint");