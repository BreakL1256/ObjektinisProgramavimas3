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
    int* tarpRez = nullptr;
    int tarpRezIt = 0;
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
                if(r[indeksas].tarpRez == nullptr){
                    r[indeksas].tarpRez = new int[1000];
                }
                r[indeksas].tarpRez[iteracija] = skaicius;
                iteracija++;
            }

        }

        // Set egzaminoRezultatas to the last element of tarpiniaiRezultatai
        if (iteracija != 0) {
            r[indeksas].egzaminoRezultatas = r[indeksas].tarpRez[iteracija-1];
            int* TarpRezCopy = new int[iteracija];
            for(int i=0; i<iteracija; i++){
                TarpRezCopy[i] = r[indeksas].tarpRez[i];
            }
            delete [] r[indeksas].tarpRez;

            r[indeksas].tarpRez = TarpRezCopy;

        }

        r[indeksas].tarpRezIt = iteracija;

        indeksas++;
        iteracija = 0;
    }
    
    if(indeksas != 0){
        mokinys* rcopy = new mokinys[indeksas];
        for(int i=0; i<indeksas; i++){
            rcopy[i] = r[i];
        }

        delete[] r;
    
   
    

        int vidurkioTipas = 0;
        cout<<"Pasirinkite kokiu budu noretumete, kad butu suskaiciuotas jus vidurkis (1 = paprastai, 2 = mediana):\n";
        cin>>vidurkioTipas;
        if(vidurkioTipas == 1){
            double galutinis = 0, pazymiuSuma = 0;
            int mokiniuSk = indeksas;
            cout<<"Pavarde"<<setw(16)<<"Vardas"<<setw(28)<<"Galutinis (Vid.)\n";
            cout<<"---------------------------------------------------\n";
            for(int i=0; i<mokiniuSk; i++){
                int rezultatuSk = rcopy[i].tarpRezIt;
                for(int j=0; j<rezultatuSk-1; j++){
                    pazymiuSuma+=rcopy[i].tarpRez[j];
                }
                galutinis = 0.4 * (double(pazymiuSuma/(rezultatuSk - 1))) + 0.6 * double(rcopy[i].egzaminoRezultatas);

                cout<<rcopy[i].pavarde<<setw(16)<<rcopy[i].vardas<<setw(28)<<fixed<<setprecision(2)<<galutinis<<endl;
                pazymiuSuma = 0;
                galutinis = 0;
            } 
        }else if (vidurkioTipas == 2){
            double mediana = 0;
            cout<<"Pavarde"<<setw(16)<<"Vardas"<<setw(28)<<"Galutinis (Med.)\n";
            cout<<"---------------------------------------------------\n";
            int mokiniuSk = indeksas;
            for(int i=0; i<mokiniuSk; i++){
                int rezultatuSk = rcopy[i].tarpRezIt;
                sort(rcopy[i].tarpRez, rcopy[i].tarpRez + rezultatuSk);
                if(rezultatuSk%2!=0){
                    int skaicius = rezultatuSk/2;
                    mediana = rcopy[i].tarpRez[skaicius];
                }else if(rezultatuSk%2==0){
                    int pirmas = rezultatuSk/2-1;
                    int antras = rezultatuSk/2+1;
                    mediana = (double(rcopy[i].tarpRez[pirmas]+rcopy[i].tarpRez[antras]))/2;
                }
                cout<<rcopy[i].pavarde<<setw(16)<<rcopy[i].vardas<<setw(28)<<fixed<<setprecision(2)<<mediana<<endl;
                mediana = 0;
            }
        }

    for (int i = 0; i < indeksas; i++) {
        delete[] rcopy[i].tarpRez;
    }
    delete[] rcopy;
    } else {
        delete[] r;
    }
    return 0;
}