#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void menu();
void Add_Entry();
void Display_Report();
void search_Record();
void delete_Record();

class Student
{
private:
    int Roll_Num;
    char name[25];
    string sub[5] = {"Tamil", "English","Maths","Science","Social Science"};
    int marks[5];
    int total{0};
    int percentage;
public:
    int get_rollnum()
    {
        return Roll_Num;
    }
    void get_details();
    void calculate();
    bool result();
    void show_report();
}s;
void Student::get_details()
{
    cout<< "\n*****Enter the Following  Details of Student******\n";
    cout << "Roll Number: ";
    cin >> Roll_Num;
    cout << "Name: ";
    cin  >> name;
    cout << "\nSubject Mark Details\n";
    for(int i = 0; i < 5; i++)
    {
        cout << sub[i] << ": ";
        cin >> marks[i];
    }
}
void Student::show_report()
{
    cout <<"*****************************************\n";
    cout <<"\tStudent Report Card\t\n\n";
    cout <<"Roll Number: " << Roll_Num << endl;
    cout <<"Name: " << name << endl;
    if(result())
    {
        cout << "Result Status: PASS\n";
        calculate();
        cout <<"Total Mark: " << total << endl;
        cout <<"Percentage: " << percentage << endl;
    }
    else
    {
        cout << "Result Status: FAIL\n";
        cout <<"Total Mark: " << total << endl;
        cout <<"Percentage: " << percentage << endl;
    }
        
    cout <<"\n\n*****************************************\n";
    
}
void Student::calculate()
{
    for(int i=0; i<5;i++)
    {
        total += marks[i];
    }
    percentage = total/5;
}
bool Student::result()
{
    int flag = 0;
    for(int i = 0; i <5; i++)
    {
        if(marks[i] < 35)
           flag++; 
    }
    if(flag == 0)
        return true;
    else
        return false;
}
void menu()
{
    //Student s;
    int ch;
   do
   {
        cout<<"\t\tStudent Record Management System\n\n";
        cout << "\nChoose your choice\n\n";
        cout << "1.Add New Entry\n2.View Student Report\n3.Search Record\n4.Delete Record\n0.Exit\n";
        
        //char op;
        cout<<"Enter Menu choice: ";
        cin >> ch;
        switch(ch)
        {
            case 1:
                Add_Entry();
                break;
            case 2:
                Display_Report();
                break;
            case 3:
                search_Record();
                break;
            case 4:
                delete_Record();
                break;
            default:
                cout<<"Invalid Choice!!!!\n";
        }
   }while(ch);
    
}
void Add_Entry()
{
    //
    char ch;
    ofstream fout;
    fout.open("Student.dat",ios::out|ios::binary|ios::app);
    do
    {
        s.get_details();
        fout.write((char *)&s,sizeof(s));
        cout << "\nOne Record Created\n";
        cout << "Add one more Entry [Y/N]:";
        cin>>ch;
    }while(ch == 'Y' || ch == 'y');
    fout.close();
}
void Display_Report()
{
    ifstream fin;
    fin.open("Student.dat",ios::out|ios::binary);
    while(fin.read((char *)&s,sizeof(s)))
    {
        s.show_report();
    }
    fin.close();
}
void search_Record()
{
    int n,flag=0;
    ifstream fin;
    fin.open("Student.dat",ios::out|ios::binary|ios::app);
    cout << "\n********Search by Roll Number*********\n";
    cout <<"Enter Student Roll Number: ";
    cin >> n;
    while(fin.read((char *)&s,sizeof(s)))
    {
        if(n == s.get_rollnum())
        {
            s.show_report();
            flag++;
            cout<<"Record Found\n";
        }
    }
    fin.close();
    if(flag == 0)
        cout << "Roll Number Not Found!!!!\n";
}
void delete_Record()
{
    ifstream fin;
    ofstream fout;
    fin.open("Student.dat",ios::out|ios::binary|ios::app);
    fout.open("temp.dat",ios::out|ios::binary);
    int n,flag=0;
    cout <<"Enter the Student Roll Number to Delete: ";
    cin>>n;
    while(fin.read((char *)&s,sizeof(s)))
    {
        if(n==s.get_rollnum())
        {
            s.show_report();
            flag++;
            cout<<"Following Record will deleted!!!\n";
        }
        else
            fout.write((char *)&s,sizeof(s));
    }
    fin.close();
    fout.close();
    if(flag==0)
        cout<<"Roll Number Not Found.\n";
    remove("Student.dat");
    rename("temp.dat","Student.dat");
}
int main()
{
    Student s;
    
    //Display_Report();
    menu();
    //s.get_details();
    //s.calculate();
    //s.show_report();
}