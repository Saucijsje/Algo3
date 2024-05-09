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
    bepaalOptimaalBoeketRec2(hoogte - 1, breedte - 1);
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

void Veld::bepaalOptimaalBoeketRec2 (int x, int y)
{
  int nieuwBoeket;
  if (x != 0) {
    bepaalOptimaalBoeketRec2 (x - 1, y);
    for (int i = 0; i <= 255; i++) {
      if (mogelijk[x - 1][y][i]) {
        nieuwBoeket = i;
        switchBit(nieuwBoeket, veld[x][y]);
        mogelijk[x][y][nieuwBoeket] = true;
      }
    }
  }
  if (y != 0) {
    bepaalOptimaalBoeketRec2 (x, y - 1);
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
} // bepaalOptimaalBoeketRec2

//****************************************************************************

bool Veld::bepaalOptimaalBoeketTD (int &optBoeket, int &optBits)
{
  // TODO: implementeer deze memberfunctie
  return false;

}  // bepaalOptimaalBoeketTD

//****************************************************************************

bool Veld::bepaalOptimaalBoeketBU (int &optBoeket, int &optBits,
                                 vector< pair<int,int> > &route)
{
  // TODO: implementeer deze memberfunctie
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
      for (int k = 0; k <= 7; k++) {
        mogelijk[i][j][k] = false;
      }
    }
  }
}