// Implementatie van klasse Veld.

//****************************************************************************

#include <iostream>
#include <fstream>
#include <cstring>
#include "standaard.h"
#include "veld.h"
using namespace std;

//****************************************************************************
/*Zodra er een file ingelezen is wordt boolean veldIngezen true, daarvoor
staat hij op false.*/
Veld::Veld ()
{
  veldIngelezen = false;
}  // constructor

//****************************************************************************
/*De meegegeven filenaam wordt geopend in de variabele mijnfile. Als het niet
lukt om hem te openen geven we een foutmelding. Als het wel lukt worden de 
eerste twee getallen opgeslagen in de variabelen hoogte en breedte en er
wordt meteen gecontroleerd of deze wel binnen de dimensies vallen (1-100).
Als dit zo is wordt het veld ingelezen in de variabele veld[][] en wordt er 
per bloemnummer gecontroleerd of deze binnen de dimensies valt (0-7). Als 
alles klopt wordt de boolean veldIngelezen op true gezet.*/
bool Veld::leesInVeld (const char *invoernaam)
{
  int getal;
  ifstream mijnfile;
  mijnfile.open(invoernaam);
  if (!mijnfile.is_open()) {
   cout << "Bestand openen niet gelukt." << endl;
   return false;
  }
  mijnfile >> getal;
  hoogte = getal;
  mijnfile >> getal;
  breedte = getal;
  if (!integerInBereik("hoogte",hoogte,1,100) || 
      !integerInBereik("breedte",breedte,1,100)) {
    return false;
  }
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      mijnfile >> getal;
      if (!integerInBereik("getal",getal,0,7)) {
        return false;
      }
      veld[i][j] = getal;
    }
  }
  veldIngelezen = true;
  return true;
}  // leesInVeld

//****************************************************************************
/*We drukken het veld met bloemen af. Omdat deze functie elke keer wordt aan-
geroepen bij het hoofdmenu roepen we hier ook de leegMogelijkheden() functie
aan: deze zorgt ervoor dat de variabele mogelijk[][][] weer gereset wordt.*/
void Veld::drukAfVeld ()
{
  if (veldIngelezen) {
    leegMogelijkheden();
    cout << endl << "Het bloemenveld: " << endl << endl;
    for (int i = 0; i < hoogte; i++) {
      for (int j = 0; j < breedte; j++) {
        cout << veld[i][j] << " ";
      }
      cout << endl;
    }
  }
}  // drukAfVeld

//****************************************************************************
/*Wrapper-functie voor de daadwerkelijke recursieve functie die recursief
het optimale boeket bepaalt. De parameters optBoeket en optBits worden op -1
gezet, de boolean die aangeeft of het optimale boeket (255) al is gevonden.
De functie die gebruik maakt van top-down gebruikt dezelfde recursieve functie
als deze, dus met een boolean TD geven we aan dat deze functie daar geen ge-
bruik van maakt. Na afloop kijken we via de functie besteBoeket wat het beste
boeket is en retourneren we true als er een veld was ingelezen, en false als 
niet.*/
bool Veld::bepaalOptimaalBoeketRec (int &optBoeket, int &optBits)
{
  if (veldIngelezen) {
    optBoeket = -1;
    optBits = -1;
    maxBoeketGevonden = false;
    bool TD = false;
    recursiefHulp(hoogte - 1, breedte - 1, TD);
    besteBoeket(optBoeket,optBits);
    return true;
  }
  return false;
}  // bepaalOptimaalBoeketRec

//****************************************************************************
/*Bijna exact hetzelfde als vorige functie, TD staat nu op true, en bij top-
down gebruiken we dat als een vakje eenmaal bekeken is, we niet nog een keer
de berekeningen voo dat vakje hoeven te doen. De boolean vakjeBekekenTD[][]
geeft voor elk vakje aan of deze al is bezocht, en alle vakjes worden in deze
functie eerst op onbezocht gezet.*/
bool Veld::bepaalOptimaalBoeketTD (int &optBoeket, int &optBits)
{
  if (veldIngelezen) {
    optBoeket = -1;
    optBits = -1;
    maxBoeketGevonden = false;
    bool TD = true;
    for (int i = 0; i < hoogte; i++) {
      for (int j = 0; j < breedte; j++) {
        vakjeBekekenTD[i][j] = false;
      }
    }
    recursiefHulp(hoogte - 1, breedte - 1, TD);
    besteBoeket(optBoeket,optBits);
    return true;
  }
  return false;
}  // bepaalOptimaalBoeketTD

//****************************************************************************
/*De daadwerkelijk recursieve functie om voor alle vakjes in het veld de moge-
lijke boeketten te vinden. Bij elke aanroep van de functie wordt er een int
nieuwBoeket gemaakt. Deze gebruiken we om te weten welke boeketten er allemaal
mogelijk zijn in het vakje veld[rij][kolom]. Als we niet tegen de bovenrand
van het veld aan zitten (dus rij != 0), bekijken we de mogelijke boeketten
in het vakje boven ons. Hetzelfde met het vakje links als kolom != 0. Zodra
de recursief aangeroepen functie voltooid is weten we dat het van het buur-
vakje duidelijk is welke boeketten daar haalbaar zijn, en kunnen we vervolgens
van het huidige vakje de mogelijke boeketten op true zetten. Dit zijn dezelfde
boeketten als die van de buren met de bit van de bloem op het huidige vakje
gewisseld. Er wordt dus eerst gekeken of het buurvakje met een bepaald boeket
mogelijk is. Als wel, dan wordt het de int nieuwBoeket gelijk gesteld aan
dit boeket en wordt i-de de bit gewisseld (waar i het bloemnr. is). Dit boeket
in het huidige vakje wordt vervolgens op true gezet. In het eindgeval waar we
bij vakje (0,0) zijn doen we simpelweg dezelfde handeling, maar zonder dat de
functie zichzelf recursief aanroept. Elke keer wordt de hele functie uitge-
voerd als TD uitstaat, maar ook als TD wel aanstaat maar het vakje nog niet
bekeken is. Dan wordt aan het einde van de functie dit vakje op bekeken gezet
en zal bij de volgende aanroep van de functie met deze rij en kolom TD aan
staan en het vakje op bekeken staan, en zal de functie niet opnieuw terugre-
kenen wat de mogelijke boeketten zijn.*/
void Veld::recursiefHulp (int rij, int kolom, bool TD)
{
  if (!maxBoeketGevonden) {
    if (!TD || !vakjeBekekenTD[rij][kolom]) {
      int nieuwBoeket;
      if (rij != 0) {
        recursiefHulp (rij - 1, kolom, TD);
        for (int i = 0; i <= 255; i++) {
          if (mogelijk[rij - 1][kolom][i]) {
            nieuwBoeket = i;
            switchBit(nieuwBoeket, veld[rij][kolom]);
            mogelijk[rij][kolom][nieuwBoeket] = true;
          }
        }
      }
      if (kolom != 0) {
        recursiefHulp (rij, kolom - 1, TD);
        for (int i = 0; i <= 255; i++) {
          if (mogelijk[rij][kolom - 1][i]) {
            nieuwBoeket = i;
            switchBit(nieuwBoeket, veld[rij][kolom]);
            mogelijk[rij][kolom][nieuwBoeket] = true;
          }
        }
      }
      if (rij == 0 && kolom == 0) {
        nieuwBoeket = 0;
        switchBit(nieuwBoeket, veld[rij][kolom]);
        mogelijk[rij][kolom][nieuwBoeket] = true;
      }
      if (mogelijk[hoogte - 1][breedte - 1][255]) {
        maxBoeketGevonden = true;
      }
      if (TD) {
        vakjeBekekenTD[rij][kolom] = true;
      }
    }
  }
} // bepaalOptimaalBoeketTD2

//****************************************************************************
/*Met for-loops en while-loops worden alle mogelijke boeketten per vakje op
true gezet. Eerst legen we de route-variabele, die de route voor het optimale
boeket opslaat, en de andere twee paramaters worden op -1 gezet. Het mogelijke
boeket in het eerste vakje van het veld wordt op true gezet en daarna gaan we
steed een diagonaal af (van rechtsboven naar linksonder), die begint bij vakje
(0,1) en (1,0) en steeds doorschuift tot hij bij het laatste vakje rechtsonder
is. We berekenen eerst de coördinaten van het meest rechtsboven vakje van de
diagonaal. We gaan hoogte + breedte - 2 diagonalen af, in het begin is de
kolom van het rechtsboven vakje van de diagonaal gelijk aan het diagonaalnum-
mer. Na de rechtsbovenhoek van het veld is de kolom gelijk aan de breedte van
het veld - 1. De rij is juist eerst de hele tijd 0, en na de hoek gelijk aan
i - breedte + 1. Dan gaan we naar linksonder lopen over de diagonaal. Als een
vakje een buur boven zich en/of links van zich heeft worden de boeketten weer
berekend zoals eerder. Als de diagonaal bij de onderste is aangekomen of lin-
kerkant van het veld stoppen we. Tot slot bepalen we weer het beste boeket
en het aantal oneven aantal bloemen, en roepen we vervolgens de bepaalRoute()
functie aan om de route die leidt tot het optimale boeket te vinden.*/
bool Veld::bepaalOptimaalBoeketBU (int &optBoeket, int &optBits,
                                 vector< pair<int,int> > &route)
{
  if (veldIngelezen) {
    route.clear();
    optBoeket = -1;
    optBits = -1;
    int nieuwBoeket = 0;
    switchBit(nieuwBoeket, veld[0][0]);
    mogelijk[0][0][nieuwBoeket] = true;
    for (int i = 1; i < breedte + hoogte - 1; i++) {
      int kolom = i;
      int rij = 0;
      if (kolom >= breedte) {
        kolom = breedte - 1;
        rij = i - breedte + 1;
      }
      while (rij != hoogte && kolom != -1) {
        if (rij != 0) {
          for (int j = 0; j <= 255; j++) {
            if (mogelijk[rij - 1][kolom][j]) {
              nieuwBoeket = j;
              switchBit(nieuwBoeket, veld[rij][kolom]);
              mogelijk[rij][kolom][nieuwBoeket] = true;
            }
          }
        }
        if (kolom != 0) {
          for (int j = 0; j <= 255; j++) {
            if (mogelijk[rij][kolom - 1][j]) {
              nieuwBoeket = j;
              switchBit(nieuwBoeket, veld[rij][kolom]);
              mogelijk[rij][kolom][nieuwBoeket] = true;
            }
          }
        }
        rij++;
        kolom--;
      }
    }
    besteBoeket(optBoeket, optBits);
    routeGevonden = false;
    bepaalRoute(optBoeket, hoogte - 1, breedte - 1, route);
    return true;
  }
  return false;
}  // bepaalOptimaalBoeketBU

//****************************************************************************
/*We laten op twee manieren zien hoe de optimale route loopt. Eerst in een ta-
bel: per regel de x- en y-coördinaten en vervolgens het boeket in dat vakje.
Daarna drukken we weer het veld af, maar controleren we per vakje in het veld
of de x- en y-coördinaten precies gelijk zijn aan een van de coördinaten in de
route-vector. Als inderdaad het vakje op de route ligt drukken we de dat vakje
af, en anders niks, waardoor we precies zien hoe de route loopt.*/
void Veld::drukAfRoute (vector< pair<int,int> > &route)
{
  cout << endl << "Tabel met coördinaten:" << endl << endl;
  int boeket = 0;
  for (int i = 0; i < route.size(); i++) {
    switchBit(boeket,veld[route[i].first][route[i].second]);
    cout << route[i].first << " " << route[i].second << " " << boeket << endl;
  }
  cout << endl << "Route gevisualiseerd:" << endl << endl;
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      bool vakjeOpRoute = false;
      for (int k = 0; k < route.size(); k++) {
        if (route[k].first == i && route[k].second == j) {
          vakjeOpRoute = true;
        }
      }
      if (vakjeOpRoute) {
        cout << veld[i][j] << " ";
      } else {
        cout << "  ";
      }
    }
    cout << endl;
  }
}  // drukAfRoute

//****************************************************************************
/*Zet alle boeketten op elk vakje op false.*/
void Veld::leegMogelijkheden ()
{
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      for (int k = 0; k <= 255; k++) {
        mogelijk[i][j][k] = false;
      }
    }
  }
}

//****************************************************************************
/*We bekijken alle boeketten in het laatste vakje. Als er een op true staat,
tellen we het aantal bits van dat boeket dat op 1 staat. Als we niet eerder
bij een boeket zoveel bits op 1 hadden wordt dit boeket het nieuwe optimale
boeket met het aantal bits opgeslagen in optBits.*/
void Veld::besteBoeket(int &optBoeket, int &optBits)
{
  for (int i = 0; i <= 255; i++) {
    int teller = 0;
    if (mogelijk[hoogte - 1][breedte - 1][i]) {
      for (int j = 0; j <= 7; j++) {
        if (getBit(i,j)) {
          teller++;
        }
      }
    }
    if (teller > optBits) {
      optBits = teller;
      optBoeket = i;
    }
  }
}

//****************************************************************************
/*We bepalen recursief de optimale route, beginnend bij het laatste vakje.
In de parameter boeket staat het boeket waarmee we eigenlijk teruglopen door 
het veld. Deze begint op het optimale boeket, en we willen teruglopen, 
steeds een vakje zoekend dat een boeket kan bevatten als we de bloem weg 
zouden halen van het vakje waar we terug van lopen. We kijken in principe dus
steeds naar de buren voor ons en veranderen ons boeket door de bloem in het
huidige vakje weg te halen (te wisselen), en als de buur dat boeket bevat
slaan we de coördinaten op in route. Eenmaal bij het beginvakje aangekomen
zetten we de routeGevonden variabele op true, en stopt hij in alle functies
met doorzoeken naar een route.*/
void Veld::bepaalRoute(int boeket, int rij, int kolom,
                      vector< pair<int,int> > &route) 
{
  int nieuwBoeket;
  if (rij == 0 && kolom == 0) {
    routeGevonden = true;
    nieuwBoeket = boeket;
    switchBit(nieuwBoeket,veld[rij][kolom]);
    route.push_back(make_pair(rij, kolom));
  }
  if (rij != 0 && !routeGevonden) {
    nieuwBoeket = boeket;
    switchBit(nieuwBoeket,veld[rij][kolom]);
    if (mogelijk[rij - 1][kolom][nieuwBoeket]) {
      bepaalRoute(nieuwBoeket, rij - 1, kolom, route);
      route.push_back(make_pair(rij, kolom));
    }
  }
  if (kolom != 0 && !routeGevonden) {
    nieuwBoeket = boeket;
    switchBit(nieuwBoeket,veld[rij][kolom]);
    if (mogelijk[rij][kolom - 1][nieuwBoeket]) {
      bepaalRoute(nieuwBoeket, rij, kolom - 1, route);
      route.push_back(make_pair(rij, kolom)); 
    }
  }
}