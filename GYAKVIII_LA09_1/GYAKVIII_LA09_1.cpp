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
        cout.setf(ios::left); // balra igaz�t�s
        cout << setw(25) << "Nev" << setw(10) << "Kor" << setw(10) << "Ar" << endl; // fejl�c ki�r�sa
        for (int i = 0; i < db; i++) { // v�gigmegy�nk a kocsikon
            cout << setw(25) << kocsik[i].nev << setw(10) << kocsik[i].kor << setw(10) << kocsik[i].ar << endl; // kocsik adatainak ki�r�sa
        }
        return db;
    }

    double Atlagar() {
        double osszeg = 0; // �sszeg v�ltoz�
        for (int i = 0; i < db; i++) { // v�gigmegy�nk a kocsikon
            osszeg += kocsik[i].ar; // �sszegz�s
        }
        return osszeg / db; // �tlag kisz�m�t�sa

    }

    Kocsi Legfiatlabb() {
        Kocsi min = kocsik[0]; // min v�ltoz�
        for (int i = 1; i < db; i++) { // v�gigmegy�nk a kocsikon
            if (min.kor < kocsik[i].kor)// ha a kocsi kor kisebb mint a min kor
            {
                min = kocsik[i]; // min friss�t�se
            }
        }
        return min; // visszat�r�s a min �rt�kkel
    }


      Kereskedes(char* filename) {
          ifstream  be(filename, ios::binary); // bin�ris f�jl megnyit�sa olvas�sra
          if (be.fail()) { // hibakezel�s
              cerr << "Nem sikerult megnyitni a fajlt!\n";
              exit(1);
          }
          int szam = 0; // kocsik sz�ma
          Kocsi k; //kocsi v�ltoz�

          while (!be.eof()) { // am�g nem �r�nk a f�jl v�g�re, a f�jlban l�v� adarok sz�mol�sa
              be.read((char*)&k, sizeof(k)); // beolvas�s
              if (!be.eof()) { // ha nem �rt�nk a f�jl v�g�re
                  szam++; // n�velj�k a kocsik sz�m�t
              }
          }
          db = szam;
          kocsik = new Kocsi[szam]; // dinamikus mem�ria foglal�s
          be.clear(); // hibakezel�s  kitakar�t�sa
          be.seekg(0, ios::beg); // be�ll�tjuk a f�jlmutat�t a f�jl elej�re
          int i = 0;
          while (!be.eof()) //az adatok t�nyleges beolvas�sa
          {
              be.read((char*)&k, sizeof(k)); // beolvas�s
              if (!be.eof())
              { // ha nem �rt�nk a f�jl v�g�re
                  kocsik[i] = k; // kocsik t�mb felt�lt�se
                  i++; // n�velj�k az indexet
              }
          }
          be.close(); // bez�rjuk a f�jlt
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



