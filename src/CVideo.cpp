/**
  @file CVideo.cpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

#include "CVideo.hpp"
using namespace std;

CVideo::CVideo( const string & name,
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

CVideo::CVideo( const CVideo & pattern ) :       CFile(pattern.name,
                                                    pattern.location,
                                                    pattern.creation,
                                                    pattern.owner,
                                                    pattern.size),
                                              extension(pattern.extension)
{
}

CFile * CVideo::clone() const{
  CVideo * clone = new CVideo(*this);
  return clone;
}

string CVideo::getFullName()const{
  return (name + extension);
}

string CVideo::getType() const{
  return "Video file";
}

void CVideo::printCFile()
{
  cout << "@  " << name<<extension;
}
