-- New object and scene system test file

-- Add scene to scene list
pc.scenes.add("system_test");


-- Create shortcuts for scene and objects table
local s = pc.scenes.system_test;
local o = s.objects;

function s.init()
	-- Add objects to the scene
	scenes["system_test"] = {
		objects = {
			tablet = obj.new(0,0,0,)
		}
	}
end