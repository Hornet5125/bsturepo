#include "heading.h"
int main() {
    Personnel obj1;
    obj1.Show();
    Personnel obj2("Иванов", 3, 5);
    obj2.Show();
    Personnel obj3(obj2);
    obj3.Show();
    Personnel* ptr1 = new Personnel("Петров", 2, 4);
    ptr1->Show();
    Personnel arr[2];
    Personnel* ptr2 = &obj2;
    ptr2->GetName();
    ptr2->GetWorkshopNumber();
    ptr2->SetRank(6);
    ptr2->Show();
    ptr1->GetName();
    ptr1->GetWorkshopNumber();
    ptr1->SetName("Елисей");
    ptr1->SetWorkshopNumber(1);
    ptr1->Show();
    Personnel** ptr3 = &ptr1;
    (*ptr3)->Show();
    Personnel* ptrArray[3];
    ptrArray[0] = &obj1;
    ptrArray[1] = &obj2;
    ptrArray[2] = &obj3;
    for(int i = 0; i < 3; i++) {
        ptrArray[i]->Show();
    }
    Personnel* ptr4 = &obj1;
    ptr4->Show();
    ptr4->SetName("Новый");
    ptr4->SetWorkshopNumber(10);
    ptr4->SetRank(7);
    ptr4->Show();
    obj2.GetName();
    ptr2->GetName();
    delete ptr1;
    return 0;
}