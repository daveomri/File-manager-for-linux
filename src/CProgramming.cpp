/**
  @file CProgramming.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CProgramming.hpp"
using namespace std;



CProgramming::CProgramming( const string & name,
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

CProgramming::CProgramming( const CProgramming & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                              extension(pattern.extension)
{
}

CFile * CProgramming::clone() const{
  CProgramming  * clone = new CProgramming (*this);
  return clone;
}



string CProgramming::getFullName()const{
  return (name + extension);
}

string CProgramming::getType() const{
  return "Programming file";
}

void CProgramming::printCFile()
{
  cout << "°  " << name<<extension;
}
