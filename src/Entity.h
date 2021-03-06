#ifndef ENTITY.H
#define ENTITY.H

#include <iostream>
#include <string>
#include <map>
#include <typeinfo>
#include <vector>
#include <string>
#include "./EntityManager.h"
#include "./Component.h"

class Component;
class EntityManager;

class Entity {
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap; // Map to keep track on type and components...
    public:
        std::string name;
        Entity(EntityManager& manager); // & is that this is going to receive reference...?
        Entity(EntityManager& manager, std::string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        void ListAllComponents() const;
        bool IsActive() const;

        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args) {
            T* newComponent(new T(std::forward<TArgs>(args)...));
            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentTypeMap[&typeid(*newComponent)] = newComponent;
            newComponent->Initialize();

            
            return *newComponent;
        }

        template <typename T>
        T* GetComponent() {
            return static_cast<T*>(componentTypeMap[&typeid(T)]);
        }

        template <typename T>
        bool HasComponent() const {
            // #######
            // TODO!!!
            // *******
        }

};

#endif