#include "lib.h"
#include "Student.h"

 int main(){
    vector <Student> Group;
    while(true){
        cout<<"Do you want to add a student? y/n ";
        char answ;
        cin >> answ;
        if(answ == 'n' || answ == 'N') break;
        Student A;
        Group.push_back(A);
        A.clear();
    }
    
    cout << endl << left << setw(15) << "Name" 
        << setw(15) << "Surname" 
        << right << setw(15) << "Final_Point(Aver.)\n";

    cout << string(45, '-') << "\n";

    for(Student i : Group){
        i.print();
    }
    cout << endl;
 }