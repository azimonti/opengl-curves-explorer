/************************/
/*  params_dialog.cpp   */
/*    Version 1.0       */
/*     2022/06/19       */
/*  © Davide Pasca      */
/*  © Marco Azimonti    */
/************************/

#include <string>
#include <vector>
#include "imguiparams_dialog.h"
#include "log/log.h"
#include "ge_mesh2.h"
#include "geomshapes.h"
#include "geomshapes2.h"
#include "gl_app.h"
#include "mesh.h"

ImguiparamsDialog::ImguiparamsDialog() : d_visible(false) {}

ImguiparamsDialog::~ImguiparamsDialog() {}

void ImguiparamsDialog::onRender(GLFWwindow* window)
{
    GLApp* w = (GLApp*)glfwGetWindowUserPointer(window);
    if (!d_visible) { return; }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    // ImGuiStyle& style = ImGui::GetStyle();
    float sz = 240;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::SetNextWindowSize(ImVec2(sz, (float)height), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2((float)width - sz, 0), ImGuiCond_Once);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.f, 0.f, 0.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.f, 0.f, 0.f, 0.7f));
    ImGui::GetStyle();
    ImGui::Begin("##params", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

    ImGui::SetCursorPos(ImVec2(0, 0));
    ImGui::TextColored(ImVec4(0.f, 1.f, 1.f, 1.f), "                   Parameters");
    ImGui::NewLine();
    const std::vector<std::string> v1 = gegt::GetAllShapesName();
    size_t shape                      = w->GetEngineWnd()->GetShape();
    size_t item_current_idx           = shape;
    if (ImGui::BeginListBox("Shapes"))
    {
        for (size_t i = 0; i < v1.size(); ++i)
        {
            const bool is_selected = (item_current_idx == i);
            if (ImGui::Selectable(v1[i].c_str(), is_selected)) item_current_idx = i;
            if (is_selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndListBox();
    }
    if (item_current_idx != shape) w->GetEngineWnd()->SetShape(item_current_idx);
    float r, R;
    bool radiusChanged = false;
    switch (shape)
    {
    case gegt::TORUS:
        r             = w->GetEngineWnd()->Getr();
        R             = w->GetEngineWnd()->GetR();
        radiusChanged = ImGui::SliderFloat("Torus R", &R, 0.1f, 10.0f);
        if (radiusChanged) w->GetEngineWnd()->SetR(R);
        radiusChanged = ImGui::SliderFloat("Torus r", &r, 0.1f, 10.0f);
        if (r > R)
        {
            radiusChanged = true;
            r             = R;
        }
        if (radiusChanged) w->GetEngineWnd()->Setr(r);
        break;
    case gegt::SOMBRERO:
        R = w->GetEngineWnd()->GetR();
        ImGui::SliderFloat("Sombrero height", &R, 0.3f, 10.0f);
        w->GetEngineWnd()->SetR(R);
        break;
    }

    size_t plane                      = w->GetEngineWnd()->GetPlane();
    item_current_idx                  = plane;
    const std::vector<std::string> v2 = gegt::GetAllPlanesName();
    const char* combo_preview_value   = v2[plane].c_str();
    if (ImGui::BeginCombo("plane", combo_preview_value))
    {
        for (size_t i = 0; i < v2.size(); ++i)
        {
            const bool is_selected = (item_current_idx == i);
            if (ImGui::Selectable(v2[i].c_str(), is_selected)) item_current_idx = i;
            if (is_selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    if (item_current_idx != plane) w->GetEngineWnd()->SetPlane(item_current_idx);
    ImGui::NewLine();

    ImGui::End();
    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(4);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiparamsDialog::SetVisibility(bool v)
{
    d_visible = v;
}

void ImguiparamsDialog::ToggleVisibility()
{
    d_visible ^= 1;
}
