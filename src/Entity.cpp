#include "./Entity.h"

Entity::Entity(EntityManager& manager): manager(manager){
    this->isActive = true;
}

// parameters and then : initialize manager(manager) and name(name)...
Entity::Entity(EntityManager& manager, std::string name): manager(manager), name(name){
    this->isActive = true;
}

void Entity::Update(float deltaTime) {
    // loop through all the components and update them...
    for (auto& component: components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
    for(auto& component: components) {
        component->Render();
    }
}

void Entity::Destroy() {
    this->isActive = false;
}

void Entity::ListAllComponents() const {
    for (auto& mapElement: componentTypeMap) {
        std::cout << "  Component<" << mapElement.first->name() << ">" << std::endl;
    }
}

bool Entity::IsActive() const {
    return this->isActive;
}