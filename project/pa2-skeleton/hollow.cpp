#include "hollow.h"

using namespace std; 

// ==== Complete your tasks after this line ====

Hollow::Hollow(int levels, int height, int width):levels(levels),height(height),width(width)
{
    grid=new BlockEntity***[levels];
    for(int i=0;i<levels;i++)
    {
        grid[i]=new BlockEntity**[height];
        for(int j=0;j<height;j++)
        {
            grid[i][j]=new BlockEntity*[width];
            for(int k=0;k<width;k++)
            {
                struct Location loc(i,k,j);
                grid[i][j][k]=new Empty(this,loc);
            }
        }
    }
}

Hollow::~Hollow()
{
    for(int i=0;i<levels;i++)
    {
        for(int j=0;j<height;j++)
        {
            for(int k=0;k<width;k++)
            {
                delete grid[i][j][k]->mentity;
                delete grid[i][j][k];
            }
            delete[] grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}

BlockEntity *Hollow::registerBlockEntity(const BlockEntity &bentity)
{
    Location loc=bentity.loc;
    delete grid[loc.level][loc.y][loc.x];// de-allocate memory of empty
    grid[loc.level][loc.y][loc.x]=bentity.newPtr();
    return grid[loc.level][loc.y][loc.x];
}

MovableEntity *Hollow::registerMovableEntity(const MovableEntity &mentity)
{
    Location loc=mentity.loc;
    grid[loc.level][loc.y][loc.x]->mentity=mentity.newPtr();
    return grid[loc.level][loc.y][loc.x]->mentity;
}

BangBoo *Hollow::registerBangBoo(const BangBoo &bangboo)
{
    if(this->bangboo!=nullptr)
    {
        return nullptr;
    }
    Location loc=bangboo.loc;
    this->bangboo=bangboo.newPtr();
    grid[loc.level][loc.y][loc.x]->mentity=this->bangboo;
    return this->bangboo;
}

bool Hollow::locInHollow(const Location &loc) const
{
    if(loc.level<0||loc.level>=levels)
    {
        return false;
    }
    else if(loc.x<0||loc.x>=width)
    {
        return false;
    }
    else if(loc.y<0||loc.y>=height)
    {
        return false;
    }
    else{
        return true;
    }
}

void Hollow::print() const
{
    int curlevel=bangboo->loc.level;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            cout<<"+ - ";
        }
        cout<<"+"<<endl;
        for(int j=0;j<width;j++)
        {
            cout<<"| "<<grid[curlevel][i][j]->toString()<<" ";
        }
        cout<<"|"<<endl;
    }
    for(int j=0;j<width;j++)
    {
        cout<<"+ - ";
    }
    cout<<"+"<<endl;
}
