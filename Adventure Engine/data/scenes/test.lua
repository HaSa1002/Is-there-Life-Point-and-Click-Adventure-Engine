local hs = utils.hash.string;
tm:add("test.png", hs("test"));
tm:add("t2.png", hs("t2"));
tm:build();

test = RenderedObject("test")
t = test:getTransformable()
t:setPosition(100, 100)
t:setRotation(50)