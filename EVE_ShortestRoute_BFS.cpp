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
#include "EVE_ShortestRoute_BFS.h"
#include "SolarSystemsMap.h"

std::vector<EVE_SolarSystem *> EVE_ShortestRoute_BFS::GetRoute(const EVE_SolarSystem *start, const EVE_SolarSystem *end) {
    return bfs_search(start->getId(), end->getId());
}

std::vector<EVE_SolarSystem*> EVE_ShortestRoute_BFS::bfs_search(unsigned long start, unsigned long end) {
    buildAdjList();
    unsigned long ADJ_LIST_SIZE = m_adjList.size();
    std::queue<unsigned long> queue;
    bool visited[ADJ_LIST_SIZE];
    unsigned long pred[ADJ_LIST_SIZE], dist[ADJ_LIST_SIZE];

    for (auto i = 0; i < ADJ_LIST_SIZE; i++) {
        visited[i] = false;
        pred[i] = -1;
        dist[i] = INT_MAX;
    }

    unsigned int startVertexIndex = getVertexIndex(start);
    unsigned int endVertexIndex = getVertexIndex(end);

    visited[startVertexIndex] = true;
    dist[startVertexIndex] = 0;
    queue.push(startVertexIndex);

    while (!queue.empty()) {
        unsigned long u = queue.front();
        queue.pop();
        for (int i = 0; i < m_adjList.at(u).getNeighbours().size(); i++) {
            unsigned long v = getVertexIndex(m_adjList.at(u).getNeighbours().at(i));
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                queue.push(v);

                if (v == endVertexIndex) {
                    std::vector<EVE_SolarSystem*> shortestPath;
                    unsigned long crawl = endVertexIndex;
                    while (pred[crawl] != -1) {
                        shortestPath.push_back(SolarSystemsMap::Instance()->getSolarSystem(m_adjList.at(crawl).getId()));
                        crawl = pred[crawl];
                    }

                    // reverse the result
                    std::reverse(shortestPath.begin(), shortestPath.end());

                    return shortestPath;
                }
            }
        }
    }
    return {};
}

void EVE_ShortestRoute_BFS::buildAdjList() {
    if (m_bInitialized) {
        return;
    }

    auto solarSystemSize = SolarSystemsMap::Instance()->getSolarSystems()->size();
    for (int i = 0; i < solarSystemSize; i++) {
        unsigned long solarSystemId = SolarSystemsMap::Instance()->getSolarSystems()->at(i).getId();
        const std::vector<unsigned long> neighbours = SolarSystemsMap::Instance()->getSolarSystems()->at(
                i).getConnectedSystems();
        m_adjList.emplace_back(EVE_ShortestRoute_BFS_Vertex(solarSystemId, neighbours));
    }

    m_bInitialized = true;
}

unsigned int EVE_ShortestRoute_BFS::getVertexIndex(unsigned long id) {
    for (int i = 0; i < m_adjList.size(); i++) {
        if (m_adjList.at(i).getId() == id) {
            return i;
        }
    }
    return -1;
}