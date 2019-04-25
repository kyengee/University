from pico2d import *
import game_framework
import random
import json


class Dot:
    def __init__(self,xDot,yDot):
        self.xDot = xDot
        self.yDot = yDot


class Grass:
    def __init__(grass_):
        grass_.image = load_image('../res/grass.png')
        print(grass_.image)
    def draw(grass_):
        grass_.image.draw(400, 300)

class Boy:
    image = 0
    def __init__(self):
        print("Creating..")
        self.count = 0
        self.state = 3
        self.Bool = False
        self.x = random.randint(0, 800)
        self.y = random.randint(0, 600)
        self.speed = random.uniform(1.0, 5.0)
        self.frame = random.randint(0, 7)
        self.name = 'myname'
    def draw(self):
        Boy.image.clip_draw(self.frame * 100, self.state*100, 100, 100, self.x, self.y)
    def update(self):
        global DirList
        global gloX, gloY
        gloX_, gloY_ = gloX,gloY
        self.frame = (self.frame + 1) % 8
        if DirList:
            if len(DirList) > self.count:
                gloX_ = DirList[self.count].xDot
                gloY_ = DirList[self.count].yDot
                self.Bool = True
            else:
                self.Bool = False
        else:
                self.Bool = False

        lengthX = gloX_ - self.x
        lengthY = gloY_ - self.y

        dist = math.sqrt(lengthX ** 2 + lengthY ** 2) 

        if lengthX < 0:
            PathX = -1
            self.state = 0
        elif lengthX > 0:
            PathX = 1
            self.state = 1
        else:
            PathX = 0
            
        if lengthY < 0:
            PathY = -1
        elif lengthY > 0:
            PathY = 1
        else:
            PathY = 0

        if dist == 0:
            if self.state == 0:
                self.state = 2
            if self.state == 1:
                self.state = 3
            
            

        if lengthX*PathX < self.speed:
            self.x = gloX_
        if lengthY*PathY < self.speed:
            self.y = gloY_

        if self.Bool == True:
            if self.x == DirList[self.count].xDot and self.y == DirList[self.count].yDot:
                self.count += 1


def handle_events():
    global running
    global gloX,gloY
    global index
    global DirList
    global boys
    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            game_framework.quit()
        elif event.type == SDL_KEYDOWN:
            if event.key == SDLK_ESCAPE:
                game_framework.pop_state()
        elif event.type == SDL_MOUSEMOTION:
             gloX,gloY = event.x, 600 - event.y
        elif event.type == SDL_MOUSEBUTTONDOWN:
            DirList.append(Dot(event.x, 600-event.y))
            index += 1
       

DirList=[]
index=0
gloX=0
gloY=0
Grass_=0
boys = []
def enter():    
    open_canvas()
    global DirList, index, running, gloX,gloY,Grass_, boys
    Boy.image = load_image('../res/animation_sheet.png')
    DirList = []
    index = 0
    gloX,gloY = 0,0
    global boys
    file = open('boys_data.json')
    List = json.load(file)
    for e in List['boys']:
        b = Boy()
        b.name = e['name']
        b.x = e['x']
        b.y = e['y']
        b.speed = e['speed']
        boys.append(b)

    Grass_ = Grass()

def update():
    global boys
    for boy in boys:
        boy.update()

def draw():
    delay(0.03)
    global Grass_,boys
    clear_canvas()
    Grass_.draw()
    for boy in boys:
        boy.draw()
    update_canvas()


def exit():
    close_canvas()

def pause():
    pass

def resume():
    pass


if __name__ == '__main__':
    import sys
    game_framework.run(sys.modules[__name__])
    
