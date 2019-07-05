#include "classroom.h"

Classroom::Classroom(int number, int x, int y) : ObjectOnMap(x, y)
{
    ClassroomNumber = number;
    timelecture = 0;
    status = false;
}

int Classroom::GetNumber()
{
    return ClassroomNumber;
}

bool Classroom::update()
{
    if (timelecture > 0 && status)
        timelecture--;
    else
    {
        status = false;
    }
    return !status;
}

int Classroom::GetStudentInClassroom()
{
    return StudentsInClassroom;
}

void Classroom::SetTimeLecture(int time)
{
    int random = rand() % 11;
    if (random < 6)
        random *= -1;
    else
        random -= 5;
    timelecture = time + random;
}

int Classroom::GetTime()
{
    return timelecture;
}

void Classroom::UpdateStatus()
{
    status = !status;
}

bool Classroom::GetStatus()
{
    return status;
}
