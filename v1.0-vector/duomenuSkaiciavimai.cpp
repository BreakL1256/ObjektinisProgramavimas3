#include "skaiciavimai.h"

using namespace std;


//Mokiniu skirstymas i pazangiuju ir nepazangiuju grupes
void MokiniuSkirstymas(vector<mokinys> & M, vector<mokinys> & N, int vidurkioTipas, int rikiavimas){
        // auto spot = lower_bound(M.begin(), M.end(), 5.0, [](const mokinys &a, const double b){ return a.vidurkis < b; });
        // N.insert(N.begin(), M.begin(), spot); 
        // M.erase(M.begin(), spot);
        if (vidurkioTipas == 1) {
        if (rikiavimas == 1) {
            auto spot = std::lower_bound(M.begin(), M.end(), 5.0, [](const mokinys& a, const double b) { return a.vid() < b; });
            std::copy(M.begin(), spot, std::back_inserter(N));
            M.erase(M.begin(), spot);
        }
        else if (rikiavimas == 2) {
            auto spot = std::upper_bound(M.begin(), M.end(), 5.0, [](const double b, const mokinys& a) { return a.vid() < b; });
            std::copy(M.begin(), spot, std::back_inserter(N));
            M.erase(M.begin(), spot);
        }
        }
        else if (vidurkioTipas == 2) {
            if (rikiavimas == 1) {
                auto spot = std::lower_bound(M.begin(), M.end(), 5.0, [](const mokinys& a, const double b) { return a.med() < b; });
                std::copy(M.begin(), spot, std::back_inserter(N));
                M.erase(M.begin(), spot);
            }
            else if (rikiavimas == 2) {
                auto spot = std::upper_bound(M.begin(), M.end(), 5.0, [](const double b, const mokinys& a) { return a.med()< b; });
                std::copy(M.begin(), spot, std::back_inserter(N));
                M.erase(M.begin(), spot);
            }
        }
}

void mokinys::VidurkioSkaiciavimas(mokinys & M, int pazymiuSuma, double & galutinis){
    int rezultatuSk = M.tarpiniaiRezultatai.size();
    //Sudedami visi pazymiai
    for(int j=0; j<rezultatuSk; j++){
        pazymiuSuma+=M.tarpiniaiRezultatai[j];
    }
    //Suskaiciuojamas galutinis pazymys pagal formule
    galutinis = 0.4 * (pazymiuSuma/rezultatuSk) + 0.6 * M.egzaminoRezultatas;
    M.vidurkis = galutinis;
    galutinis = 0;
}

void mokinys::MedianosSkaiciavimas(mokinys & M, double & mediana){
    M.tarpiniaiRezultatai.push_back(M.egzaminoRezultatas);
    int rezultatuSk = M.tarpiniaiRezultatai.size();
    sort(M.tarpiniaiRezultatai.begin(), M.tarpiniaiRezultatai.end());
    //skaiciuojama mediana
    //patikrinama ar yra lyginis ar nelyginis skaicius elementu vektoriuje
    if(rezultatuSk%2!=0){
        int skaicius = rezultatuSk/2;
        mediana = M.tarpiniaiRezultatai[skaicius];
    }else if(rezultatuSk%2==0){
        int pirmas = rezultatuSk/2-1;
        int antras = rezultatuSk/2;
        mediana = (M.tarpiniaiRezultatai[pirmas]+M.tarpiniaiRezultatai[antras])/2.0;
    }
    M.mediana = mediana;
}
bool PalygintiVardus(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() < b.length(); 
    }
    return a < b;
}

bool DidejimasVardai(const mokinys& a, const mokinys& b){return PalygintiVardus(a.vard(), b.vard());}
bool MazejimasVardai(const mokinys& a, const mokinys& b){return !PalygintiVardus(a.vard(), b.vard());}
bool DidejimasPavardes(const mokinys& a, const mokinys& b){return PalygintiVardus(a.pavard(), b.pavard());}
bool MazejimasPavardes(const mokinys& a, const mokinys& b){return !PalygintiVardus(a.pavard(), b.pavard());}
bool DidejimasVidurkis(const mokinys& a, const mokinys& b){return a.vid() < b.vid();}
bool MazejimasVidurkis(const mokinys& a, const mokinys& b){return a.vid() > b.vid();}
bool DidejimasMediana(const mokinys& a, const mokinys& b){return a.med() < b.med();}
bool MazejimasMediana(const mokinys& a, const mokinys& b){return a.med() > b.med();}

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

void mokinys::EgzaminoRezultatoGavimas(mokinys & M, int indeksas){
    if (M.tarpiniaiRezultatai.size() > 1) {
        M.setegz(M.tarpiniaiRezultatai.back());
        M.tarpiniaiRezultatai.pop_back();
    }
}

void mokinys::pazymiai(){
    cout<<"Pazymiai: ";
    for(int i : tarpiniaiRezultatai){
        cout<<i<<" ";
    }
    cout<<endl;
}

zmogus::zmogus(){
    amzius = 0;
    klase = 0;
}

zmogus::~zmogus(){
    //cout<<"Objektas sunaikintas\n";
}

mokinys::mokinys(){
    vardas = "";
    pavarde = "";
    egzaminoRezultatas = 0;
    vidurkis = 0;
    mediana = 0;
}

mokinys::mokinys(const mokinys& m)
: zmogus{m.vardas, m.pavarde},
  tarpiniaiRezultatai{m.tarpiniaiRezultatai},
  egzaminoRezultatas{m.egzaminoRezultatas},
  vidurkis{m.vidurkis},
  mediana{m.mediana}
{
    //cout<<"atlikta objekto kopija naudojant copy constructor\n";
};

mokinys::mokinys(mokinys&& m)
: zmogus{m.vardas, m.pavarde},
  tarpiniaiRezultatai{move(m.tarpiniaiRezultatai)},
  egzaminoRezultatas{m.egzaminoRezultatas},
  vidurkis{m.vidurkis},
  mediana{m.mediana}
{
    m.vardas = "";
    m.pavarde = "";
    fill_n(m.tarpiniaiRezultatai.begin(), m.tarpiniaiRezultatai.size(), 0);
    m.egzaminoRezultatas = 0;
    m.vidurkis = 0;
    m.mediana = 0;
    //cout<<"atlikta objekto perrasymas naudojant move constructor\n";
}; 

mokinys& mokinys::operator=(const mokinys& m){
    if (&m == this) return *this;
    vardas = m.vardas;
    pavarde = m.pavarde;
    tarpiniaiRezultatai = m.tarpiniaiRezultatai;
    egzaminoRezultatas = m.egzaminoRezultatas;
    vidurkis = m.vidurkis;
    mediana = m.mediana;
    return *this;
};

mokinys& mokinys::operator=(mokinys&& m){
    if (&m == this) return *this;
    vardas = move(m.vardas);
    pavarde = move(m.pavarde);
    tarpiniaiRezultatai = move(m.tarpiniaiRezultatai);
    egzaminoRezultatas = m.egzaminoRezultatas;
    vidurkis = m.vidurkis;
    mediana = m.mediana;
    m.vardas = "";
    m.pavarde = "";
    fill_n(m.tarpiniaiRezultatai.begin(), m.tarpiniaiRezultatai.size(), 0);
    m.egzaminoRezultatas = 0;
    m.vidurkis = 0;
    m.mediana = 0;
    return *this;
};

istream& operator>>(istream& in, mokinys& m){
    string eilute;
    in.ignore(1000, '\n');
    getline(in, eilute);
    istringstream iss(eilute);
    iss >> m.vardas >> m.pavarde;
    int skaic;
    while (iss >> skaic) {
        m.tarpiniaiRezultatai.push_back(skaic);
    }
    return in;
};

ostream& operator<<(ostream& out, const mokinys& m){
    out<<m.vardas<<" "<<m.pavarde<<endl;
    out<<"pažymiai: ";
    for(int i: m.tarpiniaiRezultatai){
        out<<i<<" ";
    }
    out<<"\negzamino rezultatas/vidurkis/mediana:\n";
    out<<m.egzaminoRezultatas<<" "<<m.vidurkis<<" "<<m.mediana<<endl;
    return out;
};

mokinys operator+(const mokinys& a, const mokinys& b){
    mokinys c;
    c.setVardas(a.vard()+" "+b.vard());
    c.setPavarde(a.pavard()+" "+b.pavard());
    c.tarpRezultatai().reserve(a.tarpRezultatai().size() + b.tarpRezultatai().size());
    c.tarpRezultatai().insert(c.tarpRezultatai().end(), a.tarpRezultatai().begin(), a.tarpRezultatai().end());
    c.tarpRezultatai().insert(c.tarpRezultatai().end(), b.tarpRezultatai().begin(), b.tarpRezultatai().end());
    return c;
};

mokinys::~mokinys(){
    tarpiniaiRezultatai.clear();
    //cout<<"Objektas sunaikintas\n";
}
