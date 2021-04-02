/**
  @file CAudio.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CAudio.hpp"
using namespace std;


CAudio::CAudio( const string & name,
                const string & location,
                const string & creation,
                const string & owner,
                unsigned int size,
                const string & extension) :     CFile(name,
                                                      location,
                                                      creation,
                                                      owner,
                                                      size),
                                                      extension(extension)
{
}

CAudio::CAudio( const CAudio & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                                    extension(pattern.extension)
{
}

CFile * CAudio::clone() const{
  CAudio * clone = new CAudio(*this);
  return clone;
}

string CAudio::getFullName()const{
  return (name + extension);
}

string CAudio::getType() const{
  return "Audio file";
}

void CAudio::printCFile()
{
  cout << "~  " << name<<extension;
}
