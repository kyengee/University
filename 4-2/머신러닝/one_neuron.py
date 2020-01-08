#입력, 바이어스값, 가중치의 초기값은 1
x, b, w = 1, 1, 1
#학습률은 0.1
alpha = 0.1
#타겟Y는 4
Yt = 4

def forward_process(x, b, w):
	sigma = x*w + b
	y = sigma
	return y

def check_error(targetY, realY):
	return (targetY - realY)**2/2

def new_w(w, targetY, realY, x):
	return w - alpha*(realY - targetY)*x


def new_b(b, targetY, realY):
	return b - alpha*(realY - targetY)

while 1:
	Yr = forward_process(x,b,w)
	E = check_error(Yt, Yr)
	if E < 0.001:
		break
	w = new_w(w, Yt, Yr, x)
	b = new_b(b, Yt, Yr)
	print(str(E) + "( " + str(Yt) + " - " + str(Yr) + " )" + " ,w: " + str(w) + " ,b: " + str(b))

	''' 10번 테스트
for i in range(0,10,1):
	Yr = forward_process(x,b,w)
	E = check_error(Yt, Yr)
	w = new_w(w, Yt, Yr, x)
	b = new_b(b, Yt, Yr)
	print(str(i) + "번째 error: " + str(E) + "( " + str(Yt) + " - " + str(Yr) + " )" + " ,w: " + str(w) + " ,b: " + str(b))
'''
