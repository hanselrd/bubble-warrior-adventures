local utility = require "utility"

--[[
    All the sprites in this directory,
    eventually this will also store information
    on each sprite such as: animations and locations
    of tiles in tilesets and many more.
--]]
local sprites = {
    "golden_hero_female_no_shield.png",
    "golden_hero_female_no_shield_no_hat.png",
    "golden_hero_male.png",
    "golden_hero_male_no_hat.png",
    "golden_hero_male_no_shield.png",
    "golden_hero_male_no_shield_no_hat.png",
    "regular_hero_female.png",
    "regular_hero_male.png"
}

-- Prepends 'sprites/' to every string in sprites table
utility.prepend(sprites, "sprites/")

return sprites