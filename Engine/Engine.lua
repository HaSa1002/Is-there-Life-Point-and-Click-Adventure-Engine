-- This is the config file for your game
-- Currently you have to manually register all rooms. This may get obsolete someday
-- Find your way in your scripting language

-- Some settings:
game.stdlang = "en"
game.lang = "de"

-- Set Subtitle Settings:
game.subtitleColor = {255, 255, 255,  255} -- RGBa
game.subtitleSize = 30 --pixels
game.subtitleFont = ".\\textures\\font.otf"


-- Register the language files
dofile "locals/helpers.lua"
dofile "locals/en.lang"
dofile "locals/de.lang"

-- Register the textures and objects
dofile "objects/textures.lua";


-- Register the scenes
dofile "scenes/lua_testscene.pcscene"
dofile "scenes/lua_testscene2.pcscene"
dofile "scenes/bedroom_old.pcscene"


 -- Set the first scene to be loaded.
pc.loadScene("lua_testscene")