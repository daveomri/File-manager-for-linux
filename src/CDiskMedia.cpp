/**
  @file CDiskMedia.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CDiskMedia.hpp"
using namespace std;


CDiskMedia::CDiskMedia( const string & name,
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

CDiskMedia::CDiskMedia( const CDiskMedia & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                              extension(pattern.extension)
{
}

CFile * CDiskMedia::clone() const{
  CDiskMedia * clone = new CDiskMedia(*this);
  return clone;
}

string CDiskMedia::getFullName()const{
  return (name + extension);
}

string CDiskMedia::getType() const{
  return "Disk-Media file";
}


void CDiskMedia::printCFile()
{
  cout << "<> " << name<<extension;
}
