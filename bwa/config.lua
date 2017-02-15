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

-- Display FPS counter
config.showFpsCounter = true

-- Loads all the assets
config.assets = require("assets")

-- Default GUI theme
config.theme = config.assets.themes[1]

-- TitleScreen settings
config.TitleScreen = {
	-- Background image
	background = config.assets.backgrounds[1],

	-- Title font
	font = config.assets.fonts[4]
}

return config
