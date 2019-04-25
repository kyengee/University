from pico2d import *
import game_framework
import random
import player
import game_world




class stick:
    shape = None
    target = None
    point = None
    def __init__(self):
        if stick.shape is None:
            stick.shape = load_image('./res/stick.png')
            stick.target = load_image('./res/stick_target.png')
            stick.point = load_image('./res/stick_point.png')
        self.x = random.randint(0,get_canvas_width())
        self.y = random.randint(0,get_canvas_height())
        self.speed = 5
        self.damage = 10
        self.range = 80
        self.distance = 100
        self.target_degree = 24;
        self.point_degree = 30;
        self.chosen = 0

    def update(self):
        self.point_degree += -360 if self.point_degree >= 360 else 7
        if (self.chosen == 0):
            grap(self)

    def draw(self):
        if self.chosen == 1:
            self.target.rotate_draw(self.target_degree/180.0*3.141592, player.MouseX, player.MouseY)
            self.point.rotate_draw(self.point_degree/180.0*3.141592, player.MouseX, player.MouseY)
        else:
            stick.shape.draw(self.x,self.y,30,90)

    def check(self):
        if((self.target_degree-24)%360 <= self.point_degree and 
            self.point_degree <= self.target_degree+24):
            player.ATTACK = 1
            self.target_degree = random.randint(24,360)
            self.point_degree = random.randint(0,360)



class sword:
    shape = None
    target_base = None
    target = None
    point = None
    def __init__(self):
        if sword.shape is None:
            sword.shape = load_image('./res/sword.png')
            sword.target_base = load_image('./res/sword_target_base.png')
            sword.target = load_image('./res/sword_target_point.png')
            sword.point = load_image('./res/sword_point.png')
        self.x = random.randint(0,get_canvas_width())
        self.y = random.randint(0,get_canvas_height())
        self.speed = 8
        self.damage = 15
        self.range = 80
        self.distance = 150
        self.target_x = 0
        self.point_x = 0
        self.point_dir = 5
        self.chosen = 0

    def update(self):
        self.point_dir = -3 if self.point_x >= 50 else (3 if self.point_x <= -50 else self.point_dir)
        self.point_x += self.point_dir
        if (self.chosen == 0):
            grap(self)

    def draw(self):
        if self.chosen == 1:
            self.target_base.draw(player.MouseX, player.MouseY + 5)
            self.target.draw(player.MouseX + self.target_x, player.MouseY + 5)
            self.point.draw(player.MouseX + self.point_x, player.MouseY + 5)
        else:
            sword.shape.draw(self.x,self.y,30,90)

    def check(self):
        if(self.target_x-5 <= self.point_x and 
            self.point_x <= self.target_x+5):
            player.ATTACK = 1
            self.target_x = random.randint(-45,45)
            self.point_x = random.randint(-50,50)


class ice:
    Dict = { 119:0,100:1,115:2,97:3}
    shape = None
    Key = list()
    def __init__(self):
        if ice.shape is None:
            ice.shape = load_image('./res/ice.png')
            ice.Key.append(load_image('./res/ice_one.png'))
            ice.Key.append(load_image('./res/ice_two.png'))
            ice.Key.append(load_image('./res/ice_three.png'))
            ice.Key.append(load_image('./res/ice_four.png'))
        self.x = random.randint(0,get_canvas_width())
        self.y = random.randint(0,get_canvas_height())
        self.speed = 5
        self.damage = 20
        self.range = 90
        self.distance = 200
        self.List = [random.randint(0,3) for i in range(4)]
        self.count = 0
        self.chosen = 0

    def update(self):
        if (self.chosen == 0):
            grap(self)
    def draw(self):
        if self.chosen == 1:
            self.Key[self.List[0]].draw(player.MouseX - 45, player.MouseY + 25,30,30)
            self.Key[self.List[1]].draw(player.MouseX - 15, player.MouseY + 25,30,30)
            self.Key[self.List[2]].draw(player.MouseX + 15, player.MouseY + 25,30,30)
            self.Key[self.List[3]].draw(player.MouseX + 45, player.MouseY + 25,30,30)
        else:
            ice.shape.draw(self.x,self.y,30,90)

    def check(self,key):
        if self.List[self.count] == ice.Dict[key]:
            self.count += 1
        else:
            self.List = [random.randint(0,3) for i in range(4)]
            self.count = 0
        if self.count == 4:
            player.ATTACK = 1
            self.List = [random.randint(0,3) for i in range(4)]
            self.count = 0


class fire:
    shape = None
    target_base = None
    target = None
    point = None
    def __init__(self):
        if fire.shape is None:
            fire.shape = load_image('./res/fire.png')
            fire.target_base = load_image('./res/fire_target_base.png')
            fire.target = load_image('./res/fire_target_point.png')
            fire.point = load_image('./res/fire_point.png')
        self.x = random.randint(0,get_canvas_width())
        self.y = random.randint(0,get_canvas_height())
        self.speed = 20
        self.damage = 20
        self.range = 90
        self.distance = 200
        self.target_y = 0
        self.point_y = 0
        self.point_dir = 3
        self.chosen = 0

    def update(self):
        self.point_dir = -3 if self.point_y >= 50 else (3 if self.point_y <= -50 else self.point_dir)
        self.point_y += self.point_dir
        if (self.chosen == 0):
            grap(self)

    def draw(self):
        if self.chosen == 1:
            self.target_base.draw(player.MouseX - 10, player.MouseY)
            self.target.draw(player.MouseX - 10, player.MouseY + self.target_y)
            self.point.draw(player.MouseX - 10, player.MouseY + self.point_y)
        else:
            fire.shape.draw(self.x,self.y,30,90)

    def check(self):
        if(self.target_y-7.5 <= self.point_y and 
            self.point_y <= self.target_y+7.5):
            player.ATTACK = 1
            self.target_y = random.randint(-45,45)
            self.point_y = random.randint(-50,50)

class wand:
    shape = None
    target = None
    point = None
    def __init__(self):
        if wand.shape is None:
            wand.shape = load_image('./res/wand.png')
            wand.target = load_image('./res/wand_target.png')
            wand.point = load_image('./res/wand_point.png')
        self.x = random.randint(0,get_canvas_width())
        self.y = random.randint(0,get_canvas_height())
        self.speed = 30
        self.damage = 25
        self.range = 95
        self.distance = 300
        self.target_degree = 10;
        self.point_degree = 30;
        self.chosen = 0

    def update(self):
        self.point_degree += -360 if self.point_degree >= 360 else 7
        if (self.chosen == 0):
            grap(self)

    def draw(self):
        if self.chosen == 1:
            self.target.rotate_draw(self.target_degree/180.0*3.141592, player.MouseX, player.MouseY)
            self.point.rotate_draw(self.point_degree/180.0*3.141592, player.MouseX, player.MouseY)
        else:
            wand.shape.draw(self.x,self.y,30,90)

    def check(self):
        if((self.target_degree-10)%360 <= self.point_degree and 
            self.point_degree <= self.target_degree+10):
            player.ATTACK = 1
            self.target_degree = random.randint(10,360)
            self.point_degree = random.randint(0,360)

class heal:
    shape = None
    def __init__(self):
        if heal.shape is None:
            heal.shape = load_image('./res/heal.png')
        self.x = random.randint(0,get_canvas_width())
        self.y = random.randint(0,get_canvas_height())

    def update(self):
        Player_ob = game_world.objects_at_layer(game_world.layer_player)
        Player_ob = next(Player_ob, None)

        lengthX = Player_ob.x - self.x
        lengthY = Player_ob.y - self.y
        dist = math.sqrt(lengthX ** 2 + lengthY ** 2) 
        if(dist < 40):
            Player_ob.health += 20
            game_world.remove_object(self)

    def draw(self):
            heal.shape.draw(self.x,self.y,30,30)


def grap(self):
    Player_ob = game_world.objects_at_layer(game_world.layer_player)
    Player_ob = next(Player_ob, None)
    lengthX = Player_ob.x - self.x
    lengthY = Player_ob.y - self.y
    dist = math.sqrt(lengthX ** 2 + lengthY ** 2) 
    if(dist < 40):
        game_world.remove_object(Player_ob.wepon)
        Player_ob.wepon = self
        self.chosen = 1