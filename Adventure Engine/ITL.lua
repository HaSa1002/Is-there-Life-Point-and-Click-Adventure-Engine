print "Hallo Welt"
t = textures.new()
print(utils.hash.string("test"));
t:add("test.png", utils.hash.string("test"));
t:add("test.png", utils.hash.string("t2"));
t:build();
-- test = objects.Object("test", "test", t, 0, 0, 0, 0, 1, 1);
t2 = objects.SpriteObject("test", "test", t);
objects["test"] = {}
--objects.setLayer(test, 0);
objects.setLayer(t2, 0);
t2:move(100,100);
-- test:setPosition(300,300)

function objects.test.update(dt, action, px, py)
	test:move(1,1);
end

