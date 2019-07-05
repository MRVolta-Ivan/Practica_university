#include "stall.h"

Stall::Stall(int x, int y) : ObjectOnMap(x, y)
{
    CountOfBun = rand() % 10 + 10;
    customer = nullptr;
}

void Stall::UpdateCountOfBun()
{
    CountOfBun = rand() % 10 + 10;
}

Student* Stall::update()
{
    Student* result = nullptr;
    if (customer != nullptr)
    {
        if (IndexX == customer->GetX() && IndexY == customer->GetY())
        {
            if (CountOfBun > 0)
            {
                CountOfBun--;
                customer->AfterStall();
            }
            result = customer;
            customer = nullptr;
        }
    }
    return result;
}

int Stall::GetCountBun()
{
    return CountOfBun;
}

void Stall::SetCustomer(Student *student)
{
    customer = student;
}
