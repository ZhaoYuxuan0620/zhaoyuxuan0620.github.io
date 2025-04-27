#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "utils.h"

class MovableEntity;
class Hollow;

class Entity {

    public:
        Hollow* hollow;
        Location loc;

        Entity(Hollow* hollow, const Location& loc) : hollow(hollow), loc(loc) {}
        virtual ~Entity() = default;

        // Return a ptr by "new" using the object copy's constructor
        virtual Entity* newPtr() const = 0;
        // String repr of the entity
        virtual std::string toString() const = 0;
        // Update the current entity when being pushed
        virtual bool update(MovableEntity* fromEntity, Direction toDir) = 0;

};

#endif