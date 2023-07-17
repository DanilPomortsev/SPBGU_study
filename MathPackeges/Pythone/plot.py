import matplotlib.pyplot as plt
import numpy as np

#x = [-1, 2, 3]
#y = [-2, 4, 6]

#plt.plot(x, y)
#plt.show()

#plt.plot([1, 2, 3, 4, 5], [1, 2, 3, 4, 5])
#plt.xlabel("x")
#plt.ylabel("y")
#plt.grid()
#plt.show()

# x = np.linspace(0, 10, 50)
# y = x**2+2*x+1
# plt.xlabel("x")
# plt.ylabel("y")
# plt.grid()
# plt.plot(x, y)
# plt.show()

# plt.figure(figsize=(4, 4))
# x = np.linspace(0, 10, 50)
# y = x**2+2*x+1
# y_2 = x**3+4*x**2
# plt.xlabel("x")
# plt.ylabel("y")
# plt.grid()
# plt.plot(x, y, x,y_2)
# plt.show()


#x = np.linspace(0, 10, 50)
#y = x**2+2*x+1
#y_2 = x**3+4*x**2
#plt.figure(figsize=(8, 8))
#plt.subplot(3, 1, 1)
#plt.plot(x, y)
#plt.xlim (1, 15)
#plt.ylim (1, 30)
#plt.grid()
#plt.subplot(3, 1, 2)
#plt.plot(x, y_2)
#plt.xlim (1, 15)
#plt.ylim (1, 30)
#plt.grid()
#plt.show()


fig, ax = plt.subplots()

A = [np.random.randint(0, 100), np.random.randint(0, 100), np.random.randint(0, 100), np.random.randint(0, 100), np.random.randint(0, 100), np.random.randint(0, 100)]
B = [np.random.randint(0, 100), np.random.randint(0, 100), np.random.randint(0, 100), np.random.randint(0, 100), np.random.randint(0, 100), np.random.randint(0, 100)]

ax.scatter (A, B)
ax.set_facecolor('red')
plt.xlim (0, 100)
plt.ylim (0, 100)

plt.show()