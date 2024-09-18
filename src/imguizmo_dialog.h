#ifndef _IMGUIZMO_DIALOG_H_BB43007832834935B054FC37D02507C1_
#define _IMGUIZMO_DIALOG_H_BB43007832834935B054FC37D02507C1_

/**************************/
/*   imguizmo_dialog.h    */
/*      Version 1.0       */
/*       2022/05/18       */
/*    © Davide Pasca      */
/*    © Marco Azimonti    */
/**************************/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imGuIZMOquat.h"

class ImguizmoDialog
{
  public:
    ImguizmoDialog();
    ~ImguizmoDialog();

    void onRender(GLFWwindow* window);
    void SetVisibility(bool v);
    void ToggleVisibility();

  private:
    bool d_visible{};
    bool h_visible{};
};
#endif
