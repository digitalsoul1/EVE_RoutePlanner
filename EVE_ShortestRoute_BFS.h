/*
* Copyright (c) 2023 github.com/digitalsoul1
*
* This program is free software: you can redistribute it and/or modify
        * it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
        * General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ROUTEPLANNER_EVE_SHORTESTROUTE_BFS_H
#define ROUTEPLANNER_EVE_SHORTESTROUTE_BFS_H

#include "SolarSystemsMap.h"
#include "EVE_ShortestRoute_BFS_Vertex.h"
#include <queue>

class EVE_ShortestRoute_BFS {
public:
    std::vector<EVE_SolarSystem*> GetRoute(const EVE_SolarSystem *start, const EVE_SolarSystem *end);
private:
    std::vector<EVE_SolarSystem*> bfs_search(unsigned long start, unsigned long end);

    // TODO: remove and use SolarSystemsMap as the Adjecnt List
    void buildAdjList();
    unsigned int getVertexIndex(unsigned long id);
    std::vector<EVE_ShortestRoute_BFS_Vertex> m_adjList = {};

    bool m_bInitialized = false;
};


#endif //ROUTEPLANNER_EVE_SHORTESTROUTE_BFS_H
