/**
  @file CFolder.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CFolder.hpp"
using namespace std;

CFolder::CFolder( const string & name,
                  const string & location,
                  const string & creation,
                  const string & owner,
                  unsigned int size) :      CFile(name,
                                                  location,
                                                  creation,
                                                  owner,
                                                  size)
{
}

CFolder::CFolder( const CFolder & pattern ) :   CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size)
{
}

CFile * CFolder::clone() const{
  CFolder * clone = new CFolder(*this);
  return clone;
}


string CFolder::getFullName()const{
  return name;
}


string CFolder::getType() const{
  return "Folder";
}

void CFolder::printCFile()
{
  cout << "[] /" << name;
}
