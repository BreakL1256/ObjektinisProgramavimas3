#include <iostream>
#include <random>
#include <limits>
#include <iomanip>
#include <algorithm>


using namespace std;

struct mokinys{
    string vardas;
    string pavarde;
    int n;
    double tarpiniaiRezultatai[51];
    int egzaminoRezultatas;
};

int main()
{
    mokinys M[100];
    int mokiniuSk;
    cout<<"Iveskite kiek noresite irasyti mokiniu:\n";
    cin>>mokiniuSk;
     while(mokiniuSk<=0 || mokiniuSk>100 || !cin.good()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout<<"Iveskite skaiciu (0-100)\n";
        cin>>mokiniuSk;
    }
    for(int i=0; i<mokiniuSk; i++){
        cout<<"Iveskite mokinio varda, pavarde, pazymiu skaiciu ir gautus pazymius is namu darbu\n";
       cin>>M[i].vardas>>M[i].pavarde;
       cin>>M[i].n;
       while(M[i].n<0 || M[i].n>50 || !cin.good()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout<<"Pasirinkite pazymiu skaičiu (0-50)\n";
        cin>>M[i].n;
       }
        for(int j=0; j<M[i].n; j++){
            cin>>M[i].tarpiniaiRezultatai[j];
            //cout<<M[i].tarpiniaiRezultatai[j]<<endl;
            while(M[i].tarpiniaiRezultatai[j]<0 || M[i].tarpiniaiRezultatai[j]>10 || !cin.good()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout<<"Pazymys turi buti (0-10)\n";
                cin>>M[i].tarpiniaiRezultatai[j];
            }
        }

        // for(int j=0; j<M[i].n; j++){
        //     cout<<M[i].tarpiniaiRezultatai[j]<<endl;
        // }

       cout<<"Irasykite gauta egzamino rezultata:\n";
        cin >> M[i].egzaminoRezultatas;
       while(M[i].egzaminoRezultatas<0 || M[i].egzaminoRezultatas>10 || !cin.good()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout<<"Pazimys turi buti (0-10)\n";
            cin>>M[i].egzaminoRezultatas;
       }
    }
    int vidurkioTipas = 0;
    cout<<"Pasirinkite kokiu budu noretumete, kad butu suskaiciutas jus vidurkis (1 = paprastai, 2 = mediana):\n";
    cin>>vidurkioTipas;
    if(vidurkioTipas == 1){
        double galutinis = 0, pazymiuSuma = 0;
        cout<<"Pavarde"<<setw(16)<<"Vardas"<<setw(28)<<"Galutinis (Vid.)\n";
        cout<<"---------------------------------------------------\n";
        for(int i=0; i<mokiniuSk; i++){
            for(int j=0; j<M[i].n; j++){
                pazymiuSuma+=M[i].tarpiniaiRezultatai[j];
            }
            galutinis = 0.4 * (pazymiuSuma/M[i].n) + 0.6 * M[i].egzaminoRezultatas;

            cout<<M[i].pavarde<<setw(16)<<M[i].vardas<<setw(28)<<fixed<<setprecision(2)<<galutinis<<endl;
            pazymiuSuma = 0;
            galutinis = 0;
        } 
    }


    return 0;
}