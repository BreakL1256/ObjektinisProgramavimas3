# Vidurkių skaičiavimo programa

Programa:
+ Priima įvestį iš konsolės (mokinių ir ju pažymių)
+ Priima įvestį ir išvestį į tekstinį failą
+ Generuoja tik pažymius su mokinių įvestimi rankiniu būdu
+ Generuoja ir pažymius, ir mokinius.
+ Duotas pasirinkimas rikiuoti suvestus, nuskaitytus, sugeneruotus duomenis 
  
Programos veikimas:
1. gradeVector.cpp - naudojami vektoriai atlikti skaičiavimus ir kaupti duomenis.

Sukompiliavimui, paleidziamojo failo sukūrimui ir programos paleidimui naudojamos komandos:
1. Naudojant Vektorius:
```
g++ gradeVector.c++ -o gradeVector
.\gradeVector 
```
Testavimo rezultatai (programos veikimo laiko matavimas sekundėmis) su skirtingu duomenų imties dydžiu (skaičius prie tekstinio failo rodo kiek yra skirtingu mokinių sąraše, dešinėje išvestas skaičius yra 3 skirtingų bandymų laikų vidurkis):
```
studentai10000.txt: 0.1787 s
studentai100000.txt: 2.16 s
studentai1000000.txt: 15.488 s
```
*UI - konsolė, kur pateikiami pasirinkimai kaip norima elgtis su duomenimis*
