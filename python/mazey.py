from matplotlib import pyplot as plt

import numpy as np

from matplotlib import pyplot as plt

import networkx as nx
import random
import copy

class immutable():
    def __init__(self):
        self.array = []
    
    def append(self, item):
        if item not in self.array:
            self.array.append(item)
    
    def remove(self, item):
        self.array.remove(item)
    



def graphGen(xDim, yDim):
    #directed graph of Win/Lose/Draw Conditions
    #e.g. rock -> scissors
    winStrats = nx.DiGraph()
    winStrats = dict()
    for i in range(0, xDim):
        for l in range(0, yDim):
            winStrats[(i,l)] = immutable()

    for i in range(1, xDim-1):
        for l in range(1, yDim-1):
            winStrats[(i,l)].append((i-1,l))
            winStrats[(i,l)].append((i+1,l))
            winStrats[(i,l)].append((i,l-1))
            winStrats[(i,l)].append((i,l+1))

            winStrats[(i-1,l)].append((i,l))
            winStrats[(i+1,l)].append((i,l))
            winStrats[(i,l-1)].append((i,l))
            winStrats[(i,l+1)].append((i,l))

    return winStrats

def mazeMaker(graph, location):

#while  len(graph.out_edges(location)) > 1:
    #print(location, location[0])
    
    cut = copy.deepcopy(graph[location].array)

    random.shuffle(cut)

    for i in cut:
        if len(graph[i].array) < 4:
            continue
        #print(i,len(graph[i].array))
        graph[location].remove(i)
        graph[i].remove(location)
        graph = mazeMaker(graph, i)

    return graph


xDim = 20
yDim = 20

#print([i for i in range(1, 50)])
graph = graphGen(xDim, yDim)
#print(graph)
walls = mazeMaker(graph, (1,1))

#print(walls)
for i in range(1, xDim-1):
    for l in range(1, yDim-1):
        if len(walls[(i,l)].array) > 3:
            print(i,l, walls[(i,l)].array)

paths = graphGen(xDim, yDim)

for i in range(1, xDim-1):
    for l in range(1, yDim-1):
        wallPoints = walls[(i,l)].array
        for w in wallPoints:
            paths[(i,l)].remove(w)
            #paths[w].remove((i,l))
        



for i in range(1, xDim):
    for l in range(1, yDim):
        #print(paths.out_edges((i,l)))
        for p in walls[(i,l)].array:
            x = [i, p[0]]
            y = [l, p[1]]

            midpoint = [(x[0]+x[1])/2, (y[0]+y[1])/2]
            if y[0] == y[1]:
                x1 = [midpoint[0], midpoint[0]]
                y1 = [midpoint[1]-0.5, midpoint[1]+0.5]
                plt.plot(x1, y1, color="black")
            else:
                y1 = [midpoint[1], midpoint[1]]
                x1 = [midpoint[0]-0.5, midpoint[0]+0.5]
                plt.plot(x1, y1, color="black")

#plt.show()

for i in range(1, xDim-1):
    for l in range(1, yDim-1):
        #print(paths.out_edges((i,l)))
        for p in paths[(i,l)].array:
            x = [i, p[0]]
            y = [l, p[1]]
            plt.plot(x, y, color="green")
plt.show()