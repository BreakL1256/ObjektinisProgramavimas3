# ifndef SKAICIAVIMAI_H
# define SKAICIAVIMAI_H

#include <string>
#include <vector>

using namespace std;

struct mokinys{
    string vardas;
    string pavarde;
    vector<int> tarpiniaiRezultatai;
    int egzaminoRezultatas;
    double mediana;
    double vidurkis;
};

bool SudaroTikRaides(string&);
void VarduSkaitymas(istringstream&, vector<mokinys>& ,int , bool&);
void GeneruotiPazymius(vector<mokinys>&, int);
void VarduPavardziuGeneravimas(vector<mokinys>&, int);
void VidurkioSkaiciavimas(vector<mokinys>&, int , double & , int);
void MedianosSkaiciavimas(vector<mokinys> & , double & , int );
bool PalygintiVardus(const string&, const string&);
bool DidejimasVardai(const mokinys&, const mokinys&);
bool MazejimasVardai(const mokinys&, const mokinys&);
bool DidejimasPavardes(const mokinys&, const mokinys&);
bool MazejimasPavardes(const mokinys&, const mokinys&);
bool DidejimasVidurkis(const mokinys&, const mokinys&);
bool MazejimasVidurkis(const mokinys&, const mokinys&);
bool DidejimasMediana(const mokinys&, const mokinys&);
bool MazejimasMediana(const mokinys&, const mokinys&);
vector<mokinys> Rikiavimas(vector<mokinys> &, int, int, double &);
vector<mokinys> EgzaminoRezultatoGavimas(vector<mokinys> &, int);


#endif