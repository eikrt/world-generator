import pyglet
pyglet.resource.path=["../res"]
pyglet.resource.reindex()
window = pyglet.window.Window()
tile_img = pyglet.image.load('tile.png')
tiles = []

batch = pyglet.graphics.Batch()	
def init():
	pass

def main():

	for x in range (100):
		for y in range(100):
		
			tiles.append(pyglet.sprite.Sprite(tile_img, x*16,y*16,batch=batch))
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
