/**
  @file CPhoto.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CPhoto.hpp"
using namespace std;


CPhoto::CPhoto( const string & name,
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

CPhoto::CPhoto( const CPhoto & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                              extension(pattern.extension)
{
}

CFile * CPhoto::clone() const{
  CPhoto * clone = new CPhoto(*this);
  return clone;
}


string CPhoto::getFullName()const{
  return (name + extension);
}


string CPhoto::getType() const{
  return "Photo file";
}


void CPhoto::printCFile()
{
  cout << "*  " << name<<extension;
}
