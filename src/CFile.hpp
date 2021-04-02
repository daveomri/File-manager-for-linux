/**
  @file CFile.hpp

  @author David Omrai
  @version 1.0
  @date 21/05/2019
*/
#pragma  once
#include <iostream>
#include <string>
using namespace std;

/**
      \section CFile class
      This class represents file in filesystem. All it's methods are just for printing informations about file this calss represents.
*/
class CFile{
  public:
    /**
        Class constructor.

        @param name File name.
        @param location File location.
        @param creation File creation date and time.
        @param owner File owner.
        @param size File size.
        @returns None
    */
    CFile(const string &  name,
          const string &  location,
          const string &  creation,
          const string &  owner,
          unsigned int    size);
    /**
        Virtual destructor.


        @returns None
    */
    virtual ~CFile          () = default;
    /**
        Method prints file type and name.


        @returns None
    */
    virtual void             printCFile() = 0;
    /**
        Method returns type of file.


        @returns Type of file.
    */
    virtual string            getType() const = 0;
    /**
        Method clones itself.


        @returns CFile subclass.
    */
    virtual CFile *           clone() const = 0;
    /**
        Method returns full name of file, containing name and extension.


        @returns Full name of file, name + extension.
    */
    virtual string            getFullName()const = 0;

    /**
        Method returns file name.


        @returns Name of file.
    */
    string                    getName() const;
    /**
        Method returns file creation date.


        @returns Creation date of file.
    */
    string                    getCreation() const;
    /**
        Method returns file location.


        @returns Location of file.
    */
    string                    getLocation() const;
    /**
        Method returns file owner.


        @returns Name of owner.
    */
    string                    getOwner() const;
    /**
        Method returns file size.


        @returns Size of file.
    */
    unsigned int              getSize() const;

  protected:
    string                    name; /*!< Name of file */

    string                    location;/*!< Location of file */

    string                    creation;/*!< Creation of file */

    string                    owner;/*!< Owner of file */

    unsigned int              size;/*!< Size of file */
};
