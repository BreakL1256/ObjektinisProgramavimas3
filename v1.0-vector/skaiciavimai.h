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

class zmogus{
    protected:
        string vardas;
        string pavarde;
        int amzius;
        int klase;
    public:

}
class mokinys{
    private:
        vector<int> tarpiniaiRezultatai;
        int egzaminoRezultatas;
        double vidurkis;
        double mediana;
    public: 
        mokinys();
        mokinys(const mokinys& m);
        mokinys(mokinys&& m); 
        mokinys& operator=(const mokinys& m);
        mokinys& operator=(mokinys&& m);
        friend istream& operator>>(istream& in, mokinys& m);
        friend ostream& operator<<(ostream& out, const mokinys& m);
        inline string vard() const { return vardas; }   
        inline string pavard() const { return pavarde; }  
        inline vector<int>& tarpRezultatai() {return tarpiniaiRezultatai; }
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
        void VidurkioSkaiciavimas(mokinys&, int , double &);
        void MedianosSkaiciavimas(mokinys& , double &);
        void VarduSkaitymas(istringstream&, mokinys& ,int , bool&);
        void GeneruotiPazymius(mokinys&, int);
        void VarduPavardziuGeneravimas(mokinys&, int);
        ~mokinys();
};

void MokiniuSkirstymas(vector<mokinys> &, vector<mokinys> &, int, int);
vector<mokinys> Rikiavimas(vector<mokinys> &, int, const int& sk = 0);
void MokiniuIsvedimas(vector<mokinys> &, vector<mokinys> &, int);
void FailuGeneravimas(string, int);
bool SudaroTikRaides(string &);
bool PalygintiVardus(const string&, const string&);
bool DidejimasVardai(const mokinys&, const mokinys&);
bool MazejimasVardai(const mokinys&, const mokinys&);
bool DidejimasPavardes(const mokinys&, const mokinys&);
bool MazejimasPavardes(const mokinys&, const mokinys&);
bool DidejimasVidurkis(const mokinys&, const mokinys&);
bool MazejimasVidurkis(const mokinys&, const mokinys&);
bool DidejimasMediana(const mokinys&, const mokinys&);
bool MazejimasMediana(const mokinys&, const mokinys&);

#endif