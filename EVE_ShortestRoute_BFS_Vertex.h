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

#ifndef ROUTEPLANNER_EVE_SHORTESTROUTE_BFS_VERTEX_H
#define ROUTEPLANNER_EVE_SHORTESTROUTE_BFS_VERTEX_H

#include <vector>

class EVE_ShortestRoute_BFS_Vertex {
    friend class EVE_ShortestRoute_BFS;

public:
    EVE_ShortestRoute_BFS_Vertex() = delete;

private:
    // init list
    EVE_ShortestRoute_BFS_Vertex(const unsigned long id, const std::vector<unsigned long> &neighbours) : m_id(id), m_neighbours(
                                                                                                             neighbours) {}
    // getters
    [[nodiscard]] unsigned long getId() const { return m_id; }

    [[nodiscard]] std::vector<unsigned long> getNeighbours() const { return m_neighbours; }

    const unsigned long m_id;

    const std::vector<unsigned long> m_neighbours;
};


#endif //ROUTEPLANNER_EVE_SHORTESTROUTE_BFS_VERTEX_H
