-- Button for the keypad



objects.keypad.button = class(num, function(o)
	o.pos = {0,0,3}
	o.scale = {6, 6}
	o.rotation = 0
	o.texture = "keypadButtons"
	o.actions = {'u', 'l'}
	o.type = "animated"
	o.states = {
		green = {0,0, 16,16},
		yellow = {16,0 32,16},
		red = {32,0, 48,16},
		blue = {48,0, 64,16},
		grey = {64,0, 80,16},
		default = "grey"
	}
	o.number = num
end);
Object = objects.keypad.button;

function Object:onUse()
	pc.setSubtitle(locals(self.number));
	-- object, state, callback
	pc.playAnimation(self.number, "yellow", 1, function() pc.setState("grey") end);
end