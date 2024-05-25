#include "skaiciavimai.h"
#include "Vector.h"

using namespace std;
//using namespace my_std;

int main()
{

//Veikimas padarytas, kad programa veiktu kol nepasirenkamas jos terminavimas
while(true){
    ifstream fr;
    ofstream fw;
    vector<mokinys> M, N;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> diff1, diff2, diff3, diffTotal;
    string header, vardas, pavarde;
    stringstream buffer;
    int pazSuma = 0, tvarka, l=0;
    

    
    string eilute, failoPavadinimas, pilnasFailoPav;
    int indeksas = 0, pasirinkimas, laisvaEilute = 0, sugeneruotiSk, vektoriausIlgiotikrinimas = 0, isvedimoPasirinkimas, zmoniuSkPasirinkimas = 0, skaicius = 0;
    int dydzioMasyvas[5] = {1000, 10000, 100000, 1000000, 10000000};
    bool err = 0;
    
    cout<<"Pasirinkite kaip noretumete, kad butu apdorojami jusu ivesti duomenys: 1 - is failo, 2 - ranka, 3 - generuoti pazymius, 4 - generuoti ir pazymius ir studentu vardus, pavardes, 5 - skirstyti mokinius i dvi grupes,  6 - generuoti pasirinkto dydzio failus, 7 - testavimas, 8 - baigti darba\n";
    try{
        cin>>pasirinkimas;
        if(!cin.good() || pasirinkimas<1 || pasirinkimas>8) throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO [1, 8].");
    }catch(const std::exception& e){
        cerr << "KLAIDA:" << e.what() << endl;
        while(!cin.good() || pasirinkimas<1 || pasirinkimas>8){
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Pasirinkite kaip noretumete, kad butu apdorojami jusu ivesti duomenys: 1 - is failo, 2 - ranka, 3 - generuoti pazymius, 4 - generuoti ir pazymius ir studentu vardus, pavardes, 5 - skirstyti mokinius i dvi grupes,  6 - generuoti pasirinkto dydzio failus, 7 - testavimas, 8 - baigti darba\n";
            cin>>pasirinkimas;
        }
    }
//Suteikiami 4 pasirinkimai kaip dirbti su duomenimis: 1 - is failo, 2 - ranka, 3 - generuoti pazymius, 4 - generuoti ir pazymius ir studentu vardus, pavardes, 5 - generuoti faila su mokiniu duomenimis,  6 - baigti darba

    switch(pasirinkimas){
        case 1:
            cout<<"Iveskite faila is kurio noretumete skaityti duomenis\n";
            cin>>failoPavadinimas;

            pilnasFailoPav = "../" + failoPavadinimas;

            // Naudojamas try-catch metodas tikrinti ar pavyko atidaryti skaitymo faila
            try{
                fr.open(pilnasFailoPav, std::ios::in);
                //Throwinamas error jei failas nera atidarytas
                if (!fr.is_open()) {
                    throw std::ios_base::failure("FAILAS NERA ATIDARYTAS!");
                }

                cout<<"Pasirinkite, kur noretumete, kad butu isvesti duomenys (1 - konsoleje, 2 - faile)\n";
                
                //Pasirinkimo tipo tikrinimas naudojant try-catch metoda              
                try{
                    cin>>isvedimoPasirinkimas;
                    if(!cin.good() || pasirinkimas<1 || pasirinkimas>2)
                        throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO (1 ARBA 2).");
                }catch (const std::exception& e){
                    cerr << "KLAIDA:" << e.what() << endl;
                    while(!cin.good() || pasirinkimas<1 || pasirinkimas>2){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin>>isvedimoPasirinkimas;
                    }
                }

                fr.ignore(1000, '\n');
                while (getline(fr, eilute)) {
                //Patikrinama ar kada praleidziama tuscia eilute, kad butu sustapdomas rasymo procesas
                    if (eilute.empty()) {
                            break;
                    }


                    mokinys x;

                    istringstream iss(eilute);
                    //Tkrinamas skaiciu ivedimas naudojant try-catch metoda
                    try{
                        iss >> vardas >> pavarde;
                        x.setVardas(vardas);
                        x.setPavarde(pavarde);
                        //Nuskaitomi tik skaiciai 10 sistemoje
                        while (iss >> skaicius) {
                            if (skaicius >= 0 && skaicius <= 10) {
                                x.setRez(skaicius);
                                //cout<<skaicius<<endl;
                            }
                            if(iss.fail()){ 
                                err = true;
                                throw std::invalid_argument("NETINKAMA IVESTIS: GALIMA IVESTI SKAICIUS (1-10)");
                            }
                        }
                    }catch(const std::invalid_argument& e){
                        cerr << "KLAIDA: " << e.what() << endl;
                        break;
                    }

                    if(x.tarpRezultatai().size() == 0)
                        vektoriausIlgiotikrinimas++;

                    x.EgzaminoRezultatoGavimas(x, indeksas);
                    //is vektoriaus istraukiamas egzamino rez.
                    M.push_back(x);
                    indeksas++;
                }
                fr.close();
            // Iskvieciamas blokas jei nebuvo atidarytas failas
            }catch(const ios_base::failure &e) {
                cerr << "KLAIDA: " << e.what() << endl;
                cerr << "FAILAS NEBUVO RASTAS PRISKIRTOJE LOKACIJOJE!" << endl;
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

                istringstream iss(eilute);

                //Tikrinamas vardu ivedimas
                //Jei zodis nera sudarytas is raidziu, nutraukiamas programos darbas ir ismetamas pasirinkimo duomenu apdorojimo meniu                
                try{
                    x.VarduSkaitymas(iss, x, indeksas, err);
                    if(err) throw std::invalid_argument("PASIRINKTI SIMBOLIAI NERA (STRING) TIPO.");
                
                    while (iss >> skaicius || !iss.eof()) {
                        //Nuskaitomi tik skaiciai 10 sistemoje
                        if (skaicius >= 0 && skaicius <= 10) {
                            x.setRez(skaicius);
                        }
                        if(iss.fail()){ 
                            err = true;
                            throw std::invalid_argument("NETINKAMA IVESTIS: GALIMA IVESTI SKAICIUS (1-10)");
                        }
                    }
                }catch(const std::invalid_argument& e){
                    cerr << "KLAIDA: " << e.what() << endl;
                    break;
                }

                if(x.tarpRezultatai().size() == 1)
                    vektoriausIlgiotikrinimas++;

                x.EgzaminoRezultatoGavimas(x, indeksas);
                //is vektoriaus istraukiamas egzamino rez.
                M.push_back(x);
                indeksas++;
            }
            break;

        case 3:
            isvedimoPasirinkimas = 1;
            cout<<"Parasykite kiek noretumete kad prie kiekvieno mokinio butu sugeneruota pazymiu (pazymiai generuojami 10 balu sistemoje):\n";
            //Tikrinamas ar ivestas simbolis yra int tipo ir ar yra didesnis uz 1 naudojant try-catch metoda
            try{
                cin>>sugeneruotiSk;
                if(!cin.good() || sugeneruotiSk < 2)
                    throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO (>=2).");
            }catch(const std::invalid_argument& e){
                cerr << "KLAIDA:" << e.what() << endl;
                while(!cin.good() || sugeneruotiSk < 2){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin>>sugeneruotiSk;
                }
            }

            cout<<"Iveskite mokiniu vardus ir pavardes (noredami baigti ivedima nueje i nauja eilute paspauskite enter):\n";
            while (getline(cin, eilute)) {
            if (eilute.empty()) {
                    laisvaEilute++;
                    if(laisvaEilute == 2)
                        break;
                }

                mokinys x;

                istringstream iss(eilute);
                //Tikrinama ar vardas sudaromas tik is raidziu naudojant try-catch metoda
                try{
                    x.VarduSkaitymas(iss, x, indeksas, err);
                    if(err) throw std::invalid_argument("PASIRINKTI SIMBOLIAI NERA (STRING) TIPO.");
                }catch(const std::invalid_argument& e){
                    cerr << "KLAIDA: " << e.what() << endl;
                    break;
                }
                
                //Is anksto nustatoma kiek mokinia tures pazymiu, kad butu galima generuoti atsitiktinius pazymius
                x.tarpRezultatai().resize(sugeneruotiSk);
                if(!eilute.empty())
                    x.GeneruotiPazymius(x, indeksas);
                //is vektoriaus istraukiamas egzamino rez.
                x.EgzaminoRezultatoGavimas(x, indeksas);

                M.push_back(x);
                indeksas++;
            }
            break;

        case 4:
            isvedimoPasirinkimas = 1;
            cout<<"Pasirinkite kiek noresite skirtingu mokiniu sugeneruoti ir kiek mokiniai tures sugeneruotu pazymiu (pirmas skaicius - mokiniu sk., antras skaicius - pazymiu sk.)\n";
            
            //Tikrinama ar irasytas mokiniu sk. ir pazymiu sk. atitinka int tipa ir ar atitinka nurodytus parametrus naudojant try-catch metoda            
            try{
                cin>>indeksas>>sugeneruotiSk;
                if(!cin.good() || sugeneruotiSk < 2 || indeksas < 1) throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO (MOKINIU SK. > 1 , PAZYMIU SK. > 2).");
            }catch(const std::invalid_argument& e){
                cerr << "KLAIDA:" << e.what() << endl;
                while(!cin.good() || sugeneruotiSk < 2 || indeksas < 1){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin>>indeksas>>sugeneruotiSk;
                }
            }

            //Is anksto nusprendziamas kiek bus mokiniu ir kiek mokiniai tures pazymiu
            for(int i=0; i<indeksas; i++){
                mokinys x;

                x.VarduPavardziuGeneravimas(x, i);
                x.tarpRezultatai().resize(sugeneruotiSk);
                x.GeneruotiPazymius(x, i);
                //is vektoriaus istraukiamas egzamino rez.
                x.EgzaminoRezultatoGavimas(x, indeksas);
                M.push_back(x);
            }
            break;

        case 5:
            
            //Pasirinkimas kokio dydzio norimas naudoti masyvas
            cout<<"Pasirinkite koki faila noresite naudoti (1 - 1000, 2 - 10000, 3 - 100000, 4 - 1000000, 5 - 10000000)\n";
            try{
                cin>>zmoniuSkPasirinkimas;
                if(!cin.good() || zmoniuSkPasirinkimas < 1 || zmoniuSkPasirinkimas > 5) throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO [1, 5].");
            }catch(const std::invalid_argument& e){
                cerr << "KLAIDA: " << e.what() << endl;
                while(!cin.good() || zmoniuSkPasirinkimas < 1 || zmoniuSkPasirinkimas > 5){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin>>zmoniuSkPasirinkimas;
                }
            }

            int rikiavimoPasirinkimas, vidurkioTipas;
            cout<<"Pasirinkite kuriuos duomenis noresite rikiuoti (3 - vidurkiai, 4 - medianos)\n";
            //Tikrinama ar skaicius yra int tipo naudojant try-catch blokas
            try{ 
                cin>>rikiavimoPasirinkimas;
                if(!cin.good() || rikiavimoPasirinkimas<3 || rikiavimoPasirinkimas>4) throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO [3, 4].");
            }catch(const std::invalid_argument& e){
                cerr << "KLAIDA:" << e.what() << endl;
                while(!cin.good() || rikiavimoPasirinkimas<1 || rikiavimoPasirinkimas>5){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin>>rikiavimoPasirinkimas;
                }
            }
            try{
                cout<<"Pasirinkite kokiu budu noretumete, kad butu suskaiciuotas jus vidurkis (1 = paprastai, 2 = mediana):\n";
                cin>>vidurkioTipas;
                if(!cin.good() || (vidurkioTipas != 1 && vidurkioTipas != 2) || (rikiavimoPasirinkimas == 3 && vidurkioTipas == 2) || (rikiavimoPasirinkimas == 4 && vidurkioTipas == 1)) 
                    throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO (PASIRINKTI VIDURKIO SKAICIAVIMO IR RIKIAVIMO TIPAI TURI SUTAPTI).");
            }catch(const std::invalid_argument& e){
                cerr << "KLAIDA:" << e.what() << endl;
                while(!cin.good() || (vidurkioTipas != 1 && vidurkioTipas != 2) || (rikiavimoPasirinkimas == 3 && vidurkioTipas == 2) || (rikiavimoPasirinkimas == 4 && vidurkioTipas == 1)){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin>>vidurkioTipas;
                }
            }
            if(rikiavimoPasirinkimas != 5){
                cout<<"kaip norite rikiuoti(1 - didejimo tvarka, 2 - mazejimo tvarka):\n";
                try{
                    cin>>tvarka;
                    if(!cin.good() || tvarka<1 || tvarka>2) throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO [1, 2].");
                }catch(const std::exception& e){
                    cerr << "KLAIDA:" << e.what() << endl;
                    while(!cin.good() || tvarka<1 || tvarka>2){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout<<"Galite pasirinkti tik skaicius [1, 2]!\n";
                        cin>>tvarka;
                    }
                }
            }

            failoPavadinimas = "../studentu_sarasas_" + to_string(dydzioMasyvas[zmoniuSkPasirinkimas-1]) + ".txt";

            start = std::chrono::high_resolution_clock::now();

            fr.open(failoPavadinimas);
            if (!fr.is_open()) {
                throw std::ios_base::failure("FAILAS NERA ATIDARYTAS!");
            }

            getline(fr, eilute);
            buffer << fr.rdbuf();

            fr.close();

            while (!buffer.eof()){
                getline(buffer, eilute);
                istringstream iss(eilute);

                if (eilute.empty()) break;

                mokinys x;
                iss >> vardas >> pavarde;

                x.setVardas(vardas);
                x.setPavarde(pavarde);

                while (iss >> skaicius) {
                    x.setRez(skaicius);
                }

                x.EgzaminoRezultatoGavimas(x, indeksas);

                M.push_back(x);
            }


            end = std::chrono::high_resolution_clock::now();
            diff1 = end-start; // Skirtumas (s)
            std::cout << "duomenų nuskaitymas iš failo: "<< diff1.count() << " s\n";
            

            cout<<M.size()<<endl;
            double galutinis, mediana;
            if(vidurkioTipas == 1){
                for(auto& x : M){
                    l++;
                    x.VidurkioSkaiciavimas(x, pazSuma, galutinis);
                    pazSuma = 0;
                }
                cout<<l<<endl;
            }else if(vidurkioTipas == 2){
                for(auto& x : M){
                    x.MedianosSkaiciavimas(x, mediana);
                }
            }
            start = std::chrono::high_resolution_clock::now();
            Rikiavimas(M, rikiavimoPasirinkimas, tvarka);
            end = std::chrono::high_resolution_clock::now();
            diff2 = end-start; // Skirtumas (s)
            std::cout << "Mokiniu rikiavimas: "<< diff2.count() << " s\n";
            //Paskirsto mokinius i pazangiuosius ir nepazangiuosius
            start = std::chrono::high_resolution_clock::now();
            MokiniuSkirstymas(M, N, vidurkioTipas, tvarka);
            end = std::chrono::high_resolution_clock::now();
            diff3 = end-start; // Skirtumas (s)
            std::cout << "Mokiniu skirstymas: "<< diff3.count() << " s\n";

            diffTotal = diff1 + diff2 + diff3;
            cout<< "Bendras: " << diffTotal.count() << " s\n";

            //Pazangiuju ir nepazangiuju mokiniu isvedimas i faila
            //start = std::chrono::high_resolution_clock::now();
            MokiniuIsvedimas(M, N, vidurkioTipas);
            //end = std::chrono::high_resolution_clock::now();
            //diff = end-start; // Skirtumas (s)
            //std::cout << "Mokinius isvedimas: "<< diff.count() << " s\n";


            break;
        case 6:
            //Pasirinkimas kokio dydzio norimas sugeneruoti masyvas
            cout<<"Pasirinkite kokio dydzio faila noresite sugeneruoti (1 - 1000, 2 - 10000, 3 - 100000, 4 - 1000000, 5 - 10000000)\n";
            try{
                cin>>zmoniuSkPasirinkimas;
                if(!cin.good() || zmoniuSkPasirinkimas < 1 || zmoniuSkPasirinkimas > 5) throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO [1, 5].");
            }catch(const std::invalid_argument& e){
                cerr << "KLAIDA: " << e.what() << endl;
                while(!cin.good() || zmoniuSkPasirinkimas < 1 || zmoniuSkPasirinkimas > 5){
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin>>zmoniuSkPasirinkimas;
                }
            }

            failoPavadinimas = "../studentu_sarasas_" + to_string(dydzioMasyvas[zmoniuSkPasirinkimas-1]) + ".txt";

            FailuGeneravimas(failoPavadinimas, dydzioMasyvas[zmoniuSkPasirinkimas-1]);
            continue;
        case 7:
            EfektyvumoFunkcija();
            continue;
        case 8:
            return 0;
    }
   
//Istrinamas pirmas elementas, nes del sudarytos strukutors kaip nuskaitomi duomenys yra nuskaitoma tuscia eilute
    if (!M.empty() && pasirinkimas != 4 && pasirinkimas != 1) {
        M.erase(M.begin());
    }

    // if(vektoriausIlgiotikrinimas >= 1){
    //     cout<<"Turi buti irasyti bent du pazymiai!\n";
    // }
    double galutinis = 0;
    int vidurkioTipas, rikiavimoPasirinkimas, mokiniuSk = M.size(), pazymiuSuma = 0; 
    if(indeksas!=0 && err == 0 && vektoriausIlgiotikrinimas == 0 && pasirinkimas != 5){
        cout<<"Pasirinkite kuriuos duomenis noresite rikiuoti (1 - vardai, 2 - pavardes, 3 - vidurkiai, 4 - medianos, 5 - nerikiuoti):\n";
        //Tikrinama ar skaicius yra int tipo naudojant try-catch blokas
        try{ 
            cin>>rikiavimoPasirinkimas;
            if(!cin.good() || rikiavimoPasirinkimas<1 || rikiavimoPasirinkimas>5) throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO [1, 5].");
        }catch(const std::invalid_argument& e){
            cerr << "KLAIDA:" << e.what() << endl;
            while(!cin.good() || rikiavimoPasirinkimas<1 || rikiavimoPasirinkimas>5){
                cin.clear();
                cin.ignore(1000, '\n');
                cin>>rikiavimoPasirinkimas;
            }
        }
    }
    if(pasirinkimas != 5){
        try{
            cout<<"Pasirinkite kokiu budu noretumete, kad butu suskaiciuotas jus vidurkis (1 = paprastai, 2 = mediana):\n";
            cin>>vidurkioTipas;
            if(!cin.good() || (vidurkioTipas != 1 && vidurkioTipas != 2) || (rikiavimoPasirinkimas == 3 && vidurkioTipas == 2) || (rikiavimoPasirinkimas == 4 && vidurkioTipas == 1)) 
                throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO (PASIRINKTI VIDURKIO SKAICIAVIMO IR RIKIAVIMO TIPAI TURI SUTAPTI).");
        }catch(const std::invalid_argument& e){
            cerr << "KLAIDA:" << e.what() << endl;
            while(!cin.good() || (vidurkioTipas != 1 && vidurkioTipas != 2) || (rikiavimoPasirinkimas == 3 && vidurkioTipas == 2) || (rikiavimoPasirinkimas == 4 && vidurkioTipas == 1)){
                cin.clear();
                cin.ignore(1000, '\n');
                cin>>vidurkioTipas;
            }

        }
    }
    if(indeksas != 0 && err == 0 && vektoriausIlgiotikrinimas == 0 && isvedimoPasirinkimas == 1){
        //Suteikiami 2 pasirinkimai skaiciuoti vidurkius
        if(vidurkioTipas == 1){ 
            for(auto& x : M){
                x.VidurkioSkaiciavimas(x, pazymiuSuma, galutinis);
                pazymiuSuma = 0;
            }
            Rikiavimas(M, rikiavimoPasirinkimas);
            cout << left << setw(25) <<"Pavarde";
            cout << left << setw(25) <<"Vardas";
            cout << left << setw(30) << "Galutinis (Vid.)" << endl;
            cout << "------------------------------------------------------------" << endl;
            for(const auto& p: M){
                cout << left << setw(25) << p.pavard();
                cout << left << setw(25) << p.vard();
                cout << left << setw(30) << fixed << setprecision(2) << p.vid() << endl;
            } 
        }else if (vidurkioTipas == 2){
            for(auto& x : M){
                x.MedianosSkaiciavimas(x, galutinis);
            }
            Rikiavimas(M, rikiavimoPasirinkimas);
            cout << left << setw(25) <<"Pavarde";
            cout << left << setw(25) <<"Vardas";
            cout << left << setw(30) << "Galutinis (Med.)" << endl;
            cout << string(66, '-') << endl;
            for(const auto& p: M){
                //Pridedamas egzamino rezultatas i vektoriu prie pazymiu ir surikiuojami skaiciai vektoriuje nuo didziausio iki maziausio
                cout << left << setw(25) << p.pavard();
                cout << left << setw(25) << p.vard();
                cout << left << setw(30) << fixed << setprecision(2) << p.med() << endl;
            }
        }
    }else if(indeksas != 0 && err == 0 && vektoriausIlgiotikrinimas == 0 && isvedimoPasirinkimas == 2){
        try{
            fw.open("rezultatai.txt", ios::out);
            if (!fw.is_open()) {
                throw std::ios_base::failure("FAILAS NERA ATIDARYTAS!");
            }
            //Suteikiami 2 pasirinkimai skaiciuoti vidurkius
            if(vidurkioTipas == 1){ 
                fw << left << setw(25) <<"Pavarde";
                fw  << left << setw(25) <<"Vardas";
                fw  << left << setw(30) << "Galutinis (Vid.)" << endl;
                fw  << "------------------------------------------------------------" << endl;
                for(auto& x : M){
                    x.VidurkioSkaiciavimas(x, pazymiuSuma, galutinis);
                    pazymiuSuma = 0;
                }
                Rikiavimas(M, rikiavimoPasirinkimas);
                for(const auto& p: M){
                    fw  << left << setw(25) << p.pavard();
                    fw  << left << setw(25) << p.vard();
                    fw  << left << setw(30) << fixed << setprecision(2) << p.vid() << endl;
                } 
            }else if (vidurkioTipas == 2){
                fw  << left << setw(25) <<"Pavarde";
                fw  << left << setw(25) <<"Vardas";
                fw  << left << setw(30) << "Galutinis (Med.)" << endl;
                fw  << string(66, '-') << endl;
                for(auto& x : M){
                    x.MedianosSkaiciavimas(x, galutinis);
                }
                Rikiavimas(M, rikiavimoPasirinkimas);
                for(const auto& p: M){
                    //Pridedamas egzamino rezultatas i vektoriu prie pazymiu ir surikiuojami skaiciai vektoriuje nuo didziausio iki maziausio
                    fw  << left << setw(25) << p.pavard();
                    fw  << left << setw(25) << p.vard();
                    fw  << left << setw(30) << fixed << setprecision(2) << p.med() << endl;
                }
            }
            //cout<<bendras<<endl;
            fw.close();
        }catch(const ios_base::failure &e) {
            cerr << "KLAIDA: " << e.what() << endl;
            cerr << "FAILAS NEBUVO RASTAS PRISKIRTOJE LOKACIJOJE!" << endl;
            return 1;
        }
    }
}

    return 0;
}