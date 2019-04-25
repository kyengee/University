from pico2d import *



def handle_events():
    global running
    global x,y
    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            running = False
        elif event.type == SDL_KEYDOWN:
            if event.key == SDLK_ESCAPE:
                running = False
        elif event.type == SDL_MOUSEMOTION:
            x,y = event.x, 600 - event.y


open_canvas()

running = True
grass = load_image('grass.png')
character = load_image('run_animation.png')

frame = 0
x = 0
y = 0
currntX = 0
currntY = 0
speed = 5
while (x < 800 and running):
    clear_canvas()
    grass.draw(400, 30)
    lengthX = x - currntX
    lengthY = y - currntY
    if lengthX < 0:
        PathX = -1
    else:
        PathX = 1
        
    if lengthY < 0:
        PathY = -1
    else:
        PathY = 1

    currntX += speed * PathX
    currntY += speed * PathY

    if lengthX*PathX < speed:
        currntX = x
    if lengthY*PathY < speed:
        currntY = y
        
    character.clip_draw(frame * 100, 0, 100, 100, currntX, currntY)
    frame = (frame + 1) % 8
    update_canvas()
    delay(0.05)
    handle_events()


# fill here

close_canvas()
