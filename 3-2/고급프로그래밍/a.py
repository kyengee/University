#for i in range(2,10):
#    for j in range(1,10):
#        print(i,' x ',j,' = ', i*j)

#i = 2
#j = 1

#while(i < 10):
#    while(j < 10):
#        print(i,' x ',j,' = ', i*j)
#        j = j+1
#    j=1
#    i= i+1

### 메소드에 의한 구현
import time
import threading
class RacingCar:
    carName=""

    def __init__ (self, name):
        self.carName = name

    def runCar (self) :
        while True :### for i in range (0, 3):
            carStr = self.carName
            print (carStr, end='')
            time.sleep (0.1)

if __name__ == "__main__" :
    car1 = RacingCar ("한국산업기술대학교\n")
    car2 = RacingCar ("컴퓨터공학과\n")
    car3 = RacingCar ("홍길동\n")
    thd1 = threading.Thread (target=car1.runCar)
    thd2 = threading.Thread (target=car2.runCar)
    thd3 = threading.Thread (target=car3.runCar)

    thd1.start ()
    thd2.start ()
    thd3.start ()

