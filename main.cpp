#include "EVE_RoutePlanner.h"
#include "SolarSystemsMap.h"
#include <iostream>

int main() {
    std::string start_system = "Amarr";
    std::string end_system = "Jita";

    // measure execution time
    EVE_RoutePlanner rp;
    auto start = std::chrono::high_resolution_clock::now();
    auto route = rp.GetRoute(start_system, end_system);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);


    // print route
    if (route.empty()) {
        std::cout << "No route found" << std::endl;
        return 0;
    } else {
        int i = 1;
        std::cout << "====================================" << std::endl;
        std::cout << "Route from " << start_system << " to " << end_system << std::endl;
        std::cout << "Route generated in: " << duration.count() / 1000000.0 << " seconds" << std::endl;
        std::cout << "Total jumps: " << route.size() << std::endl;
        std::cout << "====================================" << std::endl;

        std::cout << i << ". " << start_system << std::endl;
        i++;
        for (auto &solarSystem: route) {
            std::cout << i << ". " << solarSystem->getName() << std::endl;
            i++;
        }
    }

    return 0;
}
