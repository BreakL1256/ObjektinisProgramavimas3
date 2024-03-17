# Vidurkių skaičiavimo programa

Programa:
+ Priima įvestį iš konsolės (mokinių ir ju pažymių)
+ Priima įvestį ir išvestį į tekstinį failą
+ Generuoja tik pažymius su mokinių įvestimi rankiniu būdu
+ Generuoja ir pažymius, ir mokinius.
+ Duotas pasirinkimas rikiuoti suvestus, nuskaitytus, sugeneruotus duomenis
+ Pridėta pasirinkimas, kur generuojamas failas, nuskaitomas, duomenis rikiuojami pagal pasirinkimą ir po to išskirstomi į 2 failus (pažengusiųjų ir nepažengusiųjų).


Kodas: 
+ Funkcijos suskirstytos į atskirus failus (sukurtas header failas)
+ Kodas papildytas išimčių valdymu (Exception Handling)
  
Programos veikimas:
1. gradeVector.cpp - naudojami vektoriai atlikti skaičiavimus ir kaupti duomenis.
2. duomenuGeneravimas.cpp, duomenuSkaiciavimai.cpp - funkcijų failai.
3. skaiciavimai.h - antraščių (header) failas.
4. Makefile - paleidimo failas

Tyrimo rezultatai (kelių testų laikų vidurkis):
| Failų dydžiai | Failo kūrimas -> uždarymas | Duomenų nuskaitymas iš failo | Studentų rūšiavimas į grupes | Surūšiuotų studentų išvedimas į failus | visos programos veikimo laikas |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `1000` | 0.006297 s | 0.0088905 s | 0 s | 0.0073615 s | 0.022549 s |
| `10000` | 0.0570585 s | 0.047387 s | 0.005557 s | 0.06208 s | 0.1720825 s |
| `100000` | 0.465383 s | 0.3838395 s | 0.0513685 s | 0.7351935 s | 1.6357845 s |
| `1000000` | 4.611165 s | 3.7772 s | 0.465853 s | 6.84329 s | 15.697508 s |

Sukompiliavimui, paleidziamojo failo sukūrimui ir programos paleidimui naudojamos komandos:
1. Naudojant Vektorius:
```
mingw32-make
gradeVector
```
> [!NOTE]
> *UI - konsolė, kur pateikiami pasirinkimai kaip norima elgtis su duomenimis*

