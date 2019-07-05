#ifndef STUDENT_H
#define STUDENT_H

#include<string>
#include<stdlib.h>
#include<vector>
#include"objectonmap.h"

using namespace std;

class Student : public ObjectOnMap
{
private:
    static int CountOfStudent; //Общее количество студентов
    string NameStudent; //Имя студента
    int width; //ширина студента
    int speed; //Скорость студента
    int satiety; //Сытость студента
    ObjectOnMap* ObjectPurpose; //Цель студента
public:
    Student(ObjectOnMap* _purpose);
    void SetPurpose(ObjectOnMap* _purpose);
    ObjectOnMap* GetPurpose();
    int GetSatiety();
    void AfterLecture(); //Обновление сытости после лекции
    void AfterStall(); //Обносление сытости после буфета
    void update(int x, int y);
    static int GetCountStudent();
    int GetWidth();
};

#endif // STUDENT_H
