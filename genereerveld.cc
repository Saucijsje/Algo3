// Hulpprogramma voor opdracht 3 Algoritmiek, voorjaar 2024.
// Biedt de gebruiker een menu om wlllekeurige velden met bloemen
// te genereren.
//
//   Rudy van Vliet,  7 mei 2024

#include <iostream>
#include <fstream>
#include <cstdlib>  // voor rand en srand
using namespace std;

const int MaxDim = 100;      // maximale dimensie van het veld,
                             // zowel horizontaal als verticaal
const int MaxBloem = 7;      // maximaal nummer van een bloemensoort
const int MaxBestandsNaamLengte = 30; // maximale lengte van een bestandsnaam

//*************************************************************************

bool integerInBereik (const char *variabele, int waarde,
                      int minWaarde, int maxWaarde)
{
  if (waarde>=minWaarde && waarde<=maxWaarde)
    return true;
  else
  { cout << variabele << "=" << waarde << ", maar moet in [" << minWaarde
         << "," << maxWaarde << "] liggen." << endl;
    return false;
  }

}  // integerInBereik

//****************************************************************************

int randomGetal (int min, int max)
// Genereer een random geheel getal r waarvoor  min <= r <= max.
// Pre: min <= max;
{ int bereik,
      r;

  bereik = max - min + 1;

  r = ((rand())%bereik) + min;
  return r;

}  // randomGetal

//****************************************************************************

// Genereer een willekeurig hxb veld met bloemen,
// en schrijf dat naar een tekstbestand.
// De gebruiker geeft h, b en de naam van tekstbestand op.
void genereerveld ()
{ int hoogte, breedte;
  ofstream fuit;
  char bestandsnaam[MaxBestandsNaamLengte+1];

  cout << endl;
  cout << "Geef een waarde voor hoogte: ";
  cin >> hoogte;
  cout << "Geef een waarde voor breedte: ";
  cin >> breedte;
  if (integerInBereik ("hoogte", hoogte, 1, MaxDim) &&
      integerInBereik ("breedte", breedte, 1, MaxDim))
  {
    cout << "Geef een naam voor het tekstbestand, waarheen het veld geschreven moet worden: " << endl << " ";
    cin >> bestandsnaam;

    fuit.open (bestandsnaam, ios::out);
    if (fuit.is_open())
    {
      fuit << hoogte << ' ' << breedte << endl;

       // nu een willekeurig hoogtexbreedte veld met bloemen genereren
      srand ((unsigned)time(0));
      for (int i=0;i<hoogte;i++)
        for (int j=0;j<breedte;j++)
        { fuit << randomGetal (0, MaxBloem);
          if (j<breedte-1)
            fuit << ' ';
          else
            fuit << endl;
        }

      fuit.close ();
    }
    else
    { cout << "We konden het bestand `" << bestandsnaam
           << "' niet openen." << endl;
    }

  }  // hoogte en breedte in [1..MaxDim]

}  // genereerveld

//****************************************************************************

void hoofdmenu ()
{ int keuze;

  do
  { genereerveld ();

    do
    { cout << endl;
      cout << "1. Een nieuw veld genereren" << endl;
      cout << "2. Stoppen" << endl;
      cout << endl;
      cout << "Maak een keuze: ";
      cin >> keuze;

      if (keuze!=1 && keuze!=2)
        cout << "Voer een goede keuze in!" << endl;

    } while (keuze!=1 && keuze!=2);

  } while (keuze!=2);
  
}  // hoofdmenu

//*************************************************************************

int main ()
{

  hoofdmenu ();

  return 0;

}
