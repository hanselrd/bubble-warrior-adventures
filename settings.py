import sys
sys.path.append('.')
import assets
sys.path.pop()
import game

settings = {
	# Sets the game to fullscreen if true, windowed if false
	# using the values defined under resolution
	'fullscreen': False,

	# The width and height of the window
	'resolution': {
		# Window width
		'x': 800,

		# Window height
		'y': 600
	},

	# Display FPS counter
	'showFpsCounter': True,

	# Stores the assets
	'assets': assets,

	# Scripts folder
	'scriptsDir': 'assets/scripts/',

	# Maps folder
	'mapsDir': 'assets/maps/',

	# Default GUI theme
	'theme': assets.themes[0],

	# TitleScreen settings
	'TitleScreen': {
		# Background image
		'background': assets.backgrounds[0],

		# Title font
		'font': assets.fonts[3]
	}
}

# Adds the newly created settings dict to game module
game.settings = settings
