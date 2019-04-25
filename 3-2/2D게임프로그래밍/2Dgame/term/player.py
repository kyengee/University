from pico2d import *
import game_framework
import random
import Wepon
import game_world

MouseX = None
MouseY = None

IDLE_LEFT = 0
IDLE_RIGHT = 1
ATTACK_RIGHT = 2
ATTACK_LEFT = 3
ATTACK = 0

class  Player:
    blood = None
    bloodnone = None
    ranges = None
    def __init__(self):
        print("Creating..")
        global MouseX, MouseY
        MouseX, MouseY = 150,150
        if(Player.blood is None):
            Player.blood = load_image('./res/blood.png')
            Player.bloodnone = load_image('./res/bloodnone.png')
            Player.ranges = load_image('./res/range.png')
        self.x = 150;
        self.y = 150;
        self.image = load_image('./res/Playermap.png')
        self.frame = 0
        self.top = 35
        self.bottom = 30
        self.right = 25
        self.left = 15
        self.speed = 5;
        self.health = 70;
        self.wepon = Wepon.stick()
        game_world.add_object(self.wepon,game_world.layer_obstacle)
        self.wepon.chosen = 1
        self.state = IDLE_LEFT
        self.gotox = 0
        self.gotoy = 0

    def draw(self):
        if self.state == IDLE_LEFT: 
            self.image.clip_draw(int(self.frame) * 100, 0, 100, 100, self.x, self.y)
        elif self.state == IDLE_RIGHT: 
            self.image.clip_draw(int(self.frame) * 100, 100, 100, 100, self.x, self.y)
        elif self.state == ATTACK_LEFT: 
            self.image.clip_draw(int(self.frame) * 100, 300, 100, 100, self.x, self.y)
        elif self.state == ATTACK_RIGHT: 
            self.image.clip_draw(int(self.frame) * 100, 200, 100, 100, self.x, self.y)

        self.bloodnone.draw_to_origin(self.x-35,self.y+40,70,3)
        self.blood.draw_to_origin(self.x-35,self.y+40,self.health,3)

        if self.state == IDLE_LEFT: 
            self.wepon.shape.clip_draw(0, 0, 100, 300, self.x + 10, self.y ,25,80)
        elif self.state == IDLE_RIGHT: 
            self.wepon.shape.clip_draw(0, 0, 100, 300, self.x - 7, self.y ,25,80)
        elif self.state == ATTACK_LEFT: 
            self.wepon.shape.rotate_draw(75/180.0*3.141592, self.x - 40, self.y ,25,80)
        elif self.state == ATTACK_RIGHT: 
            self.wepon.shape.rotate_draw(285/180.0*3.141592, self.x + 40, self.y ,25,80)

        Player.ranges.rotate_draw(math.atan2(self.y - MouseY, self.x - MouseX), self.x, self.y ,self.wepon.distance*1.5,10)

    def update(self):
        global MouseX,MouseY,ATTACK
        self.frame = (self.frame + 0.2) % 5


        if ATTACK == 1:
            if(self.state < 2):
                lengthX = MouseX - self.x
                lengthY = MouseY - self.y
                dist = math.sqrt(lengthX ** 2 + lengthY ** 2) 
                self.gotox = self.x + self.wepon.distance * lengthX/ dist
                self.gotoy = self.y + self.wepon.distance * lengthY/ dist
                if self.x < self.gotox:
                    self.state  = ATTACK_RIGHT
                else:
                    self.state = ATTACK_LEFT

            lengthX = self.gotox - self.x
            lengthY = self.gotoy - self.y
            dist = math.sqrt(lengthX ** 2 + lengthY ** 2) 

            if dist > self.wepon.speed:
                self.x += self.wepon.speed * lengthX/ dist 
                self.y += self.wepon.speed * lengthY/ dist
            else:
                 self.x = self.gotox
                 self.y = self.gotoy
                 ATTACK = 0

        else:
            if(MouseX < self.x):
                self.state = IDLE_LEFT
            else:
                self.state = IDLE_RIGHT

    def handle_events(self,e):
        global MouseX,MouseY
        for event in e:
            if event.type == SDL_KEYDOWN:
                if self.wepon.__class__.__name__ is 'ice':
                    self.wepon.check(event.key)
            elif event.type == SDL_MOUSEMOTION:
                MouseX,MouseY = event.x, get_canvas_height() - event.y
            elif event.type == SDL_MOUSEBUTTONDOWN:
                if not self.wepon.__class__.__name__ is 'ice':
                    self.wepon.check()



