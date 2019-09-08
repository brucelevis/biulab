#include "frame.hh"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_internal.h"

using namespace std;

bool windowView::show_dock_sapce = true;
bool windowView::show_main_window = true;
bool windowView::show_demo_window = false;
bool windowView::show_main_menu_bar = true;
bool windowView::show_overlay_bar = true;
bool windowView::show_control_window = true;
bool windowView::show_display_window = true;
bool windowView::show_graph_window = true;
bool windowView::show_node_window = true;
bool windowView::show_inspector_window = true;

ImGuiDockNodeFlags windowView::dockspace_flags =
    ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode |
    ImGuiDockNodeFlags_NoWindowMenuButton;

windowView::windowView() {
    window = initWindow();
    loadFont();
    setGL(window);
    setNewTheme();
}

windowView::~windowView() {}

void windowView::drawWindow() {
    if (show_dock_sapce) {
        showDcokSpace();
    }
    if (show_main_menu_bar) {
        showMainMenuBar();
    }
    if (show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
    if (show_overlay_bar) {
        showOverlay();
    }
    if (show_control_window) {
        showControlWindow();
    }
    if (show_node_window) {
        showNodeWindow();
    }
    if (show_display_window) {
        showDisplayWindow();
    }
    if (show_inspector_window) {
        showInspector();
    }
    if (show_graph_window) {
        showGraph();
    }
}

void windowView::key_back(GLFWwindow* window, int key, int scanmode, int action,
                          int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    // if (key == GLFW_KEY_C && action == GLFW_PRESS) {
    //     show_control_window = !show_control_window;
    // }
    // if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    //     show_display_window = !show_display_window;
    // }
}

GLFWwindow* windowView::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);
    // glEnable(GL_DEPTH_TEST);
    // create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Genetic", NULL, NULL);
    glfwMakeContextCurrent(window);
    // callback function
    glfwSetKeyCallback(window, key_back);
    // glew
    glewExperimental = GL_TRUE;
    glewInit();
    // glViewport
    int height, width;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    return window;
}

void windowView::setGL(GLFWwindow* window) {
    glClearColor(0.12, 0.12, 0.12, 1.0);
    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void windowView::loadFont() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.DeltaTime = 1.0f / 30.0f;
    (void)io;
    io.Fonts->AddFontFromFileTTF(
        "./fonts/YaHei.Consolas.1.12.ttf", 18.0f, NULL,
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    io.Fonts->Fonts[0]->DisplayOffset = ImVec2(0, -1);
}

void windowView::setNewTheme() {
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    style->WindowPadding = ImVec2(8, 4);
    style->WindowRounding = 0.0f;
    style->WindowBorderSize = 0.0f;
    style->WindowTitleAlign = ImVec2(0.00, 0.37);
    style->FramePadding = ImVec2(5, 3);
    style->FrameRounding = 4.0f;
    style->PopupBorderSize = 0.0f;
    style->ChildBorderSize = 0.0f;
    style->ChildRounding = 0.0f;
    style->ItemSpacing = ImVec2(8, 4);
    style->ItemInnerSpacing = ImVec2(4, 4);
    style->IndentSpacing = 24.0f;
    style->ScrollbarSize = 12.0f;
    style->ScrollbarRounding = 6.0f;
    style->GrabMinSize = 8.0f;
    style->GrabRounding = 2.0f;

    style->DisplaySafeAreaPadding = ImVec2(0.0, 0.0);

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.62f, 0.63f, 0.63f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.54f, 0.54f, 0.54f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.61f, 0.61f, 0.61f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.63f, 0.63f, 0.63f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.50f, 0.50f, 0.50f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.67f, 0.67f, 0.67f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.63f, 0.63f, 0.64f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.03f, 0.03f, 0.04f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.03f, 0.03f, 0.04f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.04f, 0.04f, 0.05f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.50f, 0.51f, 0.52f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.64f, 0.64f, 0.64f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.68f, 0.68f, 0.68f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.20f, 0.86f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.37f, 0.37f, 0.38f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.43f, 0.43f, 0.43f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.54f, 0.54f, 0.54f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.32f, 0.21f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.96f, 0.77f, 0.37f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.95f, 0.38f, 0.40f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.44f, 0.44f, 0.44f, 0.35f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.38f, 0.39f, 0.39f, 0.70f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.58f, 0.58f, 0.57f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void windowView::setWhiteTheme() {
    ImGuiStyle* style = &ImGui::GetStyle();
    style->WindowPadding = ImVec2(10.0f, 10.0f);
    style->WindowRounding = 5.0f;
    // style->ChildWindowRounding = 5.0f;
    style->FramePadding = ImVec2(5.0f, 4.0f);
    style->FrameRounding = 5.0f;
    style->ItemSpacing = ImVec2(5.0f, 5.0f);
    style->ItemInnerSpacing = ImVec2(10.0f, 10.0f);
    style->IndentSpacing = 15.0f;
    style->ScrollbarSize = 16.0f;
    style->ScrollbarRounding = 5.0f;
    style->GrabMinSize = 7.0f;
    style->GrabRounding = 2.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.80f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.39f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.59f, 0.80f, 0.43f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.47f, 0.71f, 0.67f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.80f);
    style->Colors[ImGuiCol_TitleBgCollapsed] =
        ImVec4(0.78f, 0.78f, 0.78f, 0.39f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] =
        ImVec4(0.00f, 0.00f, 0.00f, 0.59f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] =
        ImVec4(0.00f, 0.00f, 0.00f, 0.78f);
    // style->Colors[ImGuiCol_ComboBg] = ImVec4(0.78f, 0.78f, 0.78f, 0.98f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.27f, 0.59f, 0.75f, 1.00f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
    style->Colors[ImGuiCol_SliderGrabActive] =
        ImVec4(0.00f, 0.00f, 0.00f, 0.59f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 0.27f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.59f, 0.80f, 0.43f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.47f, 0.71f, 0.67f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.71f, 0.71f, 0.71f, 0.39f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.51f, 0.67f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.08f, 0.39f, 0.55f, 1.00f);
    style->Colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_SeparatorHovered] =
        ImVec4(0.27f, 0.59f, 0.75f, 1.00f);
    style->Colors[ImGuiCol_SeparatorActive] =
        ImVec4(0.08f, 0.39f, 0.55f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ResizeGripHovered] =
        ImVec4(0.27f, 0.59f, 0.75f, 0.78f);
    style->Colors[ImGuiCol_ResizeGripActive] =
        ImVec4(0.08f, 0.39f, 0.55f, 0.78f);
    // style->Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
    // style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.71f, 0.71f, 0.71f,
    // 0.60f); style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.59f, 0.59f,
    // 0.59f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style->Colors[ImGuiCol_PlotLinesHovered] =
        ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogramHovered] =
        ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.27f, 0.59f, 0.75f, 1.00f);
    style->Colors[ImGuiCol_ModalWindowDarkening] =
        ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
}

void windowView::setDarkTheme() {
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab] =
        ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
    colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
    colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive],
                                        colors[ImGuiCol_TitleBgActive], 0.60f);
    colors[ImGuiCol_TabUnfocused] =
        ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
    colors[ImGuiCol_TabUnfocusedActive] =
        ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void windowView::showHelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void windowView::showMenuFile() {
    if (ImGui::MenuItem("New")) {
    }
    if (ImGui::MenuItem("Open", "Ctrl+O")) {
    }
    if (ImGui::BeginMenu("Open Recent")) {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More..")) {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {
    }
    if (ImGui::MenuItem("Save As..")) {
    }
    ImGui::Separator();
    if (ImGui::BeginMenu("Preferences")) {
        static bool enabled = true;
        ImGui::MenuItem("auto save", "", &enabled);
        ImGui::MenuItem("Author");
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Colors")) {
        float sz = ImGui::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRectFilled(
                p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ImGui::Dummy(ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Quit", "Alt+F4")) {
    }
}

void windowView::showMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            showMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Copy", "CTRL+C")) {
            }
            if (ImGui::MenuItem("Cut", "CTRL+X")) {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V")) {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            static bool tab_menu_button;
            static bool tab_close_button;
            if (ImGui::MenuItem("Control")) {
                show_control_window = !show_control_window;
            }
            if (ImGui::MenuItem("Display")) {
                show_display_window = !show_display_window;
            }
            if (ImGui::MenuItem("Status")) {
                show_overlay_bar = !show_overlay_bar;
            }
            if (ImGui::MenuItem("Node view")) {
                show_node_window = !show_node_window;
            }
            if (ImGui::MenuItem("Inspector")) {
                show_inspector_window = !show_inspector_window;
            }
            if (ImGui::MenuItem("Graph")) {
                show_graph_window = !show_graph_window;
            }
            if (ImGui::MenuItem("Demo")) {
                show_demo_window = !show_demo_window;
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Tab menu", NULL, &tab_menu_button)) {
                dockspace_flags ^= ImGuiDockNodeFlags_NoWindowMenuButton;
            }
            if (ImGui::MenuItem("Close button", NULL, &tab_close_button)) {
                dockspace_flags ^= ImGuiDockNodeFlags_NoCloseButton;
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Theme")) {
            if (ImGui::MenuItem("Dark theme")) {
            }
            if (ImGui::MenuItem("Light theme")) {
            }
            if (ImGui::MenuItem("Github theme")) {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("help")) {
            if (ImGui::MenuItem("Simple")) {
            }
            ImGui::SameLine();
            showHelpMarker("This is a simple text for help.");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void windowView::showOverlay() {
    ImGui::SetNextWindowBgAlpha(0.3f);
    if (ImGui::Begin("Example: Simple overlay", &show_overlay_bar)) {
        ImGui::Text("Keymap:");
        ImGui::Text("C : Open control panel.");
        ImGui::Text("D : Open display panel.");
        ImGui::Separator();
        ImGui::Text("Application FPS: %.1f.", ImGui::GetIO().Framerate);
        if (ImGui::IsMousePosValid())
            ImGui::Text("Mouse Position: (%6.1f,%6.1f)",
                        ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
        else
            ImGui::Text("Mouse Position: <invalid>");
    }
    ImGui::End();
}

void windowView::showInspector() {
    if (ImGui::Begin("Inspector", &show_inspector_window)) {
        // right
        static int selected = 0;
        ImGui::BeginChild("DSAD", ImVec2(0, 0), true);
        for (int i = 0; i < 10; i++) {
            char DS[128];
            sprintf(DS, "MyObject %d", i);
            if (ImGui::Selectable(DS, selected == i)) selected = i;
        }
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::End();
    }
}

void windowView::showGraph() {
    if (ImGui::Begin("Graph", &show_graph_window, 0)) {
        static bool animate = false;
        ImGui::Checkbox("Animate", &animate);

        static float arr[] = {0.6f,  0.1f, 21.0f, 0.5f,
                              0.92f, 0.1f, 0.2f,  13.0f};
        // ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));
        static float values[90] = {0};
        static int values_offset = 3;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0) refresh_time = ImGui::GetTime();
        while (refresh_time < ImGui::GetTime()) {
            static float phase = 0.0f;
            values[values_offset] = cosf(phase * 0.01);
            values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
            phase += 0.1f * values_offset;
            refresh_time += 1.0f / 60.0f;
        }

        {
            float average = 0.0f;
            for (int n = 0; n < IM_ARRAYSIZE(values); n++) average += values[n];
            average /= (float)IM_ARRAYSIZE(values);
            char overlay[32];
            sprintf(overlay, "avg %f", average);
            ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values),
                             values_offset, overlay, -1.0f, 1.0f,
                             ImVec2(0, 80));
        }
        // ImGui::SameLine();
        ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f,
                             1.0f, ImVec2(0, 50));

        struct Funcs {
            static float Sin(void*, int i) { return sinf(i * 0.1f); }
            static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
        };

        ImGui::End();
    }
}

void windowView::showControlWindow() {
    // Draw Control window
    static int loop_controller = 10000;
    static int loop_map = 10;
    static int max_histyory = -1000;
    static bool save_result = true;
    static char save_path[256] = "~/ELONKOU/03.GENETIC/genetic/results";

    static float mutate_rate = 0.005;
    static int robbie_cnt = 200;

    static int map_width = 16;
    static int map_height = 16;
    ImGui::Begin("Control", &show_control_window, 0);

    ImGui::BeginGroup();
    ImGui::BeginChild("item view",
                      ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
    if (ImGui::TreeNode("Controller")) {
        ImGui::SliderInt("loop controller", &loop_controller, 1, 40000);
        ImGui::SameLine();
        showHelpMarker("control all loop control for all robbies.");

        ImGui::SliderInt("loop map", &loop_map, 1, 200);
        ImGui::SameLine();
        showHelpMarker("Map count for every robbie play.");

        ImGui::SliderInt("Max histyory", &max_histyory, -2000, 1000);
        ImGui::SameLine();
        showHelpMarker("max_histyory.");

        ImGui::InputText("Save path", save_path, IM_ARRAYSIZE(save_path));
        showHelpMarker("save modle.");

        ImGui::Checkbox("Save Gene", &save_result);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Robbie")) {
        ImGui::SliderFloat("mutate rate", &mutate_rate, 0.0, 0.1);
        ImGui::SameLine();
        showHelpMarker("Mutate rate for robbies");

        ImGui::SliderInt("robbie cnt", &robbie_cnt, 1, 400);
        ImGui::SameLine();
        showHelpMarker("Robbies count for erery generation.");
        ImGui::TreePop();
    }
    // if (ImGui::TreeNode("Gene")) {
    //     ImGui::TreePop();
    // }
    if (ImGui::TreeNode("Map")) {
        ImGui::InputInt("Width", &map_width, 1, 2);
        ImGui::InputInt("Height", &map_height, 1, 2);
        ImGui::SameLine();
        showHelpMarker("Map width and height.");
        ImGui::TreePop();
    }
    ImGui::EndChild();
    if (ImGui::Button("run")) {
    }
    ImGui::SameLine();
    if (ImGui::Button("stop")) {
    }
    ImGui::SameLine();
    if (ImGui::Button("step")) {
    }
    ImGui::EndGroup();

    ImGui::End();
}

void windowView::showDisplayWindow() {
    ImGui::SetNextWindowBgAlpha(0.3f);
    if (ImGui::Begin("Display", &show_display_window, 0)) {
        int WIDTH_ = 26;
        int HEIGHT_ = 36;
        static float sc = 6.28 * 2 / WIDTH_;
        sc += 0.001;
        for (int i = 0; i < HEIGHT_; i++) {
            for (int j = 0; j < WIDTH_; j++) {
                ImGui::PushID(i);
                float h = 0.6;
                float s = 0.8;
                // float h = sin((i + j) * sc);
                // float s = cos((i + j) * sc);
                // float s = cos(i * j * sc);
                float v = 0.4;
                ImGui::PushStyleColor(ImGuiCol_Button,
                                      (ImVec4)ImColor::HSV(h, s, v));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                      (ImVec4)ImColor::HSV(h, s, v + 0.1));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                                      (ImVec4)ImColor::HSV(h, s, v + 0.2));
                ImGui::SmallButton(" ");
                ImGui::PopStyleColor(3);
                ImGui::PopID();
                if (j != WIDTH_ - 1) {
                    ImGui::SameLine();
                }
            }
        }
    };
    ImGui::End();
}

void windowView::showNodeWindow() {
    if (ImGui::Begin("Node View", &show_node_window, 0)) {
        ImGui::Text("This view display for show node connections of robbies.");
        // ImGui::End();
    }
    ImGui::End();
}

void windowView::showDcokSpace() {
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;

    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoCollapse |
                        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus |
                        ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Geneteic", &show_dock_sapce, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen) ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    } else {
        showDisabledMessage();
    }

    ImGui::End();
}

void windowView::showDisabledMessage() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
    ImGui::Text(
        "Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, "
        "or ");
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::SmallButton("click here"))
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}