from pico2d import *
import random


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
    def __init__(self):
        print("Creating..")
        self.count = 0
        self.Bool = False
        self.x = random.randint(0, 800)
        self.y = random.randint(0, 600)
        self.speed = random.uniform(1.0, 5.0)
        self.frame = random.randint(0, 7)
        self.image = load_image('../res/run_animation.png')
    def draw(self):
        self.image.clip_draw(self.frame * 100, 0, 100, 100, self.x, self.y)
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
        else:
            PathX = 1
            
        if lengthY < 0:
            PathY = -1
        else:
            PathY = 1

        if dist > 0:
            self.x += self.speed * lengthX/ dist 
            self.y += self.speed * lengthY/ dist
            

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
            running = False
        elif event.type == SDL_KEYDOWN:
            if event.key == SDLK_ESCAPE:
                running = False
        elif event.type == SDL_MOUSEMOTION:
             gloX,gloY = event.x, 600 - event.y
        elif event.type == SDL_MOUSEBUTTONDOWN:
            DirList.append(Dot(event.x, 600-event.y))
            print(DirList)
            index += 1
       
        
            
open_canvas()

DirList = []

index = 0

running = True

gloX,gloY = 0,0

Grass_ = Grass()

boys = [ Boy() for i in range(20) ]

while running:
    handle_events()

    for boy in boys:
        boy.update()

    clear_canvas()
    Grass_.draw()
    for boy in boys:
        boy.draw()
    update_canvas()

    delay(0.05)

close_canvas()


