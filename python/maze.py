#Hopfield and DAM class

import numpy as np
from PIL import Image
from os import listdir

from skimage.color import rgb2gray
from skimage.transform import resize

from matplotlib import pyplot as plt

#from helper import *

import numpy as np
from PIL import Image
from os import listdir

from skimage.color import rgb2gray
from skimage.transform import resize

from matplotlib import pyplot as plt

import networkx as nx
import random

def graphGen(xDim, yDim):
    #directed graph of Win/Lose/Draw Conditions
    #e.g. rock -> scissors
    winStrats = nx.DiGraph()
    for i in range(1, xDim-1):
        for l in range(1, yDim-1):
            winStrats.add_edges_from([((i,l), (i-1,l))])
            winStrats.add_edges_from([((i,l), (i+1,l))])
            winStrats.add_edges_from([((i,l), (i,l+1))])
            winStrats.add_edges_from([((i,l), (i,l-1))])

            winStrats.add_edges_from([((i-1,l), (i,l))])
            winStrats.add_edges_from([((i+1,l), (i,l))])
            winStrats.add_edges_from([((i,l+1), (i,l))])
            winStrats.add_edges_from([((i,l-1), (i,l))])
    #winStrats.add_edges_from([((1,1), (1,2)),((1,1), (1,0)), ((1,1), (0,1))])

    #elif(playerChoice, compChoice) in winStrats.out_edges(playerChoice):

    return winStrats

def mazeMaker(graph, location):

#while  len(graph.out_edges(location)) > 1:
    #print(location, location[0])
    
    butt = graph.out_edges(location)
    #print(location, butt)
    cut = []
    for i in butt:
        cut.append(i[1])
    #print("CUT"+str(cut))

    for i in cut:
        if len(graph.out_edges(i)) < 4:
            cut.remove(i)

    random.shuffle(cut)

    for i in cut:
        try:
            print(len(graph.out_edges(i)))
            if len(graph.out_edges(i)) < 4:
                continue
            graph.remove_edge(location, i)
            graph.remove_edge(i, location)
            graph = mazeMaker(graph, i)
        except:
            True

    return graph


xDim = 20
yDim = 20

#print([i for i in range(1, 50)])
graph = graphGen(xDim, yDim)
print(graph)
walls = mazeMaker(graph, (1,1))
print(walls)


paths = graphGen(xDim, yDim)
#paths.add_edges_from([((i,l), (i-1,l))])

for i in range(1, xDim-1):
    for l in range(1, yDim-1):
        wallPoints = walls.out_edges((i,l))
        for w in wallPoints:
            paths.remove_edge(w[0], w[1])
        

for i in range(1, xDim):
    for l in range(1, yDim):
        #print(paths.out_edges((i,l)))
        for p in walls.out_edges((i,l)):
            x = [p[0][0], p[1][0]]
            y = [p[0][1], p[1][1]]

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
        for p in paths.out_edges((i,l)):
            x = [p[0][0], p[1][0]]
            y = [p[0][1], p[1][1]]
            plt.plot(x, y, color="green")
plt.show()