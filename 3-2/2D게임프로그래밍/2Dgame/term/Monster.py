from pico2d import * # C:\Users\enjcat\AppData\Local\Programs\Python\Python36\lib\site-packages\pico2d
import game_framework
import random
import game_world
import random
import player
import Main
RIGHT = 1
LEFT = -1



class Monster:
    blood = None
    bloodnone = None
    def __init__(self):
        print("Creating..")
        if(blood is None):
            Monster.blood = load_image('./res/blood.png')
            Monster.bloodnone = load_image('./res/bloodnone.png')
    def draw(self):
        if self.dir == 1:
            self.image.clip_draw(self.frame * 100, 0, 100, 100, self.x, self.y)
        else:
            self.image.clip_composite_draw(self.frame * 100, 0, 100, 100, 0, 'h', self.x, self.y)

    def update(self):
        Player_ob = game_world.objects_at_layer(game_world.layer_player)
        Player_ob = next(Player_ob, None)
        if Player_ob.health <= 0:
            game_framework.pop_state()

        lengthX = Player_ob.x - self.x
        lengthY = Player_ob.y - self.y
        dist = math.sqrt(lengthX ** 2 + lengthY ** 2) 

        if Player_ob.state >= 2:
            if(dist < Player_ob.wepon.range):
                self.speed = self.Maxspeed * -5
                self.health -= Player_ob.wepon.damage

        if dist > 0:
            self.x += self.speed * lengthX/ dist 
            self.y += self.speed * lengthY/ dist
        if(Player_ob.x < self.x):
            self.dir = RIGHT
        else:
            self.dir = LEFT

        #colide
        if (Player_ob.state < 2):
            if(self.dir == LEFT):
                left ,right = (self.x - self.right), (self.x + self.left)
            else:
                left ,right = (self.x - self.left), (self.x + self.right)
            if(Player_ob.state == player.IDLE_LEFT):
                Tleft ,Tright = (Player_ob.x - Player_ob.right), (Player_ob.x + Player_ob.left)
            elif (Player_ob.state == player.IDLE_RIGHT):
                Tleft ,Tright = (Player_ob.x - Player_ob.left), (Player_ob.x + Player_ob.right)

            if (left < Tright and right > Tleft and
                (self.y+self.top)  > (Player_ob.y-Player_ob.bottom) and 
                (self.y-self.bottom) < (Player_ob.y+Player_ob.top)):
                    self.speed = self.Maxspeed * -5
                    Player_ob.health -= self.damage
                    

        if(self.speed != self.Maxspeed):
            self.speed += 1
        if self.health <= 0:
            game_world.remove_object(self)
            



class Tums:
    image = None
    def __init__(self):
        print("Creating..")
        Start_rocation(self)
        if Tums.image is None:
            Tums.image = load_image('./res/Tums.png')
        self.frame = 0
        self.Maxspeed = 2
        self.speed = 2
        self.top = 65
        self.bottom = 70
        self.right = 55
        self.left = 60
        self.dir = 1
        self.health = 40
        self.damage = 7
    def draw(self):
        if self.dir == 1:
            Tums.image.clip_draw(int(self.frame) * 150, 0, 150, 150, self.x, self.y)
        else:
            Tums.image.clip_composite_draw(int(self.frame) * 150, 0, 150, 150, 0, 'h', self.x, self.y,150,150)
        
        Monster.bloodnone.draw_to_origin(self.x-20,self.y+70,40,3)
        Monster.blood.draw_to_origin(self.x-20,self.y+70,self.health,3)
    def update(self):
        self.frame = (self.frame + 0.35) % 5
        Monster.update(self)

class Demon:
    image = None
    def __init__(self):
        print("Creating..")
        Start_rocation(self)
        if Demon.image is None:
            Demon.image = load_image('./res/Demon.png')
        self.frame = 0
        self.Maxspeed = 4
        self.speed = 4
        self.top = 80
        self.bottom = 80
        self.right = 35
        self.left = 40
        self.dir = 1
        self.health = 30
        self.damage = 5
    def draw(self):
        if self.dir == 1:
            Demon.image.clip_draw(int(self.frame) * 100, 0, 100, 200, self.x, self.y)
        else:
            Demon.image.clip_composite_draw(int(self.frame) * 100, 0, 100, 200, 0, 'h', self.x, self.y,100,200)
        self.frame = (self.frame + 0.5) % 2

        Monster.bloodnone.draw_to_origin(self.x-15,self.y+85,30,3)
        Monster.blood.draw_to_origin(self.x-15,self.y+85,self.health,3)
    def update(self):
        Monster.update(self)

class Imp:
    image = None
    def __init__(self):
        print("Creating..")
        Start_rocation(self)
        if Imp.image is None:
            Imp.image = load_image('./res/Imp.png')
        self.frame = 0
        self.Maxspeed = 3
        self.speed = 3
        self.top = 15
        self.bottom = 35
        self.right = 35
        self.left = 30
        self.dir = 1
        self.health = 15
        self.damage = 3
    def draw(self):
        if self.dir == 1:
            Imp.image.clip_draw(int(self.frame) * 100, 0, 100, 100, self.x, self.y)
        else:
            Imp.image.clip_composite_draw(int(self.frame) * 100, 0, 100, 100, 0, 'h', self.x, self.y,100,100)
        self.frame = (self.frame + 0.5) % 5
        Monster.bloodnone.draw_to_origin(self.x-7.5,self.y+20,15,3)
        Monster.blood.draw_to_origin(self.x-7.5,self.y+20,self.health,3)
    def update(self):
        Monster.update(self)
        
    
        
        




def update():
    global Monster_List
    for Monsters in Monster_List:
        Monsters.update()

def draw():
    global Monster_List
    for Monsters in Monster_List:
        Monsters.draw()
    update_canvas()


def exit():
    for i in game_world.all_objects():
        game_world.remove_object(i)

def pause():
    pass

def resume():
    pass

def Start_rocation(self):
    field_width = get_canvas_width()
    field_height = get_canvas_height()

    side = random.randint(1, 4) # 1=top, 2=left, 3=bottom, 4=right
    if (side == 1): # top
        self.x, self.y = random.randint(0, field_width), 0

    if (side == 2): # left
        self.x, self.y = 0, random.randint(0, field_height)

    if (side == 3): # bottom
        self.x, self.y = random.randint(0, field_width), field_height

    if (side == 4): # right
        self.x, self.y = field_width, random.randint(0, field_height)




if __name__ == '__main__':
    import sys
    game_framework.run(sys.modules[__name__])
