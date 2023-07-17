import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from mpl_toolkits.mplot3d import axes3d

a,*b = 'hello'
print(a,b)

c,*d = (1,2,3)
print(c,d)

arr = np.arange(1,5)
print(arr)
arr = np.arange(1,100,5)
print(arr)
arr = np.arange(1,10, 0.6)
print(arr)

arr = np.linspace(3,15,10) #от начального до конечногос количеством точек точки выставляются сами
print(arr)

r = np.random.rand(5,5)
print(r)
print(r @ r)
r[r>2] = 0
print(r)

def myfunc(i,j):
    return (i+1)*(j+4-i)
a = np.fromfunction(myfunc, (3,6)) #даём функцию и передаём размерность матрицы, в функцию передаются индексы
print(a)

a = np.arange(1,15)
print(a[3:8:3])#начало, конец, шаг

L = [1,2,3,4]
n = list(map(lambda x: x**2, L))# применяет правило к каждому элементу
print(n)

L = [1,3,2,5,20,21]
print(list(filter(lambda x: x % 2 == 0, L)))

fig = plt.figure()
ax = fig.add_subplot(1,1,1)

fig.set(facecolor = 'green')
ax.set(facecolor =  "red")

ax.set_xlim([-10, 10])
ax.set_ylim([-10, 10])

ax.set_xlabel("ось x")

x = [-3,-2,-1,0,1,2,3]
y = [9,4,1,0,1,4,9]
plt.plot(x,y)

fig, ax = plt.subplots(subplot_kw = {"projection": "3d"})
x = np.arange(-1,1,0.01)
y = np.arange(-1,1,0.01)

X, Y = np.meshgrid(x,y)
Z = X**2  - Y**2

s = ax.plot_wireframe(X,Y,Z, rstride=20, cstride=15)
plt.show()

