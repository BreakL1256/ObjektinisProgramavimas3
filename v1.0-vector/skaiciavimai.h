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
#include <windows.h>


using namespace std;

class mokinys{
    private:
        string vardas;
        string pavarde;
        vector<int> tarpiniaiRezultatai;
        int egzaminoRezultatas;
        double vidurkis;
        double mediana;
    public: 
        mokinys(){vidurkis = 0}
        inline string vardas() const { return vardas; }   
        inline string pavarde() const { return pavarde; }  
        inline vector<int> tarpinaiRezultatai() const {return tarpiniaiRezultatai; }
        inline int egzaminoRezultatas() const { return egzaminoRezultatas; }
        inline double vidurkis() const { return vidurkis; }
        inline double mediana() const { return vidurkis; }
        ~mokinys(){tarpiniaiRezultatai.clear();}
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
vector<mokinys> Rikiavimas(vector<mokinys> &, int, const int& sk = 0);
void FailuGeneravimas(string, int);
void MokiniuSkirstymas(vector<mokinys> &, vector<mokinys> &, int, int);
void MokiniuIsvedimas(vector<mokinys> &, vector<mokinys> &, int);

#endif