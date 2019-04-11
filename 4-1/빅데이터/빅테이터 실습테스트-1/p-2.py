def read_file(file, Dict):
	while True:
		string = file.readline()
		if not string: break
		sub_strings = string.split()
		Dict[sub_strings[0]] = int(sub_strings[1])

stock_dict = {}
f1 = open('stock.txt', 'r')
read_file(f1, stock_dict)
f1.close()

input_file = input('보유 주식 파일을 입력하시오 : ')

f2 = open(input_file, 'r')
myDict = {}
read_file(f2, myDict)
f2.close()

for i in myDict.keys():
	myDict[i] = myDict[i] * stock_dict[i]

total = 0
for i in myDict.values():
	total += i

Sorted_dict = sorted(myDict, key = lambda k : myDict[k], reverse = True)

print('총 보유금액 : ', total)
print('보유금액 순 종목명 : ',Sorted_dict)


