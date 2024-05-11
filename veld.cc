// Implementatie van klasse Veld.

//****************************************************************************

#include <iostream>
#include <fstream>
#include <cstring>
#include "standaard.h"
#include "veld.h"
using namespace std;

//****************************************************************************

Veld::Veld ()
{
  veldIngelezen = false;
}  // constructor

//****************************************************************************

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
    besteBoeket(optBoeket,optBits);
    int temp = optBoeket;
    hulpRoute.push_back(make_pair(hoogte - 1, breedte - 1));
    bepaalRoute(temp,hoogte - 1, breedte - 1);
    for (int i = hulpRoute.size() - 1; i >= 0; i--) {
      cout << i << endl;
      route.push_back(hulpRoute[i]);
    }
    return true;
  }
  return false;
}  // bepaalOptimaalBoeketBU

//****************************************************************************

void Veld::drukAfRoute (vector< pair<int,int> > &route)
{
  int boeket = 0;
  for (int i = 0; i < route.size(); i++) {
    switchBit(boeket,veld[route[i].first][route[i].second]);
    cout << route[i].first << " " << route[i].second << " " << boeket << endl;
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

bool Veld::bepaalRoute(int &boeket, int rij, int kolom) 
{
  cout << hulpRoute.size() << "a" << endl;
  int nieuwBoeket;
  if (rij == 0 && kolom == 0) {
    nieuwBoeket = boeket;
    switchBit(nieuwBoeket,veld[rij][kolom]);
    if (boeket == 0) {
      return true;
    } else {
      switchBit(nieuwBoeket,veld[rij][kolom]);
      return false;
    }
  }
  if (rij != 0) {
    nieuwBoeket = boeket;
    switchBit(nieuwBoeket,veld[rij][kolom]);
    if (mogelijk[rij - 1][kolom][nieuwBoeket]) {
      hulpRoute.push_back(make_pair(rij - 1, kolom));
      if (bepaalRoute(nieuwBoeket, rij - 1, kolom)) {
        return true;
      } else {
        hulpRoute.pop_back();
        switchBit(nieuwBoeket,veld[rij][kolom]);
      }
    }
  }
  if (kolom != 0) {
    nieuwBoeket = boeket;
    switchBit(nieuwBoeket,veld[rij][kolom]);
    if (mogelijk[rij][kolom - 1][nieuwBoeket]) {
      hulpRoute.push_back(make_pair(rij, kolom - 1));
      if (bepaalRoute(nieuwBoeket, rij, kolom - 1)) {
        return true;
      } else {
        hulpRoute.pop_back();
        switchBit(nieuwBoeket,veld[rij][kolom]);
      }
    }
  }
  cout << hulpRoute.size() << "b" << endl;
  return false;
}