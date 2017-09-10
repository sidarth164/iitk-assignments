import numpy as np
import matplotlib.pyplot as plt
y=np.linspace(-2,2,100)
x=[0.5]*100
plt.plot(x,y,color='black',ls='dashed')
plt.plot(0,1,marker='o',color='red')
plt.text(-0.3,1,r'(0,1)')
plt.plot(1,0,marker='o',color='green')
plt.text(1,-0.18,r'(1,0)')
plt.axis([-2,2,-2,2])
plt.fill_between(np.asarray(np.linspace(0.5,2,100)),y1=-2,y2=2,color='#98FB98',zorder=0)
plt.fill_between(np.asarray(np.linspace(-2,0.5,100)),y1=-2,y2=2,color='#ffc0cb',zorder=0)
plt.text(0.55,1,"2x-1=0")
plt.margins(0)
plt.axhline(0,color='black')
plt.axvline(0,color='black')
plt.xticks([])
plt.yticks([])
plt.show()
