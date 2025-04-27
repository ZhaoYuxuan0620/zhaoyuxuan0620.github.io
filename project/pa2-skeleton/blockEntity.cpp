#include "blockEntity.h"
#include "hollow.h"

// ==== Complete your tasks after this line ====

void Switch::onStep(MovableEntity *mentity)
{
    // this->mentity = mentity;
    isOn = true;
    for (int i = 0; i < doorNum; i++)
    {
        Door *door = lockDoors[i];
        door->updateDoor();
    }
}

void Button::onLeave(MovableEntity *mentity)
{
    // this->mentity = nullptr;
    isOn = false;
    for (int i = 0; i < doorNum; i++)
    {
        Door *door = lockDoors[i];
        door->updateDoor();
    }
}

void Portal::onStep(MovableEntity *mentity)
{
    // this->mentity = mentity;
    if (mentity->isBangBoo())
    {
        Location from = mentity->loc;
        Location to = mentity->loc;
        if (this->directionDown)
        {
            to.level--;
        }
        else
        {
            to.level++;
        }
        if (hollow->getBlockEntityFromLoc(to)->mentity != nullptr)
        {
            delete hollow->getBlockEntityFromLoc(to)->mentity;
        }
        hollow->moveMentityFromTo(mentity, from, to);
        return;
    }
}

void Goal::onStep(MovableEntity *mentity)
{
    // this->mentity = mentity;
    if (mentity->isBangBoo())
    {
        hollow->reachedGoal();
    }
}

bool BlockEntity::update(MovableEntity *fromEntity, Direction toDir)
{
    if (this->mentity == nullptr)
    {
        return true;
    }
    return this->mentity->update(fromEntity, toDir);
}

bool Wall::update(MovableEntity *fromEntity, Direction toDir)
{
    return false;
}

bool Door::update(MovableEntity *fromEntity, Direction toDir)
{
    if (locked)
    {
        return false;
    }
    return BlockEntity::update(fromEntity, toDir);
}
