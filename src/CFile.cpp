/**
  @file CFile.cpp
  Purpose: Declaration of CFile method and functions working with them

  @author David Omrai
  @version 1.0
  @date 21/05/2019
*/
#include "CFile.hpp"
using namespace std;

CFile::CFile( const string & name,
              const string & location,
              const string & creation,
              const string & owner,
              unsigned int size) :  name(name), location(location),
                                    creation(creation), owner(owner), size(size)
{
}

string CFile::getName() const{
  return name;
}

string CFile::getCreation() const{
  return creation;
}

string CFile::getLocation() const{
  return location;
}

string CFile::getOwner() const{
  return owner;
}

unsigned int CFile::getSize() const{
  return size;
}
