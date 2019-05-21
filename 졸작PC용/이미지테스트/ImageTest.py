import numpy as np
from itertools import chain

D2array = np.genfromtxt('testImage.txt', encoding='ascii', dtype=None)
D1array = list(chain(*D2array))

D1array = [int(a, 16) for a in D1array]
print(len(D1array))

