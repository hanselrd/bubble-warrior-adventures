local utility = require("utility")
local dir = "assets/"

local assets = {}

-- Loads all the fonts and prepends 'dir' to each filename
assets.fonts = require("assets.fonts")
utility.prepend(assets.fonts, dir)

-- Loads all the sprites and prepends 'dir' to each filename
assets.sprites = require("assets.sprites")
utility.prepend(assets.sprites, dir)

return assets
