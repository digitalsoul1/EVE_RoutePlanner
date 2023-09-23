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
#include <algorithm>
#include "EVE_RoutePlanner.h"
#include "SolarSystemsMap.h"
#include "EVE_SolarSystem.h"
#include "EVE_ShortestRoute_BFS.h"

#ifdef WITH_QT6
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#else
#include <fstream>
#include <json/json.h>
#endif

#ifndef PRIVATE_DATA_DIR
#error "PRIVATE_DATA_DIR not defined"
#endif

#define string_value_(x) #x
#define string_value(x) string_value_(x)

SOLARSYSTEMS *SOLARSYSTEMS::m_pInstance = nullptr;

void EVE_RoutePlanner::Initialize() {
    if (m_bInitialized)
        return;

#ifdef WITH_QT6
    QJsonDocument jsonDoc;
    QFile file("../../Data/solarSystems.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!file.isOpen()) {
        qDebug() << "Error: cannot open file";
        return;
    }

    jsonDoc = QJsonDocument::fromJson(file.readAll());

    // Load solar systems
    for(QJsonValueRef jsonSolarSystem: jsonDoc.array()) {
        SolarSystem solarSystem;

        // Initialize solar system
        solarSystem.setId(jsonSolarSystem.toObject()["id"].toString().toULong());
        solarSystem.setName(jsonSolarSystem.toObject()["name"].toString().toStdString());
        solarSystem.setSecurity(jsonSolarSystem.toObject()["security"].toDouble());

        // Load connections
        for(QJsonValueRef jsonConnection: jsonSolarSystem.toObject()["connectedSystems"].toArray()) {
            solarSystem.addConnectedSystem(jsonConnection.toString().toULong());
        }
        SOLARSYSTEMS::Instance()->addSolarSystem(std::move(solarSystem));

    }
    file.close();
#else
    // Create path
    std::string path= std::string(string_value(PRIVATE_DATA_DIR)) + "solarSystems.json";
    // Load solar systems
    std::ifstream ifs(path);
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);

    for (auto &jsonSolarSystem: obj) {
        EVE_SolarSystem solarSystem;

        // Initialize solar system
        auto temp_id = jsonSolarSystem["id"].asString();
        solarSystem.setId(std::stoul(temp_id));
        solarSystem.setName(jsonSolarSystem["name"].asString());
        solarSystem.setSecurity(jsonSolarSystem["security"].asFloat());

        // Load connections
        for (auto &jsonConnection: jsonSolarSystem["connectedSystems"]) {
            temp_id = jsonConnection.asString();
            solarSystem.addConnectedSystem(std::stoul(temp_id));
        }
        SOLARSYSTEMS::Instance()->addSolarSystem(std::move(solarSystem));
    }

    ifs.close();
#endif


    m_bInitialized = true;
}

std::vector<EVE_SolarSystem *> EVE_RoutePlanner::GetRoute(const std::string &start, const std::string &end) {
    if (!m_bInitialized) {
        Initialize();
    }

    auto point_a = SOLARSYSTEMS::Instance()->getSolarSystem(start);
    auto point_b = SOLARSYSTEMS::Instance()->getSolarSystem(end);

    if (point_a == nullptr || point_b == nullptr)
        return {};

    EVE_ShortestRoute_BFS shortestRoute;
    return shortestRoute.GetRoute(point_a, point_b);
}
