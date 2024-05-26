#include "skaiciavimai.h"
//#include "Vector.h"

// #include <string>
// #include <Vector>
// #include <iostream>
// #include <sstream>

//using namespace std;
//using namespace my_std;

void MokiniuIsvedimas(std::Vector<mokinys>& M, std::Vector<mokinys>& N, int vidurkioTipas) {
    std::ofstream fout;
    try {
        fout.open("../Pazangieji.txt", std::ios::out);
        if (!fout.is_open()) throw std::ios_base::failure("FAILAS NERA ATIDARYTAS!");
        fout << std::left << std::setw(17) << "Vardas";
        fout << std::left << std::setw(17) << "Pavarde";
        if (vidurkioTipas == 1) {
            fout << "Galutinis (Vid.)" << "\n";
            for (const auto& p : M) {
                fout << std::left << std::setw(17) << p.vard();
                fout << std::left << std::setw(17) << p.pavard();
                fout << std::fixed << std::setprecision(2) << p.vid() << "\n";
            }
        } else if (vidurkioTipas == 2) {
            fout << "Galutinis (Med.)" << "\n";
            for (const auto& p : M) {
                fout << std::left << std::setw(17) << p.vard();
                fout << std::left << std::setw(17) << p.pavard();
                fout << std::fixed << std::setprecision(2) << p.med() << "\n";
            }
        }
        fout.close();
    } catch (const std::ios_base::failure& e) {
        std::cerr << "KLAIDA: " << e.what() << "\n";
        std::cerr << "FAILAS NEBUVO RASTAS PRISKIRTOJE LOKACIJOJE!" << "\n";
        return;
    }

    try {
        fout.open("../Nepazangieji.txt", std::ios::out);
        if (!fout.is_open()) throw std::ios_base::failure("FAILAS NERA ATIDARYTAS!");
        fout << std::left << std::setw(17) << "Vardas";
        fout << std::left << std::setw(17) << "Pavarde";
        if (vidurkioTipas == 1) {
            fout << "Galutinis (Vid.)" << "\n";
            for (const auto& n : N) {
                fout << std::left << std::setw(17) << n.vard();
                fout << std::left << std::setw(17) << n.pavard();
                fout << std::fixed << std::setprecision(2) << n.vid() << "\n";
            }
        } else if (vidurkioTipas == 2) {
            fout << "Galutinis (Med.)" << "\n";
            for (const auto& n : N) {
                fout << std::left << std::setw(17) << n.vard();
                fout << std::left << std::setw(17) << n.pavard();
                fout << std::fixed << std::setprecision(2) << n.med() << "\n";
            }
        }
        fout.close();
    } catch (const std::ios_base::failure& e) {
        std::cerr << "KLAIDA: " << e.what() << "\n";
        std::cerr << "FAILAS NEBUVO RASTAS PRISKIRTOJE LOKACIJOJE!" << "\n";
        return;
    }
}

void FailuGeneravimas(std::string failoPavadinimas, int pasirinkimas) {
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, 10);

    auto start = std::chrono::high_resolution_clock::now();
    std::ofstream fw(failoPavadinimas);
    std::stringstream buferis;
    const int BUFFER_SIZE = 1000;

    buferis << std::left << std::setw(17) << "Vardas";
    buferis << std::left << std::setw(17) << "Pavarde";
    buferis << std::left << std::setw(5) << "ND1" << std::left << std::setw(5) << "ND2" << std::left << std::setw(5) << "ND3" << std::left << std::setw(5) << "ND4" << std::left << std::setw(5) << "ND5";
    buferis << std::left << std::setw(5) << "ND6" << std::left << std::setw(5) << "ND7" << std::left << std::setw(5) << "ND8" << std::left << std::setw(5) << "ND9";
    buferis << "Egz.";
    buferis << "\n";
    for (int i = 0; i < pasirinkimas; i++) {
        if (buferis.str().size() > BUFFER_SIZE) {
            fw << buferis.rdbuf();
            buferis.str("");
            buferis.clear();
        }
        buferis << std::left << std::setw(17) << "Vardas" + std::to_string(i + 1);
        buferis << std::left << std::setw(17) << "Pavarde" + std::to_string(i + 1);
        for (int j = 0; j < 10; j++) {
            buferis << std::left << std::setw(5) << dist(mt);
        }
        buferis << "\n";
    }
    fw << buferis.rdbuf();
    fw.close();
    auto end = std::chrono::high_resolution_clock::now(); // Stabdyti
    std::chrono::duration<double> diff = end - start; // Skirtumas (s)
    std::cout << "Elementų užpildymas užtruko: " << diff.count() << " s\n";
}

bool SudaroTikRaides(std::string& str) {
    for (int i = 0; i < str.length(); i++) {
        if (!std::isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

// Funkcija, kuri leidzia perskaityti varda ir pavarde ir kartu patikrina ar vardas ir pavarde yra zodziai sudaryti is raidziu
void mokinys::VarduSkaitymas(std::istringstream& iss, mokinys& M, int indeksas, bool& err) {
    iss >> M.vardas >> M.pavarde;
    if (!SudaroTikRaides(M.vardas) || !SudaroTikRaides(M.pavarde)) {
        std::cout << "Varda ir pavarde gali sudaryti tik raides!\n";
        err = 1;
    } else {
        err = 0;
    }
}

// Funkcija skirta generuoti atsitiktinius pazymius
void mokinys::GeneruotiPazymius(mokinys& M, int indeksas) {
    for (int i = 0; i < M.tarpiniaiRezultatai.size(); i++) {
        M.tarpiniaiRezultatai[i] = (double)rand() / RAND_MAX * 10;
    }
}

// Funkcija skirta atsitikitiniu vardu ir pavardziu generavimui sudarytu is atsitiktiniu raidziu
void mokinys::VarduPavardziuGeneravimas(mokinys& M, int indeksas) {
    char v;
    int vardoIlgis = 0, pavardesIlgis = 0;
    vardoIlgis = 6 + (double)rand() / RAND_MAX * (12 - 6);
    pavardesIlgis = 6 + (double)rand() / RAND_MAX * (12 - 6);
    for (int i = 0; i < vardoIlgis; i++) {
        if (i == 0)
            v = 65 + (double)rand() / RAND_MAX * (90 - 65);
        else
            v = 97 + (double)rand() / RAND_MAX * (122 - 97);
        M.vardas.push_back(v);
    }
    for (int i = 0; i < pavardesIlgis; i++) {
        if (i == 0)
            v = 65 + (double)rand() / RAND_MAX * (90 - 65);
        else
            v = 97 + (double)rand() / RAND_MAX * (122 - 97);
        M.pavarde.push_back(v);
    }
}

void testavimas() {
    try {
        mokinys a{"Tom", "Tom", {3, 5, 6}}, b{"Tom", "Tom", {3, 5, 6}};

        // Copy constructor
        mokinys c{a};
        std::Vector<int> aVec = a.tarpRezultatai();
        std::Vector<int> cVec = c.tarpRezultatai();

        if (a.vard() != c.vard() || a.pavard() != c.pavard() || aVec.size() != cVec.size()) throw std::runtime_error("Copy constructor neveikia tvarkingai!");

        for (int i = 0; i < aVec.size(); ++i) {
            if (aVec[i] != cVec[i]) {
                throw std::runtime_error("Copy constructor neveikia tvarkingai!");
                break;
            }
        }

        // Move constructor
        mokinys d{std::move(b)};

        if (b.vard() != "" || b.pavard() != "" || !b.tarpRezultatai().empty()) throw std::runtime_error("Move constructor neveikia tvarkingai_1!");

        std::Vector<int> dVec = d.tarpRezultatai();

        if (d.vard() != a.vard() || d.pavard() != a.pavard() || aVec.size() != dVec.size()) throw std::runtime_error("Move constructor neveikia tvarkingai_2!");

        for (int i = 0; i < dVec.size(); ++i) {
            if (dVec[i] != aVec[i]) {
                throw std::runtime_error("Move constructor neveikia tvarkingai_3!");
                break;
            }
        }

        // copy assignment operator
        b = a;

        std::Vector<int> bVec = b.tarpRezultatai();

        if (a.vard() != b.vard() || a.pavard() != b.pavard() || aVec.size() != bVec.size()) throw std::runtime_error("Copy assignment operator neveikia tvarkingai!");

        for (int i = 0; i < bVec.size(); ++i) {
            if (bVec[i] != aVec[i]) {
                throw std::runtime_error("Copy assignment operator neveikia tvarkingai!");
                break;
            }
        }

        // Move assignment operator
        b = mokinys{"Dom", "Dom", {1, 4, 5}};

        b = std::move(a);

        if (a.vard() != "" || a.pavard() != "" || !a.tarpRezultatai().empty()) throw std::runtime_error("Move assignment operator neveikia tvarkingai!");

        if (d.vard() != b.vard() || d.pavard() != b.pavard() || bVec.size() != dVec.size()) throw std::runtime_error("Move assignment operator neveikia tvarkingai!");

        for (int i = 0; i < dVec.size(); ++i) {
            if (dVec[i] != bVec[i]) {
                throw std::runtime_error("Move assignment operator neveikia tvarkingai!");
                break;
            }
        }
        // Ivesties operatorius
        mokinys e;

        if (!(std::cin >> e)) throw std::runtime_error("Ivesties operatorius neveikia tvarkingai!");

        // Isvesties operatorius
        if (!(std::cout << e)) throw std::runtime_error("Isvesties operatorius neveikia tvarkingai!");

    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << std::endl;
    }
}

void EfektyvumoFunkcija() {
    // Pradėti v1 užpildymo laiko matavimą
    auto start = std::chrono::high_resolution_clock::now();
    unsigned int sz = 100000000; // 100000, 1000000, 10000000, 100000000
    std::vector<int> v1;
    for (int i = 1; i <= sz; ++i)
        v1.push_back(i);
    // Baigti v1 užpildymo laiko matavimą
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start; // Skirtumas (s)
    std::cout << "Elementų užpildymas užtruko (Vector)" << sz << ": " << diff.count() << " s\n";

    // Pradėti v2 užpildymo laiko matavimą
    start = std::chrono::high_resolution_clock::now();
    std::Vector<int> v2;
    for (int i = 1; i <= sz; ++i)
        v2.push_back(i);
    // Baigti v2 užpildymo laiko matavimą
    end = std::chrono::high_resolution_clock::now();
    diff = end - start; // Skirtumas (s)
    std::cout << "Elementų užpildymas užtruko (Vector)" << sz << ": " << diff.count() << " s\n";
}

void PerskirstymoSkaiciavimas() {
    unsigned int sz = 100000000, sk1 = 0, sk2 = 0;
    std::vector<int> v1;
    std::Vector<int> v2;
    for (int i = 1; i <= sz; ++i) {
        v1.push_back(i);
        if (v1.capacity() == v1.size()) sk1++;
    }
    v1.clear();
    for (int i = 1; i <= sz; ++i) {
        v2.push_back(i);
        if (v2.capacity() == v2.size()) sk2++;
    }
    v2.clear();
    std::cout << "Vector perkelimai: " << sk1 << std::endl << "Vector perkelimai: " << sk2 << std::endl;
}