# ifndef SKAICIAVIMAI_H
# define SKAICIAVIMAI_H

#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <list>
#include <sstream>
#include <fstream>
#include <ctime>
#include <ios>
#include <exception>
#include <string>
#include <chrono>
#include <random>
#include <windows.h>


using namespace std;

struct mokinys{
    string vardas;
    string pavarde;
    list<int> tarpiniaiRezultatai;
    int egzaminoRezultatas;
    double vidurkis;
    double mediana;
};

struct nepazangieji{
    string vardas;
    string pavarde;
    double galutinis;
};


bool SudaroTikRaides(string &);
void VarduSkaitymas(istringstream&, mokinys & ,int , bool&);
void GeneruotiPazymius(mokinys &, int);
void VarduPavardziuGeneravimas(mokinys &, int);
void VidurkioSkaiciavimas(mokinys&, int , double &);
void MedianosSkaiciavimas(mokinys & , double &);
bool PalygintiVardus(const string&, const string&);
bool DidejimasVardai(const mokinys&, const mokinys&);
bool MazejimasVardai(const mokinys&, const mokinys&);
bool DidejimasPavardes(const mokinys&, const mokinys&);
bool MazejimasPavardes(const mokinys&, const mokinys&);
bool DidejimasVidurkis(const mokinys&, const mokinys&);
bool MazejimasVidurkis(const mokinys&, const mokinys&);
bool DidejimasMediana(const mokinys&, const mokinys&);
bool MazejimasMediana(const mokinys&, const mokinys&);
mokinys EgzaminoRezultatoGavimas(mokinys &);
list<mokinys> Rikiavimas(list<mokinys> &, int);
void FailuGeneravimas(string, int);
void MokiniuSkirstymas(list<mokinys> &, list<nepazangieji> &, int);
void MokiniuIsvedimas(list<mokinys> &, list<nepazangieji> &, int);

#endif