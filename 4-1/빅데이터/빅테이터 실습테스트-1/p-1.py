import sys

inNum = int(sys.argv[1])
count = 3
nums = []

for i in range(inNum,2,-1):
	if count == 0:
		break
	chk = True
	for j in range(2,i):
		if i%j == 0:
			chk = False
			break
	if chk:
		nums.append(i)
		count -= 1


if count != 0:
	print('number is so small')
else:
	print('the biggest prime number up to 10 : ', str(nums[2]),str(nums[1]),str(nums[0]))