#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include"map.h"
#include<time.h>

class University
{
private:
    static University *single; //Единственный объект университет
    University();
    ~University();

    Map* MapUniversity; //Карта университета
    int timetocall; //Время до звонка
    bool islecture; //Состояние университета

public:
    static University* GetUniversity();
    static bool DeleteUniversity();
    void update();
    char** GetMap();
    vector<Student*> GetListStudent();
    vector<Stall*> GetListStall();
    int GetMapWidth();
    int GetMapLength();
    bool GetStatus();
    int GetTime();
};

#endif // UNIVERSITY_H
