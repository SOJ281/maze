#include <iostream>
#include <string>
#include <map>
using namespace std;
#include <cmath>
#include <vector>

#include <algorithm>
#include <random>

#include <cstdint> // for specific size integers
#include <fstream> // for file handling

#include <stdexcept>

pair<int, int> mp(int x, int y) {
    return make_pair(x,y);
}

void deleteEdge(map<pair<int, int>, vector<pair<int, int>>> * graph, pair<int, int> * first, pair<int, int> * second) {
    (*graph)[(*first)].erase(remove((*graph)[(*first)].begin(), (*graph)[(*first)].end(), (*second)), (*graph)[(*first)].end());
    (*graph)[(*second)].erase(remove((*graph)[(*second)].begin(), (*graph)[(*second)].end(), (*first)), (*graph)[(*second)].end());
}

void deleteItem(vector<pair<int, int>> * array, pair<int, int> *item) {
    (*array).erase(std::remove((*array).begin(), (*array).end(), (*item)), (*array).end());
}

int pairsEqual(pair<int, int> *a, pair<int, int> *b) {
    if (((*a).first == (*b).first) && ((*a).second == (*b).second)) {
        return 1;
    }
    return 0;
}

int searchVector(vector<pair<int, int>> * array, pair<int, int> *(item)) {
    for (int i = 0; i < (*array).size(); i++) {
        if (((*item).first == (*array)[i].first) && ((*item).second == (*array)[i].second)) {
            return 1;
        }
    }
    return 0;
}

map<pair<int, int>, vector<pair<int, int>>> graphGen(int xDim, int yDim) {

    map<pair<int, int>, vector<pair<int, int>>> winStrats;

    //std::map< std::pair<int, int>, string> testMap;
    //testMap[std::make_pair(1,3)] = "Hello";

    //winStrats[make_pair(1,2)][0] = {};
    for (int x = 0; x < xDim; x++) {
        for (int y = 0; y < yDim; y++) {
            winStrats[mp(x,y)] = {};
        }
    }

    for (int x = 0; x < xDim; x++) {
        for (int y = 0; y < yDim; y++) {
            //winStrats[make_pair(x,y)] = {};
            
            if (y>0) {
                winStrats[mp(x,y)].push_back(mp(x,y-1));
            }
            if (y < yDim-1) {
                winStrats[mp(x,y)].push_back(mp(x,y+1));
            }
            if (x > 0) {
                winStrats[mp(x,y)].push_back(mp(x-1,y));
            }
            if (x < xDim-1) {
                winStrats[mp(x,y)].push_back(mp(x+1,y));
            }
            /*
            winStrats[mp(x,y)].push_back(mp(x,y-1));
            winStrats[mp(x,y)].push_back(mp(x,y+1));
            winStrats[mp(x,y)].push_back(mp(x-1,y));
            winStrats[mp(x,y)].push_back(mp(x+1,y));
            */

            shuffle(begin(winStrats[mp(x,y)]), end(winStrats[mp(x,y)]), default_random_engine { random_device {}()});
        }
    }
    return winStrats;
}

void makePic(map<pair<int, int>, vector<pair<int, int>>> walls, int xDim, int yDim, string name, map<pair<int, int>, vector<pair<int, int>>> paths, vector<pair<int, int>> solution) {
    vector<int> row(xDim*2+1, 0);
    vector<vector<int>> trueMaze(yDim*2+1, row);


    for (int x = 0; x < xDim*2+1; x++) {
        for (int y = 0; y < yDim*2+1; y++) {
            trueMaze[x][y] = 0;
        }
    }
    int color = 255;
    for (int x = 0; x < xDim; x++) {
        for (int y = 0; y < yDim; y++) {
            int Xloc = x*2+1;
            int YLoc = y*2+1;
            
            vector<pair<int, int>> loca = paths[mp(x, y)];

            color = 255;
            pair<int, int> s = mp(x,y);
            if (searchVector(&solution, &s))
                color = 100;

            trueMaze[x*2+1][y*2+1] = color;


            auto it = find(loca.begin(), loca.end(), mp(x-1, y));
            if (it!=loca.end())
                trueMaze[Xloc -1][YLoc] = color;
            
            auto itt = find(loca.begin(), loca.end(), mp(x+1, y));
            if (itt!=loca.end())
                trueMaze[Xloc + 1][YLoc] = color;

            auto iy = find(loca.begin(), loca.end(), mp(x, y-1));
            if (iy!=loca.end())
                trueMaze[Xloc][YLoc - 1] = color;
            
            auto iyy = find(loca.begin(), loca.end(), mp(x, y+1));
            if (iyy!=loca.end())
                trueMaze[Xloc][YLoc + 1] = color;

        }
    }

    ofstream img (name+".ppm");
    img << "P3" << endl;
    img << (xDim*2+1) << " " << (yDim*2+1) << endl;
    img << "255" << endl;

    for (int x = 0; x < xDim*2+1; x++) {
        for (int y = 0; y < yDim*2+1; y++) {
            img << trueMaze[x][y] << " " << trueMaze[x][y] << " " << trueMaze[x][y] << endl;
        }
    }
}

void makePic(map<pair<int, int>, vector<pair<int, int>>> walls, int xDim, int yDim, string name) {
    map<pair<int, int>, vector<pair<int, int>>> paths = graphGen(xDim, yDim);
    
    for (int i = 0; i < xDim; i++) {
        for (int l = 0; l < yDim; l++) {
            vector<pair<int, int>> wallPoints = walls[mp(i, l)];
            for (auto w : wallPoints) {
                paths[mp(i,l)].erase(remove(paths[mp(i,l)].begin(), paths[mp(i,l)].end(), w), paths[mp(i,l)].end());
            }
        }
    }

    vector<int> row(xDim*2+1, 0);
    vector<vector<int>> trueMaze(yDim*2+1, row);


    for (int x = 0; x < xDim*2+1; x++) {
        for (int y = 0; y < yDim*2+1; y++) {
            trueMaze[x][y] = 0;
        }
    }
    for (int x = 0; x < xDim; x++) {
        for (int y = 0; y < yDim; y++) {
            int Xloc = x*2+1;
            int YLoc = y*2+1;
            trueMaze[x*2+1][y*2+1] = 255;
            
            vector<pair<int, int>> loca = paths[mp(x, y)];

            auto it = find(loca.begin(), loca.end(), mp(x-1, y));
            if (it!=loca.end())
                trueMaze[Xloc -1][YLoc] = 255;
            
            auto itt = find(loca.begin(), loca.end(), mp(x+1, y));
            if (itt!=loca.end())
                trueMaze[Xloc + 1][YLoc] = 255;

            auto iy = find(loca.begin(), loca.end(), mp(x, y-1));
            if (iy!=loca.end())
                trueMaze[Xloc][YLoc - 1] = 255;
            
            auto iyy = find(loca.begin(), loca.end(), mp(x, y+1));
            if (iyy!=loca.end())
                trueMaze[Xloc][YLoc + 1] = 255;
        }
    }

    ofstream img (name+".ppm");
    img << "P3" << endl;
    img << (xDim*2+1) << " " << (yDim*2+1) << endl;
    img << "255" << endl;

    for (int x = 0; x < xDim*2+1; x++) {
        for (int y = 0; y < yDim*2+1; y++) {
            img << trueMaze[x][y] << " " << trueMaze[x][y] << " " << trueMaze[x][y] << endl;
        }
    }
}

void mazeMakerPrim(map<pair<int, int>, vector<pair<int, int>>> * graph, pair<int, int> * location) {
    pair<int, int> * currLoc = (pair<int, int>*)malloc(sizeof(pair<int, int>));
    for (int i = 0; i < (*graph)[(*location)].size(); i++) {

        if ((*graph)[(*graph)[(*location)].at(i)].size() < 3) { if ((rand() % 1001 > 5)) {continue;}}
        * currLoc = (*graph)[(*location)].at(i);

        (*graph)[(*currLoc)].erase(remove((*graph)[(*currLoc)].begin(), (*graph)[(*currLoc)].end(), (*location)), (*graph)[(*currLoc)].end());
        (*graph)[(*location)].erase((*graph)[(*location)].begin()+i);
        mazeMakerPrim(graph, currLoc);
        i--;
    }
    free(currLoc);
}

map<pair<int, int>, vector<pair<int, int>>> mazeMakerNonRec(map<pair<int, int>, vector<pair<int, int>>> graph, int xDim, int yDim) {

    for (int x = 1; x < xDim-1; x++) {
        for (int y = 1; y < yDim-1; y++) {
            pair<int, int> location = mp(x,y);
            shuffle(begin(graph[location]), end(graph[location]), default_random_engine { random_device {}()});

            pair<int, int> currLoc = graph[location].at(0);
            graph[currLoc].erase(remove(graph[currLoc].begin(), graph[currLoc].end(), location), graph[currLoc].end());
            graph[location].erase(graph[location].begin());
        }
    }
    return graph;
}

map<pair<int, int>, vector<pair<int, int>>> mazeMakerKruz(map<pair<int, int>, vector<pair<int, int>>> graph, int xDim, int yDim) {
    map<pair<int, int>, int> disconnBits;
    for (int x = 0; x < xDim; x++) {
        for (int y = 0; y < yDim; y++) {
            disconnBits[mp(x,y)] = 4;
        }
    }
    disconnBits[mp(1,1)] = 0;
    vector<pair<int, int>> connectedParts;
    connectedParts.push_back(mp(1, 1));

    shuffle(begin(connectedParts), end(connectedParts), default_random_engine { random_device {}()});
    int found  = 0;
    int eep = connectedParts.size();
    while (1) {
        found  = 0;
        for (int i = 1; i < connectedParts.size()+1; i++) {
            eep = connectedParts.size();
            vector<pair<int, int>> cut = graph[connectedParts[eep-i]];
            shuffle(begin(cut), end(cut), default_random_engine { random_device {}()});
            for (auto loc : cut) {
                if (disconnBits[loc] > 3) {
                    deleteEdge(&graph, &loc, &connectedParts[eep-i]);
                    disconnBits[loc]--;
                    found = 1;
                    connectedParts.push_back(loc);

                }
                if ((disconnBits[loc] > 2) && (rand() % 1001 < 5)) {
                    deleteEdge(&graph, &loc, &connectedParts[eep-i]);
                    disconnBits[loc]--;
                    found = 1;
                    connectedParts.push_back(loc);
                }
            }
            if (found) {break;}
        }
        if (!found) {break;}
    }

    return graph;
}

map<pair<int, int>, vector<pair<int, int>>> mazeMakerWilson(map<pair<int, int>, vector<pair<int, int>>> graph, int xDim, int yDim) {
    map<pair<int, int>, int> disconnBits;
    vector<pair<int, int>> disconnectedParts;
    for (int x = 0; x < xDim; x++) {
        for (int y = 0; y < yDim; y++) {
            disconnBits[mp(x,y)] = 1;
            disconnectedParts.push_back(mp(x, y));
        }
    }

    disconnBits[mp(1,1)] = 0;
    vector<pair<int, int>> connectedParts;
    connectedParts.push_back(mp(1, 1));
    deleteItem(&disconnectedParts, &connectedParts[0]);

    int found  = 0;
    int startLoc = 0;
    int eep = connectedParts.size();
    pair<int, int> start = mp(1, 1);
    pair<int, int> end = mp(3, 3);
    
    while (disconnectedParts.size() > 0) {
        found = 0;
        if (startLoc >= connectedParts.size()+1) {break;}
        start = connectedParts[startLoc];

        while (1) {
            vector<pair<int, int>> cut = graph[start];
            for (auto loc : cut) {
                if (searchVector(&disconnectedParts, &loc)) {
                    deleteEdge(&graph, &loc, &start);
                    start = loc;
                    connectedParts.push_back(start);
                    deleteItem(&disconnectedParts, &start);
                    found = 1;
                    break;
                }
            }

            if (pairsEqual(&start, &end)) {
                startLoc=0;
                shuffle(begin(connectedParts), connectedParts.end(), default_random_engine { random_device {}()});
                if (disconnectedParts.size() > 0) {
                    end = disconnectedParts[rand() % disconnectedParts.size()];
                }
                break;
            }
            //cout << "FOUND?" << endl;
            if (!found) {
                startLoc++;
                break;
            }
            found = 0;
        }

    }

    return graph;
}

map<pair<int, int>, vector<pair<int, int>>> removeDeadEnds(map<pair<int, int>, vector<pair<int, int>>> graph, int xDim, int yDim) {
    pair<int, int> currLoc = mp(1,1);
    for (int x = 0; x < xDim; x++) {
        for (int y = 0; y < yDim; y++) {
            if (graph[mp(x,y)].size() > 2) {
                currLoc = mp(x,y);
                //cout <<graph[mp(x,y)].size() << ",";
                deleteEdge(&graph, &currLoc, &graph[currLoc][0]);
                //break;
                //cout <<graph[mp(x,y)].size() << endl;
            }
        }
    }
    return graph;
}



vector<pair<int, int>> mazeSolver(map<pair<int, int>, vector<pair<int, int>>> * graph, pair<int, int> * location, pair<int, int> * goal, vector<pair<int, int>> * visited) {
    if (pairsEqual(location, goal)) {
        vector<pair<int, int>> path;
        path.push_back(*location);
        return path;
    }

    pair<int, int> * currLoc = (pair<int, int>*)malloc(sizeof(pair<int, int>));

    for (int i = 0; i < (*graph)[(*location)].size(); i++) {
        * currLoc = (*graph)[(*location)].at(i);
        if (searchVector(visited, currLoc)){continue;}
        (*visited).push_back(*currLoc);

        vector<pair<int, int>> possPath = mazeSolver(graph, currLoc, goal, visited);
        if (possPath.size() > 0){
            possPath.push_back(*location);
            return possPath;
        }

    }
    free(currLoc);
    vector<pair<int, int>> noPath;
    return noPath;
}


int main() {
    cout << "Making your maze..." << endl;
    int xDim = 300;
    int yDim = 300;

    cout << "With Pointers! SQUIGLLy (" << xDim << "," << yDim << ")" << endl;
    map<pair<int, int>, vector<pair<int, int>>> walls = graphGen(xDim, yDim);
    cout << "Graph Made!" << endl;
    pair<int, int> location = mp(1,1);
    map<pair<int, int>, vector<pair<int, int>>> nWalls;
    try {
        //mazeMakerPrim(&walls, &location);
        //walls = mazeMakerKruz(walls, xDim, yDim);
        walls = mazeMakerWilson(walls, xDim, yDim);
        nWalls = removeDeadEnds(walls, xDim, yDim);
    } catch (const exception& e) {
        cout << "Exception " << e.what() << endl;
        return 0;
    }
    cout << "MAZED!" << endl;
    
    makePic(walls, xDim, yDim, "Maze");
    makePic(nWalls, xDim, yDim, "MazeUndead");

    cout << "AND Another! YAY!";

    map<pair<int, int>, vector<pair<int, int>>> paths = graphGen(xDim, yDim);
    
    for (int i = 0; i < xDim; i++) {
        for (int l = 0; l < yDim; l++) {
            vector<pair<int, int>> wallPoints = walls[mp(i, l)];
            for (auto w : wallPoints) {
                paths[mp(i,l)].erase(remove(paths[mp(i,l)].begin(), paths[mp(i,l)].end(), w), paths[mp(i,l)].end());
            }
        }
    }
    pair<int, int> start = mp(1,1);

    pair<int, int> goal = mp(xDim-1, yDim-1);
    vector<pair<int, int>> visited;
    visited.push_back(start);

    vector<pair<int, int>> solution = mazeSolver(&paths, &start, &goal, &visited);

    makePic(walls, xDim, yDim, "MazeSolved", paths, solution);

    cout << "PATH FOUND!";

    return 0;
} 