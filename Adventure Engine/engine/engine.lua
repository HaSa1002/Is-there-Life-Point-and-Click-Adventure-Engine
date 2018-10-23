game = {}
game.lang = "de";
game.stdlang = "de";
localisations = {};

-- Load Localisation files

-- Helper for selecting automatically the correct string
function locals( string )
	if localisations[game.lang] ~= nil then
		return localisations[game.lang][string];
		elseif localisations[game.stdlang] ~= nil then
		return localisations[game.stdlang][string];
		else return "Error: The Key is not set for the language you chose to use!";
	end
end

-- Load the first scene

-----------------------------------------
-- New Stuff to do since Moving to Lua --
-----------------------------------------


		-----------------------
		-- End of that stuff --
		-----------------------
tm:add("eolas.png", utils.hash.string("player"))
changeScene("test");


