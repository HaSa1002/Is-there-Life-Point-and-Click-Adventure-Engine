local hs = utils.hash.string;
tm:add("test.png", hs("test"));
tm:add("t2.png", hs("t2"));
tm:build();

t2 = Object(hs("test"));
objects.setLayer(t2, 0);
t2:move(100,100);
t2:set(hs("time"), 1.0);
t2:set(hs("next_texture"), "t2")

t2:update (function (dt, action)
	local time = hs("time");
	local t = t2:get(time);
	t = t + dt;
	if t >= 2 then
		local h_next_texture = hs("next_texture");
		t = t - 2;
		t2:texture(hs(t2:get(h_next_texture)), tm);
		if t2:get(h_next_texture) == "t2" then t2:set(h_next_texture, "test");
		else t2:set(h_next_texture, "t2");
		end
	end

	if action == 'l' then
		changeScene("test");
	end
	--t2:rotate(360 * dt);
	t2:set(time, t);
	
end);

