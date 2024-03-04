#include "skaiciavimai.h"
// #include <string>
// #include <vector>
// #include <iostream>
// #include <sstream>

using namespace std;

void FailuGeneravimas(fstream & fread, string failoPavadinimas, int pasirinkimas){
    //Atsitiktinio skaiciaus generavimas
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, 10);

    fread.open(failoPavadinimas, std::ios::out);
    fread << left << setw(30) << "Vardas";
    fread << left << setw(30) << "Pavarde";
    fread << left << setw(30) << "ND1" << left << setw(30) << "ND2" << left << setw(30) << "ND3" << left << setw(30) << "ND4" << left << setw(30) << "ND5";
    fread << left << setw(30) << "ND6" << left << setw(30) << "ND7" << left << setw(30) << "ND8" << left << setw(30) << "ND9" << left << setw(30) << "ND10";
    fread << left << setw(30) << "ND11" << left << setw(30) << "ND12" << left << setw(30) << "ND13" << left << setw(30) << "ND14" << left << setw(30) << "ND15";
    fread << left << setw(30) << "Egz.";
    fread << endl;
    for(int i=0; i<pasirinkimas; i++){
        fread << left << setw(30) << "Vardas" + to_string(i + 1);
        fread << left << setw(30) << "Pavarde" + to_string(i + 1);
        for(int j = 0; j < 16; j++){
            fread << left << setw(30) << dist(mt);
        }
        fread << endl; 
    }



    fread.close();
}
bool SudaroTikRaides(string& str) {
    for (int i=0; i<str.length(); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

//Funkcija, kuri leidzia perskaityti varda ir pavarde ir kartu patikrina ar vardas ir pavarde yra zodziai sudaryti is raidziu
void VarduSkaitymas(istringstream & iss, vector<mokinys> & M, int indeksas, bool & err){
    iss >> M[indeksas].vardas >> M[indeksas].pavarde;
    if(!SudaroTikRaides(M[indeksas].vardas) || !SudaroTikRaides(M[indeksas].pavarde)){
        cout<<"Varda ir pavarde gali sudaryti tik raides!\n";
        err=1;   
    } else {
        err=0;
    }
}
//Funkcija skirta generuoti atsitiktinius pazymius
void GeneruotiPazymius(vector<mokinys> & M, int indeksas){
    for(int i=0; i<M[indeksas].tarpiniaiRezultatai.size(); i++){
       M[indeksas].tarpiniaiRezultatai[i] = (double)rand()/RAND_MAX * 10;
    }
}
//Funkcija skirta atsitikitiniu vardu ir pavardziu generavimui sudarytu is atsitiktiniu raidziu
void VarduPavardziuGeneravimas(vector<mokinys> & M, int indeksas){
    char v;
    int vardoIlgis = 0, pavardesIlgis = 0; 
    vardoIlgis = 6 + (double)rand()/RAND_MAX * (12-6);
    pavardesIlgis = 6 + (double)rand()/RAND_MAX * (12-6);
    for(int i=0; i<vardoIlgis; i++){
        if(i==0)
            v = 65 + (double)rand()/RAND_MAX * (90-65);
        else
            v = 97 + (double)rand()/RAND_MAX * (122-97);
        M[indeksas].vardas.push_back(v);
    }
    for(int i=0; i<pavardesIlgis; i++){
        if(i==0)
            v = 65 + (double)rand()/RAND_MAX * (90-65);
        else
            v = 97 + (double)rand()/RAND_MAX * (122-97);
        M[indeksas].pavarde.push_back(v);
    }
}