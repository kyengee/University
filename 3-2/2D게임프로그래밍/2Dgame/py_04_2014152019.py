from turtle import * 


def draw_(long,degree):
    width(long)
    if long < 4:
        color("#FF33FF")
    else:
        color("#A0AFFF")
        
    if long > 0:
        down()
        seth(heading()+degree)
        forward(long*7)

        draw_(long-1,-25)
        draw_(long-1,25)

        up()
        back(long*7)
        seth(heading()-degree)


speed(0)
draw_(8,90)
        
    
