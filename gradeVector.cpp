#include "skaiciavimai.h"

using namespace std;

int main()
{
double skaicius;

//Veikimas padarytas, kad programa veiktu kol nepasirenkamas jos terminavimas
while(true){
    fstream fread;
    vector<mokinys> M;
    vector<pazangieji> P;
    vector<nepazangieji> N;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> diff;
    
    string eilute, failoPavadinimas;;
    int indeksas = 0, pasirinkimas, laisvaEilute = 0, sugeneruotiSk, vektoriausIlgiotikrinimas = 0, isvedimoPasirinkimas, zmoniuSkPasirinkimas = 0, sk = 0;
    int dydzioMasyvas[5] = {1000, 10000, 100000, 1000000, 10000000};
    bool err = 0;
    
    cout<<"Pasirinkite kaip noretumete, kad butu apdorojami jusu ivesti duomenys: 1 - is failo, 2 - ranka, 3 - generuoti pazymius, 4 - generuoti ir pazymius ir studentu vardus, pavardes, 5 - generuoti faila su mokiniu duomenimis,  6 - baigti darba\n";
    try{
        cin>>pasirinkimas;
        if(!cin.good() || pasirinkimas<1 || pasirinkimas>6) throw std::invalid_argument("PASIRINKTAS SIMBOLIS NERA (INT) TIPO [1, 6].");
    }catch(const std::exception& e){
        cerr << "KLAIDA:" << e.what() << endl;
        while(!cin.good() || pasirinkimas<1 || pasirinkimas>6){
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Pasirinkite kaip noretumete, kad butu apdorojami jusu ivesti duomenys: 1 - is failo, 2 - ranka, 3 - generuoti pazymius, 4 - generuoti ir pazymius ir studentu vardus, pavardes, 5 - generuoti faila su mokiniu duomenimis,  6 - baigti darba\n";
            cin>>pasirinkimas;
        }
    }
//Suteikiami 4 pasirinkimai kaip dirbti su duomenimis: 1 - is failo, 2 - ranka, 3 - generuoti pazymius, 4 - generuoti ir pazymius ir studentu vardus, pavardes, 5 - generuoti faila su mokiniu duomenimis,  6 - baigti darba

    switch(pasirinkimas){
        case 1:
            // Naudojamas try-catch metodas tikrinti ar pavyko atidaryti skaitymo faila
            try{
                fread.open("studentai10000.txt", std::ios::in);
                //Throwinamas error jei failas nera atidarytas
                if (!fread.is_open()) {
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

                fread.ignore(1000, '\n');
                while (getline(fread, eilute)) {
                //Patikrinama ar kada praleidziama tuscia eilute, kad butu sustapdomas rasymo procesas
                    if (eilute.empty()) {
                            break;
                    }


                    mokinys x;
                    M.push_back(x);

                    istringstream iss(eilute);
                    //Tkrinamas skaiciu ivedimas naudojant try-catch metoda
                    try{
                        iss >> M[indeksas].vardas >> M[indeksas].pavarde;

                        //Nuskaitomi tik skaiciai 10 sistemoje
                        while (iss >> skaicius) {
                            if (skaicius >= 0 && skaicius <= 10) {
                                M[indeksas].tarpiniaiRezultatai.push_back(skaicius);
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

                    if(M[indeksas].tarpiniaiRezultatai.size() == 0)
                        vektoriausIlgiotikrinimas++;

                    EgzaminoRezultatoGavimas(M, indeksas);
                    //is vektoriaus istraukiamas egzamino rez.
                    indeksas++;
                }
                fread.close();
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
                M.push_back(x);

                istringstream iss(eilute);

                //Tikrinamas vardu ivedimas
                //Jei zodis nera sudarytas is raidziu, nutraukiamas programos darbas ir ismetamas pasirinkimo duomenu apdorojimo meniu                
                try{
                    VarduSkaitymas(iss, M, indeksas, err);
                    if(err) throw std::invalid_argument("PASIRINKTI SIMBOLIAI NERA (STRING) TIPO.");
                
                    while (iss >> skaicius || !iss.eof()) {
                        //Nuskaitomi tik skaiciai 10 sistemoje
                        if (skaicius >= 0 && skaicius <= 10) {
                            M[indeksas].tarpiniaiRezultatai.push_back(skaicius);
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

                if(M[indeksas].tarpiniaiRezultatai.size() == 1)
                    vektoriausIlgiotikrinimas++;

                EgzaminoRezultatoGavimas(M, indeksas);
                //is vektoriaus istraukiamas egzamino rez.
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
                M.push_back(x);

                istringstream iss(eilute);
                //Tikrinama ar vardas sudaromas tik is raidziu naudojant try-catch metoda
                try{
                    VarduSkaitymas(iss, M, indeksas, err);
                    if(err) throw std::invalid_argument("PASIRINKTI SIMBOLIAI NERA (STRING) TIPO.");
                }catch(const std::invalid_argument& e){
                    cerr << "KLAIDA: " << e.what() << endl;
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
                M.push_back(x);

                VarduPavardziuGeneravimas(M, i);
                M[i].tarpiniaiRezultatai.resize(sugeneruotiSk);
                GeneruotiPazymius(M, i);
                //is vektoriaus istraukiamas egzamino rez.
                EgzaminoRezultatoGavimas(M, i);
            }
            break;

        case 5:
            
            //Pasirinkimas kokio dydzio norimas generuoti masyvas
            cout<<"Pasirinkite kiek noresite, kad butu sugeneruota mokiniu faile (1 - 1000, 2 - 10000, 3 - 100000, 4 - 1000000, 5 - 10000000)\n";
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

            failoPavadinimas = "studentu_sarasas_" + to_string(dydzioMasyvas[zmoniuSkPasirinkimas-1]) + ".txt";
            //failoPavadinimas = "studentu_sarasas_1000.txt";
            FailuGeneravimas(fread, failoPavadinimas, dydzioMasyvas[zmoniuSkPasirinkimas-1]);

            try{
                start = std::chrono::high_resolution_clock::now();
                fread.open(failoPavadinimas, std::ios::in);
                if (!fread.is_open()) {
                    throw std::ios_base::failure("FAILAS NERA ATIDARYTAS!");
                }
                

                // std::stringstream buffer;
                // if(zmoniuSkPasirinkimas == 4) buffer.str(std::string(100000000, '\0'));
                // if(zmoniuSkPasirinkimas == 5) buffer.str(std::string(999999999, '\0'));

                // buffer << fread.rdbuf();
                // fread.close();


                string header;
                // getline(buffer, header);
                getline(fread, header);

                size_t bufferSize = 1000000;
                
                stringstream buffer;
                //buffer << header << endl;

                string buf;
                while (getline(fread, buf)) {
                    buffer << buf << endl;
                    if(buffer.str().size() > bufferSize){
                        while (getline(buffer, eilute)) {
                        //Patikrinama ar kada praleidziama tuscia eilute, kad butu sustapdomas rasymo procesas
                            // if (eilute.empty()) {
                            //         break;
                            // }
                            sk++;
                            mokinys x;

                            istringstream iss(eilute);
                            //Tkrinamas skaiciu ivedimas naudojant try-catch metoda
                            try{
                                iss >> x.vardas >> x.pavarde;

                                //Nuskaitomi tik skaiciai 10 sistemoje
                                while (iss >> skaicius) {
                                    if (skaicius >= 0 && skaicius <= 10) {
                                        x.tarpiniaiRezultatai.push_back(skaicius);
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

                            if(x.tarpiniaiRezultatai.size() == 0)
                                vektoriausIlgiotikrinimas++;

                            if (x.tarpiniaiRezultatai.size() > 1) {
                                x.egzaminoRezultatas = x.tarpiniaiRezultatai.back();
                                x.tarpiniaiRezultatai.pop_back();
                            }
                        // EgzaminoRezultatoGavimas(M, indeksas);
                            //is vektoriaus istraukiamas egzamino rez.
                            M.push_back(x);
                        }
                        buffer.str("");
                        buffer.clear();
                    }
                }

                while (getline(buffer, eilute)) {
                //Patikrinama ar kada praleidziama tuscia eilute, kad butu sustapdomas rasymo procesas
                    // if (eilute.empty()) {
                    //         break;
                    // }
                    sk++;
                    mokinys x;

                    istringstream iss(eilute);
                    //Tkrinamas skaiciu ivedimas naudojant try-catch metoda
                    try{
                        iss >> x.vardas >> x.pavarde;

                        //Nuskaitomi tik skaiciai 10 sistemoje
                        while (iss >> skaicius) {
                            if (skaicius >= 0 && skaicius <= 10) {
                                x.tarpiniaiRezultatai.push_back(skaicius);
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

                    if(x.tarpiniaiRezultatai.size() == 0)
                        vektoriausIlgiotikrinimas++;

                    if (x.tarpiniaiRezultatai.size() > 1) {
                        x.egzaminoRezultatas = x.tarpiniaiRezultatai.back();
                        x.tarpiniaiRezultatai.pop_back();
                    }
                // EgzaminoRezultatoGavimas(M, indeksas);
                    //is vektoriaus istraukiamas egzamino rez.
                    M.push_back(x);
                }
                // Close the file
                fread.close();

                //cout<< header<<endl;
                // std::cout << "Buffer contents:" << std::endl;
                // std::cout << buffer.str() << std::endl;

                //cout<<M.size();
                //fread.close();
                end = std::chrono::high_resolution_clock::now();
                diff = end-start; // Skirtumas (s)
                std::cout << "duomenų nuskaitymą iš failo: "<< diff.count() << " s\n";
                
                //return 1;
                int rikiavimoPasirinkimas, vidurkioTipas;
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
                cout<<sk<<endl;
                cout<<M.size()<<endl;
                int pazymiuSuma = 0;
                double galutinis, mediana;
                if(vidurkioTipas == 1){
                    for(long long i=0; i<M.size(); i++){
                        VidurkioSkaiciavimas(M, pazymiuSuma, galutinis, i);
                        pazymiuSuma = 0;
                    }
                }else if(vidurkioTipas == 2){
                    for(long long i=0; i<M.size(); i++){
                        MedianosSkaiciavimas(M, mediana, i);
                    }
                }

                Rikiavimas(M, rikiavimoPasirinkimas);

                //Paskirsto mokinius i pazangiuosius ir nepazangiuosius
                start = std::chrono::high_resolution_clock::now();
                MokiniuSkirstymas(M, P, N, vidurkioTipas);
                end = std::chrono::high_resolution_clock::now();
                diff = end-start; // Skirtumas (s)
                std::cout << "Mokinius skirstymas: "<< diff.count() << " s\n";

                //Pazangiuju ir nepazangiuju mokiniu isvedimas i faila
                start = std::chrono::high_resolution_clock::now();
                MokiniuIsvedimas(P, N, vidurkioTipas);
                end = std::chrono::high_resolution_clock::now();
                diff = end-start; // Skirtumas (s)
                std::cout << "Mokinius isvedimas: "<< diff.count() << " s\n";

            }catch(const ios_base::failure &e){
                cerr << "KLAIDA: " << e.what() << endl;
                cerr << "FAILAS NEBUVO RASTAS PRISKIRTOJE LOKACIJOJE!" << endl;
                return 1;
            }

            break;
        case 6:
            return 0;
    }
   
//Istrinamas pirmas elementas, nes del sudarytos strukutors kaip nuskaitomi duomenys yra nuskaitoma tuscia eilute
    if (!M.empty() && pasirinkimas != 4 && pasirinkimas != 1) {
        M.erase(M.begin());
    }

    // if(vektoriausIlgiotikrinimas >= 1){
    //     cout<<"Turi buti irasyti bent du pazymiai!\n";
    // }

    int vidurkioTipas, rikiavimoPasirinkimas, mokiniuSk = M.size(), pazymiuSuma = 0; 
    double mediana = 0, galutinis = 0; 
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
            for(int i=0; i<mokiniuSk; i++){
                VidurkioSkaiciavimas(M, pazymiuSuma, galutinis, i);
                pazymiuSuma = 0;
            }
            Rikiavimas(M, rikiavimoPasirinkimas);
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
            Rikiavimas(M, rikiavimoPasirinkimas);
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
    }else if(indeksas != 0 && err == 0 && vektoriausIlgiotikrinimas == 0 && isvedimoPasirinkimas == 2){
        try{
            fread.open("rezultatai.txt", ios::out);
            if (!fread.is_open()) {
                throw std::ios_base::failure("FAILAS NERA ATIDARYTAS!");
            }
            //Suteikiami 2 pasirinkimai skaiciuoti vidurkius
            if(vidurkioTipas == 1){ 
                fread << left << setw(25) <<"Pavarde";
                fread  << left << setw(25) <<"Vardas";
                fread  << left << setw(30) << "Galutinis (Vid.)" << endl;
                fread  << "------------------------------------------------------------" << endl;
                for(int i=0; i<mokiniuSk; i++){
                    VidurkioSkaiciavimas(M, pazymiuSuma, galutinis, i);
                    pazymiuSuma = 0;
                }
                Rikiavimas(M, rikiavimoPasirinkimas);
                for(int i=0; i<mokiniuSk; i++){
                    fread  << left << setw(25) << M[i].pavarde;
                    fread  << left << setw(25) << M[i].vardas;
                    fread  << left << setw(30) << fixed << setprecision(2) << M[i].vidurkis << endl;
                } 
            }else if (vidurkioTipas == 2){
                fread  << left << setw(25) <<"Pavarde";
                fread  << left << setw(25) <<"Vardas";
                fread  << left << setw(30) << "Galutinis (Med.)" << endl;
                fread  << string(66, '-') << endl;
                for(int i=0; i<mokiniuSk; i++){
                    MedianosSkaiciavimas(M, mediana, i);
                }
                Rikiavimas(M, rikiavimoPasirinkimas);
                for(int i=0; i<mokiniuSk; i++){
                    //Pridedamas egzamino rezultatas i vektoriu prie pazymiu ir surikiuojami skaiciai vektoriuje nuo didziausio iki maziausio
                    fread  << left << setw(25) << M[i].pavarde;
                    fread  << left << setw(25) << M[i].vardas;
                    fread  << left << setw(30) << fixed << setprecision(2) << M[i].mediana << endl;
                }
            }
            //cout<<bendras<<endl;
            fread.close();
        }catch(const ios_base::failure &e) {
            cerr << "KLAIDA: " << e.what() << endl;
            cerr << "FAILAS NEBUVO RASTAS PRISKIRTOJE LOKACIJOJE!" << endl;
            return 1;
        }
    }
}

    return 0;
}