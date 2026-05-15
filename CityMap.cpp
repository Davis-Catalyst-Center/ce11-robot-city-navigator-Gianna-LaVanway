#include "CityMap.hpp"
#include <iostream>

CityMap::CityMap() {
    locations.resize(8);

    locations[0].name = "Downtown";
    locations[0].x = 4; locations[0].y = 4;
    locations[0].neighbors = {{1, 8}, {3, 15}, {6, 12}};

    locations[1].name = "Harbor";
    locations[1].x = 4; locations[1].y = 0;
    locations[1].neighbors = {{0, 8}, {2, 20}, {4, 10}};

    locations[2].name = "Airport";
    locations[2].x = 10; locations[2].y = 0;
    locations[2].neighbors = {{1, 20}, {4, 5}, {7, 18}};

    locations[3].name = "University";
    locations[3].x = 0; locations[3].y = 6;
    locations[3].neighbors = {{0, 15}, {5, 9}, {6, 7}};

    locations[4].name = "Industrial";
    locations[4].x = 9; locations[4].y = 1;
    locations[4].neighbors = {{1, 10}, {2, 5}, {7, 8}};

    locations[5].name = "Medical Center";
    locations[5].x = 2; locations[5].y = 9;
    locations[5].neighbors = {{3, 9}, {6, 11}, {7, 14}};

    locations[6].name = "Suburb North";
    locations[6].x = 1; locations[6].y = 5;
    locations[6].neighbors = {{0, 12}, {3, 7}, {5, 11}};

    locations[7].name = "Suburb South";
    locations[7].x = 8; locations[7].y = 8;
    locations[7].neighbors = {{2, 18}, {4, 8}, {5, 14}};
}

void CityMap::printCity() const {
    std::cout << "City Locations:\n";
    for (int i = 0; i < (int)locations.size(); i++) {
        std::cout << "  [" << i << "] " << locations[i].name << "\n";
        std::cout << "       neighbors: ";
        for (int j = 0; j < (int)locations[i].neighbors.size(); j++) {
            auto [idx, time] = locations[i].neighbors[j];
            std::cout << locations[idx].name << "(" << time << ")";
            if (j < (int)locations[i].neighbors.size() - 1) std::cout << ", ";
        }
        std::cout << "\n";
    }
}

std::pair<std::vector<std::string>, int> CityMap::greedyPath(int start, int end) {
    if (start < 0 || start >= (int)locations.size() || end < 0 || end >= (int)locations.size()) {
        return {{}, -1};
    }

    if(start == end) {
        return {reconstructPath({start}, start, end), 0};
    }
    // location index
    std::vector<int> visited;
    // total travel time
    int totalCost = 0;
    // location index
    int currentIndex = start;
    // index of neighbor for current index
    int smallestNeighbor;
    // bool to see if neighbor has been visited
    bool hasBeenVisited;

    // empty vector, will be the names of the locations visted before returning
    std::vector<std::string> visitedNames;

    // if every location is marked as visited, then we cannot reach the end
    while(visited.size() < locations.size()) {
        // reset smallestNeighbor for each iteration
        smallestNeighbor = -1;
        // for each neighbor of the current index, find which one has the shortest travel time
        // start at index 0, to make sure that we don't end with a visited neightbor
        for(int i=0; i<locations.at(currentIndex).neighbors.size(); i++) {
            // reset visited to false
            hasBeenVisited = false;
            // check if current index has been visited
            for(int j=0; j<visited.size(); j++) {
                if(locations.at(currentIndex).neighbors.at(i).first == visited.at(j)) {
                    hasBeenVisited = true;
                }
            }
            // make sure smallest neighbor != -1
            if(smallestNeighbor != -1) {
                // compare the current neighbor to the smallest neighbor, and make sure it hasn't been visited
                if(locations.at(currentIndex).neighbors.at(i).second < locations.at(currentIndex).neighbors.at(smallestNeighbor).second && !hasBeenVisited) {
                    smallestNeighbor = i;
                }
            }
            else {
                // smallest neighbor == -1,
                if(!hasBeenVisited) {
                    smallestNeighbor = i;
                }
            }
        }
        // if every neighbor has already been visited, smallestNeighbor will still be -1
        if(smallestNeighbor == -1) {
            return {{}, -1};
        }
        // mark current index as visited
        visited.push_back(currentIndex);
        // increase travel time
        totalCost += locations.at(currentIndex).neighbors.at(smallestNeighbor).second;
        // set current index to the smallest neighbor's location index
        currentIndex = locations.at(currentIndex).neighbors.at(smallestNeighbor).first;
        
        // before we go again, make sure we haven't reached the end
        if(currentIndex == end) {
            visited.push_back(currentIndex);
            return {reconstructPath(visited, start, end), totalCost};
        }
    }
    return {{}, -1};
}

std::pair<std::vector<std::string>, int> CityMap::dijkstraPath(int start, int end) {
    if (start < 0 || start >= (int)locations.size() || end < 0 || end >= (int)locations.size()) {
        return {{}, -1};
    }

    // {cost, index}
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> priorityQueue;

    // keep track of the distances
    std::vector<int> distances(locations.size(), INT_MAX);
    // keep track of the paths
    std::vector<std::vector<int>> paths(locations.size());

    // the distance from start-start is 0
    // add start now, so there is something in priorityQueue
    distances.at(start) = 0;
    priorityQueue.push({0, start});

    // while there are still items in the priority queue
    while(!priorityQueue.empty()) {
        std::pair<int, int> top = priorityQueue.top();
        priorityQueue.pop();

        int dist = top.first;
        int current = top.second;
        // update the path
        // make sure that current isn't already there
        bool added = false;
        for(int i=0; i<paths.at(current).size(); i++) {
            if(paths.at(current).at(i) == current) {
                added = true;
            }
        }
        if(!added) {
            paths.at(current).push_back(current);
        }
        
        // if this isn't the smallest possible distance for this location, skip it
        if(dist > distances.at(current)) {
            continue;
        }

        // check each neighbor of the node
        for(int j=0; j<locations.at(current).neighbors.size(); j++) {
            int nIndex = locations.at(current).neighbors.at(j).first;
            int nDist = locations.at(current).neighbors.at(j).second;

            // see if there is a smaller path to each neighbor than the current one
            if(distances.at(current) + nDist < distances.at(nIndex)) {
                distances.at(nIndex) = distances.at(current) + nDist;
                // update the path saved to the shorter path
                paths.at(nIndex) = paths.at(current);
                priorityQueue.push({distances.at(nIndex), nIndex});
            }
        }
    }
    // at this point, distances has the smallest possible distance to each location

    return {reconstructPath(paths.at(end), start, end), distances.at(end)};
}

std::pair<std::vector<std::string>, int> CityMap::aStarPath(int start, int end) {
    if (start < 0 || start >= (int)locations.size() || end < 0 || end >= (int)locations.size()) {
        return {{}, -1};
    }


    std::vector<int> gScore(locations.size(), INT_MAX);
    gScore.at(start) = 0;

    std::vector<std::vector<int>> paths(locations.size());

    //{fScore, index}
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> priorityQueue;

    priorityQueue.push({heuristic(start, start), start});


    while(!priorityQueue.empty()) {
        std::pair<int,int> top = priorityQueue.top();
        priorityQueue.pop();
        int fScore = top.first;
        int index = top.second;

        bool added = false;
        for(int i=0; i<paths.at(index).size(); i++) {
            if(paths.at(index).at(i) == index) {
                added = true;
            }
        }
        if(!added) {
            paths.at(index).push_back(index);
        }

        for(int i=0; i<locations.at(index).neighbors.size(); i++) {
            int newG = gScore.at(index) + locations.at(index).neighbors.at(i).second;
            if(newG < gScore.at(locations.at(index).neighbors.at(i).first)) {
                gScore.at(locations.at(index).neighbors.at(i).first) = newG;
                fScore = newG + heuristic(locations.at(index).neighbors.at(i).first, end);
                priorityQueue.push({fScore, locations.at(index).neighbors.at(i).first});
                paths.at(locations.at(index).neighbors.at(i).first) = paths.at(index);
            }
        }
    }
    return {reconstructPath(paths.at(end), start, end), gScore.at(end)};
}

int CityMap::heuristic(int from, int to) const {
    return (int)sqrt(((locations.at(to).x - locations.at(from).x) ^ 2) + ((locations.at(to).y - locations.at(from).y) ^ 2));
}

std::vector<std::string> CityMap::reconstructPath(const std::vector<int>& prev, int start, int end) const {
    std::vector<std::string> names;
    for(int i=0; i<prev.size(); i++) {
        names.push_back(locations.at(prev.at(i)).name);
    }
    return names;
}