from pico2d import *
from math import *

    
    

open_canvas()

grass = load_image('grass.png')
character_down = load_image('run_down.png')
character_right = load_image('run_right.png')
character_up = load_image('run_up.png')
character_left = load_image('run_left.png')

Dir = 0

while(1):
    if Dir % 2 > 0:
        Max = 600
    else:
        Max = 800

    frame = 0
    x = 0
    while (x < Max):
        clear_canvas()
        grass.draw(400, 30)
        if Dir == 0:
            character_down.clip_draw(frame * 100, 0, 100, 100, x, 90)
            if x == 400:
                Dir = 5
                x = 0
        elif Dir == 1:
            character_right.clip_draw(0, frame * 100, 100, 100, 770, x)
        elif Dir == 2:
            character_up.clip_draw(frame * 100, 0, 100, 100, 800-x, 570)
        elif Dir == 3:
            character_left.clip_draw(0, frame * 100, 100, 100, 30, 600-x)
        elif Dir == 5:
            character_down.clip_draw(frame * 100, 0, 100, 100, 400 + 200*cos(radians(270 + x)), 290 + 200*sin(radians(270 + x)))
            if x == 360:
                x = 401
                Dir = 0
            
        frame = (frame + 1) % 8
        update_canvas()
        x = x + 10
        delay(0.05)
        get_events()
    if Dir == 3:
        Dir = 0
    else:
        Dir += 1


        

close_canvas()
