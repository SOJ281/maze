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

#include <tuple>
//https://en.wikipedia.org/wiki/Hexagonal_Efficient_Coordinate_System
pair<int, int> mp(int x, int y) {
    return make_pair(x,y);
}

tuple<int, int, int> mt(int a, int r, int c) {
    return make_tuple(a, r, c);
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



void deleteItem(vector<tuple<int, int, int>> * array, tuple<int, int, int> *item) {
    (*array).erase(std::remove((*array).begin(), (*array).end(), (*item)), (*array).end());
}

int searchVector(vector<tuple<int, int, int>> * array, tuple<int, int, int> *(item)) {
    for (int i = 0; i < (*array).size(); i++) {
        if ((*item) == (*item)) {
            return 1;
        }
    }
    return 0;
}


void deleteEdge(map<tuple<int, int, int>, vector<tuple<int, int, int>>> * graph, tuple<int, int, int> * first, tuple<int, int, int> * second) {
    (*graph)[(*first)].erase(remove((*graph)[(*first)].begin(), (*graph)[(*first)].end(), (*second)), (*graph)[(*first)].end());
    (*graph)[(*second)].erase(remove((*graph)[(*second)].begin(), (*graph)[(*second)].end(), (*first)), (*graph)[(*second)].end());
}

map<tuple<int, int, int>, vector<tuple<int, int, int>>> graphGen(int xDim, int yDim) {
    map<tuple<int, int, int>, vector<tuple<int, int, int>>> winStrats;

    for (int a = 0; a < 2; a++) {
        for (int r = 0; r < xDim; r++) {
            for (int c = 0; c < yDim; c++) {
                winStrats[mt(a,r,c)] = {};
            }
        }
    }

    for (int a = 0; a < 2; a++) {
        for (int r = 0; r < xDim; r++) {
            for (int c = 0; c < yDim; c++) {
                if (c > 0) {
                    winStrats[mt(a,r,c)].push_back(mt(a,r,c-1));
                }
                if (c < yDim-1) {
                    winStrats[mt(a,r,c)].push_back(mt(a,r,c+1));
                }


                if (r > 0) {
                    winStrats[mt(a,r,c)].push_back(mt(1-a, r-(1-a), c-(1-a)));
                }
                if (r < xDim-1) {
                    winStrats[mt(a,r,c)].push_back(mt(1-a, r-(1-a), c+a));
                }

                if (r > 0) {
                    winStrats[mt(a,r,c)].push_back(mt(1-a, r+a, c-(1-a)));
                }
                if (r < xDim-1) {
                    winStrats[mt(a,r,c)].push_back(mt(1-a, r+a, c+a));
                }

                shuffle(begin(winStrats[mt(a,r,c)]), end(winStrats[mt(a,r,c)]), default_random_engine { random_device {}()});
            }
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
/*
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
*/


map<tuple<int, int, int>, vector<tuple<int, int, int>>> mazeMakerWilson(map<tuple<int, int, int>, vector<tuple<int, int, int>>> graph, int xDim, int yDim) {
    map<tuple<int, int, int>, int> disconnBits;
    vector<tuple<int, int, int>> disconnectedParts;

    for(auto const& imap: graph) {
        disconnBits[imap.first] = 1;
        disconnectedParts.push_back(imap.first);
    }

    disconnBits[mt(0,1,1)] = 0;
    vector<tuple<int, int, int>> connectedParts;
    connectedParts.push_back(mt(0,1,1));
    deleteItem(&disconnectedParts, &connectedParts[0]);

    int found  = 0;
    int startLoc = 0;
    int eep = connectedParts.size();
    tuple<int, int, int> start = mt(0, 1, 1);
    tuple<int, int, int> end = mt(0, 3, 3);
    
    while (disconnectedParts.size() > 0) {
        found = 0;
        if (startLoc >= connectedParts.size()+1) {break;}
        start = connectedParts[startLoc];

        while (1) {
            vector<tuple<int, int, int>> cut = graph[start];
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

            //if (pairsEqual(&start, &end)) {
            if (start == end) {
                startLoc=0;
                shuffle(begin(connectedParts), connectedParts.end(), default_random_engine { random_device {}()});
                if (disconnectedParts.size() > 0) {
                    end = disconnectedParts[rand() % disconnectedParts.size()];
                }
                break;
            }
            
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
    int xDim = 30;
    int yDim = 30;

    cout << "With Pointers! SQUIGLLy (" << xDim << "," << yDim << ")" << endl;
    map<tuple<int, int, int>, vector<tuple<int, int, int>>> walls = graphGen(xDim, yDim);
    cout << "Graph Made!" << endl;

    //pair<int, int> location = mp(1,1);
    map<tuple<int, int, int>, vector<tuple<int, int, int>>> nWalls;
    try {
        walls = mazeMakerWilson(walls, xDim, yDim);
    } catch (const exception& e) {
        cout << "Exception " << e.what() << endl;
        return 0;
    }
    cout << "MAZED!" << endl;
    



    /*
    
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
    */
    return 0;
} 