def main(map):
    from game import settings
    from game.tmx import Map, Layer

    print('Map [%s]:' % 'some map')
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
            [(o.name, o.type,
                (o.rect.x, o.rect.y, o.rect.w, o.rect.h)) for o in layer.objects])
