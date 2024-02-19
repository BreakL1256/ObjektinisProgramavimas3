#include <iostream>
#include <random>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cctype>



using namespace std;

struct mokinys{
    string vardas;
    string pavarde;
    int* tarpRez = nullptr;
    int tarpRezIt = 0;
    int egzaminoRezultatas;
};


bool SudaroTikRaides(string& str) {
    for (int i=0; i<str.length(); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

void VarduSkaitymas(istringstream & iss, mokinys* r, int indeksas, bool & err){
    iss >> r[indeksas].vardas >> r[indeksas].pavarde;
    if(!SudaroTikRaides(r[indeksas].vardas) || !SudaroTikRaides(r[indeksas].vardas)){
        cout<<"Varda ir pavarde gali sudaryti tik raides!\n";
        err=1;   
    } else {
        err=0;
    }
}

void GeneruotiPazymius(mokinys* r, int indeksas){
    r[indeksas].tarpRez = new int[r[indeksas].tarpRezIt];
    for(int i=0; i<r[indeksas].tarpRezIt; i++){
       r[indeksas].tarpRez[i] = (double)rand()/RAND_MAX * 10;
    }
}

void VarduPavardziuGeneravimas(mokinys* r, int indeksas){
    char v, p;
    int vardoIlgis = 0, pavardesIlgis = 0; 
    vardoIlgis = 6 + (double)rand()/RAND_MAX * (12-6);
    pavardesIlgis = 6 + (double)rand()/RAND_MAX * (12-6);
    for(int i=0; i<vardoIlgis; i++){
        if(i==0)
            v = 65 + (double)rand()/RAND_MAX * (90-65);
        else
            v = 97 + (double)rand()/RAND_MAX * (122-97);
        r[indeksas].vardas.push_back(v);
    }
    for(int i=0; i<pavardesIlgis; i++){
        if(i==0)
            v = 65 + (double)rand()/RAND_MAX * (90-65);
        else
            v = 97 + (double)rand()/RAND_MAX * (122-97);
        r[indeksas].pavarde.push_back(v);
    }
}

int main()
{
    int pasirinkimas;
    srand(time(nullptr));

while(true){
    mokinys* r = new mokinys[100000];
    int indeksas = 0, skaicius, iteracija = 0, laisvaEilute = 0, sugeneruotiSk;
    string eilute;
    bool err = 0;

    cout<<"Pasirinkite kaip noretumete, kad butu apdorojami jusu ivesti duomenys: 1 - ranka, 2 - generuoti pazymius, 3 - generuoti ir pazymius ir studentu vardus, pavardes, 4 - baigti darba\n";
    cin>>pasirinkimas;


    switch(pasirinkimas){
        case 1:
            cout<<"Iveskite mokinio varda, pavarde, gautus pazymius is namu darbu (paskutinis pazymys turi buti egzamino).Jei norite baigti sarasa paspauskite du kartus enter\n";
            while (getline(cin, eilute)) {
                if (eilute.empty()) {
                    laisvaEilute++;
                    if(laisvaEilute == 2)
                        break;
                }

                istringstream iss(eilute);
                VarduSkaitymas(iss, r, indeksas, err);

                if(err){
                    break;
                }

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
           break;
        
           
        case 2:
            
            cout<<"Parasykite kiek noretumete kad prie kiekvieno mokinio butu sugeneruota pazymiu (pazymiai generuojami 10 balu sistemoje):\n";
            cin>>sugeneruotiSk;
            cout<<"Iveskite mokiniu vardus ir pavardes (noredami baigti ivedima nueje i nauja eilute paspauskite enter):\n";
            while (getline(cin, eilute)) {
                if (eilute.empty()) {
                    laisvaEilute++;
                    if(laisvaEilute == 2)
                        break;
                }
                istringstream iss(eilute);
                VarduSkaitymas(iss, r, indeksas, err);
                if(err){
                    break;
                }
                r[indeksas].tarpRezIt = sugeneruotiSk;
                GeneruotiPazymius(r, indeksas);
                indeksas++;
            }
            break;
        
        case 3:

            cout<<"Pasirinkite kiek noresite skirtingu mokiniu sugeneruoti ir kiek mokiniai tures sugeneruotu pazymiu (pirmas skaicius - mokiniu sk., antras skaicius - pazymiu sk.)\n";
            cin>>indeksas>>sugeneruotiSk;

            for(int i=0; i<indeksas; i++){
                VarduPavardziuGeneravimas(r, i);
                r[i].tarpRezIt = sugeneruotiSk;
                GeneruotiPazymius(r, i);
            }
            

        break;

        case 4:
        return 0;
    }
    


    if(indeksas != 0 && err == 0){     
        mokinys* rcopy = new mokinys[indeksas];
        if(pasirinkimas == 3){
            for(int i=0; i<indeksas; i++){
                rcopy[i] = r[i];
            }
        } else{

            indeksas--;
            for(int i=0; i<indeksas; i++){
                rcopy[i] = r[i+1];
            }
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
                    int antras = rezultatuSk/2;
                    mediana = (double(rcopy[i].tarpRez[pirmas]+rcopy[i].tarpRez[antras]))/2;
                }
                cout<<rcopy[i].pavarde<<setw(16)<<rcopy[i].vardas<<setw(28)<<fixed<<setprecision(2)<<mediana<<endl;
                mediana = 0;
            }
        }
    if(pasirinkimas != 3)
        indeksas++;
        
    for (int i = 0; i < indeksas; i++) {
        delete[] rcopy[i].tarpRez;
    }
    delete[] rcopy;
    } else {
        delete[] r;
    }
}
    return 0;
}