#include <vector>
#include "pathing.h"
#include "mainwindow.h"
#include <QDebug>

using namespace std;

bool grid[80][60];

bool fnCheckPathBlock(vector<Coordinates> vList,int iCurrentXGrid[8],int iCurrentYGrid[8], int iCarIndex)
{
    if(vList.size() >= 1)
    {
        for(int i = 0; i < 1; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if((vList.at(i).x == iCurrentXGrid[j] && vList.at(i).y == iCurrentYGrid[j]) && iCarIndex != j)

                {
                    return true;
                }
            }
        }
     }
     else
     {
        for(int i = 0; i < vList.size(); i++){
            for(int j = 0; j < 8; j++)
            {
                if((vList.at(i).x == iCurrentXGrid[j] && vList.at(i).y == iCurrentYGrid[j]) && iCarIndex != j)

                {
                    return true;
                }
            }
        }
     }
    return false;
}

void fnUpdateGrid(int iCarIndex,int iCurrentXGrid[8],int iCurrentYGrid[8],QString qsMode)
{
   for(int i = 0; i < 8; i++)
   {
       if(iCarIndex != i)
       {
           if(qsMode == "Set")
                grid[iCurrentXGrid[i]][iCurrentYGrid[i]] = false; //Where car is
           if(qsMode == "Reset")
                grid[iCurrentXGrid[i]][iCurrentYGrid[i]] = true; //Where car is
           qDebug() << "x:" << iCurrentXGrid[i] << " y:" << iCurrentYGrid[i];
       }
   }
}


void fnSetupGrid()
{
    for (int x = 0; x < 80; x++) {
            for (int y = 0; y < 60; y++) {
                grid[x][y] = true;
            }
        }

        for (int x = 0; x <= 79 ; x++) {
            grid[x][0] = false;
        }

        for (int y = 0; y <= 59; y++) {
            grid[0][y] = false;
        }

        for (int x = 0; x <= 79; x++) {
            grid[x][59] = false;
        }

        for (int y = 0; y <= 59; y++) {
            grid[79][y] = false;
        }

        for (int y = 3; y <= 55; y++) {
            grid[12][y] = false;
        }

        for (int y = 3; y <= 50; y++) {
            grid[18][y] = false;
        }

        for (int x = 12; x <= 48; x++) {
            grid[x][55] = false;
        }

        for (int x = 18; x <= 48; x++) {
            grid[x][49] = false;
        }

        for (int x = 27; x <= 33; x++) {
            grid[x][2] = false;
        }

        for (int y = 2; y <= 10; y++) {
            grid[27][y] = false;
        }

        for (int y = 2; y <= 10; y++) {
            grid[33][y] = false;
        }

        for (int x = 39; x <= 45; x++) {
            grid[x][2] = false;
        }

        for (int y = 2; y <= 10; y++) {
            grid[39][y] = false;
        }

        for (int y = 2; y <= 10; y++) {
            grid[45][y] = false;
        }

        for (int x = 51; x <= 74; x++) {
            grid[x][2] = false;
        }

        for (int y = 2; y <= 10; y++) {
            grid[51][y] = false;
        }

        for (int y = 2; y <= 8; y++) {
            grid[74][y] = false;
        }

        for (int x = 60; x <= 74; x++) {
            grid[x][8] = false;
        }

        for (int y = 5; y <= 8; y++) {
            grid[60][y] = false;
        }

        for (int x = 54; x <= 60; x++) {
            grid[x][5] = false;
        }

        for (int y = 5; y <= 10; y++) {
            grid[54][y] = false;
        }


        for (int x = 63; x <= 69; x++) {
            grid[x][10] = false;
        }

        for (int y = 10; y <= 18; y++) {
            grid[63][y] = false;
        }

        for (int y = 10; y <= 18; y++) {
            grid[69][y] = false;
        }

        for (int x = 71; x <= 77; x++) {
            grid[x][10] = false;
        }

        for (int y = 10; y <= 18; y++) {
            grid[71][y] = false;
        }

        for (int y = 10; y <= 18; y++) {
            grid[77][y] = false;
        }

        for (int y = 39; y <= 47; y++) {
            grid[37][y] = false;
        }

        for (int x = 37; x <= 43; x++) {
            grid[x][47] = false;
        }

        for (int y = 39; y <= 47; y++) {
            grid[43][y] = false;
        }

        for (int x = 22; x <= 29; x++) {
            grid[x][47] = false;
        }

        for (int y = 41; y <= 47; y++) {
            grid[22][y] = false;
        }

        for (int x = 22; x <= 24; x++) {
            grid[x][41] = false;
        }

        for (int y = 30; y <= 41; y++) {
            grid[24][y] = false;
        }

        for (int x = 24; x <= 29; x++) {
            grid[x][30] = false;
        }

        for (int y = 41; y <= 47; y++) {
            grid[29][y] = false;
        }

        for (int x = 27; x <= 29; x++) {
            grid[x][41] = false;
        }

        for (int y = 33; y <= 41; y++) {
            grid[27][y] = false;
        }

        for (int x = 27; x <= 29; x++) {
            grid[x][33] = false;
        }


        for (int x = 7; x <= 12; x++) {
            grid[x][25] = false;
        }

        for (int x = 18; x <= 29; x++) {
            grid[x][25] = false;
        }

        for (int y = 23; y <= 25; y++) {
            grid[7][y] = false;
        }

        for (int x = 2; x <= 7; x++) {
            grid[x][23] = false;
        }

        for (int y = 23; y <= 30; y++) {
            grid[2][y] = false;
        }


        for (int x = 2; x <= 7; x++) {
            grid[x][30] = false;
        }

        for (int y = 28; y <= 30; y++) {
            grid[7][y] = false;
        }

        for (int x = 7; x <= 12; x++) {
            grid[x][28] = false;
        }

        for (int x = 18; x <= 29; x++) {
            grid[x][28] = false;
        }

        for (int y = 45; y <= 50; y++) {
            grid[73][y] = false;
        }

        for (int x = 67; x <= 73; x++) {
            grid[x][50] = false;
        }

        for (int y = 50; y <= 57; y++) {
            grid[67][y] = false;
        }

        for (int x = 67; x <= 77; x++) {
            grid[x][57] = false;
        }

        for (int y = 45; y <= 57; y++) {
            grid[77][y] = false;
        }

        for (int x = 20; x <= 26; x++) {
            grid[x][12] = false;
        }

        for (int y = 12; y <= 19; y++) {
            grid[20][y] = false;
        }

        for (int x = 20; x <= 26; x++) {
            grid[x][19] = false;
        }

        for (int y = 12; y <= 19; y++) {
            grid[26][y] = false;
        }

        for (int y = 16; y <= 20; y++) {
            grid[35][y] = false;
        }

        for (int x = 35; x <= 41; x++) {
            grid[x][20] = false;
        }

        for (int y = 20; y <= 27; y++) {
            grid[41][y] = false;
        }

        for (int x = 41; x <= 43; x++) {
            grid[x][27] = false;
        }

        for (int y = 27; y <= 31; y++) {
            grid[43][y] = false;
        }


        for (int x = 43; x <= 52; x++) {
            grid[x][31] = false;
        }

        for (int y = 27; y <= 31; y++) {
            grid[52][y] = false;
        }

        for (int x = 49; x <= 52; x++) {
            grid[x][27] = false;
        }

        for (int y = 27; y <= 21; y++) {
            grid[49][y] = false;
        }

        for (int x = 47; x <= 49; x++) {
            grid[x][21] = false;
        }

        for (int y = 16; y <= 21; y++) {
            grid[47][y] = false;
        }

        for (int x = 35; x <= 47; x++) {
            grid[x][16] = false;
        }

        for (int y = 21; y <= 27; y++) {
            grid[58][y] = false;
        }

        for (int y = 21; y <= 27; y++) {
            grid[59][y] = false;
        }

        for (int y = 21; y <= 27; y++) {
            grid[60][y] = false;
        }

        for (int y = 10; y <= 28; y++) {
            grid[70][y] = false;
        }

        for (int x = 68; x <= 72; x++) {
            grid[x][26] = false;
        }

        for (int x = 68; x <= 72; x++) {
            grid[x][27] = false;
        }

        for (int y = 19; y <= 28; y++) {
            grid[69][y] = false;
        }

        for (int y = 19; y <= 28; y++) {
            grid[71][y] = false;
        }

        for (int x = 59; x <= 67; x++) {
            grid[x][39] = false;
        }

        for (int y = 39; y <= 46; y++) {
            grid[67][y] = false;
        }

        for (int x = 59; x <= 67; x++) {
            grid[x][46] = false;
        }

        for (int y = 39; y <= 46; y++) {
            grid[59][y] = false;
        }

        for (int y = 21; y <= 26; y++) {   //grass 2 fix
            grid[49][y] = false;
        }

        //Runway Fix
        grid[12][27] = true;
        grid[12][26] = true;
        grid[18][27] = true;
        grid[18][26] = true;
        grid[18][50] = true;
}

vector<Coordinates> fnFindPath(int startX, int startY, int endX, int endY){
    vector<Coordinates> list1;
    vector<Coordinates> list2;

    //Vector initilized with the end coordinate
    Coordinates end;
    end.x = endX;
    end.y = endY;
    end.count = 0;
    list1.push_back(end);


    for(int i = 0; i < list1.size(); i++){
        Coordinates end1;
        Coordinates end2;
        Coordinates end3;
        Coordinates end4;


        if(list1.at(i).x > -1){
            end1.x = list1.at(i).x - 1;
            end1.y = list1.at(i).y;
            end1.count = list1.at(i).count + 1;
            list2.push_back(end1);
        }

        if(list1.at(i).y < 60){
            end2.x = list1.at(i).x;
            end2.y = list1.at(i).y + 1;
            end2.count = list1.at(i).count + 1;
            list2.push_back(end2);
        }

        if(list1.at(i).x < 80){
            end3.x = list1.at(i).x + 1;
            end3.y = list1.at(i).y;
            end3.count = list1.at(i).count + 1;
            list2.push_back(end3);
        }

        if(list1.at(i).y > -1){
            end4.x = list1.at(i).x;
            end4.y = list1.at(i).y - 1;
            end4.count = list1.at(i).count + 1;
            list2.push_back(end4);
        }

        //Removes coordinates from list2 that are walls
        for(int i = 0; i < list2.size(); i++){
            Coordinates temp = list2.at(i);
            if(!grid[temp.x][temp.y]){
                list2.erase(list2.begin() + i);
                i--;
            }
        }

        //Removes coordinates from list2 that are already in the main list.
        for(int j = 0; j < list1.size(); j++){
            for(int i = 0; i < list2.size(); i++){
                Coordinates temp1 = list1.at(j);
                Coordinates temp2 = list2.at(i);
                if((temp1.x == temp2.x) && (temp1.y == temp2.y) &&((temp1.count == temp2.count)||(temp2.count > temp1.count))){
                    list2.erase(list2.begin() + i);
                    i--;
                }
            }
        }

        //Add all the elements from list2 to list 1
        for(int i = 0; i < list2.size(); i++){
            Coordinates temp = list2.at(i);
            list1.push_back(temp);
        }

        //Delete all elements from list2
        list2.clear();

        //Check list1, if any are the starting position then
        for(int i = 0; i < list1.size(); i++){
            if((list1.at(i).x == startX) && (list1.at(i).y == startY)){
                return selectPath(list1, startX, startY, list1.back().count);
            }
        }
    }
    return list1;
}

vector<Coordinates> selectPath(vector<Coordinates> list, int startX, int startY, int startCount){
    vector<Coordinates> temp;
    vector<Coordinates> choices;
    Coordinates temp2;
    temp2.x = startX;
    temp2.y = startY;
    temp2.count = startCount;
    temp.push_back(temp2);
    for(int i = startCount; i > -1; i--){
        for(int j = 0; j < list.size(); j++){
            if((i - 1) == list.at(j).count){
                choices.push_back(list.at(j));
            }
        }
        Coordinates back = temp.back();
        for(int k = 0; k < choices.size(); k++){
            if((back.x == choices.at(k).x && back.y == choices.at(k).y - 1) || (back.x == choices.at(k).x && back.y == choices.at(k).y + 1) || (back.y == choices.at(k).y && back.x == choices.at(k).x - 1) || (back.y == choices.at(k).y && back.x == choices.at(k).x + 1)){
                temp.push_back(choices.at(k));
                break;
            }
        }
        choices.clear();
    }
    temp.erase(temp.begin());
    return temp;
}
