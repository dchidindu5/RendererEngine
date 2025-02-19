#include <pch.h>
#include <SceneViewportUIComponent.h>
#include <ZEngine/Logging/LoggerDefinition.h>
#include <Layers/UILayer.h>
#include <Event/EventDispatcher.h>
#include <Messengers/Messenger.h>
#include <MessageToken.h>

using namespace ZEngine::Components::UI::Event;
using namespace Tetragrama::Components::Event;
using namespace ZEngine::Rendering::Renderers;
using namespace ZEngine::Hardwares;
using namespace ZEngine::Rendering;


namespace Tetragrama::Components
{
    SceneViewportUIComponent::SceneViewportUIComponent(std::string_view name, bool visibility) : UIComponent(name, visibility, false) {}

    SceneViewportUIComponent::~SceneViewportUIComponent() {}

    void SceneViewportUIComponent::Update(ZEngine::Core::TimeStep dt)
    {
        if ((m_viewport_size.x != m_content_region_available_size.x) || (m_viewport_size.y != m_content_region_available_size.y))
        {
            m_viewport_size = m_content_region_available_size;

            GraphicRenderer::SetViewportSize(m_viewport_size.x, m_viewport_size.y);
            m_refresh_texture_handle = true;

            Messengers::IMessenger::SendAsync<ZEngine::Layers::Layer, Messengers::GenericMessage<std::pair<float, float>>>(
                EDITOR_RENDER_LAYER_SCENE_REQUEST_RESIZE, Messengers::GenericMessage<std::pair<float, float>>{{m_viewport_size.x, m_viewport_size.y}});
        }

        if (m_is_window_hovered && m_is_window_focused)
        {
            Messengers::IMessenger::SendAsync<ZEngine::Components::UI::UIComponent, Messengers::GenericMessage<bool>>(
                EDITOR_COMPONENT_SCENEVIEWPORT_FOCUSED, Messengers::GenericMessage<bool>{true});
        }
        else
        {
            Messengers::IMessenger::SendAsync<ZEngine::Components::UI::UIComponent, Messengers::GenericMessage<bool>>(
                EDITOR_COMPONENT_SCENEVIEWPORT_UNFOCUSED, Messengers::GenericMessage<bool>{false});
        }

        if (m_is_window_clicked && m_is_window_hovered && m_is_window_focused)
        {
            auto mouse_position = ImGui::GetMousePos();
            mouse_position.x -= m_viewport_bounds[0].x;
            mouse_position.y -= m_viewport_bounds[0].y;

            auto mouse_bounded_x = static_cast<int>(mouse_position.x);
            auto mouse_bounded_y = static_cast<int>(mouse_position.y);
            auto message_data = std::array{mouse_bounded_x, mouse_bounded_y};
            Messengers::IMessenger::SendAsync<ZEngine::Components::UI::UIComponent, Messengers::ArrayValueMessage<int, 2>>(
                EDITOR_COMPONENT_SCENEVIEWPORT_CLICKED, Messengers::ArrayValueMessage<int, 2>{message_data});
        }
    }

    void SceneViewportUIComponent::Render()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin(m_name.c_str(), (m_can_be_closed ? &m_can_be_closed : NULL), ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

        auto viewport_offset = ImGui::GetCursorPos();

        m_content_region_available_size = ImGui::GetContentRegionAvail();
        m_is_window_focused             = ImGui::IsWindowFocused();
        m_is_window_hovered             = ImGui::IsWindowHovered();
        m_is_window_clicked             = ImGui::IsMouseClicked(static_cast<int>(ZENGINE_KEY_MOUSE_LEFT));

        // ImGuizmo configuration
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

        // Scene texture representation
        if (!m_scene_texture || m_refresh_texture_handle)
        {
            auto frame_output = GraphicRenderer::GetFrameOutput();
            auto buffer       = frame_output->GetColorAttachmentCollection().at(0);

            if (m_refresh_texture_handle)
            {
                VkDescriptorSet old_scene_texture = m_scene_texture;
                m_scene_texture                   = VK_NULL_HANDLE;
                m_refresh_texture_handle          = false;
            }
            m_scene_texture = ImGui_ImplVulkan_AddTexture(buffer->GetSampler(), buffer->GetImageViewHandle(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        }

        ImGui::Image(m_scene_texture, m_viewport_size, ImVec2(0, 1), ImVec2(1, 0));
        // ViewPort bound computation
        ImVec2 viewport_windows_size = ImGui::GetWindowSize();
        ImVec2 minimum_bound         = ImGui::GetWindowPos();
        minimum_bound.x += viewport_offset.x;
        minimum_bound.y += viewport_offset.y;

        ImVec2 maximum_bound = {minimum_bound.x + viewport_windows_size.x, minimum_bound.y + viewport_windows_size.y};

        m_viewport_bounds[0] = minimum_bound;
        m_viewport_bounds[1] = maximum_bound;

        ImGui::End();

        ImGui::PopStyleVar();
    }

    std::future<void> SceneViewportUIComponent::SceneViewportClickedMessageHandler(Messengers::ArrayValueMessage<int, 2>& e)
    {
        // Messengers::IMessenger::Send<ZEngine::Layers::Layer, Messengers::GenericMessage<std::pair<int, int>>>(
        //     EDITOR_RENDER_LAYER_SCENE_REQUEST_SELECT_ENTITY_FROM_PIXEL, Messengers::GenericMessage<std::pair<int, int>>{e});
        co_return;
    }

    std::future<void> SceneViewportUIComponent::SceneViewportFocusedMessageHandler(Messengers::GenericMessage<bool>& e)
    {
        co_await Messengers::IMessenger::SendAsync<ZEngine::Layers::Layer, Messengers::GenericMessage<bool>>(
            EDITOR_RENDER_LAYER_SCENE_REQUEST_FOCUS, Messengers::GenericMessage<bool>{e});
    }

    std::future<void> SceneViewportUIComponent::SceneViewportUnfocusedMessageHandler(Messengers::GenericMessage<bool>& e)
    {
        co_await Messengers::IMessenger::SendAsync<ZEngine::Layers::Layer, Messengers::GenericMessage<bool>>(
            EDITOR_RENDER_LAYER_SCENE_REQUEST_UNFOCUS, Messengers::GenericMessage<bool>{e});
    }
} // namespace Tetragrama::Components
