// Defintie van standaard functies.

#ifndef StandaardHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define StandaardHVar  // wordt ge-include 

// Controleer of variabele met naam `variabele' een waarde `waarde' heeft
// die tussen (inclusief) minWaarde en maxWaarde in ligt.
// Zo nee, geef een passende foutmelding.
//
// Voorbeeld van aanroep:
//   if (integerInBereik ("teller", teller, 0, 1000))
//     ...
bool integerInBereik (const char *variabele, int waarde,
                      int minWaarde, int maxWaarde);

// Controleer of waarde `waarde' tussen (inclusief) minWaarde en maxWaarde
// in ligt.
// Geef GEEN foutmelding als het niet zo is.
bool integerInBereik (int waarde, int minWaarde, int maxWaarde);

// Maak het i-de bit (vanaf rechts) van getal gelijk aan 1 (als nwBit is true)
// of 0 (als nwBit is false).
// Pre: 0 <= i <= 31
void setBit (int &getal, int i, bool nwBit);

// Return: true, als het i-de bit (vanaf rechts) van getal 1 is
//         false, als het i-de bit (vanaf rechts) van getal 0 is
// Pre: 0 <= i <= 31
bool getBit (int getal, int i);

// Verander het i-de bit (vanaf rechts) van getal.
// Pre: 0 <= i <= 31
void switchBit (int &getal, int i);

#endif

