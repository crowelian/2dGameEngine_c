#ifndef ENTITYMANAGER.H
#define ENTITYMANAGER.H

#include "./Entity.h"
#include "./Component.h"
#include <vector>

class EntityManager {
    private:
        std::vector<Entity*> entities;
    public:
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities();
        void ListAllEntities() const;
        Entity& AddEntity(std::string entityName);
        std::vector<Entity*> GetEntities() const;
        unsigned int GetEntityCount();

};

#endif