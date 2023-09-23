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
#ifndef ROUTEPLANNER_SOLARSYSTEMSMAP_H
#define ROUTEPLANNER_SOLARSYSTEMSMAP_H

#include <vector>
#include "EVE_SolarSystem.h"

class SolarSystemsMap {
public:
    bool addSolarSystem(EVE_SolarSystem &&solarSystem);

    EVE_SolarSystem *getSolarSystem(unsigned long id);

    EVE_SolarSystem *getSolarSystem(const std::string &name);

    std::vector<EVE_SolarSystem>  *getSolarSystems();

    [[nodiscard]] unsigned long getSolarSystemCount() const;

    [[maybe_unused]] void dumpToTerminal();

    static SolarSystemsMap *Instance();

    [[maybe_unused]]void clearMap();

private:
    SolarSystemsMap() = default;

    std::vector<EVE_SolarSystem> m_SolarSystems;
    static SolarSystemsMap *m_pInstance;
};

typedef SolarSystemsMap SOLARSYSTEMS;

#endif //ROUTEPLANNER_SOLARSYSTEMSMAP_H
