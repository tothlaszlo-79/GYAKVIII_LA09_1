#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Kocsi {
    char nev[25];
    int kor;
    int ar;
};


class Kereskedes {
private: Kocsi* kocsik;
       int db;
public:
    int Kiir() {
        cout.setf(ios::left); // balra igazítás
        cout << setw(25) << "Nev" << setw(10) << "Kor" << setw(10) << "Ar" << endl; // fejléc kiírása
        for (int i = 0; i < db; i++) { // végigmegyünk a kocsikon
            cout << setw(25) << kocsik[i].nev << setw(10) << kocsik[i].kor << setw(10) << kocsik[i].ar << endl; // kocsik adatainak kiírása
        }
        return db;
    }

    double Atlagar() {
        double osszeg = 0; // összeg változó
        for (int i = 0; i < db; i++) { // végigmegyünk a kocsikon
            osszeg += kocsik[i].ar; // összegzés
        }
        return osszeg / db; // átlag kiszámítása

    }

    Kocsi Legfiatlabb() {
        Kocsi min = kocsik[0]; // min változó
        for (int i = 1; i < db; i++) { // végigmegyünk a kocsikon
            if (min.kor < kocsik[i].kor)// ha a kocsi kor kisebb mint a min kor
            {
                min = kocsik[i]; // min frissítése
            }
        }
        return min; // visszatérés a min értékkel
    }


      Kereskedes(char* filename) {
          ifstream  be(filename, ios::binary); // bináris fájl megnyitása olvasásra
          if (be.fail()) { // hibakezelés
              cerr << "Nem sikerult megnyitni a fajlt!\n";
              exit(1);
          }
          int szam = 0; // kocsik száma
          Kocsi k; //kocsi változó

          while (!be.eof()) { // amíg nem érünk a fájl végére, a fájlban lévõ adarok számolása
              be.read((char*)&k, sizeof(k)); // beolvasás
              if (!be.eof()) { // ha nem értünk a fájl végére
                  szam++; // növeljük a kocsik számát
              }
          }
          db = szam;
          kocsik = new Kocsi[szam]; // dinamikus memória foglalás
          be.clear(); // hibakezelés  kitakarítása
          be.seekg(0, ios::beg); // beállítjuk a fájlmutatót a fájl elejére
          int i = 0;
          while (!be.eof()) //az adatok tényleges beolvasása
          {
              be.read((char*)&k, sizeof(k)); // beolvasás
              if (!be.eof())
              { // ha nem értünk a fájl végére
                  kocsik[i] = k; // kocsik tömb feltöltése
                  i++; // növeljük az indexet
              }
          }
          be.close(); // bezárjuk a fájlt
      }

      ~Kereskedes() {
          delete[] kocsik;
      }
};

int main()
{
    char filename[] = "auto.dat";

    Kereskedes kereskedes(filename);

   

    cout << "\nA kereskedesben levo autok szama: " << kereskedes.Kiir() << endl;
    cout << setprecision(9) << "\nA kereskedesben levo autok atlagara: " << kereskedes.Atlagar() << endl;
    Kocsi aut = kereskedes.Legfiatlabb();
    cout << "\nA kereskedesben levo legfiatalabb auto adatai: " << aut.nev << " "
        << aut.kor << " " << aut.ar << endl;
    system("pause");
    return 0;

    
}



