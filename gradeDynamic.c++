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
    int* tarpRez = new int[100000];
    int egzaminoRezultatas;
};

int main()
{
    mokinys* r = new mokinys[100000];
    string eilute;
    int indeksas = 0;
    
    cout<<"Iveskite mokinio varda, pavarde, gautus pazymius is namu darbu (paskutinis pazymys turi buti egzamino).Jei norite baigti sarasa paspauskite du kartus enter\n";

    while (getline(cin, eilute)) {
        if (eilute.empty()) {
            break;
        }


        istringstream iss(eilute);
        iss >> r[indeksas].vardas >> r[indeksas].pavarde;
        //cout<<M[indeksas].vardas<<" ";
        int skaicius, iteracija = 0;
        while (iss >> skaicius) {
            if (skaicius >= 0 && skaicius <= 10) {
                r[indeksas].tarpRez[iteracija]=skaicius;
                iteracija++;
            }

        }

        // Set egzaminoRezultatas to the last element of tarpiniaiRezultatai
        if (iteracija != 0) {
            r[indeksas].egzaminoRezultatas = r[indeksas].tarpRez[iteracija];
            int* TarpRezCopy = new int[iteracija];
            for(int i=0; i<iteracija; i++){
                TarpRezCopy[i] = r[indeksas].tarpRez[i];
            }
            delete [] r[indeksas].tarpRez;

            r[indeksas].tarpRez = new int[iteracija];

           for(int i=0; i<iteracija; i++){
                r[indeksas].tarpRez[i] = TarpRezCopy[i];
            }

            delete [] TarpRezCopy;
        }
        indeksas++;
        iteracija = 0;
    }

    for(int i=0; i<100000; i++){
        if(r[i].tarpRez == nullptr){
            delete [] r[i].tarpRez;
        }
    }

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