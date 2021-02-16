#ifndef __LEVEL_H__
#define __LEVEL_H__

struct level {
    double startX, startY;
    double startFuel;
    int obstacles;
    int map[75][100];
} level[10];

#endif // __LEVEL_H__
