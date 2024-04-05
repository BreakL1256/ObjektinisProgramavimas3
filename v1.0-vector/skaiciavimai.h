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
        mokinys(){}
        inline string vard() const { return vardas; }   
        inline string pavard() const { return pavarde; }  
        inline vector<int> tarpRezultatai() {return tarpiniaiRezultatai; }
        inline int egzaminoRezult() const { return egzaminoRezultatas; }
        inline double vid() const { return vidurkis; }
        inline double med() const { return vidurkis; }
        void setVardas(const string& vard){vardas = vard;}
        void setPavarde(const string& pavard){pavarde = pavard;}
        void setRez(const int& rez){tarpiniaiRezultatai.push_back(rez);}
        void setegz(const int& egz){egzaminoRezultatas = egz;}
        void setVidurkis(const double& vid){vidurkis = vid;}
        void setMediana(const double& med){mediana = med;}
        void EgzaminoRezultatoGavimas(mokinys &, int);
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
vector<mokinys> Rikiavimas(vector<mokinys> &, int, const int& sk = 0);
void FailuGeneravimas(string, int);
void MokiniuSkirstymas(vector<mokinys> &, vector<mokinys> &, int, int);
void MokiniuIsvedimas(vector<mokinys> &, vector<mokinys> &, int);

#endif