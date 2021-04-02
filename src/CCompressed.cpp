/**
  @file CCompressed.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CCompressed.hpp"
using namespace std;



CCompressed::CCompressed( const string & name,
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

CCompressed::CCompressed( const CCompressed & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                              extension(pattern.extension)
{
}

CFile * CCompressed::clone() const{
  CCompressed * clone = new CCompressed(*this);
  return clone;
}

string CCompressed::getFullName()const{
  return (name + extension);
}

string CCompressed::getType() const{
  return "Compressed file";
}

void CCompressed::printCFile()
{
  cout << "$  " << name<<extension;
}
