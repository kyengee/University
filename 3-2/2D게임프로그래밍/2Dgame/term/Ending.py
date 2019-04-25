from pico2d import *
import game_framework

EndImage1 = None
EndImage2 = None
EndImage3 = None
EndImage4 = None
EndImage5 = None
EndImage6 = None
count = 0
def enter():
	resize_canvas(500,500)
	global EndImage1,EndImage2,EndImage3,EndImage4,EndImage5,EndImage6,count
	if EndImage1 == None:
		EndImage1 = load_image('./res/Ending1.png')
		EndImage2 = load_image('./res/Ending2.png')
		EndImage3 = load_image('./res/Ending3.png')
		EndImage4 = load_image('./res/Ending4.png')
		EndImage5 = load_image('./res/Ending5.png')
		EndImage6 = load_image('./res/Ending6.png')
		count = 0

def exit():
	global EndImage1,EndImage2,EndImage3,EndImage4,EndImage5,EndImage6
	del EndImage1,EndImage2,EndImage3,EndImage4,EndImage5,EndImage6

def draw():
	global EndImage1,EndImage2,EndImage3,EndImage4,EndImage5,EndImage6,count
	clear_canvas()
	if count is 0:
		EndImage1.draw(250, 250)
		count += 1
	elif count is 1:
		EndImage2.draw(250, 250)
		count += 1
	elif count is 2:
		EndImage3.draw(250, 250)
		count += 1
	elif count is 3:
		EndImage4.draw(250, 250)
		count += 1
	elif count is 4:
		EndImage5.draw(250, 250)
		count += 1
	elif count is 5:
		EndImage6.draw(250, 250)
		count += 1
	elif count is 6:
		EndImage2.draw(250, 250)
		count += 1
	elif count is 7:
		game_framework.pop_state()
		count += 1
	update_canvas()

def update():
	delay(3)

def handle_events():
	events = get_events()
	for e in events:
		if e.type == SDL_QUIT:
			game_framework.quit()
		elif e.type == SDL_KEYDOWN:
			if e.key == SDLK_ESCAPE:
				game_framework.quit()
				# game_framework.pop_state()
			elif e.key == SDLK_SPACE:
				pass

def pause():
	pass

def resume():
	pass

if __name__ == '__main__':
	import sys
	current_module = sys.modules[__name__]	
	open_canvas(498,423)
	game_framework.run(current_module)
	close_canvas()
