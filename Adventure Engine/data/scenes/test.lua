local hs = utils.hash.string;
tm:add("test.png", hs("sirene"));
tm:add("t2.png", hs("t2"));
tm:build();

t2 = Player()
test = Sirene()
t = test:getTransformable()
t:setPosition(500, 500)
