/**
  @file CDatabase.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CDatabase.hpp"
using namespace std;


CDatabase::CDatabase( const string & name,
                const string & location,
                const string & creation,
                const string & owner,
                unsigned int size,
                const string & extension) :   CFile(name,
                                                location,
                                                creation,
                                                owner,
                                                size),
                                            extension(extension)
{
}

CDatabase::CDatabase( const CDatabase & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                              extension(pattern.extension)
{
}

CFile * CDatabase::clone() const{
  CDatabase * clone = new CDatabase(*this);
  return clone;
}

string CDatabase::getFullName()const{
  return (name + extension);
}

string CDatabase::getType() const{
  return "Database file";
}

void CDatabase::printCFile()
{
  cout << "(> " << name<<extension;
}
