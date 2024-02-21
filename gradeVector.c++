#include <iostream>
#include <random>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>


using namespace std;
//Struktura skirta saugoti mokinio duomenis
struct mokinys{
    string vardas;
    string pavarde;
    vector<int> tarpiniaiRezultatai;
    int egzaminoRezultatas;
};

//Funkcija, kuri patikrina ar irasytame zodyje yra tik raides
bool SudaroTikRaides(string& str) {
    for (int i=0; i<str.length(); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

//Funkcija, kuri leidzia perskaityti varda ir pavarde ir kartu patikrina ar vardas ir pavarde yra zodziai sudaryti is raidziu
void VarduSkaitymas(istringstream & iss, vector<mokinys> & M, int indeksas, bool & err){
    iss >> M[indeksas].vardas >> M[indeksas].pavarde;
    if(!SudaroTikRaides(M[indeksas].vardas) || !SudaroTikRaides(M[indeksas].vardas)){
        cout<<"Varda ir pavarde gali sudaryti tik raides!\n";
        err=1;   
    } else {
        err=0;
    }
}
//Funkcija skirta generuoti atsitiktinius pazymius
void GeneruotiPazymius(vector<mokinys> & M, int indeksas){
    for(int i=0; i<M[indeksas].tarpiniaiRezultatai.size(); i++){
       M[indeksas].tarpiniaiRezultatai[i] = (double)rand()/RAND_MAX * 10;
    }
}
//Funkcija skirta atsitikitiniu vardu ir pavardziu generavimui sudarytu is atsitiktiniu raidziu
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
//Veikimas padarytas, kad programa veiktu kol nepasirenkamas jos terminavimas
fstream fread("studentai10000.txt");
while(true){
    vector<mokinys> M;
    string eilute;
    int indeksas = 0, pasirinkimas, laisvaEilute = 0, sugeneruotiSk, vektoriausIlgiotikrinimas = 0;
    bool err = 0;
    
    cout<<"Pasirinkite kaip noretumete, kad butu apdorojami jusu ivesti duomenys: 1 - is failo, 2 - ranka, 3 - generuoti pazymius, 4 - generuoti ir pazymius ir studentu vardus, pavardes, 5 - baigti darba\n";
    cin>>pasirinkimas;
    while(!cin.good() || pasirinkimas<1 || pasirinkimas>5){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Pasirinkite kaip noretumete, kad butu apdorojami jusu ivesti duomenys: 1 - is failo, 2 - ranka, 3 - generuoti pazymius, 4 - generuoti ir pazymius ir studentu vardus, pavardes, 5 - baigti darba\n";
        cin>>pasirinkimas;
    }
//Suteikiami 4 pasirinkimai kaip dirbti su duomenimis: 1 - is failo, 2 - ranka, 3 - generuoti pazymius, 4 - generuoti ir pazymius ir studentu vardus, pavardes, 5 - baigti darba

    switch(pasirinkimas){
        case 1:
            fread.ignore(1000, '\n');
            while (getline(fread, eilute)) {
            //Patikrinama ar kada praleidziama tuscia eilute, kad butu sustapdomas rasymo procesas
                if (eilute.empty()) {
                    laisvaEilute++;
                    if(laisvaEilute == 2)
                        break;
                }

                //cout<<eilute<<endl;

                mokinys x;
                M.push_back(x);


                istringstream iss(eilute);
                iss >> M[indeksas].vardas >> M[indeksas].pavarde;
                //Jei zodis nera sudarytas is raidziu, nutraukiamas programos darbas ir ismetamas pasirinkimo duomenu apdorojimo meniu 
                if(err){
                    break;
                }
                int skaicius;
                //Nuskaitomi tik skaiciai 10 sistemoje
                while (iss >> skaicius) {
                    if (skaicius >= 0 && skaicius <= 10) {
                        M[indeksas].tarpiniaiRezultatai.push_back(skaicius);
                    }
                }
                if(M[indeksas].tarpiniaiRezultatai.size() == 0)
                    vektoriausIlgiotikrinimas++;

                //is vektoriaus istraukiamas egzamino rez.
                if (M[indeksas].tarpiniaiRezultatai.size() > 1) {
                    M[indeksas].egzaminoRezultatas = M[indeksas].tarpiniaiRezultatai.back();
                    M[indeksas].tarpiniaiRezultatai.pop_back();
                }
                indeksas++;
            }
            break;
        case 2:
            cout<<"Iveskite mokinio varda, pavarde, gautus pazymius is namu darbu (paskutinis pazymys turi buti egzamino).Jei norite baigti sarasa paspauskite du kartus enter\n";

            while (getline(cin, eilute)) {
                //Patikrinama ar kada praleidziama tuscia eilute, kad butu sustapdomas rasymo procesas
            if (eilute.empty()) {
                    laisvaEilute++;
                    if(laisvaEilute == 2)
                        break;
                }

                mokinys x;
                M.push_back(x);


                istringstream iss(eilute);
                VarduSkaitymas(iss, M, indeksas, err);
                //Jei zodis nera sudarytas is raidziu, nutraukiamas programos darbas ir ismetamas pasirinkimo duomenu apdorojimo meniu 
                if(err){
                    break;
                }
                int skaicius;
                //Nuskaitomi tik skaiciai 10 sistemoje
                while (iss >> skaicius) {
                    if (skaicius >= 0 && skaicius <= 10) {
                        M[indeksas].tarpiniaiRezultatai.push_back(skaicius);
                    }
                }
                if(M[indeksas].tarpiniaiRezultatai.size() == 0)
                    vektoriausIlgiotikrinimas++;

                //is vektoriaus istraukiamas egzamino rez.
                if (M[indeksas].tarpiniaiRezultatai.size() > 1) {
                    M[indeksas].egzaminoRezultatas = M[indeksas].tarpiniaiRezultatai.back();
                    M[indeksas].tarpiniaiRezultatai.pop_back();
                }
                indeksas++;
            }
            break;

        case 3:
            cout<<"Parasykite kiek noretumete kad prie kiekvieno mokinio butu sugeneruota pazymiu (pazymiai generuojami 10 balu sistemoje):\n";
            cin>>sugeneruotiSk;
            while(!cin.good() || sugeneruotiSk < 2){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Galima irasyti tik skaicius ( turi buti: skaicius>=2)\n";
                cin>>sugeneruotiSk;
            }
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
                //Is anksto nustatoma kiek mokinia tures pazymiu, kad butu galima generuoti atsitiktinius pazymius
                M[indeksas].tarpiniaiRezultatai.resize(sugeneruotiSk);
                GeneruotiPazymius(M, indeksas);
                indeksas++;
            }
            break;

        case 4:
            cout<<"Pasirinkite kiek noresite skirtingu mokiniu sugeneruoti ir kiek mokiniai tures sugeneruotu pazymiu (pirmas skaicius - mokiniu sk., antras skaicius - pazymiu sk.)\n";
            cin>>indeksas>>sugeneruotiSk;
            while(!cin.good() || sugeneruotiSk < 2 || indeksas < 1){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Galima irasyti tik skaicius ( turi buti: skaicius>=2)\n";
                cin>>indeksas>>sugeneruotiSk;
            }
            //Is anksto nusprendziamas kiek bus mokiniu ir kiek mokiniai tures pazymiu
            for(int i=0; i<indeksas; i++){
                mokinys x;
                M.push_back(x);

                VarduPavardziuGeneravimas(M, i);
                M[i].tarpiniaiRezultatai.resize(sugeneruotiSk);
                GeneruotiPazymius(M, i);
            }
            break;

        case 5:
            return 0;
    }

//Istrinamas pirmas elementas, nes del sudarytos strukutors kaip nuskaitomi duomenys yra nuskaitoma tuscia eilute
    if (!M.empty() && pasirinkimas != 3) {
        M.erase(M.begin());
    }

    if(vektoriausIlgiotikrinimas > 1){
        cout<<"Prie pazymiu galima vesti tik skaicius!\n";
    }

    if(indeksas != 0 && err == 0 && vektoriausIlgiotikrinimas < 2){
        int vidurkioTipas = 0;
        cout<<"Pasirinkite kokiu budu noretumete, kad butu suskaiciuotas jus vidurkis (1 = paprastai, 2 = mediana):\n";
        cin>>vidurkioTipas;
        while(!cin.good() || vidurkioTipas!=1 && vidurkioTipas!=2){
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Galima irasyti tik skaicius ( 1 arba 2)\n";
            cin>>vidurkioTipas;
        }
        //Suteikiami 2 pasirinkimai skaiciuoti vidurkius
        if(vidurkioTipas == 1){
            double galutinis = 0, pazymiuSuma = 0;
            int mokiniuSk = M.size();
            cout << left << setw(25) <<"Pavarde";
            cout << left << setw(25) <<"Vardas";
            cout << left << setw(30) << "Galutinis (Vid.)" << endl;
            cout << "------------------------------------------------------------" << endl;
            for(int i=0; i<mokiniuSk; i++){
                int rezultatuSk = M[i].tarpiniaiRezultatai.size();
                //Sudedami visi pazymiai
                for(int j=0; j<rezultatuSk; j++){
                    pazymiuSuma+=M[i].tarpiniaiRezultatai[j];
                }
                //Suskaiciuojamas galutinis pazymys pagal formule
                galutinis = 0.4 * (pazymiuSuma/rezultatuSk) + 0.6 * M[i].egzaminoRezultatas;

                cout << left << setw(25) << M[i].pavarde;
                cout << left << setw(25) << M[i].vardas;
                cout << left << setw(30) << fixed << setprecision(2) << galutinis << endl;
                pazymiuSuma = 0;
                galutinis = 0;
            } 
        }else if (vidurkioTipas == 2){
            double mediana = 0;
            cout << left << setw(25) <<"Pavarde";
            cout << left << setw(25) <<"Vardas";
            cout << left << setw(30) << "Galutinis (Med.)" << endl;
            cout << string(66, '-') << endl;
            int mokiniuSk = M.size();
            for(int i=0; i<mokiniuSk; i++){
                //Pridedamas egzamino rezultatas i vektoriu prie pazymiu ir surikiuojami skaiciai vektoriuje nuo didziausio iki maziausio
                M[i].tarpiniaiRezultatai.push_back(M[i].egzaminoRezultatas);
                int rezultatuSk = M[i].tarpiniaiRezultatai.size();
                sort(M[i].tarpiniaiRezultatai.begin(), M[i].tarpiniaiRezultatai.end());
                //skaiciuojama mediana
                //patikrinama ar yra lyginis ar nelyginis skaicius elementu vektoriuje
                if(rezultatuSk%2!=0){
                    int skaicius = rezultatuSk/2;
                    mediana = M[i].tarpiniaiRezultatai[skaicius];
                }else if(rezultatuSk%2==0){
                    int pirmas = rezultatuSk/2-1;
                    int antras = rezultatuSk/2;
                    mediana = (M[i].tarpiniaiRezultatai[pirmas]+M[i].tarpiniaiRezultatai[antras])/2;
                }
                cout << left << setw(25) << M[i].pavarde;
                cout << left << setw(25) << M[i].vardas;
                cout << left << setw(30) << fixed << setprecision(2) << mediana << endl;
                mediana = 0;
            }
        }
    }
}

    return 0;
}