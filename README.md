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

## Perdengti metodai:
Galimas įvedimas ir rankiniu būdu, ir automatiniu, ir nuskaitant iš failo. Duomenys gali būti išvesti kartu ir į failą, ir į ekraną. Išvedimo("<<") ir įvedimo(">>") operatoriai, gali būti kartu naudojami įvedimui/išvedimui ir į ekraną, ir į failą.

## Funkcijų aprašymai:
#### Operatorius (=):
Skirtas kopijavimui, perkėlimui ir elementų priskyrimui. Kopijuojant elementus nauji elementai yra pridedami prie esamojo vektoriaus. Perkėliant vieno vektoriaus elementai priskiriami kitam. Galima priskirti norima skaičių pasirinktų elementų į vektorių.

#### begin():
Funkcija paremta iteratorių veikimu. Grąžina vektoriaus adresą, tai yra nuorodą į pirmą elementą.

#### resize():
Funkcija skirta pakeisti vektoriaus užimamą dydį. Jei norimas dydis yra didesnis už rezervuota, vyksta perkėlimas, tai yra užrezervuojama daugiau vietos. Jei norimas dydis yra didesnis tik už esamą vektoriaus dydį (nepoasiekiant capacity limito), vektorius yra inicializuojamas iki naujojo dydžio su default reikšmėmis, jei norimas dydis yra mažesnis esamos reikšmės yra panaikinamos (tampa nebestabilios, nebepriklauso vektoriui).

#### push_back():
Funkcija skirta pridėti elementams prie vektoriaus galo. Jei vektoriaus dydis yra lygus capacity dydžiui, rezervuojamas naujas atminties blokas vektoriui ir tada inicializuojama nauja vieta su norima reikšme, jei dydis mažesnis už capacity, veikia tik konstravimo dalis.

#### erase():
Funkcija skirta ištrinti arba specifines reikšmes, arba nustatyta dalį vektoriaus. Pirmiausia patikrinama ar specifikuojama pozicija yra vektoriuje. Jei tokia pozicija egzistuoja norima reikšmė yra ištrinama ir visos reikšmės einančios po ištrintos reikšmės yra pastumiamos ir sumažinamas vektoriaus dydis (Gražinamas iteratorius į ištrintą vietą).

## Efektyvumo/spartos analizė:
|Konteineriai| 10000 | 100000 | 1000000 | 10000000 | 100000000|
| --- | --- | --- | --- | --- |  --- |
| vector | 0.0000791 s | 0.0005638 s | 0.0019324 s | 0.0247602 s | 0.1886815 s |
| Vector | 0.00003825 s | 0.0003189 s | 0.0018669 s | 0.0222908 s | 0.2328435 s |

## Perskirstymai:
|Konteineriai| 100000000 |
| --- | --- |
| vector | 27 |
| Vector | 27 |

## Spartos analizė (studentų įrašai):
### vector:
 | Failų dydžiai | Programos veikimo laikas |
 | :--- | :---: | 
 | `100000` | 0.225129 s |
 | `1000000` | 2.22867 s | 
 | `10000000` | 25.14615 s |
 
### Vector:
 | Failų dydžiai | Programos veikimo laikas |
 | :--- | :---: | 
 | `100000` | 0.207378 s |
 | `1000000` | 2.28044 s | 
 | `10000000` | 25.0881 s |

 ## Programos veikimas su custom Vector klase:
 ![image](https://github.com/BreakL1256/ObjektinisProgramavimas3/assets/96627090/a688bcd1-8b02-447a-a9b5-6de82fb85aac)
 ![image](https://github.com/BreakL1256/ObjektinisProgramavimas3/assets/96627090/b8b694d4-5398-4d85-a7d7-f035804b5da3)

## Sukompiliavimui, paleidziamojo failo sukūrimui ir programos paleidimui naudojamos komandos (naudojamas Makefile):
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
