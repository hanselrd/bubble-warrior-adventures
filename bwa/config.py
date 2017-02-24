import sys
sys.path.append('.')

import assets

config = {
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

	# Loads all the assets
	'assets': assets,

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
