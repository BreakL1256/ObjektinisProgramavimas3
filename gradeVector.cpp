#include <iostream>
#include <random>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <ios>
#include <exception>
#include "skaiciavimai.h"

using namespace std;

int main()
{
clock_t pradzia, pabaiga;
double bendras, skaicius;
srand(time(nullptr));

//Veikimas padarytas, kad programa veiktu kol nepasirenkamas jos terminavimas
while(true){
    fstream fread;
    vector<mokinys> M;
    string eilute;
    int indeksas = 0, pasirinkimas, laisvaEilute = 0, sugeneruotiSk, vektoriausIlgiotikrinimas = 0, isvedimoPasirinkimas;
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
            try{
                fread.open("studentai10000.txt", std::ios::in);
                //Throwinamas error jei failas nera atidarytas
                if (!fread.is_open()) {
                    throw std::ios_base::failure("Failas nera atidarytas!");
                }

                cout<<"Pasirinkite, kur noretumete, kad butu isvesti duomenys (1 - konsoleje, 2 - faile)\n";
                //Pasirinkimo tipo tikrinimas naudojant try-catch metoda
                try{
                    cin>>isvedimoPasirinkimas;
                    if(!cin.good())
                        throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO.");
                }catch (const std::exception& e){
                    cerr << "KLAIDA:" << e.what() << endl;
                    while(!cin.good() || pasirinkimas<1 || pasirinkimas>2){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout<<"Pasirinkite, kur noretumete, kad butu isvesti duomenys (1 - konsoleje, 2 - faile)\n";
                        cin>>isvedimoPasirinkimas;
                    }
                }

                pradzia = clock();
                fread.ignore(1000, '\n');
                while (getline(fread, eilute)) {
                //Patikrinama ar kada praleidziama tuscia eilute, kad butu sustapdomas rasymo procesas
                    if (eilute.empty()) {
                            break;
                    }


                    mokinys x;
                    M.push_back(x);

                    istringstream iss(eilute);
                    iss >> M[indeksas].vardas >> M[indeksas].pavarde;

                    //Nuskaitomi tik skaiciai 10 sistemoje
                    while (iss >> skaicius) {
                        if (skaicius >= 0 && skaicius <= 10) {
                            M[indeksas].tarpiniaiRezultatai.push_back(skaicius);
                            //cout<<skaicius<<endl;
                        }
                    }

                    if(M[indeksas].tarpiniaiRezultatai.size() == 0)
                        vektoriausIlgiotikrinimas++;

                    EgzaminoRezultatoGavimas(M, indeksas);
                    //is vektoriaus istraukiamas egzamino rez.
                    indeksas++;
                }
                pabaiga = clock();
                bendras = 1.0*( pabaiga - pradzia )/ CLOCKS_PER_SEC;
                fread.close();
            // Iskvieciamas blokas jei nebuvo atidarytas failas
            }catch(const ios_base::failure &e) {
                cerr << "Error: " << e.what() << endl;
                cerr << "Failas nebuvo rastas specifikuotoje lokacijoje!" << endl;
                return 1;
            }
            //cout<<bendras<<endl;
            break;
        case 2:
            isvedimoPasirinkimas = 1;
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

                try{
                    VarduSkaitymas(iss, M, indeksas, err);
                    if(err) throw std::invalid_argument("PASIRINKTI SIMBOLIAI NERA (STRING) TIPO.");
                }catch(const std::invalid_argument& e){
                    cerr << "KLAIDA: " << e.what() << endl;
                    continue;
                }
                //Jei zodis nera sudarytas is raidziu, nutraukiamas programos darbas ir ismetamas pasirinkimo duomenu apdorojimo meniu 
  
                //Nuskaitomi tik skaiciai 10 sistemoje
                try{
                    while (iss >> skaicius) {
                        //cout<<skaicius<<endl;
                        if (skaicius >= 0 && skaicius <= 10) {
                            M[indeksas].tarpiniaiRezultatai.push_back(skaicius);
                        }
                        if(!iss.good()) throw std::invalid_argument("NETINKAMA IVESTIS: GALIMA IVESTI SKAICIUS (1-10)");
                    }
                }catch(const std::invalid_argument& e){
                    cerr << "KLAIDA: " << e.what() << endl;
                    continue;
                }
                if(M[indeksas].tarpiniaiRezultatai.size() == 0)
                    vektoriausIlgiotikrinimas++;

                EgzaminoRezultatoGavimas(M, indeksas);
                //is vektoriaus istraukiamas egzamino rez.
                indeksas++;
            }
            break;

        case 3:
            isvedimoPasirinkimas = 1;
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
                if(!eilute.empty())
                    GeneruotiPazymius(M, indeksas);
                //is vektoriaus istraukiamas egzamino rez.
                EgzaminoRezultatoGavimas(M, indeksas);
                indeksas++;
            }
            break;

        case 4:
            isvedimoPasirinkimas = 1;
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
                //is vektoriaus istraukiamas egzamino rez.
                EgzaminoRezultatoGavimas(M, i);
            }
            break;

        case 5:
            return 0;
    }
   
//Istrinamas pirmas elementas, nes del sudarytos strukutors kaip nuskaitomi duomenys yra nuskaitoma tuscia eilute
    if (!M.empty() && pasirinkimas != 4 && pasirinkimas != 1) {
        M.erase(M.begin());
    }

    if(vektoriausIlgiotikrinimas > 1){
        cout<<"Prie pazymiu galima vesti tik skaicius!\n";
    }

    int vidurkioTipas, rikiavimoPasirinkimas, mokiniuSk = M.size(), sk = 0, pazymiuSuma = 0; 
    double mediana = 0, galutinis = 0; 
    if(vektoriausIlgiotikrinimas < 2){
        cout<<"Pasirinkite kuriuos duomenis noresite rikiuoti (1 - vardai, 2 - pavardes, 3 - vidurkiai, 4 - medianos, 5 - nerikiuoti):\n";
        cin>>rikiavimoPasirinkimas;
        while(!cin.good() || rikiavimoPasirinkimas<1 || rikiavimoPasirinkimas>5){
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Galima irasyti tik skaicius [1, 5]\n";
            cin>>rikiavimoPasirinkimas;
        }
    }
    if(indeksas != 0 && err == 0 && vektoriausIlgiotikrinimas < 2 && isvedimoPasirinkimas == 1){
        cout<<"Pasirinkite kokiu budu noretumete, kad butu suskaiciuotas jus vidurkis (1 = paprastai, 2 = mediana):\n";
        cin>>vidurkioTipas;
        while(!cin.good() || vidurkioTipas!=1 && vidurkioTipas!=2 || rikiavimoPasirinkimas == 3 && vidurkioTipas == 2 || rikiavimoPasirinkimas == 4 && vidurkioTipas == 1){
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Galima irasyti tik skaicius ( 1 arba 2) ir galite pasirinkti rikiuoti tik ta rezultatu tipa kuri pasirinkote!\n";
            cin>>vidurkioTipas;
        }
        //Suteikiami 2 pasirinkimai skaiciuoti vidurkius
        if(vidurkioTipas == 1){ 
            for(int i=0; i<mokiniuSk; i++){
                VidurkioSkaiciavimas(M, pazymiuSuma, galutinis, i);
                pazymiuSuma = 0;
            }
            Rikiavimas(M, rikiavimoPasirinkimas, vidurkioTipas, bendras);
            cout << left << setw(25) <<"Pavarde";
            cout << left << setw(25) <<"Vardas";
            cout << left << setw(30) << "Galutinis (Vid.)" << endl;
            cout << "------------------------------------------------------------" << endl;
            for(int i=0; i<mokiniuSk; i++){
                cout << left << setw(25) << M[i].pavarde;
                cout << left << setw(25) << M[i].vardas;
                cout << left << setw(30) << fixed << setprecision(2) << M[i].vidurkis << endl;
            } 
        }else if (vidurkioTipas == 2){
            for(int i=0; i<mokiniuSk; i++){
                MedianosSkaiciavimas(M, mediana, i);
            }
            Rikiavimas(M, rikiavimoPasirinkimas, vidurkioTipas, bendras);
            cout << left << setw(25) <<"Pavarde";
            cout << left << setw(25) <<"Vardas";
            cout << left << setw(30) << "Galutinis (Med.)" << endl;
            cout << string(66, '-') << endl;
            for(int i=0; i<mokiniuSk; i++){
                //Pridedamas egzamino rezultatas i vektoriu prie pazymiu ir surikiuojami skaiciai vektoriuje nuo didziausio iki maziausio
                cout << left << setw(25) << M[i].pavarde;
                cout << left << setw(25) << M[i].vardas;
                cout << left << setw(30) << fixed << setprecision(2) << M[i].mediana << endl;
            }
        }
    }else if(indeksas != 0 && err == 0 && vektoriausIlgiotikrinimas < 2 && isvedimoPasirinkimas == 2){
        try{
            fread.open("rezultatai.txt", ios::out);
            if (!fread.is_open()) {
                throw std::ios_base::failure("Failas nera atidarytas!");
            }
            cout<<"Pasirinkite kokiu budu noretumete, kad butu suskaiciuotas jus vidurkis (1 = paprastai, 2 = mediana):\n";
            cin>>vidurkioTipas;
            while(!cin.good() || vidurkioTipas!=1 && vidurkioTipas!=2 || rikiavimoPasirinkimas == 3 && vidurkioTipas == 2 || rikiavimoPasirinkimas == 4 && vidurkioTipas == 1){
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Galima irasyti tik skaicius ( 1 arba 2)\n";
                cin>>vidurkioTipas;
            }
            //Suteikiami 2 pasirinkimai skaiciuoti vidurkius
            if(vidurkioTipas == 1){ 
                pradzia = clock();
                fread << left << setw(25) <<"Pavarde";
                fread  << left << setw(25) <<"Vardas";
                fread  << left << setw(30) << "Galutinis (Vid.)" << endl;
                fread  << "------------------------------------------------------------" << endl;
                for(int i=0; i<mokiniuSk; i++){
                    VidurkioSkaiciavimas(M, pazymiuSuma, galutinis, i);
                    pazymiuSuma = 0;
                }
                pabaiga = clock();
                bendras+=1.0*( pabaiga - pradzia )/ CLOCKS_PER_SEC;
                Rikiavimas(M, rikiavimoPasirinkimas, vidurkioTipas, bendras);
                pradzia = clock();
                for(int i=0; i<mokiniuSk; i++){
                    fread  << left << setw(25) << M[i].pavarde;
                    fread  << left << setw(25) << M[i].vardas;
                    fread  << left << setw(30) << fixed << setprecision(2) << M[i].vidurkis << endl;
                } 
                pabaiga = clock();
                bendras+=1.0*( pabaiga - pradzia )/ CLOCKS_PER_SEC;
            }else if (vidurkioTipas == 2){
                pradzia = clock();
                fread  << left << setw(25) <<"Pavarde";
                fread  << left << setw(25) <<"Vardas";
                fread  << left << setw(30) << "Galutinis (Med.)" << endl;
                fread  << string(66, '-') << endl;
                for(int i=0; i<mokiniuSk; i++){
                    MedianosSkaiciavimas(M, mediana, i);
                }
                pabaiga = clock();
                bendras+=1.0*( pabaiga - pradzia )/ CLOCKS_PER_SEC;
                Rikiavimas(M, rikiavimoPasirinkimas, vidurkioTipas, bendras);
                pradzia = clock();
                for(int i=0; i<mokiniuSk; i++){
                    //Pridedamas egzamino rezultatas i vektoriu prie pazymiu ir surikiuojami skaiciai vektoriuje nuo didziausio iki maziausio
                    fread  << left << setw(25) << M[i].pavarde;
                    fread  << left << setw(25) << M[i].vardas;
                    fread  << left << setw(30) << fixed << setprecision(2) << M[i].mediana << endl;
                }
                pabaiga = clock();
                bendras+=1.0*( pabaiga - pradzia )/ CLOCKS_PER_SEC;
            }
            //cout<<bendras<<endl;
            fread.close();
        }catch(const ios_base::failure &e) {
            cerr << "Error: " << e.what() << endl;
            cerr << "Failas nebuvo rastas specifikuotoje lokacijoje!" << endl;
            return 1;
        }
    }
}

    return 0;
}