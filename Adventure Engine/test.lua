local hs = utils.hash.string;
tm:add("keypad/base.png", hs("base"));
tm:add("keypad/numbers.png", hs("nums"));
tm:add("keypad/none.png", hs("sN"));
tm:add("keypad/blue.png", hs("sB"));
tm:add("keypad/green.png", hs("sG"));
tm:add("keypad/red.png", hs("sR"));
tm:add("keypad/yellow.png", hs("sY"));
tm:build();

keypadBase = Object(hs("base"));
keypadNum = Object(hs("nums"));
keypad1 = Object(hs("sG"));
keypad2 = Object(hs("sB"));

keypadNum:setPosition(11,27);
keypad1:setPosition(9,26);
keypad2:setPosition(29, 26);
keypadBase:setPosition(50,50);

objects.attach(keypadBase, keypad1);
objects.attach(keypadBase, keypad2);
objects.attach(keypadBase, keypadNum);
objects.setLayer(keypadBase, 1);


keypadBase:setScale(6,6);

keypad1:set(hs("time"), nil);
keypad1:set(hs("click"), false);


keypad1:update(function (dt, action, cend)
	if action == 'l' then 
		keypad1:texture(hs("sB"), tm);

		if cend then 
			keypad1:set(hs("click"), false);
			keypad1:set(hs("time"), 0.002);
		else
			keypad1:set(hs("click"), true);
		end
	end
	

	if action == 'r' then
		keypad1:texture(hs("sR"), tm);
		keypad1:set(hs("time"), 5);
	end

	if keypad1:get(hs("time")) >= 0 then
		keypad1:set(hs("time"), keypad1:get(hs("time")) - dt);
	end

	if keypad1:get(hs("time")) < 0 then
		keypad1:texture(hs("sN"), tm);
		keypad1:set(hs("time"), nil)
	end

	
end);

keypad2:update(function (dt, action)
	if action == 'l' then 
		keypad2:texture(hs("sG"), tm);
	end
	if action == 'r' then changeScene("scene"); end
end);