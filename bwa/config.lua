-- Configuration for game
local config = {}

-- Sets the game to fullscreen if true, windowed if false
-- using the values defined under resolution
config.fullscreen = false

-- The width and height of the window
config.resolution = {
	-- Window width
	x = 800,
	-- Window height
	y = 600
}

config.assets = require "assets"
--[[ Where to find scripts
script_dir = 'scripts/'

-- Where to find assets
assets_dir = 'assets/'

-- Where to find fonts
fonts_dir = assets_dir .. 'fonts/'

-- Default game fonts
game_fonts = {
	normal = fonts_dir .. 'animeace.ttf',
	bold = fonts_dir .. 'animeace_b.ttf',
	italics = fonts_dir .. 'animeace_i.ttf'
} --]]

-- Display FPS counter
config.show_fps_counter = true

return config