from pico2d import *
import game_framework
import random
import game_world
import Monster
import player
import Wepon
import BackGround
import Holy
import ui
import Ending

time = None
Impcount = 0
Holycount = 0
Tumscount = 0
Demoncount = 0
size = 0

def handle_events():
    global Angel
    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            game_framework.quit()
        elif event.type == SDL_KEYDOWN:
            if event.key == SDLK_ESCAPE:
                game_framework.pop_state()
            else:
                Angel.handle_events(events)
        elif event.type == SDL_MOUSEMOTION:
            Angel.handle_events(events)
        elif event.type == SDL_MOUSEBUTTONDOWN:
            Angel.handle_events(events)
            




def enter():
    global Angel,time
    resize_canvas(500,500)
    time = (get_time()//1)
    bg = BackGround.BackGround()
    Angel = player.Player()
    tower = Holy.Tower()
    game_world.add_object(bg,game_world.layer_bg)
    game_world.add_object(Angel,game_world.layer_player)
    if(Monster.Monster.blood is None):
        Monster.Monster.blood = load_image('./res/blood.png')
        Monster.Monster.bloodnone = load_image('./res/bloodnone.png')

    game_world.add_object(tower,game_world.layer_tw)

def update():
    global time,Impcount,Holycount,Tumscount,Demoncount,size
    delay(0.03)
    tw = game_world.objects_at_layer(game_world.layer_tw)
    tw = next(tw, None)
    time = (get_time()//1)
    if(time < 60):
        if(time%10== 0 and Impcount == 0):
            game_world.add_object(Monster.Imp(),game_world.layer_monster)
            Impcount = 1
        if(time%10== 9 and Impcount == 1):
            Impcount = 0
        if(time%20== 0 and Holycount == 0):
            tw.pop()
            Holycount = 1
        if(time%20== 19 and Holycount == 1):
            Holycount = 0
    elif(time < 180):
        if(size == 0):
            resize_canvas(800,600)
            size = 1
        if(time%5== 0 and Impcount == 0):
            game_world.add_object(Monster.Imp(),game_world.layer_monster)
            Impcount = 1
        if(time%5== 4 and Impcount == 1):
            Impcount = 0
        if(time%30== 0 and Holycount == 0):
            tw.pop()
            Holycount = 1
        if(time%30== 29 and Holycount == 1):
            Holycount = 0
        if(time%20== 0 and Tumscount == 0):
            game_world.add_object(Monster.Tums(),game_world.layer_monster)
            Tumscount = 1
        if(time%20== 19 and Tumscount == 1):
            Tumscount = 0
    elif(time < 300):
        if(size == 1):
            resize_canvas(1000,800)
            size = 2
        if(time%3== 0 and Impcount == 0):
            game_world.add_object(Monster.Imp(),game_world.layer_monster)
            Impcount = 1
        if(time%3== 2 and Impcount == 1):
            Impcount = 0
        if(time%30== 0 and Holycount == 0):
            tw.pop()
            Holycount = 1
        if(time%30== 29 and Holycount == 1):
            Holycount = 0
        if(time%10== 0 and Tumscount == 0):
            game_world.add_object(Monster.Tums(),game_world.layer_monster)
            Tumscount = 1
        if(time%10== 9 and Tumscount == 1):
            Tumscount = 0
        if(time%30== 0 and Demoncount == 0):
            game_world.add_object(Monster.Demon(),game_world.layer_monster)
            Demoncount = 1
        if(time%30== 29 and Demoncount == 1):
            Demoncount = 0
    elif(time > 300):
        game_framework.change_state(Ending)





    game_world.update()

def draw():
    clear_canvas()
    game_world.draw()
    update_canvas()


def exit():
    game_world.clear()

def pause():
    pass

def resume():
    pass
if __name__ == '__main__':
    import sys
    game_framework.run(sys.modules[__name__])
