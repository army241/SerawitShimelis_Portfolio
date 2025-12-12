#include <iostream>
using namespace std;
struct student
{
    int idno;
    string fname;
    int age;
    double gpa;
};

void getData(student s[], int &n);
void display(student s[], int n);

const int MAX_SIZE=100;
int main()
{
    
    student s[MAX_SIZE];
    int n;
    cout<<"how many student do u want to register: ";
    cin>>n;
    getData(s,n);
    display(s,n);



}
void getData(student s[], int &n)
{
    for (int i =0;i<n;i++)
    {
        cout<<"enter idno: "<<endl;
        cin>>s[i].idno;
        cout<<"enter fname: "<<endl;
        cin>>s[i].fname;
        cout<<"enter age: "<<endl;
        cin>>s[i].age;
        cout<<"enter gpa: "<<endl;
        cin>>s[i].gpa;
        cout<<"successfully submitted student report enter another student"<<endl;

    }

};
void display(student s[], int n)
{
    cout<<"student information"<<endl;
    for (int i =0;i<n;i++)
    {
        cout<<"idno: "<<s[i].idno<<endl;
        cout<<"fname: "<<s[i].fname<<endl;
        cout<<"age: "<<s[i].age<<endl;
        cout<<"gpa: "<<s[i].gpa<<endl;

    }
}

