#ifndef _GEOMSHAPES2_H_46209A31A62C4B7B80C8E8E2B95022A1_
#define _GEOMSHAPES2_H_46209A31A62C4B7B80C8E8E2B95022A1_

/************************/
/*    geomshapes2.h      */
/*    Version 1.0       */
/*     2022/06/18       */
/*  © Davide Pasca      */
/*  © Marco Azimonti    */
/************************/

#include <memory>
#include <string>
#include <vector>
#include <stddef.h>
#include "ge_mathbase.h"
#include "geomplanes.h"
#include "geomprocessing.h"

namespace ge
{
    class Mesh;
}

namespace gegt
{
    enum SHAPES : size_t { TORUS = 0, SOMBRERO, SHAPELAST };

    bool IsShapeManifold(size_t s);

    const std::string& GetShapeName(size_t s);

    std::vector<std::string> GetAllShapesName();

    gegp::MapUVPos_FnT make_sombrero(const float H = 1.f);

} // namespace gegt
#endif
