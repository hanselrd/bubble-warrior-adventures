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

-- Loads all the assets
config.assets = require("assets")

-- Display FPS counter
config.show_fps_counter = true

return config
