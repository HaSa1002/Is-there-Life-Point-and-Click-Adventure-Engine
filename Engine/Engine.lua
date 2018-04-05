-- This is the config file for your game
-- Currently you have to manually register all rooms. This may get obsolete someday
-- Load our helpers


-- Initalize Tables
scenes = {}
localisations = {}
game = {}

-- Load our smart helpers
dofile "helpers.lua"

-- Some settings:
game.stdlang = "en"
game.lang = "de"

-- Set Subtitle Settings:
game.subtitleColor = {255, 255, 255,  255} -- RGBa
game.subtitleSize = 30
game.subtitleFont = ".\\textures\\font.otf"
-- dofile "Game.conf"


-- Register the language files
dofile "locals/en.lang"
dofile "locals/de.lang"

-- Register the scenes
 dofile "scenes/lua_testscene.pcscene"
 dofile "scenes/lua_testscene2.pcscene"


 -- Set the first scene to be loaded.
 loadScene "lua_testscene"