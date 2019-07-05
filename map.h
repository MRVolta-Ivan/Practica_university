#ifndef MAP_H
#define MAP_H

#include"stall.h"
#include"classroom.h"
#include<fstream>

class Map
{
private:
    int width; //Ширина карты
    int length; //Длина карты
    char** TableMap; //Массив элементов карты
    vector<Student*> ListStudent; //Список студентов
    vector<Classroom*> ListClassrooms; //Список аудиторий
    vector<Stall*> ListStore; //Список буфетов
public:
    Map();
    void update(bool status);
    void changepurpose(bool status, int time);
    vector<int> FindRoute(int x, int y, int purpX, int purpY); //Ищет маршрут от первых до вторых коодинат
    ObjectOnMap* FindStall(int x, int y); //Ищет ближайший буфет от текущих координат
    char** GetMap();
    vector<Student*> GetListStudent();
    int GetMapWidth();
    int getMapLength();
    vector<Stall*> GetListStall();
};

#endif // MAP_H
