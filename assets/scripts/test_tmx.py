def main():
    from game import settings
    from game.tmx import Map, Layer

    fn = 'assets/maps/world.tmx'
    map = Map(fn)
    print('Map [%s]:' % fn)
    print('  width:', map.width)
    print('  height:', map.height)
    print('  tilewidth:', map.tilewidth)
    print('  tileheight:', map.tileheight)
    print('  layers:')
    for layer in map.layers:
        print('    %s [%s]:' % (layer.name, layer.type))
        if layer.type == Layer.Tile:
            for tile in layer.tiles:
                print(tile.pos.x, end=' ')
            print()

        elif layer.type == Layer.Object:
            print('      objects:',
            [(o.name, o.type, o.tile.gid if o.tile != None else 'nullptr',
                (o.rect.x, o.rect.y, o.rect.w, o.rect.h)) for o in layer.objects])
