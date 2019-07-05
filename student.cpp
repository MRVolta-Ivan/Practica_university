#include "student.h"

int Student::CountOfStudent = 0;

Student::Student(ObjectOnMap* _purpose):ObjectOnMap (0, 0)
{
    //Разобраться с рандомом.
    NameStudent = "Student " + to_string(CountOfStudent++);
    width = 20 + rand() % 21;
    speed = 30 + rand() % 21;
    satiety = 50 + rand() % 51;
    ObjectPurpose = _purpose;
    IndexX = ObjectPurpose->GetX();
    IndexY = ObjectPurpose->GetY();
}

void Student::SetPurpose(ObjectOnMap* _purpose)
{
    ObjectPurpose = _purpose;
}

ObjectOnMap* Student::GetPurpose()
{
    return ObjectPurpose;
}

int Student::GetSatiety()
{
    return satiety;
}

void Student::AfterLecture()
{
    satiety -= 20;
    if (satiety < 0)
        satiety = 0;
}

void Student::AfterStall()
{
    satiety += 55;
}

void Student::update(int x, int y)
{
    IndexX = x;
    IndexY = y;
}

int Student::GetCountStudent()
{
    return CountOfStudent;
}

int Student::GetWidth()
{
    return width;
}
