/**
  @file CExe.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CExe.hpp"
using namespace std;


CExe::CExe( const string & name,
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

CExe::CExe( const CExe & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                              extension(pattern.extension)
{
}

CFile * CExe::clone() const{
  CExe * clone = new CExe(*this);
  return clone;
}
string CExe::getFullName()const{
  return (name + extension);
}


string CExe::getType() const{
  return "Executable file";
}

void CExe::printCFile()
{
  cout << "<) " << name<<extension;
}
