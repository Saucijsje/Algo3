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
  // TODO: implementeer deze memberfunctie
  return false;

}  // bepaalOptimaalBoeketRec

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

