/**
  @file CLink.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CLink.hpp"
using namespace std;


CLink::CLink(     const string & name,
                  const string & location,
                  const string & creation,
                  const string & owner,
                  unsigned int size) :       CFile(name,
                                                  location,
                                                  creation,
                                                  owner,
                                                  size)
{
}

CLink::CLink( const CLink & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size)
{
}

CFile * CLink::clone() const{
  CLink * clone = new CLink(*this);
  return clone;
}

string CLink::getFullName()const{
  return name;
}

string CLink::getType() const{
  return "Link";
}

void CLink::printCFile()
{
  cout << "-> " << name;
}
