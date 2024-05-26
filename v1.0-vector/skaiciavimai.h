# ifndef SKAICIAVIMAI_H
# define SKAICIAVIMAI_H

#include <iostream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <Vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <ios>
#include <exception>
#include <string>
#include <chrono>
#include <random>
#include <windows.h>
#include "Vector.h"

class zmogus {
protected:
    std::string vardas;
    std::string pavarde;
    int amzius;
    int klase;

public:
    zmogus();
    zmogus(const std::string& v, const std::string& p) : vardas{v}, pavarde{p} {};
    zmogus(const std::string& v, const std::string& p, int a, int k)
        : vardas(v), pavarde(p), amzius(a), klase(k) {}
    virtual void pazymiai() = 0;
    virtual ~zmogus();
};

class mokinys : public zmogus {
private:
    std::Vector<int> tarpiniaiRezultatai;
    int egzaminoRezultatas;
    double vidurkis;
    double mediana;

public:
    mokinys();
    mokinys(std::string vardas_, std::string pavarde_, std::initializer_list<int> tarpiniai)
        : zmogus{vardas_, pavarde_}, tarpiniaiRezultatai{tarpiniai} {};
    mokinys(const mokinys& m);
    mokinys(mokinys&& m);
    mokinys& operator=(const mokinys& m);
    mokinys& operator=(mokinys&& m);
    friend std::istream& operator>>(std::istream& in, mokinys& m);
    friend std::ostream& operator<<(std::ostream& out, const mokinys& m);
    friend mokinys operator+(const mokinys& a, const mokinys& b);
    void pazymiai();
    inline std::string vard() const { return vardas; }
    inline std::string pavard() const { return pavarde; }
    inline std::Vector<int>& tarpRezultatai() { return tarpiniaiRezultatai; }
    inline std::Vector<int> tarpRezultatai() const { return tarpiniaiRezultatai; }
    inline int egzaminoRezult() const { return egzaminoRezultatas; }
    inline double vid() const { return vidurkis; }
    inline double med() const { return vidurkis; }
    void setVardas(const std::string& vard) { vardas = vard; }
    void setPavarde(const std::string& pavard) { pavarde = pavard; }
    void setRez(const int& rez) { tarpiniaiRezultatai.push_back(rez); }
    void setegz(const int& egz) { egzaminoRezultatas = egz; }
    void setVidurkis(const double& vid) { vidurkis = vid; }
    void setMediana(const double& med) { mediana = med; }
    void EgzaminoRezultatoGavimas(mokinys&, int);
    void VidurkioSkaiciavimas(mokinys&, int, double&);
    void MedianosSkaiciavimas(mokinys&, double&);
    void VarduSkaitymas(std::istringstream&, mokinys&, int, bool&);
    void GeneruotiPazymius(mokinys&, int);
    void VarduPavardziuGeneravimas(mokinys&, int);
    ~mokinys();
};

void MokiniuSkirstymas(std::Vector<mokinys>&, std::Vector<mokinys>&, int, int);
std::Vector<mokinys> Rikiavimas(std::Vector<mokinys>&, int, const int& sk = 0);
void MokiniuIsvedimas(std::Vector<mokinys>&, std::Vector<mokinys>&, int);
void FailuGeneravimas(std::string, int);
bool SudaroTikRaides(std::string&);
bool PalygintiVardus(const std::string&, const std::string&);
bool DidejimasVardai(const mokinys&, const mokinys&);
bool MazejimasVardai(const mokinys&, const mokinys&);
bool DidejimasPavardes(const mokinys&, const mokinys&);
bool MazejimasPavardes(const mokinys&, const mokinys&);
bool DidejimasVidurkis(const mokinys&, const mokinys&);
bool MazejimasVidurkis(const mokinys&, const mokinys&);
bool DidejimasMediana(const mokinys&, const mokinys&);
bool MazejimasMediana(const mokinys&, const mokinys&);
void testavimas();
void EfektyvumoFunkcija();
void PerskirstymoSkaiciavimas();


#endif