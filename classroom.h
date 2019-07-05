#ifndef CLASSROOM_H
#define CLASSROOM_H

#include"objectonmap.h"
#include<stdlib.h>
#include<ctime>

class Classroom : public ObjectOnMap
{
private:
    int ClassroomNumber; //Номер комнаты
    int timelecture; //Время занятия
    static const int StudentsInClassroom = 5; //Примерное количество студентов в одной аудитории
    bool status; //Статус, который информирует о проведении занятия
public:
    Classroom(int numberm, int x, int y);
    int GetNumber();
    bool update();
    static int GetStudentInClassroom();
    void SetTimeLecture(int time);
    int GetTime();
    void UpdateStatus();
    bool GetStatus();
};

#endif // CLASSROOM_H
