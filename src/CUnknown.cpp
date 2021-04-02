/**
  @file CUnknown.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CUnknown.hpp"
using namespace std;


CUnknown::CUnknown(     const string & name,
                        const string & location,
                        const string & creation,
                        const string & owner,
                        unsigned int size,
                        const string & extension) :  CFile(name,
                                                        location,
                                                        creation,
                                                        owner,
                                                        size),
                                                  extension(extension)
{
}

CUnknown::CUnknown( const CUnknown & pattern ) : CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                              extension(pattern.extension)
{
}

CFile * CUnknown::clone() const{
  CUnknown * clone = new CUnknown(*this);
  return clone;
}

string CUnknown::getFullName()const{
  return (name + extension);
}



string CUnknown::getType() const{
  return "Unknown file";
}


void CUnknown::printCFile()
{
  cout << "?  " << name<<extension;
}
