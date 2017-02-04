local utility = require "utility"

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

utility.prepend(sprites, "sprites/")

return sprites