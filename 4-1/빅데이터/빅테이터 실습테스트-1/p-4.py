from matplotlib import pyplot as plt


Dict = {}
f = open('stock.txt', 'r')

while True:
	string = f.readline()
	if not string: break
	a = string.split()
	Dict[a[0]] = int(a[1])
f.close()

key = Dict.keys()
value = Dict.values()

xs = [i + 0.1 for i, _ in enumerate(key)]

plt.bar(xs, value)

plt.xticks([i + 0.1 for i, _ in enumerate(key)], key, rotation = 45)

plt.xlabel('Name')
plt.ylabel('Price')
plt.show()


