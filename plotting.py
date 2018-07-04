import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation
from scipy.misc import imread
from math import *
fig = plt.figure()

xmin = -30
ymin = -30
xmax = 30
ymax = 30

ax = plt.axes(xlim=(xmin, xmax), ylim=(ymin, ymax))
population = int(input())
temp=[]

def holder(x,y):
    return(-np.abs(np.sin(x)*np.cos(y)*np.exp(np.abs(1-((x*x+y*y)**0.5/pi)))))

def sphere(x,y):
    return(x**2+y**2)

def booths(x,y):
    return((x+2*y-7)**2+(2*x+y-5)**2)

def ackley(x,y):
    return(-20*(np.exp(-0.2*((x*x+y*y)**0.5)))-np.exp(0.5*(np.cos(2*pi*x)+np.cos(2*pi*y)))+e+20) 

X = np.arange(xmin,xmax,0.01)
Y = np.arange(ymin,ymax,0.01)
X_grid,Y_grid = np.meshgrid(X,Y)
Z_grid = holder(X_grid,Y_grid)
plt.contour(X_grid, Y_grid, Z_grid)



for i in range(population):
    temp.append(ax.plot([],[],lw = 4,color = "blue")[0])
temp.append(ax.plot([],[],lw = 8,color = "red")[0])

line = tuple(temp)


def init():
    for i in line:
        i.set_data([],[])
    return line 


try:
    d = list(input().strip().split())
except EOFError:
    print("end")


def animate(i):
    try:
        for j in range(population+1):
            x=[]
            y=[]
            x = np.array(d[(population+1)*2*i+2*j :(population+1)*2*i+2*j+2*(population+1)+1:(population+1)*2],dtype = np.double)
            y = np.array(d[(population+1)*2*i+2*j+1:(population+1)*2*i+2*j+2*(population+1)+2:(population+1)*2],dtype = np.double)
            line[j].set_data(x,y)
        print(holder(x,y),x,y)    

        return line 

    except EOFError:
        print("End")
    
    

anim = animation.FuncAnimation(fig, animate,frames=500, init_func=init,
                                interval=200)


#anim.save('basic_animation.mp4', fps=5, extra_args=['-vcodec', 'libx264'])

plt.show()

