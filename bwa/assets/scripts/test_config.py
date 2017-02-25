def main():
    from game import config
    assets = config['assets']

    print('Game Configuration')
    print('  fullscreen:', config['fullscreen'])
    print('  resolution:', config['resolution'])
    print('  showFpsCounter:', config['showFpsCounter'])
    print('  assets:')
    print('    backgrounds:', assets.backgrounds)
    print('    fonts:', assets.fonts)
    print('    sprites:', assets.sprites)
    print('    themes:', assets.themes)
    print('  scriptsDir:', config['scriptsDir'])
    print('  mapsDir:', config['mapsDir'])
    print('  theme:', config['theme'])
    print('  TitleScreen:', config['TitleScreen'])
