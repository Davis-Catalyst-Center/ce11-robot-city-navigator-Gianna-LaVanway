#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "CityMap.hpp"

void printResult(const std::string& algorithm, const std::pair<std::vector<std::string>, int>& result);

int main() {
    CityMap city;

    std::cout << "=== George's City Navigation System ===\n\n";

    city.printCity();
    std::cout << "\n";

    std::cout << "--- Route: Downtown -> Airport ---\n\n";

    /* Test all three algorithms on this route */
    // Greedy
    printResult("Greedy Algorithm", city.greedyPath(0,2));    

    // Dijkstra
    printResult("Dijkstra Path", city.dijkstraPath(0,2)); 
    
    // A*
    printResult("A* Algorithm", city.aStarPath(0,2)); 

    std::cout << "\n";

    std::cout << "--- Route: Downtown -> Suburb South ---\n\n";

    /* Test all three algorithms on this route */
    // Greedy
    printResult("Greedy Algorithm", city.greedyPath(0,7));

    // Dijkstra
    printResult("Dijkstra Path", city.dijkstraPath(0,7));  

    // A*
    printResult("A* Algorithm", city.aStarPath(0,7));   

    std::cout << "\n";

    std::cout << "--- Route: University -> University ---\n\n";

    /* Pick your own start/end pair and test all three algorithms */
    // Greedy
    printResult("Greedy Algorithm", city.greedyPath(3,3));

    // Dijkstra
    printResult("Dijkstra Path", city.dijkstraPath(3,3));   
    
    // A*
    printResult("A* Algorithm", city.aStarPath(3,3));   

    std::cout << "\n";


    std::cout << "--- Route: Suburb South -> Downtown ---\n\n";

    /* Pick your own start/end pair and test all three algorithms */
    // Greedy
    printResult("Greedy Algorithm", city.greedyPath(7,0));

    // Dijkstra
    printResult("Dijkstra Path", city.dijkstraPath(7,0));   
    
    // A*
    printResult("A* Algorithm", city.aStarPath(7,0));   

    std::cout << "\n";


    std::cout << "--- Route: out of bounds ---\n\n";

    /* Pick your own start/end pair and test all three algorithms */
    // Greedy
    printResult("Greedy Algorithm", city.greedyPath(0,8));

    // Dijkstra
    printResult("Dijkstra Path", city.dijkstraPath(0,8));   
    
    // A*
    printResult("A* Algorithm", city.aStarPath(0,8));   

    std::cout << "\n";


    std::cout << "--- Route: Harbor -> Medical Center ---\n\n";

    /* Pick your own start/end pair and test all three algorithms */
    // Greedy
    printResult("Greedy Algorithm", city.greedyPath(1,5));

    // Dijkstra
    printResult("Dijkstra Path", city.dijkstraPath(1,5));   
    
    // A*
    printResult("A* Algorithm", city.aStarPath(1,5));   

    std::cout << "\n";



    return 0;
}

void printResult(const std::string& algorithm, const std::pair<std::vector<std::string>, int>& result) {
    std::cout << "[" << algorithm << "]\n";
    if (result.first.empty() || result.second == -1) {
        std::cout << "  No path found.\n";
        return;
    }
    std::cout << "  Path: ";
    for (int i = 0; i < (int)result.first.size(); i++) {
        std::cout << result.first[i];
        if (i < (int)result.first.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n  Total time: " << result.second << " min\n";
}
