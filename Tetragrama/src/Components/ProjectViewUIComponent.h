#pragma once
#include <string>
#include <ZEngine/ZEngine.h>

namespace Tetragrama::Components {
    class ProjectViewUIComponent : public ZEngine::Components::UI::UIComponent {
    public:
        ProjectViewUIComponent(std::string_view name = "Project", bool visibility = true);
        virtual ~ProjectViewUIComponent();

        void Update(ZEngine::Core::TimeStep dt) override;

        virtual void Render() override;

    protected:
        virtual bool OnUIComponentRaised(ZEngine::Components::UI::Event::UIComponentEvent&) override;
    };
} // namespace Tetragrama::Components
