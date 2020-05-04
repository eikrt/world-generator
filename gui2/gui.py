import pyglet
pyglet.resource.path=["../res"]
pyglet.resource.reindex()
window = pyglet.window.Window()

tile_img = pyglet.image.load('tile.png')
ground_img = pyglet.image.load('ground.png')
tiles = []
batch = pyglet.graphics.Batch()

def loadMap():
		
	map = [[]]
	with open('../generator/map/map.txt', encoding = 'utf-8') as f:
		ln = 0;
		i = 0;
		for line in f:  
				
			for ch in line:
				if not ch == '\n': 
					map[ln].append(ch)
		
			map.append([])
			ln+=1
	print(map)	
	return map	

def init():
	pass

def main():
	map = loadMap()
	print(len(map))
	for x in range (len(map[0])):
		for y in range(len(map[0])):
			if (map[x][y] == '0'):	

				tiles.append(pyglet.sprite.Sprite(tile_img, x*16,y*16,batch=batch))
			else:
				
				tiles.append(pyglet.sprite.Sprite(ground_img, x*16,y*16,batch=batch))
	pyglet.app.run()
	init();
	
def loop():

	pass
@window.event
def on_draw():
	window.clear()

	batch.draw()
def update(dt):
	pass

main()
