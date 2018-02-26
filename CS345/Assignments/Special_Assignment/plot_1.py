import numpy as np
import matplotlib.pyplot as plt
#import matplotlib.pyplot.scatter as plt'''

'''with open('on.txt') as f:
    lines = f.readlines()
    x = [line.split(' ')[0] for line in lines]
   # y = [line.split()[1] for line in lines]
    z = [line.split(' ')[3] for line in lines]
   ''' 
with open('on.txt') as f:
    lines = f.readlines()
    a = [line.split(' ')[0] for line in lines]
    #b = [line.split()[1] for line in lines]
    c = [line.split(' ')[1] for line in lines]

fig = plt.figure()

ax1 = fig.add_subplot(111)

ax1.set_title("Plot title")    
ax1.set_xlabel('x label')
ax1.set_ylabel('y label')

ax1.plot(x,z, c='r')
#ax1.plot(a,c, c='b', label='SCD')

leg = ax1.legend()

plt.show()

'''import numpy as np
import matplotlib.pyplot as plt
#import plotly.plotly as py  # tools to communicate with Plotly's server

alpha = plt.figure()

data = [i for i in range(8) for j in range(np.random.randint(10))]
#x, y = np.array(data), np.array(data)
plt.scatter(x, z, alpha=.1, s=4)
plt.show()

#plot_url = py.plot_mpl(alpha, filename='mpl-docs/alpha')'''
