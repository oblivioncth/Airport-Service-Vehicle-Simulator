#ifndef PATHING_H
#define PATHING_H

#include <QString>

using namespace std;

class Coordinates{
public:
    int x;
    int y;
    int count;
};

void fnSetupGrid();
vector<Coordinates> fnFindPath(int startX, int startY, int endX, int endY);
vector<Coordinates> selectPath(vector<Coordinates> list, int startX, int startY, int startCount);
bool fnCheckPathBlock(vector<Coordinates> vList, int iCurrentXGrid[], int iCurrentYGrid[], int iCarIndex);
void fnUpdateGrid(int iCarIndex, int iCurrentXGrid[], int iCurrentYGrid[], QString qsMode);

#endif // PATHING_H
