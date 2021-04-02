/**
  @file CText.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/
#include "CText.hpp"
using namespace std;


CText::CText( const string & name,
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

CText::CText( const CText & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                              extension(pattern.extension)
{
}

CFile * CText::clone() const{
  CText * clone = new CText(*this);
  return clone;
}

string CText::getFullName()const{
  return (name + extension);
}

string CText::getType() const{
  return "Text file";
}

void CText::printCFile()
{
  cout << "#  " << name<<extension;
}
