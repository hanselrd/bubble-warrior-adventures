def main():
    from game import config
    from game.tmx import Map

    fn = config['maps'] + 'world.tmx'
    map = Map(fn)
    print('Map [%s]:' % fn)
    print('  Width:', map.width)
    print('  Height:', map.height)
    print('  Tilewidth:', map.tilewidth)
    print('  Tileheight:', map.tileheight)
