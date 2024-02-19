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

bool SudaroTikRaides(string& str) {
    for (int i=0; i<str.length(); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

void VarduSkaitymas(istringstream & iss, vector<mokinys> & M, int indeksas, bool & err){
    iss >> M[indeksas].vardas >> M[indeksas].pavarde;
    if(!SudaroTikRaides(M[indeksas].vardas) || !SudaroTikRaides(M[indeksas].vardas)){
        cout<<"Varda ir pavarde gali sudaryti tik raides!\n";
        err=1;   
    } else {
        err=0;
    }
}

void GeneruotiPazymius(vector<mokinys> & M, int indeksas){
    for(int i=0; i<M[indeksas].tarpiniaiRezultatai.size(); i++){
       M[indeksas].tarpiniaiRezultatai[i] = (double)rand()/RAND_MAX * 10;
    }
}

void VarduPavardziuGeneravimas(vector<mokinys> & M, int indeksas){
    char v, p;
    int vardoIlgis = 0, pavardesIlgis = 0; 
    vardoIlgis = 6 + (double)rand()/RAND_MAX * (12-6);
    pavardesIlgis = 6 + (double)rand()/RAND_MAX * (12-6);
    for(int i=0; i<vardoIlgis; i++){
        if(i==0)
            v = 65 + (double)rand()/RAND_MAX * (90-65);
        else
            v = 97 + (double)rand()/RAND_MAX * (122-97);
        M[indeksas].vardas.push_back(v);
    }
    for(int i=0; i<pavardesIlgis; i++){
        if(i==0)
            v = 65 + (double)rand()/RAND_MAX * (90-65);
        else
            v = 97 + (double)rand()/RAND_MAX * (122-97);
        M[indeksas].pavarde.push_back(v);
    }
}

int main()
{
srand(time(nullptr));

while(true){
    vector<mokinys> M;
    string eilute;
    int indeksas = 0, pasirinkimas, laisvaEilute = 0, sugeneruotiSk;
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

                mokinys x;
                M.push_back(x);


                istringstream iss(eilute);
                VarduSkaitymas(iss, M, indeksas, err);
                if(err){
                    break;
                }
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

                mokinys x;
                M.push_back(x);

                istringstream iss(eilute);
                VarduSkaitymas(iss, M, indeksas, err);
                if(err){
                    break;
                }

                M[indeksas].tarpiniaiRezultatai.resize(sugeneruotiSk);
                GeneruotiPazymius(M, indeksas);
                indeksas++;
            }
            break;

        case 3:
            cout<<"Pasirinkite kiek noresite skirtingu mokiniu sugeneruoti ir kiek mokiniai tures sugeneruotu pazymiu (pirmas skaicius - mokiniu sk., antras skaicius - pazymiu sk.)\n";
            cin>>indeksas>>sugeneruotiSk;
            for(int i=0; i<indeksas; i++){
                mokinys x;
                M.push_back(x);
                
                VarduPavardziuGeneravimas(M, i);
                M[i].tarpiniaiRezultatai.resize(sugeneruotiSk);
                GeneruotiPazymius(M, i);
            }
            break;

        case 4:
            return 0;
    }

    if (!M.empty() && pasirinkimas != 3) {
        M.erase(M.begin());
    }


    if(indeksas != 0 && err == 0){
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

                M[i].tarpiniaiRezultatai.push_back(M[i].egzaminoRezultatas);
                int rezultatuSk = M[i].tarpiniaiRezultatai.size();
                sort(M[i].tarpiniaiRezultatai.begin(), M[i].tarpiniaiRezultatai.end());

                if(rezultatuSk%2!=0){
                    int skaicius = rezultatuSk/2;
                    mediana = M[i].tarpiniaiRezultatai[skaicius];
                }else if(rezultatuSk%2==0){
                    int pirmas = rezultatuSk/2-1;
                    int antras = rezultatuSk/2;
                    mediana = (M[i].tarpiniaiRezultatai[pirmas]+M[i].tarpiniaiRezultatai[antras])/2;
                }
                cout<<M[i].pavarde<<setw(16)<<M[i].vardas<<setw(28)<<fixed<<setprecision(2)<<mediana<<endl;
                mediana = 0;
            }
        }
    }
}

    return 0;
}