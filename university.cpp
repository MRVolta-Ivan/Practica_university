#include "university.h"

University* University::single = nullptr;

University* University::GetUniversity()
{
    if (!single)
            single = new University();
    return single;
}

bool University::DeleteUniversity()
{
    if (single)
    {
        delete single;
        single = nullptr;
        return true;
    }
    return false;
}

University::University()
{
    MapUniversity = new Map();

    srand((unsigned int) time(nullptr));

    timetocall = 3 * Student::GetCountStudent();
    islecture = false;

    MapUniversity->changepurpose(islecture, 30);
}

University::~University()
{

}

void University::update()
{
    timetocall--;

    //Когда время до звонка законилось
    if(timetocall == 0)
    {
        //в зависимости от текущего состояния мы обновляем время и измением состояние на противоположное, меняем цели для студентов
        if (islecture)
        {
          islecture = false;
          timetocall = 3 * Student::GetCountStudent();
        }
        else
        {
            islecture = true;
            timetocall = 30;
        }
        MapUniversity->changepurpose(islecture, 30);
    }

    MapUniversity->update(islecture);
}

char** University::GetMap()
{
    return MapUniversity->GetMap();
}

vector<Student*> University::GetListStudent()
{
    return MapUniversity->GetListStudent();
}

int University::GetMapWidth()
{
    return MapUniversity->GetMapWidth();
}

int University::GetMapLength()
{
    return MapUniversity->getMapLength();
}

bool University::GetStatus()
{
    return islecture;
}

int University::GetTime()
{
    return timetocall;
}

vector<Stall*> University::GetListStall()
{
    return MapUniversity->GetListStall();
}
