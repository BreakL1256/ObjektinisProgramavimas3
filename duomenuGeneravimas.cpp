#include "skaiciavimai.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;


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
    if(!SudaroTikRaides(M[indeksas].vardas) || !SudaroTikRaides(M[indeksas].vardas)){
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
       //double rnd = (double)rand()/RAND_MAX * 10;
       cout<<M[indeksas].tarpiniaiRezultatai[i]<<" ";
    }
    cout<<endl;
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