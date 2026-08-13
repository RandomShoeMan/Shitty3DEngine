#include "objLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool OBJLoader::load(const char* filename) {

    cout << "Loading OBJ: " << filename << endl;

    ifstream file(filename);

    if (!file.is_open()) {

        cout << "Failed to open OBJ file!" << endl;

        return false;

    }

    string line;

    while (getline(file, line)) {

        stringstream stream(line);

        string type;

        stream >> type;

        // Vertex
        if (type == "v") {

            float x;
            float y;
            float z;

            stream >> x >> y >> z;

            vertices.push_back(Vec3(x, y, z));

        }

        // Face
        else if (type == "f") {

            string face[4];

            int count = 0;

            while (count < 4 && stream >> face[count]) {

                count++;

            }

            if (count < 3) {

                continue;

            }

            // Get the vertex number from something like:
            // 12/5/3
            // 12/5
            // 12
            auto getIndex = [&](string value) {

                stringstream faceStream(value);

                string vertexIndex;

                getline(faceStream, vertexIndex, '/');

                return stoi(vertexIndex) - 1;

            };

            // Triangle
            if (count == 3) {

                indices.push_back(getIndex(face[0]));
                indices.push_back(getIndex(face[1]));
                indices.push_back(getIndex(face[2]));

            }

            // Quad
            else if (count == 4) {

                // First triangle
                indices.push_back(getIndex(face[0]));
                indices.push_back(getIndex(face[1]));
                indices.push_back(getIndex(face[2]));

                // Second triangle
                indices.push_back(getIndex(face[0]));
                indices.push_back(getIndex(face[2]));
                indices.push_back(getIndex(face[3]));

            }

        }

    }

    file.close();

    cout << "Loaded OBJ file!" << endl;
    cout << "Vertices: " << vertices.size() << endl;
    cout << "Indices: " << indices.size() << endl;

    return true;

}