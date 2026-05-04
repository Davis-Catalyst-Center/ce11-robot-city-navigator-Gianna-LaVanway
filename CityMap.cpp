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
    int smallestNeighbor = locations.size();
    int smallestTime;
    std::vector<std::string> visited;
    int totalTime;
    std::pair<std::vector<std::string>, int> returned;
    visited.push_back(locations.at(start).name);
    for(int i=0; i<locations.at(start).neighbors.size(); i++) {
        if(locations.at(start).neighbors.at(i).second < smallestNeighbor) {
            smallestNeighbor = locations.at(start).neighbors.at(i).first;
            smallestTime = locations.at(start).neighbors.at(i).second;
        }
    }
    
    if(smallestNeighbor == end) {
        visited.push_back(locations.at(smallestNeighbor).name);
        totalTime = smallestTime;
    }
    else {
        returned = greedyPath(smallestNeighbor, end);
        for(int i=0; i<returned.first.size(); i++) {
            visited.push_back(returned.first.at(i));
        }
        totalTime += returned.second;
    }
    returned.first = visited;
    returned.second = totalTime;

    return returned;
}