# ifndef SKAICIAVIMAI_H
# define SKAICIAVIMAI_H

#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <deque>
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
    deque<int> tarpiniaiRezultatai;
    int egzaminoRezultatas;
    double vidurkis;
    double mediana;
};


bool SudaroTikRaides(string &);
void VarduSkaitymas(istringstream&, deque<mokinys>& ,int , bool&);
void GeneruotiPazymius(deque<mokinys>&, int);
void VarduPavardziuGeneravimas(deque<mokinys>&, int);
void VidurkioSkaiciavimas(deque<mokinys>&, int , double & , int);
void MedianosSkaiciavimas(deque<mokinys> & , double & , int);
bool PalygintiVardus(const string&, const string&);
bool DidejimasVardai(const mokinys&, const mokinys&);
bool MazejimasVardai(const mokinys&, const mokinys&);
bool DidejimasPavardes(const mokinys&, const mokinys&);
bool MazejimasPavardes(const mokinys&, const mokinys&);
bool DidejimasVidurkis(const mokinys&, const mokinys&);
bool MazejimasVidurkis(const mokinys&, const mokinys&);
bool DidejimasMediana(const mokinys&, const mokinys&);
bool MazejimasMediana(const mokinys&, const mokinys&);
deque<mokinys> EgzaminoRezultatoGavimas(deque<mokinys> &, int);
deque<mokinys> Rikiavimas(deque<mokinys> &, int, const int& sk = 0);
void FailuGeneravimas(string, int);
void MokiniuSkirstymas(deque<mokinys> &, deque<mokinys> &, int, int);
void MokiniuIsvedimas(deque<mokinys> &, deque<mokinys> &, int);

#endif