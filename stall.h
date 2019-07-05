#ifndef STALL_H
#define STALL_H

#include<vector>
#include"student.h"

using namespace std;

class Stall : public ObjectOnMap
{
private:
    int CountOfBun;
   //vector<Student*> ListStudents;
    Student* customer;
public:
    Stall(int x, int y);
    Student* update();
    void UpdateCountOfBun(); //Обновляет количество булочек в буфете
    int GetCountBun();
    void SetCustomer(Student* student);
};

#endif // STALL_H
