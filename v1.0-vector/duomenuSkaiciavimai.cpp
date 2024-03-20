#include "skaiciavimai.h"

using namespace std;


//Mokiniu skirstymas i pazangiuju ir nepazangiuju grupes
void MokiniuSkirstymas(vector<mokinys> & M, vector<mokinys> & N, int vidurkioTipas, int rikiavimas){
        // auto spot = lower_bound(M.begin(), M.end(), 5.0, [](const mokinys &a, const double b){ return a.vidurkis < b; });
        // N.insert(N.begin(), M.begin(), spot); 
        // M.erase(M.begin(), spot);
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

void VidurkioSkaiciavimas(vector<mokinys> & M, int pazymiuSuma, double & galutinis, int i){
    int rezultatuSk = M[i].tarpiniaiRezultatai.size();
    //Sudedami visi pazymiai
    for(int j=0; j<rezultatuSk; j++){
        pazymiuSuma+=M[i].tarpiniaiRezultatai[j];
    }
    //Suskaiciuojamas galutinis pazymys pagal formule
    galutinis = 0.4 * (pazymiuSuma/rezultatuSk) + 0.6 * M[i].egzaminoRezultatas;
    M[i].vidurkis = galutinis;
    galutinis = 0;
}

void MedianosSkaiciavimas(vector<mokinys> & M, double & mediana, int i){
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
        mediana = (M[i].tarpiniaiRezultatai[pirmas]+M[i].tarpiniaiRezultatai[antras])/2.0;
    }
    M[i].mediana = mediana;
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

vector<mokinys> Rikiavimas(vector<mokinys> & M, int rikiavimoPasirinkimas, const int& sk){
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
            sort(M.begin(), M.end(), DidejimasVardai);
            }else if(tvarka == 2){
            sort(M.begin(), M.end(), MazejimasVardai);
            }
            break;
        case 2:
            if(tvarka == 1){
            sort(M.begin(), M.end(), DidejimasPavardes);
            }else if(tvarka == 2){
            sort(M.begin(), M.end(), MazejimasPavardes);    
            }
            break;
        case 3:
            if(tvarka == 1){
            sort(M.begin(), M.end(), DidejimasVidurkis);
            }else if(tvarka == 2){
            sort(M.begin(), M.end(), MazejimasVidurkis);    
            }
            break;
        case 4:
            if(tvarka == 1){
            sort(M.begin(), M.end(), DidejimasMediana);
            }else if(tvarka == 2){
            sort(M.begin(), M.end(), MazejimasMediana);   
            }
            break;
        case 5:
            break;
    }
    return M;
}

vector<mokinys> EgzaminoRezultatoGavimas(vector<mokinys> & M, int indeksas){
    if (M[indeksas].tarpiniaiRezultatai.size() > 1) {
        M[indeksas].egzaminoRezultatas = M[indeksas].tarpiniaiRezultatai.back();
        M[indeksas].tarpiniaiRezultatai.pop_back();
    }
    return M;
}