/************************/
/*    gl_window.cpp     */
/*    Version 2.0       */
/*     2022/06/11       */
/*  © Davide Pasca      */
/*  © Marco Azimonti    */
/************************/

#include <algorithm>
#include <functional>
#include <stdarg.h>
#include <stdexcept>
#include <vector>
#include "gl_window.h"
#include "log/log.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "geomprocessing.h"
#include "ge_mesh2.h"
#include "geomshapes.h"
#include "geomshapes2.h"
#include "mesh.h"
#include "scene.h"

GLWindow::GLWindow()
    : meshRotate(false), wiredObj(false), wiredGrid(true), geom(gegt::TORUS), mainplane(gegt::XZ), r(1.f), R(2.f)
{
    const float CAM_ELEVATION = 2.0f; // meters
    const float CAM_DISTANCE  = 9.0f; //
    mCamera.GetTransform().SetMatrix(glm::mat4(1.f));
    mCamera.GetTransform().Translate(-glm::vec3(3.0f, CAM_ELEVATION, CAM_DISTANCE));
}

GLWindow::~GLWindow() {}

void GLWindow::makeObject()
{
    moObjMesh                 = std::make_unique<ge::Mesh>(!wiredObj);
    const int TORUS_POINTS    = 100;
    const glm::vec4 TORUS_COL = {0.8f, 0.8f, 0.8f, 1};

    const bool isManifold     = gegt::IsShapeManifold(geom);
    switch (geom)
    {
    case gegt::TORUS:
        gegp::GenMeshUV(*moObjMesh, TORUS_POINTS / 4, TORUS_POINTS / 2, TORUS_COL, gegt::make_torus(r, R, mainplane),
                        isManifold);
        break;
    case gegt::SOMBRERO:
        gegp::GenMeshUV(*moObjMesh, 51, 51, {0.1f, 0.8f, 0.1f, 1.f}, gegt::make_sombrero(R * 2.f), isManifold);
        break;
    default: throw std::invalid_argument("Unknown shape");
    }

    moObjMesh->OnGeometryUpdate();
}

void GLWindow::onInit()
{
    if (wiredGrid) moGridMesh = gegt::MakeGridMeshWired({10.f, 10.f}, {10, 10});
    else moGridMesh = gegt::MakeGridMeshSolid({10.f, 10.f}, {10, 10});
    makeObject();

    moScene                       = std::make_unique<ge::Scene>();

    moScene->GetDirLight().mDirWS = glm::normalize(glm::vec3(0.1f, 0.6f, 0.3f));
}

void GLWindow::onExit() {}

void GLWindow::onRender(GLFWwindow* window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    // skip rendering if the window has no size (or aspect-ratio will blow)
    if (!width || !height) return;

    // camera projection setup
    mCamera.mFOV        = 60.f;
    mCamera.mAspect_woh = (float)width / (float)height;

    ge::RendSetup rsetup;
    rsetup.mpCamera    = &mCamera;
    rsetup.mRTargetSiz = ge::Vec2((float)width, (float)height);

    moScene->BeginRender(rsetup);

    if (meshRotate) moObjMesh->RotateObjMatrix(glm::pi<float>() / 100.f, glm::vec3(0, 1, 0));

    moScene->AddMesh(*moGridMesh);
    moScene->AddMesh(*moObjMesh);
}

void GLWindow::onReshape(GLint w, GLint h)
{
    (void)w;
    (void)h;
}

void GLWindow::onKeyUp(int key, int x, int y)
{
    (void)key;
    (void)x;
    (void)y;
}

void GLWindow::onSpecialKeyDown(int key, int x, int y)
{
    (void)key;
    (void)x;
    (void)y;
}

void GLWindow::onKeyDown(int key, int x, int y)
{
    (void)key;
    (void)x;
    (void)y;
}

void GLWindow::onSpecialKeyUp(int key, int x, int y)
{
    (void)key;
    (void)x;
    (void)y;
}

void GLWindow::onMouseButton(int button, int upOrDown, int x, int y)
{
    (void)button;
    (void)upOrDown;
    (void)x;
    (void)y;
}

void GLWindow::onMouseWheel(int wheel, int direction, int x, int y)
{
    (void)wheel;
    (void)direction;
    (void)x;
    (void)y;
}

void GLWindow::onMotion(int x, int y)
{
    (void)x;
    (void)y;
}

void GLWindow::onPassiveMotion(int x, int y)
{
    (void)x;
    (void)y;
}

void GLWindow::SetAutoRotation(bool v)
{
    meshRotate = v;
}

void GLWindow::ToggleAutoRotation()
{
    meshRotate ^= 1;
}
