-- This is a simple object test
-- Work in progress! Some more or less functions might be not included in the engine :D
-- We are using the tablet texture


-- Add the object to the library
pc.objects.add("simple");

-- Define an easy-access variable
local obj = pc.objects.simple;

-- Set or get the position
local pos = obj.pos();
obj.pos(0,0,1);
obj.pos(val);

-- Set or get the scale
local scale = obj.scale();
obj.scale(4.9, 6);
obj.scale(scale);

-- Set or get the rotation
local rotation = obj.rotation();
obj.rotation(100);
obj.rotation(rotation);

-- Set or get the texture string
local texture = obj.texture();
obj.texture(".\\textures\\tablet.png");
obj.texture(texture);

-- Set or get the actions
local actions = obj.action();
obj.action({'u', 'l', 'h'});
obj.action(actions);


-- Add missing stuff