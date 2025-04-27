#ifndef UTILS_H
#define UTILS_H

enum Direction {
    LEFT,
    RIGHT,
    DOWN,
    UP
};

struct Location {

    int level, x, y;

    Location(int level, int x, int y) : level(level), x(x), y(y) {}
    Location addDir(Direction dir) const {
        switch (dir) {
            case LEFT:
                return Location(level, x-1, y);
            case RIGHT:
                return Location(level, x+1, y);
            case UP:
                return Location(level, x, y-1);
            case DOWN:
                return Location(level, x, y+1);
            default:
                return Location(*this);
        }
    };
    Location addLevel(int dl) const {
        return Location(level + dl, x, y);
    }

};

#endif