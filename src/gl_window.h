#ifndef _GL_WINDOW_H_8A3D71EFF00845FFA4471E34874A6E27_
#define _GL_WINDOW_H_8A3D71EFF00845FFA4471E34874A6E27_

/************************/
/*     gl_window.h      */
/*    Version 1.0       */
/*     2022/05/18       */
/*  © Davide Pasca      */
/*  © Marco Azimonti    */
/************************/

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include "camera.h"

namespace ge
{
    class Mesh;
    class Scene;
} // namespace ge

class GLWindow
{
  public:
    GLWindow();
    virtual ~GLWindow();

    void onInit();
    void onExit();

    void onRender(GLFWwindow* window);
    void onReshape(GLint w, GLint h);

    void SetAutoRotation(bool v);
    void ToggleAutoRotation();

    const ge::Mesh* GetObjMesh() const { return moObjMesh.get(); }

    ge::Mesh* GetObjMesh() { return moObjMesh.get(); }

    const ge::Camera& GetCamera() const { return mCamera; }

    ge::Camera& GetCamera() { return mCamera; }

    const ge::Scene& GetScene() const { return *moScene; }

    ge::Scene& GetScene() { return *moScene; }

    size_t GetShape() const { return geom; }

    void SetShape(const size_t s)
    {
        geom = s;
        makeObject();
    }

    float Getr() const { return r; }

    void Setr(const float f)
    {
        r = f;
        makeObject();
    }

    float GetR() const { return R; }

    void SetR(const float f)
    {
        R = f;
        makeObject();
    }

    size_t GetPlane() const { return mainplane; }

    void SetPlane(const size_t s)
    {
        mainplane = s;
        makeObject();
    }

    void onMouseButton(int button, int upOrDown, int x, int y);
    void onMouseWheel(int wheel, int direction, int x, int y);
    void onMotion(int x, int y);
    void onPassiveMotion(int x, int y);

    void onKeyDown(int key, int x, int y);
    void onKeyUp(int key, int x, int y);
    void onSpecialKeyUp(int key, int x, int y);
    void onSpecialKeyDown(int key, int x, int y);

  private:
    void makeObject();
    ge::Camera mCamera;
    std::unique_ptr<ge::Mesh> moGridMesh;
    std::unique_ptr<ge::Mesh> moObjMesh;
    std::unique_ptr<ge::Scene> moScene;
    bool meshRotate{};
    bool wiredObj{};
    bool wiredGrid{};
    size_t geom{};
    size_t mainplane{};
    float r{};
    float R{};
};

#endif
