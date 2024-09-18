#ifndef _IMGUIPARAMS_DIALOG_H_F489FCDBBAE94D37A4A1A02E55A378D5_
#define _IMGUIPARAMS_DIALOG_H_F489FCDBBAE94D37A4A1A02E55A378D5_

/*****************************/
/*    imguiparams_dialog.h   */
/*         Version 1.0       */
/*          2022/06/19       */
/*       © Davide Pasca      */
/*       © Marco Azimonti    */
/*****************************/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class ImguiparamsDialog
{
  public:
    ImguiparamsDialog();
    ~ImguiparamsDialog();

    void onRender(GLFWwindow* window);
    void SetVisibility(bool v);
    void ToggleVisibility();

  private:
    bool d_visible;
};
#endif
