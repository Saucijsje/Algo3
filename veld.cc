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
Als dit zo is wordt het veld ingelezen in de variabele veld[maxDim][maxDim] en
wordt er per bloemnummer gecontroleerd of deze binnen de dimensies valt (0-7).
Als alles klopt wordt de boolean veldIngelezen op true gezet.*/
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

bool Veld::bepaalOptimaalBoeketBU (int &optBoeket, int &optBits,
                                 vector< pair<int,int> > &route)
{
  if (veldIngelezen) {
    route.clear();
    optBoeket = -1;
    optBits = -1;
    int nieuwBoeket = 0;
    switchBit(nieuwBoeket,veld[0][0]);
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
              switchBit(nieuwBoeket,veld[rij][kolom]);
              mogelijk[rij][kolom][nieuwBoeket] = true;
            }
          }
        }
        if (kolom != 0) {
          for (int j = 0; j <= 255; j++) {
            if (mogelijk[rij][kolom - 1][j]) {
              nieuwBoeket = j;
              switchBit(nieuwBoeket,veld[rij][kolom]);
              mogelijk[rij][kolom][nieuwBoeket] = true;
            }
          }
        }
        rij++;
        kolom--;
      }
    }
    besteBoeket(optBoeket, optBits);
    bepaalRoute(optBoeket, hoogte - 1, breedte - 1,route);
    return true;
  }
  return false;
}  // bepaalOptimaalBoeketBU

//****************************************************************************

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

bool Veld::bepaalRoute(int boeket, int rij, int kolom,
                      vector< pair<int,int> > &route) 
{
  int nieuwBoeket;
  if (rij == 0 && kolom == 0) {
    nieuwBoeket = boeket;
    switchBit(nieuwBoeket,veld[rij][kolom]);
    if (nieuwBoeket == 0) {
      route.push_back(make_pair(rij, kolom));
      return true;
    } else {
      return false;
    }
  }
  if (rij != 0) {
    nieuwBoeket = boeket;
    switchBit(nieuwBoeket,veld[rij][kolom]);
    if (mogelijk[rij - 1][kolom][nieuwBoeket]) {
      if (bepaalRoute(nieuwBoeket, rij - 1, kolom, route)) {
        route.push_back(make_pair(rij, kolom));
        return true;
      } 
    }
  }
  if (kolom != 0) {
    nieuwBoeket = boeket;
    switchBit(nieuwBoeket,veld[rij][kolom]);
    if (mogelijk[rij][kolom - 1][nieuwBoeket]) {
      if (bepaalRoute(nieuwBoeket, rij, kolom - 1, route)) {
        route.push_back(make_pair(rij, kolom));
        return true;
      } 
    }
  }
  return false;
}