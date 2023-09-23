This is a sample program that demonstrates how
to calculate the fatest path between two eve online systems.

The repository is final and no further updates will me made to the code.

The code is distributed under the GNU General Public License v3.0.

## Requirements
* C++ compiler
* CMake
* libjsoncpp

## Important
If you are not using cmake to build the project, please make sure, make sure
to set path to the folder containing the solarSystems.json file bundled with the project:

```
-DPRIVATE_DATA_DIR=/path/to/solar/system/data
```
or
```
#define PRIVATE_DATA_DIR "C:\path\to\solar\system\data"
```

## Sample usage
Please consult the file 'main.cpp' in this repository
for sample usage.

## 3RD Party Software
This project uses the following 3rd party software:
libjsoncpp

Qt6

The solar system data come from https://www.fuzzwork.co.uk/dump/
and were converted to json format by myself.

The breadth first search algorithm is based on the code from

https://www.geeksforgeeks.org/shortest-path-unweighted-graph/