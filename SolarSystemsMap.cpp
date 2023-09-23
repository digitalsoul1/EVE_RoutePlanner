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
#include "SolarSystemsMap.h"
#include <iostream>
#include <algorithm>


void SolarSystemsMap::clearMap() {
    m_SolarSystems.clear();
}


EVE_SolarSystem *SolarSystemsMap::getSolarSystem(unsigned long id) {
    for (auto &solarSystem: m_SolarSystems) {
        if (solarSystem.getId() == id) {
            return &solarSystem;
        }
    }
    return nullptr;
}

EVE_SolarSystem *SolarSystemsMap::getSolarSystem(const std::string &name) {
    for (auto &solarSystem: m_SolarSystems) {
        if (solarSystem.getName() == name) {
            return &solarSystem;
        }
    }
    return nullptr;
}


bool SolarSystemsMap::addSolarSystem(EVE_SolarSystem &&solarSystem) {
    //
    auto result = std::any_of(m_SolarSystems.begin(), m_SolarSystems.end(), [&solarSystem](EVE_SolarSystem &s) {
        return s.getId() == solarSystem.getId();
    });

    if (result) {
        return false;
    }
    m_SolarSystems.emplace_back(solarSystem);

    return true;
}

SolarSystemsMap *SolarSystemsMap::Instance() {
    if (m_pInstance == nullptr) {
        m_pInstance = new SolarSystemsMap();
    }
    return m_pInstance;
}

[[maybe_unused]] void SolarSystemsMap::dumpToTerminal() {
    for (auto &solarSystem: m_SolarSystems) {
        std::cout << solarSystem.getId() << " " << solarSystem.getName();
        std::cout << "(" << solarSystem.getSecurity() << ")";
        std::cout << " ->";
        for (auto &connection: solarSystem.getConnectedSystems()) {
            std::cout << "\" " << SOLARSYSTEMS::Instance()->getSolarSystem(connection)->getName() << "\"   ";
        }

        std::cout << std::endl;
    }
}

unsigned long SolarSystemsMap::getSolarSystemCount() const {
    return m_SolarSystems.size();
}

std::vector<EVE_SolarSystem> *SolarSystemsMap::getSolarSystems() {
    return &m_SolarSystems;
}

