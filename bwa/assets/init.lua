local utility = require "utility"
local dir = "assets/"

local assets = {}

assets.fonts = require "assets.fonts"
utility.prepend(assets.fonts, dir)

assets.sprites = require "assets.sprites"
utility.prepend(assets.sprites, dir)

return assets