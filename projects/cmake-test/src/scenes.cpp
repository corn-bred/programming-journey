#include "scenes.h"
#include "game.h"          
#include <cornjam/inputmanager.h>  
#include <misc/globals.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

//PlayingScene

void PlayingScene::Init() {
}

void PlayingScene::Update() {
}

void PlayingScene::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Test test");

    ImGui::SliderFloat("Slider", &fTemp, -10.0, 10.0);
    
    ImGui::Checkbox("Check", &bTemp);

    const char *mTemp[] = {"Type 1", "Type 2", "Type 3"};
    
    ImGui::Combo("Mode", &ModeChoice, mTemp, IM_ARRAYSIZE(mTemp));

    if (ImGui::Button("Press me")) 
        ButtonState = ButtonState ? false : true;

    if (ButtonState)
        ImGui::Text("You pressed the button!");

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void PlayingScene::Exit() {
}