from pico2d import *
import game_framework
import random

class BackGround:
	def __init__(self):
		self.image = load_image('./res/map.png')

	def update(self):
		pass
		
	def draw(self):
		self.image.clip_draw(500 - get_canvas_width()//2,400 - get_canvas_height()//2,
			get_canvas_width(),get_canvas_height(),get_canvas_width()//2,get_canvas_height()//2)



