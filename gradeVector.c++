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
        if (eilute.empty()) {
            break;
        }

        mokinys x;
        M.push_back(x);


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

    // for(int i=0; i<M.size(); i++){
    //     for(int j=0; j<M[i].tarpiniaiRezultatai.size(); j++){
    //         cout<<M[i].tarpiniaiRezultatai[j]<<" ";
    //     }
    //     cout<<endl;
    // }

    int vidurkioTipas = 0;
    cout<<"Pasirinkite kokiu budu noretumete, kad butu suskaiciuotas jus vidurkis (1 = paprastai, 2 = mediana):\n";
    cin>>vidurkioTipas;
    if(vidurkioTipas == 1){
        double galutinis = 0, pazymiuSuma = 0;
        int mokiniuSk = M.size();
        cout<<"Pavarde"<<setw(16)<<"Vardas"<<setw(28)<<"Galutinis (Vid.)\n";
        cout<<"---------------------------------------------------\n";
        for(int i=0; i<mokiniuSk; i++){
            int rezultatuSk = M[i].tarpiniaiRezultatai.size();
            for(int j=0; j<rezultatuSk; j++){
                pazymiuSuma+=M[i].tarpiniaiRezultatai[j];
            }
            galutinis = 0.4 * (pazymiuSuma/rezultatuSk) + 0.6 * M[i].egzaminoRezultatas;

            cout<<M[i].pavarde<<setw(16)<<M[i].vardas<<setw(28)<<fixed<<setprecision(2)<<galutinis<<endl;
            pazymiuSuma = 0;
            galutinis = 0;
        } 
    }else if (vidurkioTipas == 2){
        double mediana = 0;
        cout<<"Pavarde"<<setw(16)<<"Vardas"<<setw(28)<<"Galutinis (Med.)\n";
        cout<<"---------------------------------------------------\n";
        int mokiniuSk = M.size();
        for(int i=0; i<mokiniuSk; i++){
//-----------------------------------------------------------------------
            M[i].tarpiniaiRezultatai.push_back(M[i].egzaminoRezultatas);
          int rezultatuSk = M[i].tarpiniaiRezultatai.size();
                sort(M[i].tarpiniaiRezultatai.begin(), M[i].tarpiniaiRezultatai.end());
            // for(int j=0; j<M[i].n; j++){
            //     cout<<M[i].tarpiniaiRezultatai[j]<<" ";
            // }
//------------------------------------------------------------------------
            if(rezultatuSk%2!=0){
                int skaicius = rezultatuSk/2;
                mediana = M[i].tarpiniaiRezultatai[skaicius];
            }else if(rezultatuSk%2==0){
                int pirmas = rezultatuSk/2-1;
                int antras = rezultatuSk/2+1;
                mediana = (M[i].tarpiniaiRezultatai[pirmas]+M[i].tarpiniaiRezultatai[antras])/2;
            }
            cout<<M[i].pavarde<<setw(16)<<M[i].vardas<<setw(28)<<fixed<<setprecision(2)<<mediana<<endl;
            mediana = 0;
        }
    }


    return 0;
}