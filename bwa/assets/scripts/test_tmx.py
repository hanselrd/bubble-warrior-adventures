def main():
    from game import config
    from game.tmx import Map

    fn = config['mapsDir'] + 'world.tmx'
    map = Map(fn)
    print('Map [%s]:' % fn)
    print('  width:', map.width)
    print('  height:', map.height)
    print('  tilewidth:', map.tilewidth)
    print('  tileheight:', map.tileheight)
