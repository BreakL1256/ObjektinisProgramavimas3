#include <iostream>
#include <random>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>


using namespace std;

struct mokinys{
    string vardas;
    string pavarde;
    vector<int> tarpiniaiRezultatai;
    int egzaminoRezultatas;
};

int main()
{
    vector<mokinys> M;
    string eilute;
    int indeksas = 0;
    
    cout<<"Iveskite mokinio varda, pavarde, gautus pazymius is namu darbu (paskutinis pazymys turi buti egzamino).Jei norite baigti sarasa paspauskite du kartus enter\n";

    while (getline(cin, eilute)) {
        mokinys x;
        M.push_back(x);

        if (eilute.empty()) {
            break;
        }

        istringstream iss(eilute);
        iss >> M[indeksas].vardas >> M[indeksas].pavarde;
        //cout<<M[indeksas].vardas<<" ";
        int skaicius;
        while (iss >> skaicius) {
            if (skaicius >= 0 && skaicius <= 10) {
                M[indeksas].tarpiniaiRezultatai.push_back(skaicius);
            }

        }

        // Set egzaminoRezultatas to the last element of tarpiniaiRezultatai
        if (!M[indeksas].tarpiniaiRezultatai.empty()) {
            M[indeksas].egzaminoRezultatas = M[indeksas].tarpiniaiRezultatai.back();
            M[indeksas].tarpiniaiRezultatai.pop_back();
        }
        indeksas++;
    }

    // for(int i=0; i<mokiniuSk; i++){
    //     cout<<"Iveskite mokinio varda, pavarde, gautus pazymius is namu darbu\n";
    //    cin>>M[i].vardas>>M[i].pavarde;
    //    cin>>M[i].n;
    //    while(M[i].n<0 || M[i].n>50 || !cin.good()){
    //     cin.clear();
    //     cin.ignore(10000, '\n');
    //     cout<<"Pasirinkite pazymiu skaičiu (0-50)\n";
    //     cin>>M[i].n;
    //    }
    //     for(int j=0; j<M[i].n; j++){
    //         cin>>M[i].tarpiniaiRezultatai[j];
    //         //cout<<M[i].tarpiniaiRezultatai[j]<<endl;
    //     }

    //     // for(int j=0; j<M[i].n; j++){
    //     //     cout<<M[i].tarpiniaiRezultatai[j]<<endl;
    //     // }

    //    cout<<"Irasykite gauta egzamino rezultata:\n";
    //     cin >> M[i].egzaminoRezultatas;
    //    while(M[i].egzaminoRezultatas<0 || M[i].egzaminoRezultatas>10 || !cin.good()){
    //         cin.clear();
    //         cin.ignore(10000, '\n');
    //         cout<<"Pazimys turi buti (0-10)\n";
    //         cin>>M[i].egzaminoRezultatas;
    //    }
    // }
//     int vidurkioTipas = 0;
//     cout<<"Pasirinkite kokiu budu noretumete, kad butu suskaiciuotas jus vidurkis (1 = paprastai, 2 = mediana):\n";
//     cin>>vidurkioTipas;
//     if(vidurkioTipas == 1){
//         double galutinis = 0, pazymiuSuma = 0;
//         cout<<"Pavarde"<<setw(16)<<"Vardas"<<setw(28)<<"Galutinis (Vid.)\n";
//         cout<<"---------------------------------------------------\n";
//         for(int i=0; i<mokiniuSk; i++){
//             for(int j=0; j<M[i].n; j++){
//                 pazymiuSuma+=M[i].tarpiniaiRezultatai[j];
//             }
//             galutinis = 0.4 * (pazymiuSuma/M[i].n) + 0.6 * M[i].egzaminoRezultatas;

//             cout<<M[i].pavarde<<setw(16)<<M[i].vardas<<setw(28)<<fixed<<setprecision(2)<<galutinis<<endl;
//             pazymiuSuma = 0;
//             galutinis = 0;
//         } 
//     }else if (vidurkioTipas == 2){
//         double mediana = 0;
//         cout<<"Pavarde"<<setw(16)<<"Vardas"<<setw(28)<<"Galutinis (Med.)\n";
//         cout<<"---------------------------------------------------\n";
//         for(int i=0; i<mokiniuSk; i++){
// //-----------------------------------------------------------------------
//             M[i].n++;
//                 M[i].tarpiniaiRezultatai[M[i].n-1]=M[i].egzaminoRezultatas;
//                 sort(M[i].tarpiniaiRezultatai, M[i].tarpiniaiRezultatai + M[i].n);
//             // for(int j=0; j<M[i].n; j++){
//             //     cout<<M[i].tarpiniaiRezultatai[j]<<" ";
//             // }
// //------------------------------------------------------------------------
//             if(M[i].n%2!=0){
//                 int skaicius = M[i].n/2;
//                 mediana = M[i].tarpiniaiRezultatai[skaicius];
//             }else if(M[i].n%2==0){
//                 int pirmas = M[i].n/2-1;
//                 int antras = M[i].n/2+1;
//                 mediana = (M[i].tarpiniaiRezultatai[pirmas]+M[i].tarpiniaiRezultatai[antras])/2;
//             }
//             cout<<M[i].pavarde<<setw(16)<<M[i].vardas<<setw(28)<<fixed<<setprecision(2)<<mediana<<endl;
//             mediana = 0;
//         }
//     }


    return 0;
}