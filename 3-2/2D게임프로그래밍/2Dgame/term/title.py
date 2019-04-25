from pico2d import *
import game_framework
import Main


def enter():
	global bgImage
	open_canvas(498,423)
	bgImage = load_image('./res/title.png')

def exit():
	global bgImage
	del bgImage
	close_canvas()

def draw():
	clear_canvas()
	bgImage.draw(498/2, 423/2)
	update_canvas()

def update():
	delay(0.03)

def handle_events():
	events = get_events()
	for e in events:
		if e.type == SDL_QUIT:
			game_framework.quit()
		elif e.type == SDL_KEYDOWN:
			if e.key == SDLK_ESCAPE:
				game_framework.quit()
			elif e.key == SDLK_SPACE:
				game_framework.push_state(Main)

def pause():
	global bgImage
	del bgImage

def resume():
	global bgImage
	resize_canvas(498,423)
	bgImage = load_image('./res/title.png')

if __name__ == '__main__':
	import sys
	open_canvas(498,423)
	print(sys.modules[__name__])
	game_framework.run(sys.modules[__name__])
	close_canvas()
