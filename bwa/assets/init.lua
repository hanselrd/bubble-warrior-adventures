local assets = {}

local dir = "assets/"

-- Loads all the backgrounds and prepends 'dir' to each filename
assets.backgrounds = require("assets.backgrounds")
utility.prepend(assets.backgrounds, dir)

-- Loads all the fonts and prepends 'dir' to each filename
assets.fonts = require("assets.fonts")
utility.prepend(assets.fonts, dir)

-- Loads all the sprites and prepends 'dir' to each filename
assets.sprites = require("assets.sprites")
utility.prepend(assets.sprites, dir)

-- Loads all the themes and prepends 'dir' to each filename
assets.themes = require("assets.themes")
utility.prepend(assets.themes, dir)

-- Maps directory
assets.maps_dir = dir .. "maps/"

-- Scripts directory
assets.scripts_dir = dir .. "scripts/"

return assets
