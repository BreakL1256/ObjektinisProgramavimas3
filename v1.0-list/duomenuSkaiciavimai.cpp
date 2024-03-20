#include "skaiciavimai.h"


using namespace std;

//Mokiniu skirstymas i pazangiuju ir nepazangiuju grupes
void MokiniuSkirstymas(list<mokinys> & M, list<mokinys> & N, int vidurkioTipas, int rikiavimas){
    if (vidurkioTipas == 1) {
        if (rikiavimas == 1) {
            auto spot = std::lower_bound(M.begin(), M.end(), 5.0, [](const mokinys& a, const double b) { return a.vidurkis < b; });
            std::copy(M.begin(), spot, std::back_inserter(N));
            M.erase(M.begin(), spot);
        }
        else if (rikiavimas == 2) {
            auto spot = std::upper_bound(M.begin(), M.end(), 5.0, [](const double b, const mokinys& a) { return a.vidurkis < b; });
            std::copy(M.begin(), spot, std::back_inserter(N));
            M.erase(M.begin(), spot);
        }
    }
    else if (vidurkioTipas == 2) {
        if (rikiavimas == 1) {
            auto spot = std::lower_bound(M.begin(), M.end(), 5.0, [](const mokinys& a, const double b) { return a.mediana < b; });
            std::copy(M.begin(), spot, std::back_inserter(N));
            M.erase(M.begin(), spot);
        }
        else if (rikiavimas == 2) {
            auto spot = std::upper_bound(M.begin(), M.end(), 5.0, [](const double b, const mokinys& a) { return a.mediana < b; });
            std::copy(M.begin(), spot, std::back_inserter(N));
            M.erase(M.begin(), spot);
        }
    }
}

void VidurkioSkaiciavimas(mokinys& x, int pazymiuSuma, double & galutinis){
    int rezultatuSk = x.tarpiniaiRezultatai.size();
    //Sudedami visi pazymiai
    for(const auto& i: x.tarpiniaiRezultatai){
        pazymiuSuma+=i;
    }
    //Suskaiciuojamas galutinis pazymys pagal formule
    galutinis = 0.4 * (pazymiuSuma/rezultatuSk) + 0.6 * x.egzaminoRezultatas;
    x.vidurkis = galutinis;
    galutinis = 0;
}

void MedianosSkaiciavimas(mokinys & x, double & mediana){
    x.tarpiniaiRezultatai.push_back(x.egzaminoRezultatas);
    int rezultatuSk = x.tarpiniaiRezultatai.size();
    //sort(x.tarpiniaiRezultatai.begin(), x.tarpiniaiRezultatai.end());
    x.tarpiniaiRezultatai.sort();
    //skaiciuojama mediana
    //patikrinama ar yra lyginis ar nelyginis skaicius elementu vektoriuje
    auto mid1 = x.tarpiniaiRezultatai.begin();
    advance(mid1, (rezultatuSk-1)/2);
    if(rezultatuSk%2!=0){
        //int skaicius = rezultatuSk/2;
        //advance(mid, (rezultatuSk-1)/2);
        mediana = *mid1;
    }else if(rezultatuSk%2==0){
        auto mid2 = mid1;
        advance(mid2, 1);
        mediana = (*mid1 + *mid2)/2;
    }
    x.mediana = mediana;
}
bool PalygintiVardus(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() < b.length(); 
    }
    return a < b;
}

bool DidejimasVardai(const mokinys& a, const mokinys& b){return PalygintiVardus(a.vardas, b.vardas);}
bool MazejimasVardai(const mokinys& a, const mokinys& b){return !PalygintiVardus(a.vardas, b.vardas);}
bool DidejimasPavardes(const mokinys& a, const mokinys& b){return PalygintiVardus(a.pavarde, b.pavarde);}
bool MazejimasPavardes(const mokinys& a, const mokinys& b){return !PalygintiVardus(a.pavarde, b.pavarde);}
bool DidejimasVidurkis(const mokinys& a, const mokinys& b){return a.vidurkis < b.vidurkis;}
bool MazejimasVidurkis(const mokinys& a, const mokinys& b){return a.vidurkis > b.vidurkis;}
bool DidejimasMediana(const mokinys& a, const mokinys& b){return a.mediana < b.mediana;}
bool MazejimasMediana(const mokinys& a, const mokinys& b){return a.mediana > b.mediana;}

list<mokinys> Rikiavimas(list<mokinys> & M, int rikiavimoPasirinkimas, const int& sk){
    int tvarka;
    if(rikiavimoPasirinkimas != 5 && sk == 0){
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
    }else if(rikiavimoPasirinkimas != 5 && sk != 0) tvarka = sk;
    switch(rikiavimoPasirinkimas){
        case 1:
            if(tvarka == 1){
            M.sort( DidejimasVardai);
            }else if(tvarka == 2){
            M.sort( MazejimasVardai);
            }
            break;
        case 2:
            if(tvarka == 1){
            M.sort(DidejimasPavardes);
            }else if(tvarka == 2){
            M.sort(MazejimasPavardes);    
            }
            break;
        case 3:
            if(tvarka == 1){
            M.sort(DidejimasVidurkis);
            }else if(tvarka == 2){
            M.sort(MazejimasVidurkis);    
            }
            break;
        case 4:
            if(tvarka == 1){
            M.sort(DidejimasMediana);
            }else if(tvarka == 2){
            M.sort(MazejimasMediana);   
            }
            break;
        case 5:
            break;
    }
    return M;
}

mokinys EgzaminoRezultatoGavimas(mokinys & x){
    if (x.tarpiniaiRezultatai.size() > 1) {
        x.egzaminoRezultatas = x.tarpiniaiRezultatai.back();
        x.tarpiniaiRezultatai.pop_back();
    }
    return x;
}