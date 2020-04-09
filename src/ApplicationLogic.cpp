#include <Application.hpp>
#include <array>
#include <ImGui.hpp>
#include <imgui.h>
#include <iostream>
#include <ratio>

static double elapsed;
static float fov = glm::radians(60.0f);
static int max_frame_rate = 60;
static double last_frame;

static bool debug_window = true;

void Application::update(double delta)
{
    if (debug_window) {
        if (ImGui::Begin("Test", &debug_window)) {
            ImGui::SliderAngle("FOV", &fov, 1, 180, "%.3f deg");
            ImGui::SliderInt("Max Frame Rate", &max_frame_rate, 5, 145, max_frame_rate == 145 ? " Unlimited" : "%d fps");
        }
        ImGui::End();
    }

    elapsed += delta;

    // we don't actually sleep, to keep updating on user input,
    // even though they may not see the effects just yet
    if (max_frame_rate == 145 || elapsed - last_frame >= 1.0 / max_frame_rate) {
        m_needs_redraw = true;
        last_frame = elapsed;
    } else {
        m_needs_redraw = false;
    }
}

void Application::on_event(const sf::Event& event)
{

    if (event.type == sf::Event::Closed) {
        m_window.close();
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::F3) {
            debug_window = !debug_window;
        }
    }
}

#include <glm/gtx/io.hpp>

void Application::render()
{
    glDepthFunc(GL_LESS);
    glDepthMask(true);
    glEnable(GL_DEPTH_TEST);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0.25, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_program.bind();
    vertex_array.bind();

    glActiveTexture(GL_TEXTURE0);
    texture1.bind();

    glm::ivec4 viewport;
    glGetIntegerv(GL_VIEWPORT, &viewport.x);

    glm::mat4 model = glm::rotate(glm::mat4 { 1.0 }, glm::radians(static_cast<float>(elapsed * 100)), glm::vec3 { 0.0, 1.0, 0.0 });
    glm::mat4 view = glm::translate(glm::mat4 { 1.0 }, glm::vec3 { 0.0, 0.0, -3.0 });
    glm::mat4 projection = glm::perspectiveFov(fov, static_cast<float>(viewport.z), static_cast<float>(viewport.w), 0.1f, 100.0f);

    shader_program.uniform("modelMatrix", model);
    shader_program.uniform("viewMatrix", view);
    shader_program.uniform("projectionMatrix", projection);
    shader_program.uniform("texture1", 0);

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}
