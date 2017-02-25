def main():
    from game.tmx import Map

    fn = 'assets/maps/world.tmx'
    map = Map(fn)
    print('Map [%s]:' % fn)
    print('  Width:', map.width)
    print('  Height:', map.height)
    print('  Tilewidth:', map.tilewidth)
    print('  Tileheight:', map.tileheight)
