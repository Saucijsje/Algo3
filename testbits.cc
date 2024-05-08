// Programma om te spelen met bitrepresentaties van getallen.
//   Rudy van Vliet, 7 mei 2024

#include <iostream>
using namespace std;

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

//*************************************************************************

// Maak het i-de bit (vanaf rechts) van getal gelijk aan 1 (als nwBit is true)
// of 0 (als nwBit is false).
// Pre: 0 <= i <= 31
void setBit (int &getal, int i, bool nwBit)
{ int mask;

  if (nwBit)
  { mask = 1 << i;
    getal = getal | mask;
  }
  else
  { mask = ~(1 << i);  // bitsgewijs omkeren
    getal = getal & mask;
  }

}  // setBit

//*************************************************************************

// Return: true, als het i-de bit (vanaf rechts) van getal 1 is
//         false, als het i-de bit (vanaf rechts) van getal 0 is
// Pre: 0 <= i <= 31
bool getBit (int getal, int i)
{ int mask;

  mask = 1 << i;
  if ( (getal & mask) == mask)
    return true;
  else
    return false;

}  // getBit

//*************************************************************************

// Schrijf het i-de bit (vanaf rechts) van getal naar het scherm.
// Pre: 0 <= i <= 31
void schrijfBit (int getal, int i)
{
  if (getBit (getal, i))
    cout << '1';
  else
    cout << '0';

}  // schrijfBit

//*************************************************************************

// Schrijf de bitrepresentatie van getal naar het scherm.
void schrijfGetal (int getal)
{
  for (int i=31;i>=0;i--)
    schrijfBit (getal, i);

}  // schrijfGetal

//*************************************************************************

void menu ()
{ int keuze,
      getal,
      i,
      bitGetal;  // getalswaarde van een bit

  getal = 0;

  do
  { cout << endl;
    cout << "1. Een getal opgeven" << endl;
    cout << "2. Een bit opvragen" << endl;
    cout << "3. Een bit instellen" << endl;
    cout << "4. Stoppen" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;

    switch (keuze)
    { case 1: cout << "Geef een getal op: ";
              cin >> getal;
              cout << "De bitrepresentatie is: ";
              schrijfGetal (getal);
              cout << endl;
              break;
      case 2: cout << "Welk bit van het getal " << getal
                   << " wilt u weten (0..31): ";
              cin >> i;
              if (integerInBereik ("i" , i, 0, 31))
              { cout << "Het " << i << "-de bit van " << getal << " is: ";
                schrijfBit (getal, i);
                cout << endl;
              }
              break;
      case 3: cout << "Welk bit van het getal " << getal
                   << " wilt u instellen (0..31): ";
              cin >> i;
              if (integerInBereik ("i" , i, 0, 31))
              { cout << "Wat moet dit bit worden (0/1): ";
                cin >> bitGetal;
                if (integerInBereik ("bit" , bitGetal, 0, 1))
                  setBit (getal, i, (bitGetal==1));
                cout << "Nu is de bitrepresentatie van getal: ";
                schrijfGetal (getal);
                cout << endl;
              }
              break;
      case 4: break;
      default: cout << "Voer een goede keuze in!" << endl;
    }  // switch

  } while (keuze!=4);

}  // menu

//*************************************************************************

int main ()
{
  menu ();

  return 0;

}
