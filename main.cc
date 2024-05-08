// Hoofdprogramma voor oplossing voor programmeeropdracht 3 van Algoritmiek,
// voorjaar 2024: Trouwboeket
//
// Biedt de gebruiker een menustructuur om
// * een veld met bloemen in te lezen, en vervolgens
// - rechtstreeks recursief een optimaal boeket te bepalen
// - met top-down DP een optimaal boeket te bepalen
// - met bottom-up DP een optimaal boeket met bijbehorende route te bepalen
//
// Namen studenten, datum

#include <iostream>
#include <ctime>  // voor clock() en clock_t
#include "standaard.h"
#include "veld.h"
using namespace std;

const int MaxBestandsNaamLengte = 30; // maximale lengte van een bestandsnaam

//*************************************************************************

// Schrijf het menu voor het veld op het scherm, en vraag een keuze
// van de gebruiker.
// Retourneer: de keuze van de gebruiker
int keuzeUitMenu ()
{ int keuze;

  cout << endl;
  cout << "1. Optimaal boeket bepalen (rechtstreeks recursief)" << endl;
  cout << "2. Optimaal boeket bepalen (top-down DP)" << endl;
  cout << "3. Optimaal boeket met bijbehorende route bepalen"
       << " (bottom-up DP)" << endl;
  cout << "4. Stoppen met dit veld" << endl;
  cout << endl;
  cout << "Maak een keuze: ";
  cin >> keuze;

  return keuze;

}  // keuzeUitMenu

//*************************************************************************

// Bied de gebruiker een menu om voor veld v1
// * rechtstreeks recursief een optimaal boeket te bepalen
// * met top-down DP een optimaal boeket te bepalen
// * met bottom-up DP een optimaal boeket met bijbehorende route te bepalen
// Roep vervolgens v1 aan voor de gekozen functie.
// Herhaal dit totdat de gebruiker aangeeft te willen stoppen.
void menuVoorVeld (Veld *v1)
{ int keuze,
      optBoeket, optBits;
  vector< pair<int,int> > route;
  bool gelukt;
  clock_t t1, t2;

  keuze = 0;
  gelukt = false;  // om compiler warning te voorkomen
  while (keuze!=4)
  { v1->drukAfVeld ();

    keuze = keuzeUitMenu ();

    t1 = clock ();
    cout << endl;
    switch (keuze)
    {
      case 1: gelukt = v1->bepaalOptimaalBoeketRec (optBoeket, optBits);
              break;
      case 2: gelukt = v1->bepaalOptimaalBoeketTD (optBoeket, optBits);
              break;
      case 3: gelukt = v1->bepaalOptimaalBoeketBU (optBoeket, optBits, route);
              break;
      case 4: break;
      default: cout << "Voer een goede keuze in!" << endl;
    }  // switch
    t2 = clock ();

    if (integerInBereik (keuze, 1, 3))
    { cout << endl;
      if (gelukt)
      { cout << endl;
        cout << "Optimaal boeket: " << optBoeket;
        cout << " met " << optBits << " soorten bloemen met oneven aantal"
             << endl;
        if (keuze==3)  // bottom-up
          v1->drukAfRoute (route);
      }
      else
        cout << "Het is niet gelukt om een optimaal boeket te bepalen."
             << endl;

      cout << endl;
      cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
        << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;

    }  // integerInBereik
  }  // while

}  // menuVoorVeld

//*************************************************************************

void hoofdmenu ()
{ Veld *v1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
             // en weer weg te gooien
  int keuze;
  char invoerNaam[MaxBestandsNaamLengte+1];

  do
  {
    cout << endl;
    cout << "1. Een nieuw veld inlezen" << endl;
    cout << "2. Stoppen" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;

    switch (keuze)
    { case 1: v1 = new Veld ();
              cout << endl;
              cout << "Geef een naam voor het tekstbestand met het veld: ";
              cin >> invoerNaam;
              if (v1->leesInVeld (invoerNaam))  // gelukt om veld in te lezen
                menuVoorVeld (v1);
              delete v1;  // netjes opruimen
              break;
      case 2: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }

  } while (keuze!=2);

}  // hoofdmenu

//*************************************************************************
  
int main ()
{
  hoofdmenu ();

  return 0;

}

