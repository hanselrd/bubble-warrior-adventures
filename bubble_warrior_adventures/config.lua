-- Sets the game to fullscreen if true, windowed if false
-- using the values defined under resolution
fullscreen = false

resolution = {
	-- Sets the x component of game's resolution
	x = 800,
	-- Sets the y component of game's resolution
	y = 600
}

-- Where to find scripts
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
}

-- Display FPS counter
show_fps_counter = true