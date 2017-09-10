import numpy as np
import matplotlib.pyplot as plt
x=np.linspace(-2,2,100)
y=3*x-1
plt.plot(x,y,color='black',ls='dashed')
plt.plot(0,1,marker='o',color='red')
plt.text(-0.3,1,r'(0,1)')
plt.plot(1,0,marker='o',color='green')
plt.text(1,-0.18,r'(1,0)')
plt.axis([-2,2,-2,2])
s="3x-y-1=0"
plt.text(0.7,0.7,s)
xlim=np.array(plt.gca().get_xlim())
ylim=np.array(plt.gca().get_ylim())
plt.fill_between(xlim,y1=3*xlim-1,y2=[ylim[0],ylim[0]],color='#98FB98',zorder=0)
plt.fill_between(xlim,y1=3*xlim-1,y2=[ylim[1],ylim[1]],color='#ffc0cb',zorder=0)
plt.margins(0)
plt.axhline(0,color='black')
plt.axvline(0,color='black')
plt.xticks([])
plt.yticks([])
plt.show()
