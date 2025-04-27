#include "movableEntity.h"
#include "hollow.h"
// #include <iostream>
// using namespace std;
// ==== Complete your tasks after this line ====

bool MovableEntity::update(MovableEntity *fromEntity, Direction toDir)
{
    BlockEntity *curEntity = hollow->getBlockEntityFromLoc(loc);
    Location next = loc.addDir(toDir);
    if (hollow->locInHollow(next) == false)
    {
        return false;
    }
    BlockEntity *nextEntity = hollow->getBlockEntityFromLoc(next);
    if (fromEntity == nullptr)
    {
        if (nextEntity->mentity == nullptr)
        {
            if (nextEntity->update(this, toDir) == true)
            {
                Location to=this->loc.addDir(toDir);
                hollow->moveMentityFromTo(this, this->loc, to);
                curEntity->onLeave(this);
                nextEntity->onStep(this);
                return true;
            }
            return false;
        }
        return nextEntity->mentity->update(this, toDir);
    }
    else
    {
        BlockEntity *preEntity = hollow->getBlockEntityFromLoc(fromEntity->loc);
        if (nextEntity->mentity == nullptr)
        {
            if (nextEntity->update(this, toDir) == true)
            {
                Location temp=loc;
                hollow->moveMentityFromTo(this, this->loc, next);
                curEntity->onLeave(this);
                nextEntity->onStep(this);
                hollow->moveMentityFromTo(fromEntity, fromEntity->loc,temp);
                preEntity->onLeave(fromEntity);
                curEntity->onStep(fromEntity);
                return true;
            }
            return false;
        }
        else
        {
            if (nextEntity->mentity->update(this, toDir) == true)
            {
                hollow->moveMentityFromTo(fromEntity, fromEntity->loc, fromEntity->loc.addDir(toDir));
                preEntity->onLeave(fromEntity);
                curEntity->onStep(fromEntity);
                return true;
            }
            return false;
        }
    }
}

bool Box::update(MovableEntity *fromEntity, Direction toDir)
{
    if (fromEntity == nullptr)
    {
        return true;
    }
    if (fromEntity->isBangBoo() == false)
    {
        return this->MovableEntity::update(fromEntity, toDir);
    }
    if (this->MovableEntity::update(fromEntity, toDir) == true)
    {
        return true;
    }
    BlockEntity *curEntity = hollow->getBlockEntityFromLoc(this->loc);
    BlockEntity *preEntity = hollow->getBlockEntityFromLoc(fromEntity->loc);
    Location temp=fromEntity->loc;
    hollow->moveMentityFromTo(fromEntity, fromEntity->loc, fromEntity->loc.addDir(toDir));
    hollow->moveMentityFromTo(this, this->loc,temp);
    curEntity->onLeave(this);
    curEntity->onStep(fromEntity);
    preEntity->onLeave(fromEntity);
    preEntity->onStep(this);
    return true;
}
