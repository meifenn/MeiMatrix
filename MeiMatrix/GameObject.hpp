// GameObject.hpp
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>
#include <memory>
#include "Component.hpp"
#include "TransformComponent.hpp"

class GameObject {
public:
    std::vector<std::shared_ptr<Component>> components;

    template<typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args&&... args) {
        auto comp = std::make_shared<T>(std::forward<Args>(args)...);
        components.push_back(comp);
        return comp;
    }

    template<typename T>
    std::shared_ptr<T> getComponent() {
        for (auto& c : components) {
            if (auto t = std::dynamic_pointer_cast<T>(c))
                return t;
        }
        return nullptr;
    }

    void update() {
        for (auto& c : components) {
            c->update();
        }
    }
};
#endif
