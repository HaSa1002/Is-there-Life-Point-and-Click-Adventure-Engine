-- New object and scene system test file

-- Add scene to scene list
pc.scenes.add("system_test");


-- Create shortcuts for scene and objects table
local s = pc.scenes.system_test;
local o = s.objects;

function s.init()
	-- Add the "simple" object to the scene
	s.add(pc.objects.simple, "tablet");
	o.tablet.pos(0,0,0);
end

-- Different approach
pc.scenes.add("system_test");
scenes["system_test"] = {
	objects = {
		tablet = {function()
			o = objects.simple();
			tablet.pos(0,0,0);
			tablet.scale(6,6);
		end},
	}
}