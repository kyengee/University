from pico2d import *
import game_framework
import threading
import title_state

image = 0
flag = 0

def add_num():
    global flag
    flag += 1

def enter():
    threading.Timer(1,add_num).start()
    open_canvas()
    global image
    image = load_image('./kpu_credit.png')
    

def exit():
    pass

def update():
    global flag
    if flag == 1:
        game_framework.change_state(title_state)
    update_canvas()
        

def draw():
        global image
        delay(0.03)
        clear_canvas()
        image.draw(400,300)

def handle_events():
    pass
