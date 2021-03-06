#pragma once

#include "core/events/event.hpp"

#include <string>

namespace engine::core
{
    class Layer
    {
    public:
        explicit Layer(std::string_view name = "Layer") : debug_name_(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnEvent(events::Event &) {}

        [[nodiscard]] std::string_view name() const { return debug_name_; }

    private:
        std::string debug_name_;
    };
} // namespace engine::core