#include "Mesh.h"

Mesh::~Mesh()
{
    m_vertices.clear();
    m_indices.clear();
}

std::shared_ptr<Mesh> Mesh::CreateCube()
{
    auto mesh = std::make_shared<Mesh>();

    const float radius    = 1.0f;
    const float lengthInv = 1.0f / radius;

    mesh->m_indices = {
        0, 1, 2, 0, 2, 3,       // front
        4, 5, 6, 4, 6, 7,       // right
        8, 9, 10, 8, 10, 11,    // back
        12, 13, 14, 12, 14, 15, // left
        16, 17, 18, 16, 18, 19, // upper
        20, 21, 22, 20, 22, 23  // bottom
    };

    mesh->m_vertices = {
        Vertex{-1.0f, -1.0f, 1.0f, -1.0f * lengthInv, -1.0f * lengthInv, 1.0f * lengthInv},
        Vertex{1.0f, -1.0f, 1.0f, 1.0f * lengthInv, -1.0f * lengthInv, 1.0f * lengthInv},
        Vertex{1.0f, 1.0f, 1.0f, 1.0f * lengthInv, 1.0f * lengthInv, 1.0f * lengthInv},
        Vertex{-1.0f, 1.0f, 1.0f, -1.0f * lengthInv, 1.0f * lengthInv, 1.0f * lengthInv}, // front
        Vertex{-1.0f, -1.0f, -1.0f, -1.0f * lengthInv, -1.0f * lengthInv, -1.0f * lengthInv},
        Vertex{-1.0f, 1.0f, -1.0f, -1.0f * lengthInv, 1.0f * lengthInv, -1.0f * lengthInv},
        Vertex{1.0f, 1.0f, -1.0f, 1.0f * lengthInv, 1.0f * lengthInv, -1.0f * lengthInv},
        Vertex{1.0f, -1.0f, -1.0f, 1.0f * lengthInv, -1.0f * lengthInv, -1.0f * lengthInv}, // back
        Vertex{-1.0f, 1.0f, -1.0f, -1.0f * lengthInv, 1.0f * lengthInv, -1.0f * lengthInv},
        Vertex{-1.0f, 1.0f, 1.0f, -1.0f * lengthInv, 1.0f * lengthInv, 1.0f * lengthInv},
        Vertex{1.0f, 1.0f, 1.0f, 1.0f * lengthInv, 1.0f * lengthInv, 1.0f * lengthInv},
        Vertex{1.0f, 1.0f, -1.0f, 1.0f * lengthInv, 1.0f * lengthInv, -1.0f * lengthInv}, // upper
        Vertex{-1.0f, -1.0f, -1.0f, -1.0f * lengthInv, -1.0f * lengthInv, -1.0f * lengthInv},
        Vertex{1.0f, -1.0f, -1.0f, 1.0f * lengthInv, -1.0f * lengthInv, -1.0f * lengthInv},
        Vertex{1.0f, -1.0f, 1.0f, 1.0f * lengthInv, -1.0f * lengthInv, 1.0f * lengthInv},
        Vertex{-1.0f, -1.0f, 1.0f, -1.0f * lengthInv, -1.0f * lengthInv, 1.0f * lengthInv}, // bottom
        Vertex{1.0f, -1.0f, -1.0f, 1.0f * lengthInv, -1.0f * lengthInv, -1.0f * lengthInv},
        Vertex{1.0f, 1.0f, -1.0f, 1.0f * lengthInv, 1.0f * lengthInv, -1.0f * lengthInv},
        Vertex{1.0f, 1.0f, 1.0f, 1.0f * lengthInv, 1.0f * lengthInv, 1.0f * lengthInv},
        Vertex{1.0f, -1.0f, 1.0f, 1.0f * lengthInv, -1.0f * lengthInv, 1.0f * lengthInv}, // right
        Vertex{-1.0f, -1.0f, -1.0f, -1.0f * lengthInv, -1.0f * lengthInv, -1.0f * lengthInv},
        Vertex{-1.0f, -1.0f, 1.0f, -1.0f * lengthInv, -1.0f * lengthInv, 1.0f * lengthInv},
        Vertex{-1.0f, 1.0f, 1.0f, -1.0f * lengthInv, 1.0f * lengthInv, 1.0f * lengthInv},
        Vertex{-1.0f, 1.0f, -1.0f, -1.0f * lengthInv, 1.0f * lengthInv, -1.0f * lengthInv}, // left
    };

    //mesh->vertices.back().normal = Maths::Vector::Vec3{ nx, ny, nz }; // add it while constructing the vertex ?

    return std::make_shared<Mesh>(*mesh);
}

std::shared_ptr<Mesh> Mesh::CreateSphere(const int p_latitudeCount, const int p_longitudeCount)
{
    auto mesh = std::make_shared<Mesh>();

    constexpr auto mPi = 3.14159265f;

    // clear memory of prev arrays
    //std::vector<float>().swap(vertices);
    //std::vector<float>().swap(normals);
    //std::vector<float>().swap(texCoords);

    const float radius = 1.0f; // radius of the sphere

    float x  = 0.0f;
    float y  = 0.0f;
    float z  = 0.0f;
    float xy = 1.0f;  // vertex position
    float nx, ny, nz; // vertex normal
    const float lengthInv = 1.0f / radius;
    //float s, t;      // vertex texCoord

    const int sectorCount = p_longitudeCount;
    const int stackCount  = p_latitudeCount;

    float sectorStep  = 2 * mPi / sectorCount;
    float stackStep   = mPi / stackCount;
    float sectorAngle = 0.0f;
    float stackAngle  = 0.0f;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = mPi / 2 - i * stackStep;  // starting from pi/2 to -pi/2
        xy         = radius * cos(stackAngle); // r * cos(u)
        z          = radius * sin(stackAngle); // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;

            // vertex position (x, y, z)
            x = xy * cos(sectorAngle); // r * cos(u) * cos(v)
            y = xy * sin(sectorAngle); // r * cos(u) * sin(v)
            (*mesh).m_vertices.emplace_back(x, y, z);

            // vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            // mesh->vertices.back().normal = Maths::Vector::Vec3{ nx, ny, nz };
            /*
            // vertex tex coord (s, t)
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            texCoords.push_back(s);
            texCoords.push_back(t);*/
        }
    }

    // indices
    unsigned int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1); // beginning of current stack
        k2 = k1 + sectorCount + 1;  // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0)
            {
                mesh->m_indices.push_back(k1);
                mesh->m_indices.push_back(k2);
                mesh->m_indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1))
            {
                mesh->m_indices.push_back(k1 + 1);
                mesh->m_indices.push_back(k2);
                mesh->m_indices.push_back(k2 + 1);
            }

            // vertical lines for all stacks
            //lineIndices.push_back(k1);
            //lineIndices.push_back(k2);
            /*if (i != 0)  // horizontal lines except 1st stack
            {
                lineIndices.push_back(k1);
                lineIndices.push_back(k1 + 1);
            }*/
        }
    }

    return std::make_shared<Mesh>(*mesh);
}
