#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <miniaudio.h>
#include "SoundManager.hpp"

#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "GameObject.hpp"

using namespace MEI;

const char* vShader = R"(
#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord;
layout(location=3) in vec3 aNormal;

out vec3 vertexColor;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform float size;
uniform mat4 model, view, projection;

void main() {
    vec4 worldPos = model * vec4(aPos.x*size, aPos.y*size, aPos.z*size, 1.0);
    fragPos = vec3(worldPos);
    gl_Position = projection * view * worldPos;
    vertexColor = aColor;
    texCoord = aTexCoord;
    normal= normalize(aNormal);
}
)";

const char* fShader = R"(
#version 330 core
in vec3 vertexColor;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;
uniform sampler2D mytexture;
uniform float ambientIntensity;
uniform vec3 lightPos;

vec3 lightColor;
vec3 finalLight;

void main() {
    lightColor = vec3(1.0);
    vec3 lightDirection = normalize(lightPos-fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffLight = diff * lightColor;
    vec3 ambientLight = ambientIntensity * lightColor;
    finalLight = ambientLight + diffLight;
    FragColor = vec4(finalLight ,1.0) * texture(mytexture, texCoord);
}
)";

int main(void) {
    MEI::SoundManager soundManager;
    if (soundManager.init() < 0) {
        std::cout << "Sound Init is Failed.";
        return -1;
    }
    soundManager.playMusic("assets/bgmusic.mp3");

    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* win = glfwCreateWindow(800, 600, "One Textured Square", NULL, NULL);
    glfwMakeContextCurrent(win);
    glewInit();

    glEnable(GL_DEPTH_TEST);

    Shader shader(vShader, fShader);
    Texture texture("assets/texture.png");
    Camera camera;
    Mesh mesh;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init();

    GameObject square;
    auto transform = square.addComponent<TransformComponent>();

    glm::vec3 camPos(0, 0, 1), camCenter(0);
    glm::vec3 lightPos(3.0f, 3.0f, 3.0f);
    float size = 1.0f;
    float ambientIntensity = 0.5f;

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        texture.bind();

        glm::mat4 view = camera.getView(camPos, camCenter);
        glm::mat4 proj = camera.getProjection(800.0f / 600.0f);
        shader.setFloat("size", size);
        shader.setMat4("view", view);
        shader.setMat4("projection", proj);
        shader.setInt("mytexture", 0);
        shader.setFloat("ambientIntensity", ambientIntensity);
        shader.setVec3("lightPos", lightPos);

        shader.setMat4("model", transform->getModelMatrix());
        mesh.draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Inspector");
        ImGui::SliderFloat("Size", &size, 0.1f, 3.0f);
        ImGui::DragFloat3("Position", &transform->position.x, 0.1f);
        ImGui::DragFloat3("Rotation", &transform->rotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &transform->scale.x, 0.1f);
        ImGui::DragFloat3("Camera Position", &camPos.x, 0.1f);
        ImGui::DragFloat3("Camera Center", &camCenter.x, 0.1f);
        ImGui::Spacing();
        ImGui::DragFloat3("Light Position", &lightPos.x, -0.1f, 0.1f);
        ImGui::SliderFloat("Ambient Intensity", &ambientIntensity, 0.0f, 1.0f);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(win);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
