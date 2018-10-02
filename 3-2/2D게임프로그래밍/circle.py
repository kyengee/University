import turtle

def draw_circle(x,y,r):
    turtle.up()
    turtle.goto(x,y)
    turtle.stamp()
    turtle.forward(r)
    turtle.down()
    turtle.left(90)
    turtle.circle(r)

    
turtle.shape("turtle")
draw_circle(0,0,50)
draw_circle(200,200,100)
draw_circle(100,-100,50)
