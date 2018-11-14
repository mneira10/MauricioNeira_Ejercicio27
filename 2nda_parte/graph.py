import numpy as np 
import matplotlib.pyplot as plt 
from os import listdir
from os.path import isfile, join
from scipy.stats import norm

onlyfiles = [f for f in listdir("./") if (isfile(join("./", f)) and f.endswith('.dat'))]
# string for string in list if string.endswith("foo")
data = np.array([])


for f in onlyfiles:
  nums = np.loadtxt(f)
  data = np.concatenate([nums, data])



plt.hist(data,density = True)

mu, std = norm.fit(data)
xmin, xmax = plt.xlim()
x = np.linspace(xmin, xmax, 100)
p = norm.pdf(x, mu, std)
plt.plot(x, p, 'k', linewidth=2)
title = "Fit results: mu = %.2f,  std = %.2f" % (mu, std)
plt.title(title)
# plt.show()
plt.savefig('sample.pdf')
