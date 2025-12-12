#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(){

    string letters="abcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()_13";
    string password="";
    int length;
    cout<<"enter length of password";
    cin>>length;
    srand(time(0));
    for (int i=0;i<length;i++)
    {
        password+=letters[rand()%letters.size()];
    }

    cout<<"gnereated password is: "<<password<<endl;
}
