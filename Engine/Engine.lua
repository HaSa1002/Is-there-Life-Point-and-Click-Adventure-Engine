-- This is the config file for your game
-- Currently you have to manually register all rooms. This may get obsolete someday
-- Load our helpers
dofile "helpers.lua"

-- Firstly we allways need to have the rooms table initialized. This may be done in short time by the engine directly
scenes = {}

-- Don't forget the Localisations
localisations = {}

-- Register the language files
dofile "locals/en.lang"
dofile "locals/de.lang"

-- Create the Game Table with all Settings etc.
game = {}
game.stdlang = "en"
game.lang = "de"
-- Load the user configs
-- dofile "Game.conf"

-- Register the scenes
 dofile "scenes/lua_testscene.pcscene"
