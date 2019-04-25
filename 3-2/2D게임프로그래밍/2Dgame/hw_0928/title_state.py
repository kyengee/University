from pico2d import *
import game_framework
import boys_state



image = 0

def enter():
    open_canvas()
    global image
    image = load_image('./title.png')
    

def exit():
    close_canvas()

def update():
    update_canvas()

def pause():
    pass

def resume():
    enter()
        

def draw():
        global image
        delay(0.03)
        clear_canvas()
        image.draw(400,300)

def handle_events():
    events = get_events()
    for event in events:
        if event.type == SDL_KEYDOWN:
            if event.key == SDLK_ESCAPE:
                game_framework.quit()
            if event.key == SDLK_SPACE:
                game_framework.push_state(boys_state)

        

