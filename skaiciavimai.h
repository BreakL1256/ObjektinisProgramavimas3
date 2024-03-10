# ifndef SKAICIAVIMAI_H
# define SKAICIAVIMAI_H

#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <ios>
#include <exception>
#include <string>
#include <chrono>
#include <random>


using namespace std;

struct mokinys{
    string vardas;
    string pavarde;
    vector<int> tarpiniaiRezultatai;
    int egzaminoRezultatas;
    double mediana;
    double vidurkis;
};

struct pazangieji{
    string vardas;
    string pavarde;
    double galutinis;
};

struct nepazangieji{
    string vardas;
    string pavarde;
    double galutinis;
};


bool SudaroTikRaides(string &);
void VarduSkaitymas(istringstream&, vector<mokinys>& ,int , bool&);
void GeneruotiPazymius(vector<mokinys>&, int);
void VarduPavardziuGeneravimas(vector<mokinys>&, int);
void VidurkioSkaiciavimas(vector<mokinys>&, int , double & , int);
void MedianosSkaiciavimas(vector<mokinys> & , double & , int);
bool PalygintiVardus(const string&, const string&);
bool DidejimasVardai(const mokinys&, const mokinys&);
bool MazejimasVardai(const mokinys&, const mokinys&);
bool DidejimasPavardes(const mokinys&, const mokinys&);
bool MazejimasPavardes(const mokinys&, const mokinys&);
bool DidejimasVidurkis(const mokinys&, const mokinys&);
bool MazejimasVidurkis(const mokinys&, const mokinys&);
bool DidejimasMediana(const mokinys&, const mokinys&);
bool MazejimasMediana(const mokinys&, const mokinys&);
vector<mokinys> EgzaminoRezultatoGavimas(vector<mokinys> &, int);
vector<mokinys> Rikiavimas(vector<mokinys> &, int);
void FailuGeneravimas(string, int);
void MokiniuSkirstymas(vector<mokinys> &, vector<pazangieji> &, vector<nepazangieji> &, int);
void MokiniuIsvedimas(vector<pazangieji> &, vector<nepazangieji> &, int);

#endif