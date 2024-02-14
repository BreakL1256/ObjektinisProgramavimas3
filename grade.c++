#include <iostream>
#include <random>


using namespace std;

struct mokinys{
    string vardas;
    string pavarde;
    int n;
    int tarpiniaiRezultatai[50];
    int egzaminoRezultatas;
};

int main()
{
    mokinys M[100];
    int mokiniuSk;
    cout<<"Įveskite kiek norėsite įrašyti mokinių:\n";
    cin>>mokiniuSk;
     while(mokiniuSk<=0 || mokiniuSk>100){
        cin>>mokiniuSk;
    }
    cout<<"Įveskite mokinio vardą, pavardę, pažymių skaičių ir gautus pažymius iš namų darbų\n";
    for(int i=0; i<mokiniuSk; i++){
       cin>>M[i].vardas>>M[i].pavarde;
       cin>>M[i].n;
       while(M[i].n<0 || M[i].n>50){
        cout<<"Pasirinkite pažymių skaičių (0-50)\n";
        cin>>M[i].n;
       }
        for(int j=0; j<M[i].n; j++){
            cin>>M[i].tarpiniaiRezultatai[j];
        }

       cout<<"Įrašykite gautą egzamino rezultatą:\n";
        cin >> M[i].egzaminoRezultatas;
       while(M[i].egzaminoRezultatas<0 || M[i].egzaminoRezultatas>10){
            cout<<"Pažimys turi būti (0-10)\n";
            cin>>M[i].egzaminoRezultatas;
       }
    }
   


    return 0;
}