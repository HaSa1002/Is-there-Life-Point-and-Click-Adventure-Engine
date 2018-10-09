print "Hallo Welt"
t = textures.new()
print(utils.hash.string("test"));
t:add("test.png", utils.hash.string("test"));
t:build();
--test = obj.new("test", "test", t, 0, 0, 0);
--objects["test"] = {"test"}
--objects.setLayer(test, 0);
--objects.setPosition(test, 300,300)
--test:scale(300,300)

function objects.test.update(dt, action, px, py)
	print("hi");
	--test:move(1,1);
end

