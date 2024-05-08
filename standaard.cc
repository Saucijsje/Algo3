// Implementatie van standaard functies.

#include <iostream>
#include "standaard.h"
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

bool integerInBereik (int waarde, int minWaarde, int maxWaarde)
{
  if (waarde>=minWaarde && waarde<=maxWaarde)
    return true;
  else
    return false;

}  // integerInBereik

//*************************************************************************

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

bool getBit (int getal, int i)
{ int mask;

  mask = 1 << i;
  if ( (getal & mask) == mask)
    return true;
  else
    return false;

}  // getBit

//*************************************************************************

void switchBit (int &getal, int i)
{
  if (getBit (getal, i))
    setBit (getal, i, false);
  else
    setBit (getal, i, true);

}  // switchBit

