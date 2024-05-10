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
    return true;
  }
  return false;
}  // bepaalOptimaalBoeketTD

//****************************************************************************

void Veld::recursiefHulp (int x, int y, bool TD)
{
  if (!maxBoeketGevonden) {
    if (!TD || !vakjeBekekenTD[x][y]) {
      int nieuwBoeket;
      if (x != 0) {
        recursiefHulp (x - 1, y, TD);
        for (int i = 0; i <= 255; i++) {
          if (mogelijk[x - 1][y][i]) {
            nieuwBoeket = i;
            switchBit(nieuwBoeket, veld[x][y]);
            mogelijk[x][y][nieuwBoeket] = true;
          }
        }
      }
      if (y != 0) {
        recursiefHulp (x, y - 1, TD);
        for (int i = 0; i <= 255; i++) {
          if (mogelijk[x][y - 1][i]) {
            nieuwBoeket = i;
            switchBit(nieuwBoeket, veld[x][y]);
            mogelijk[x][y][nieuwBoeket] = true;
          }
        }
      }
      if (x == 0 && y == 0) {
        nieuwBoeket = 0;
        switchBit(nieuwBoeket, veld[x][y]);
        mogelijk[x][y][nieuwBoeket] = true;
      }
      if (mogelijk[hoogte - 1][breedte - 1][255]) {
        maxBoeketGevonden = true;
      }
      if (TD) {
        vakjeBekekenTD[x][y] = true;
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
      cout << rij << " " << kolom << endl;
    }
    return true;
  }
  return false;

}  // bepaalOptimaalBoeketBU

//****************************************************************************

void Veld::drukAfRoute (vector< pair<int,int> > &route)
{

  // TODO: implementeer deze memberfunctie

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