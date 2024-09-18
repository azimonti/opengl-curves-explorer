/************************/
/*   geomshapes2.cpp    */
/*    Version 1.0       */
/*     2022/06/19       */
/*  © Davide Pasca      */
/*  © Marco Azimonti    */
/************************/

#include <stdexcept>
#include "geomshapes2.h"
#include "mesh.h"

namespace gegt
{

    struct ShapeInfo
    {
        std::string name;
        bool isManifold{};
    };

    // NOTICE: entries must match SHAPES enums
    static std::vector<ShapeInfo> sInfos{
        {   "Torus",  true}, // TORUS
        {"Sombrero", false}, // SOMBRERO
    };

    static const ShapeInfo& getShapeInfo(size_t s)
    {
        if (s >= sInfos.size()) throw std::invalid_argument("Unknown shape");
        return sInfos[s];
    }

    bool IsShapeManifold(size_t s)
    {
        return getShapeInfo(s).isManifold;
    }

    const std::string& GetShapeName(size_t s)
    {
        return getShapeInfo(s).name;
    }

    std::vector<std::string> GetAllShapesName()
    {
        std::vector<std::string> v;
        for (size_t i = TORUS; i < SHAPELAST; ++i) v.push_back(GetShapeName(i));
        return v;
    }

    gegp::MapUVPos_FnT make_sombrero(const float H)
    {
        return [=](const float u, const float v) -> glm::vec3 {
            // https://docs.octave.org/v4.2.1/Three_002dDimensional-Plots.html
            const auto x   = glm::mix(-3.f, 3.f, u); // 0..1 -> -3..3
            const auto z   = glm::mix(-3.f, 3.f, v); // 0..1 -> -3..3
            // y = fn( x(u), z(v) )
            const auto rho = sqrt(x * x + z * z) * H;
            const auto y   = sin(rho) / rho;
            // return the 3D coords
            return {x, y, z};
        };
    }
} // namespace gegt
