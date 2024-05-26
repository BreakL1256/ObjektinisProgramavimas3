# Vidurkių skaičiavimo programa

## Programa:
- Priima įvestį iš konsolės (mokinių ir jų pažymių)
- Priima įvestį ir išvestį į tekstinį failą
- Generuoja tik pažymius su mokinių įvestimi rankiniu būdu
- Generuoja ir pažymius, ir mokinius.
- Duotas pasirinkimas rikiuoti suvestus, nuskaitytus, sugeneruotus duomenis
- Pridėta pasirinkimas, kur generuojamas failas, nuskaitomas, duomenys rikiuojami pagal pasirinkimą ir po to išskirstomi į 2 failus (pažengusiųjų ir nepažengusiųjų).

## Releas'ai:
v0.1 - programa realizuota naudojant struktūras, pasitelkiant C masyvus ir vektorius. Galima pasirinkti kurią programos versiją norite naudoti (vektoriai, c masyvai). <br /> 
v0.2 - Remiamasi v0.1 versija, tačiau pridėta galimybė pasirinkti kokiu būdų galima įvesti duomenis (per konsolę, iš failo). Pridėtas duomenų rušiavimas. <br /> 
v0.3 - Remiamasi v0.2 versija, kur nepridėta jokių papildomų funkcionalumų iš vartotojo pusės. sutvarkytas source kodas ir pridėtas error handling. <br /> 
v0.4 - Remiamasi v0.3 versija. Pridėtas failų generatorius ir pridėta galimybė vartotojui skirstyti duomenis į pažengusiųjų ir nepažengusiųjų grupes. Atlikti programos testavimai, kurie yra pateikti README.txt faile. <br /> 
v1.0 - Remiamasi v0.4 versija. Programa realizuota su trimis skirtingais konteineriais, pridėtas Makefile(vector, list, deque). Su visais konteineriais taip pat atliktos trys skirtingos duomenų apdorojimo strategijos (papildomų konteinerių kūrimas, konteinerio perrašymas, greičiausia iš išvardintų strategijų papildomai pasitelkiant specialus algoritmus darbui su konteneriais). Tyrimas dokumentuotas README.txt faile. <br /> 
v1.1 - Remiamasi v1.0 versija. Sukurta nauja repozicija, struktūros pakeistos klasėmis. Struktūrų ir klasių efektyvumo testavimas dokumentuotas README.txt faile. <br /> 
v1.2 - Remiamasi v1.1 versija. Realizuoti "Rule of five", išvesties ir įvesties operatoriai. Parašyta funkcija įgyvendintų operatorių testavimui (pridėta pasirinkimas vartotojui). <br /> 
v1.5 - Remiamasi v1.2 versija. Mokinio klasė išskirstyta į dvi klases: zmogaus (bazinė, abstrakčioji), mokinio (išvestinė). <br /> 
v2.0 - Remiamasi v1.5 versija. Kodas dokumentuotas naudojantis Doxygen (įkelti atskiri doxygen HTML ir TeX katalogai). Atlikti Unit testai naudojantis catch2 biblioteka (perrašyti v1.2 versijoje ištestuotų operatorių testai). Patobulintas Makefile, kad galėtų būti naudojamas ir Unix OS turinčiuose kompiuteriuose. 

## Kodas: 
- Funkcijos suskirstytos į atskirus failus (sukurtas header failas)
- Kodas papildytas išimčių valdymu (Exception Handling)

## Programos veikimas:
### Su vektoriais:
1. `gradeVector.cpp` - naudojami vektoriai atlikti skaičiavimus ir kaupti duomenis.
2. `duomenuGeneravimas.cpp`, `duomenuSkaiciavimai.cpp` - funkcijų failai.
3. `skaiciavimai.h` - antraščių (header) failas.
4. `Makefile` - paleidimo failas

## Sistemos parametrai:
CPU - AMD Ryzen 5 6600HS Creator Edition <br /> 
RAM - 16 GB <br /> 
SSD - 500 GB <br /> 

## Unit tests:
![Testavimas](https://github.com/BreakL1256/ObjektinisProgramavimas2/assets/96627090/daa20803-b002-4b40-b5dd-c4746aa81874)

## Perdengti metodai:
Galimas įvedimas ir rankiniu būdu, ir automatiniu, ir nuskaitant iš failo. Duomenys gali būti išvesti kartu ir į failą, ir į ekraną. Išvedimo("<<") ir įvedimo(">>") operatoriai, gali būti kartu naudojami įvedimui/išvedimui ir į ekraną, ir į failą.

## Tyrimas (klasės ir struktūros): 
### Aprašymas
Tyrimai padaryti pirmiausia su struktūromis (po 2 bandymus) ir po to su klasėmis (po 2 bandymus).

### Rezultatai
 #### Struktūros:
 
   | Failų dydžiai | Programos veik. (-O3) | Programos veik. (-O2) | Programos veik. (-O1) |
   | :--- | :---: | :---: | :---: | 
   | `1000000` | 3.554805  s | 3.65927 s | 3.554275 s | 
   | `10000000` | 26.60045  s | 31.46395 s | 28.5036 s |

 #### Klasės:

   | Failų dydžiai | Programos veik. (-O3) | Programos veik. (-O2) | Programos veik. (-O1) |
   | :--- | :---: | :---: | :---: | 
   | `1000000` | 2.49207  s | 2.53267 s | 2.582605 s | 
   | `10000000` | 29.26335  s | 29.01405 s | 34.13615 s |

## Tyrimas
### Aprašymas
Ištestuotos 3 skirtingos strategijos (1 - skirstant mokinius naudojami du nauji skirtingi konteineriai, 2 - skirstant mokinius naudojamas 1 naujas konteineris, 3 - naudojama antra strategija tik su funkcijomis paspartinančiomis darbą). Kiekviena strategija ištestuota su 3 skirtingais konteineriais (vector, list, deque).

### Rezultatai
#### 1 strategija (vector/list/deque):
 #### Vektoriai:
   
   | Failų dydžiai | Duomenų nuskaitymas iš failo | Studentų rikiavimas | Studentų rūšiavimas į grupes |
   | :--- | :---: | :---: | :---: | 
   | `1000` | 0.019548 s | 3.096015 s | 0.002248 s | 
   | `10000` | 0.100993 s | 2.757575 s | 0.0132415 s |
   | `100000` | 0.961472 s | 1.922885 s | 0.093909 s | 
   | `1000000` | 6.965875  s | 7.295025 s | 0.5697185 s | 
   | `10000000` | 15.8109  s | 23.04525 s | 1.57281 s |
   
 #### List'ai:
 
   | Failų dydžiai | Duomenų nuskaitymas iš failo | Studentų rikiavimas | Studentų rūšiavimas į grupes |
   | :--- | :---: | :---: | :---: | 
   | `1000` | 0.0078645 s | 0.8457075 s | 0.0011985 s | 
   | `10000` | 0.093457 s | 0.726366 s | 0.0112395 s |
   | `100000` | 1.03687 s | 1.6117 s | 0.1036905 s | 
   | `1000000` |  7.337395 s | 5.388295 s | 0.602523 s |
   | `10000000` | 21.81155  s | 59.72665 s | 6.89016 s |
   
 #### Dekai:
 
   | Failų dydžiai | Duomenų nuskaitymas iš failo | Studentų rikiavimas | Studentų rūšiavimas į grupes |
   | :--- | :---: | :---: | :---: | 
   | `1000` | 0.005698 s | 0.5659815 s | 0.000848 s | 
   | `10000` | 0.0596895 s | 0.9029195 s | 0.0040235 s |
   | `100000` | 0.5597055 s | 1.29229 s | 0.039016 s | 
   | `1000000` | 5.814525 s | 6.90788 s | 0.3924585 s |
   | `10000000` | 16.4762  s | 197.358 s | 8.98066 s |
   
#### 2 strategija (vector/list/deque):
 #### Vektoriai:
 
| Failų dydžiai | Duomenų nuskaitymas iš failo | Studentų rikiavimas | Studentų rūšiavimas į grupes |
| :--- | :---: | :---: | :---: | 
| `1000` | 0.002234 s | 1.220428 s | 0.0112495 s | 
| `10000` | 0.0567355 s | 0.829485 s | 1.264535 s |
| `100000` | 0.558775 s | 1.072447s | 0.01728365 s | 
| `1000000` | 1.47241 s | 1.72988 s | 0.2344925 s |
| `10000000` | 18.3888  s | 20.50225 s | 2.567225 s |

#### List'ai:

| Failų dydžiai | Duomenų nuskaitymas iš failo | Studentų rikiavimas | Studentų rūšiavimas į grupes |
| :--- | :---: | :---: | :---: | 
| `1000` | 0.00794 s | 0.7569035 s | 0 s | 
| `10000` | 0.0637105 s | 0.8100015 s | 0.0015275 s |
| `100000` | 0.609602 s | 0.9425365 s | 0.0669145 s | 
| `1000000` | 6.027405 s | 3.97259 s | 0.692482 s | 
| `10000000` | 19.529  s | 53.54415 s | 9.834555 s |

#### Dekai:

| Failų dydžiai | Duomenų nuskaitymas iš failo | Studentų rikiavimas | Studentų rūšiavimas į grupes |
| :--- | :---: | :---: | :---: | 
| `1000` | 0.006979 s | 0.811568 s | 0 s | 
| `10000` | 0.055645 s | 0.7543825 s | 0.0039765 s |
| `100000` | 0.5582785 s | 1.137155 s | 0.038725 s | 
| `1000000` | 5.70688 s | 6.963815 s | 0.4322945 s | 
| `10000000` | 17.06235  s | 149.7765 s | 11.21226 s |

#### 3 strategija (vector/list/deque):
#### Vektoriai:

| Failų dydžiai | Studentų rūšiavimas į grupes |
| :--- | :---: | 
| `1000` | 0.00018085 s |  
| `10000` | 0.00180935 s | 
| `100000` | 0.0225674 s | 
| `1000000` | 0.25924  s |  
| `10000000` | 3.178805  s | 

#### List'ai:

| Failų dydžiai | Studentų rūšiavimas į grupes |
| :--- | :---: | 
| `1000` | 0.00099145 s |  
| `10000` |  0.01207075  s | 
| `100000` | 0.1684105 s | 
| `1000000` | 1.936505 s |  
| `10000000` | 24.70635  s | 

#### Dekai:

| Failų dydžiai | Studentų rūšiavimas į grupes |
| :--- | :---: | 
| `1000` | 0.00048125 s |  
| `10000` | 0.0036659 s | 
| `100000` | 0.0432157 s | 
| `1000000` | 0.529235 s |  
| `10000000` | 32.4737  s | 


Sukompiliavimui, paleidziamojo failo sukūrimui ir programos paleidimui naudojamos komandos (naudojamas Makefile):
1. Naudojant Vektorius:
```
cd v1.0-vector
mingw32-make
gradeVector
```
Testavimo programos sukompiliavimas:
```
g++ *.cpp -o test
test
```
> [!NOTE]
> *UI - konsolė, kur pateikiami pasirinkimai kaip norima elgtis su duomenimis*
