#include "map.h"

Map::Map()
{
    ifstream file("map_university.txt");
    file >> width >> length;
    TableMap = new char*[width];
    for (int i = 0; i < width; i++)
    {
        TableMap[i] = new char[length];
        for (int j = 0; j < length; j++)
        {
            file >> TableMap[i][j];
        }
    }
    int countclassrooms = 0;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (TableMap[i][j] == '2')
            {
                ListClassrooms.push_back(new Classroom(countclassrooms++ + 1, i, j));
            }
            if (TableMap[i][j] == '3')
            {
                ListStore.push_back(new Stall(i, j));
            }
        }
    }

    for (int i = 0; i < countclassrooms * Classroom::GetStudentInClassroom(); i++)
    {
        ListStudent.push_back(new Student(ListClassrooms[ i/Classroom::GetStudentInClassroom() ]));
    }
}

void Map::update(bool status)
{

   //Лекция
    int count = ListClassrooms.size();
    for (int i = 0; i < count; i++)
    {
        //Если занятие закончилось
        if (ListClassrooms[i]->update() &&  ListClassrooms[i]->GetTime() == 0)
        {
            //Найти студентов, которые занимались в данной аудитории и дать им новые цели
            for (int j = 0; j < ListStudent.size(); j++)
            {
                if (ListStudent[j]->GetX() == ListClassrooms[i]->GetX()
                        && ListStudent[j]->GetY() == ListClassrooms[i]->GetY())
                {
                    ListStudent[j]->AfterLecture();
                    if (ListStudent[j]->GetSatiety() < 20)
                    {
                        ObjectOnMap* stall = FindStall(ListStudent[j]->GetX(), ListStudent[j]->GetY());
                        if (stall != nullptr)
                            ListStudent[j]->SetPurpose(stall);
                        else
                            ListStudent[j]->SetPurpose(ListClassrooms[ rand() % ListClassrooms.size() ]);
                    }
                    else
                        ListStudent[j]->SetPurpose(ListClassrooms[ rand() % ListClassrooms.size() ]);
                }
            }

            ListClassrooms[i]->SetTimeLecture(20);
        }
    }

    //Буфет
     count = ListStore.size();
     for (int i = 0; i < count; i++)
     {
         //Если при обновлении буфет обслужил кого-то, то дать ему новую цель.
         Student* stud = ListStore[i]->update();
         if (stud != nullptr)
             stud->SetPurpose(ListClassrooms[ rand() % ListClassrooms.size()]);
     }

   //Студенты
   count = ListStudent.size();
   for (int i = 0; i < count; i++)
   {
        int x = ListStudent[i]->GetX();
        int y = ListStudent[i]->GetY();
        ObjectOnMap* purpose = ListStudent[i]->GetPurpose();
        int purpx = purpose->GetX();
        int purpy = purpose->GetY();
        Stall* store = nullptr;
        //Если цель буфет, то находим его в списке.
        if (TableMap[purpose->GetX()][purpose->GetY()] == '3')
        {
            for (int j = 0; j < ListStore.size(); j++)
            {
                if (purpose->GetX() == ListStore[j]->GetX() && purpose->GetY() == ListStore[j]->GetY())
                {
                    store = ListStore[j];
                    break;
                }
            }
        }
        //Находим маршрут от текущего положения до нашей цели.
        vector<int> route = FindRoute(x, y, purpx, purpy);
        if (route.size() != 0)
        {
            //Если такой маршрут найден, то перемещаемся
            if (TableMap[x][y] == '4')
                TableMap[x][y] = '1';
            //Если в аудитории всё ещё идут занятия и осталось немного до звонка, то не заходим в неё.
            if (TableMap[route[0]][route[1]] == '2')
            {
                for (int j = 0; j < ListClassrooms.size(); j++)
                    if (ListClassrooms[j]->GetX() == route[0] && ListClassrooms[j]->GetY() == route[1])
                    {
                        if (ListClassrooms[j]->GetStatus() && (!status || (status && ListClassrooms[j]->GetTime() < 10)))
                        {
                            route[0] = x;
                            route[1] = y;
                        }
                    }
            }
            x = route[0];
            y = route[1];
            //Если следующий шаг буфет, то устанавливаем покупателя в буфете.
            if (TableMap[x][y] == '3')
                 store->SetCustomer(ListStudent[i]);
            if (TableMap[x][y] == '1')
                TableMap[x][y] = '4';
            ListStudent[i]->update(x, y);
        }
   }
}

void Map::changepurpose(bool status, int time)
{
    int countclassrooms = ListClassrooms.size();
    int countstudent = ListStudent.size();
    //с наступлением лекции обновляем количество булочек в буфете и запускаем занятия в аудиториях.
    if (status)
    {
        for (int j = 0; j < ListStore.size(); j++)
            ListStore[j]->UpdateCountOfBun();
        for (int j = 0; j < countclassrooms; j++)
        {
            ListClassrooms[j]->SetTimeLecture(time);
            ListClassrooms[j]->UpdateStatus();
        }
    }

    for (int i = 0; i < countstudent; i++)
    {
        if (status)
        {
            //С наступлением лекции, тем, кто всё ещё направляется в буфет, устанавливаем направлятся на занятия.
            if (TableMap[ListStudent[i]->GetPurpose()->GetX()][ListStudent[i]->GetPurpose()->GetY()] == '3')
                ListStudent[i]->SetPurpose(ListClassrooms[ rand() % countclassrooms ]);
        }
    }
}

vector<int> Map::FindRoute(int x, int y, int purpX, int purpY)
{
    int tempx = x;
    int tempy = y;
    vector<int> route;
    bool find = true;

    if (tempx == purpX && tempy == purpY)
        return route;

    //Создаётся двумерный массив, такой же как карта.
    int** massdist = nullptr;
    massdist = new int*[width];
    for (int i = 0; i < width; i++)
    {
        massdist[i] = new int[length];
        for (int j = 0; j < length; j++)
            massdist[i][j] = -1;
    }

    massdist[tempx][tempy] = 0;
    vector<int> st;

    //По карте строится в новом массиве карта достижимости и кратчайших маршрутов.
    while (find)
    {
        if (tempx > 0)
            if (TableMap[tempx - 1][tempy] == '1')
            {
                if (massdist[tempx - 1][tempy] > massdist[tempx][tempy] + 1 || massdist[tempx - 1][tempy] == -1)
                {
                    massdist[tempx - 1][tempy] = massdist[tempx][tempy] + 1;
                    st.push_back(tempx - 1);
                    st.push_back(tempy);
                }
            }
        if (tempx < width - 1)
            if (TableMap[tempx + 1][tempy] == '1')
            {
                if (massdist[tempx + 1][tempy] > massdist[tempx][tempy] + 1 || massdist[tempx + 1][tempy] == -1)
                {
                    massdist[tempx + 1][tempy] = massdist[tempx][tempy] + 1;
                    st.push_back(tempx + 1);
                    st.push_back(tempy);
                }
            }
        if (tempy > 0)
            if (TableMap[tempx][tempy - 1] == '1')
            {
                if (massdist[tempx][tempy - 1] > massdist[tempx][tempy] + 1 || massdist[tempx][tempy - 1] == -1)
                {
                    massdist[tempx][tempy - 1] = massdist[tempx][tempy] + 1;
                    st.push_back(tempx);
                    st.push_back(tempy - 1);
                }
            }
        if (tempy < length - 1)
            if (TableMap[tempx][tempy + 1] == '1')
            {
                if (massdist[tempx][tempy + 1] > massdist[tempx][tempy] + 1 || massdist[tempx][tempy + 1] == -1)
                {
                    massdist[tempx][tempy + 1] = massdist[tempx][tempy] + 1;
                    st.push_back(tempx);
                    st.push_back(tempy + 1);
                }
            }

        if (st.empty())
            find = false;
        else
        {
            tempy = st[st.size() - 1];
            st.pop_back();
            tempx = st[st.size() - 1];
            st.pop_back();
        }


    }
    tempx = purpX;
    tempy = purpY;

    //От координат цели пытаемся попасть в координаты возле координат студента.
    while (massdist[tempx][tempy] != 1)
    {
        int number = massdist[tempx][tempy];
        if (tempx > 0 && (massdist[tempx - 1][tempy] < number || number == -1) && massdist[tempx - 1][tempy] != -1)
            if (massdist[tempx - 1][tempy] == 0)
                break;
            else
                tempx = tempx-1;
        else
        if (tempx < width - 1 && (massdist[tempx + 1][tempy] < number || number == -1) && massdist[tempx + 1][tempy] != -1)
            if (massdist[tempx + 1][tempy] == 0)
                break;
            else
                tempx = tempx+1;
        else
        if (tempy > 0 && (massdist[tempx][tempy - 1] < number || number == -1) && massdist[tempx][tempy - 1] != -1)
            if (massdist[tempx][tempy - 1] == 0)
                break;
            else
                tempy = tempy - 1;
        else
        if (tempy < length - 1 && (massdist[tempx][tempy + 1] < number || number == -1) && massdist[tempx][tempy + 1] != -1)
            if (massdist[tempx][tempy + 1] == 0)
                break;
            else
                tempy = tempy + 1;

        if (tempx == purpX && tempy == purpY)
            return route;
    }

    for (int i = 0; i < width; i++)
        delete massdist[i];
    delete massdist;

    route.push_back(tempx);
    route.push_back(tempy);

    return route;
}

ObjectOnMap* Map::FindStall(int x, int y)
{
    int count = ListStore.size();
    ObjectOnMap* result= nullptr;
    int dx = 0;
    int dy = 0;
    for (int i = 0; i < count; i++)
    {
        if (ListStore[i]->GetCountBun() > 0)
        {
            int distx = ListStore[i]->GetX() - x;
            if (distx < 0)
                distx *= -1;
            int disty = ListStore[i]->GetY() - y;
            if (disty < 0)
                disty *= -1;
            if ((dx == 0 && dy == 0) || (distx <= dx && disty <= dy))
            {
                dx = distx;
                dy = disty;
                result = ListStore[i];
            }
        }
    }
    return result;
}

char** Map::GetMap()
{
    return TableMap;
}

vector<Student*> Map::GetListStudent()
{
    return ListStudent;
}

int Map::GetMapWidth()
{
    return width;
}

int Map::getMapLength()
{
    return length;
}

vector<Stall*> Map::GetListStall()
{
    return ListStore;
}
