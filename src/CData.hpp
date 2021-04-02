/**
  @file CData.hpp

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/
#pragma  once
#include "CAudio.hpp"
#include "CCompressed.hpp"
#include "CDatabase.hpp"
#include "CDiskMedia.hpp"
#include "CExe.hpp"
#include "CFolder.hpp"
#include "CLink.hpp"
#include "CPhoto.hpp"
#include "CProgramming.hpp"
#include "CText.hpp"
#include "CVideo.hpp"
#include "CUnknown.hpp"
#include <vector>
using namespace std;

/**
    \section CData class
    This class offers works directly with filesystem. It contains methods to create file, directories or links, and also methods to delete these files.
    This class saves files as CFile clases, also saved some of informations about these files in this class. File can be classified as directory, link or regular file.
    This classification is being make by three methods in this class.
*/
class CData{
  public:
    /**
        Basic class constructor.

        @returns None
    */
    CData         ();
    /**
        Class destructor deallocate allocated memory of vectors.

        @returns None
    */
    ~CData        ();
    /**
        Method sends file extension to compare with vector containing photo extensions.
        Comparison is being make by isIn(...) method.

        @param extension String representation of file extension.
        @returns True if extension is photo format, false otherwise.
    */
    bool          isPhoto(const string & extension );
    /**
        Method sends file extension to compare with vector containing text extensions.
        Comparison is being make by isIn(...) method.

        @param extension String representation of file extension.
        @returns True if extension is text format, false otherwise.
    */
    bool          isText(const string & extension );
    /**
        Method sends file extension to compare with vector containing video extensions.
        Comparison is being make by isIn(...) method.

        @param extension String representation of file extension.
        @returns True if extension is video format, false otherwise.
    */
    bool          isVideo(const string & extension );
    /**
        Method sends file extension to compare with vector containing audio extensions.
        Comparison is being make by isIn(...) method.

        @param extension String representation of file extension.
        @returns True if extension is audio format, false otherwise.
    */
    bool          isAudio(const string & extension );
    /**
        Method sends file extension to compare with vector containing compressed extensions.
        Comparison is being make by isIn(...) method.

        @param extension String representation of file extension.
        @returns True if extension is compressed format, false otherwise.
    */
    bool           isCompressed(const string & extension );
    /**
        Method sends file extension to compare with vector containing disk-media extensions.
        Comparison is being make by isIn(...) method.

        @param extension String representation of file extension.
        @returns True if extension is disk-media format, false otherwise.
    */
    bool           isDiskMedia(const string & extension );
    /**
        Method sends file extension to compare with vector containing database extensions.
        Comparison is being make by isIn(...) method.

        @param extension String representation of file extension.
        @returns True if extension is database format, false otherwise.
    */
    bool           isDatabase(const string & extension);
    /**
        Method sends file extension to compare with vector containing executable extensions.
        Comparison is being make by isIn(...) method.

        @param extension String representation of file extension.
        @returns True if extension is execution format, false otherwise.
    */
    bool           isExe(const string & extension );
    /**
        Method sends file extension to compare with vector containing programming extensions.
        Comparison is being make by isIn(...) method.

        @param extension String representation of file extension.
        @returns True if extension is programming format, false otherwise.
    */
    bool           isProgramming(const string & extension );
    /**
        Method searches for extension in given vector.

        @param extension String representation of file extension.
        @param extensionVector Vector where is extension searched.
        @returns True if extension is in vector, false otherwise.
    */
    bool          isIn(const string & extension, const vector<string> & extensionVector);
    /**
        Method loads files from given directory and saves them into dirContent vector.
        In this method is also being determinate type of file, and saved by it to vector.

        @param dirName Name of directory which content is saved in vector.
        @returns None
    */
    void          loadFiles( const string & dirName);
    /**
        Method searches for given file in dirContent vector, if it's there, then it loads file
        information to fileInfo vector.

        @param fileName Name of searching file.
        @returns True if the file is in vector, false otherwise.
    */
    bool          loadFileInfoDir  ( const string & fileName );
    /**
        Method searches for given file in copyContent vector, if it's there, then it loads file
        information to fileInfo vector.

        @param fileName Name of searching file.
        @returns True if the file is in vector, false otherwise.
    */
    bool          loadFileInfoCopy ( const string & fileName );
    /**
        Method searches for given file in moveContent vector, if it's there, then it loads file
        information to fileInfo vector.

        @param fileName Name of searching file.
        @returns True if the file is in vector, false otherwise.
    */
    bool          loadFileInfoMove ( const string & fileName );
    /**
        Method loads information about file to fileInfo vector, this vector is used to print these informations.

        @param file This CFile class given by pointer represents file from vector.
        @returns None
    */
    void          loadInfo( const CFile * file );
    /**
        Method prints fileInfo vector content.

        @param from Number representing beginning index, from where program wants print content.
        @param to Number representing ending index of printed content of fileInfo vector.
    */
    void          printInfo( size_t from, size_t to );
    /**
        Method simply cleans fileInfo vector.


        @returns None
    */
    void          cleanInfo();
    /**
        Method deletes files that match with given regular expresion.

        @param input Regular expresion.
        @param errFiles All files that matches with regular expresion but couldn't be deleted are stored here.
        @returns False if some files couldn't be deleted or if regular expresion has a wrong format,
                 True if file/s is/are successfuly deleted.
    */
    bool         regDeleteFile(const string & input, string & errFiles);
    /**
        Method deletes file that matches with given name.

        @param input Name of file.
        @returns False if the file couldn't be deleted,
                 True if the file is successfuly deleted.
    */
    bool          norDeleteFile(const string & input);
    /**
        Method returns file creation date.

        @param fileName Name of file.
        @returns String containing nothing if reading of date was unsuccessful, creation date otherwise.
    */
    string        getCreationDate ( const string & fileName);
    /**
        Method returns name of file, that's given by filename.

        @param fileName Name of file.
        @returns Nothing is reading of owner from file was unsuccessful, owner name otherwise.
    */
    string        getFileOwner ( const string & fileName);
    /**
        Method creates direcotry named by given name.

        @param dirName Name of directory.
        @returns True if directory could be created, False otherwise.
    */
    bool           createDir( const string & dirName );
    /**
        Method creates file named by given name.

        @param fileName Name of file.
        @returns True if file could be created, false otherwise.
    */
    bool           createFile(const string & fileName);
    /**
        Method creates link named by given name.

        @param linkName Name of file.
        @param linkPath Path where link points.
        @returns True if link could be created, false otherwise.
    */
    bool           createLink(const string & linkName, const string & linkPath);
    /**
        Method renames file by given name.

        @param prevName Represents file.
        @param newName Represents new file name.
    */
    bool           renameFile( const string & prevName, const string & newName );
    /**
        Method copies whole directory to a target directory.
        Directory content is recursively copied to a target directory.

        @param sourceDir Source directory.
        @param targetDir Target directory.
        @returns True if file could be copied, false otherwise.
    */
    bool           copyDirFiles( const string & sourceDir, const string & targetDir );
    /**
        Method copies all files that are stored in moveContent vector.

        @param errMes All files that couldn't be copied are stored here.
        @returns None.
    */
    void           copyMoveContent( string & errMes );
    /**
        Method copies all files that are stored in copyContent vector.

        @param errMes All files that couldn't be copied are stored here.
        @returns None.
    */
    void           copyCopyContent( string & errMes );
    /**
        Method finishes moving files by deleting them from source,
        files are stored in moveContent vector.

        @param errMes All files that couldn't be copied are stored here.
        @returns None.
    */
    void           deleteMoveContent(string & errMes);
    /**
        Method returns size of dirContent vector.


        @returns Size of dirContent vector
    */
    int           getDirContentSize();
    /**
        Method returns size of copyContent vector.


        @returns Size of copyContent vector
    */
    int           getCopyContentSize();
    /**
        Method returns size of moveContent vector.


        @returns Size of moveContent vector
    */
    int           getMoveContentSize();
    /**
        Method changes curent directory to a given one.

        @param newCurDir New curent directory.
        @returns True if firectory is changed, false otherwise.
    */
    bool          changeCurDir(const string & newCurDir);
    /**
        Method returns curDir variable.


        @returns None
    */
    string        getCurDir() const;
    /**
        Method adds a given file to dirContent vector.

        @param newFile New file passed to vector.
        @returns None
    */
    void          addFile( const CFile & newFile );
    /**
        Method test presence of file in dirContent vector.

        @param fileName Name of file.
        @returns True if the file is in vector, false otherwise.
    */
    bool          fileInDir( const string & fileName );
    /**
        Method adds to copyContent files, that match with given regular expresion.

        @param newFile Regular expresion.
        @returns False if regular expresion is incorrect, true otherwise.
    */
    bool          regAddCopyFile( const string & newFile );
    /**
        Method adds given file to copyContent vector.

        @param newFile Name of file.
        @returns None
    */
    void          norAddCopyFile( const string & newFile );
    /**
        Method adds to moveContent files, that match with given regular expresion.

        @param newFile Regular expresion.
        @returns False if regular expresion is incorrect, true otherwise.
    */
    bool          regAddMoveFile( const string & newFile );
    /**
        Method adds given file to moveContent vector.

        @param newFile Name of file.
        @returns None
    */
    void          norAddMoveFile( const string & newFile );
    /**
        Method cleans dirContent vector.


        @returns None
    */
    void          cleanFiles();
    /**
        Method cleans copyContent vector.


        @returns None
    */
    void          cleanCopy();
    /**
        Method cleans moveContent vector.


        @returns None
    */
    void          cleanMove();
    /**
        Method finds file given by name in given vector.

        @param fileName Name of the file.
        @param vecContent Vector where is file searched.
        @returns Null if no file i found, address of file otherwise.
    */
    CFile *       findFile( const string & fileName, vector<CFile*> &vecContent ) const;
    /**
        Method sorts dirContent vector by name.


        @returns None
    */
    void          sortByName();
    /**
        Method sorts dirContent vector by size.


        @returns None
    */
    void          sortBySize();
    /**
        Method sorts dirContent vector by date of creation.


        @returns None
    */
    void          sortByDate();
    /**
        Method prints files stored in dirContent vector.

        @param from Print from this index.
        @param to Print to this index.
        @returns None
    */
    void          printFiles(size_t from, size_t to);
    /**
        Method prints files stored in copyContent vector.

        @param from Print from this index.
        @param to Print to this index.
        @returns None
    */
    void          printCopy(size_t from, size_t to);
    /**
        Method prints files stored in moveContent vector.

        @param from Print from this index.
        @param to Print to this index.
        @returns None
    */
    void          printMove(size_t from, size_t to);

    /**
        Method sorts items in dirContent vector by given function.

        @param compare Function for comparisment.
        @returns None
    */
    template      <class _T>
    void          sortFiles( _T compare );
    /**
        Method returns full path of current directory.


        @returns None
    */
    string gcw();
  private:

    vector<string>  photoextension =        {".jpg", ".png", ".gif", ".tiff", ".raw", ".ai",
                                         ".bmp", ".ico", ".jpeg", ".ps", ".psd", ".svg",
                                         ".tif",}; /*!< Extension of photo files */

    vector<string>  textextension =         {".doc", ".odt", ".pdf", ".rtf", ".tex", ".txt",
                                         ".wks", ".wps", ".wpd"}; /*!< Extension of text files */

    vector<string>  videoextension =        {".3g2", ".3qp", ".avi", ".flv", ".h264",
                                         ".m4v", ".mkv", ".mov", ".mp4", ".mpg",
                                         ".mpeg", ".rm", ".swf", ".vob", ".wmv"}; /*!< Extension of video files */

    vector<string>  audioextension =        {".aif", ".cda", ".mid", ".midi", ".mp3",
                                         ".mpa", ".ogg", ".wav", ".wma", ".wpl"}; /*!< Extension of audio files */

    vector<string>  compressedextension =   {".7z", ".arj", ".deb", ".pkg", ".rar",
                                         ".rpm", ".tar.gz", ".z", ".zip"}; /*!< Extension of compressedextension files */

    vector<string>  diskMediaextension =    {".bin", ".dmg", ".iso", ".toast", ".vcd", ".conf", ".cfg",
                                         ".config", ".lock", ".mime", ".dll", ".inf", ".o"}; /*!< Extension of diskmedia files */

    vector<string>  databaseextension =     {".csv", ".dat", ".db", ".dbf", ".log", ".mdb",
                                         ".sav", ".sql", ".tar", ".xml"}; /*!< Extension of database files */

    vector<string>  exeextension =          {".apk", ".bat", ".bin", ".cgi", ".pl",
                                         ".com", ".exe", ".gadget", ".jar", ".wsf"}; /*!< Extension of executable files */

    vector<string>  programmingextension =  {".c", ".class", ".cpp", ".hpp", ".cs", ".h", ".java",
                                         ".sh", ".swift", ".vb", ".py", ".asp", ".aspx",
                                         ".cer", ".cfm", ".css", ".htm", ".html", ".js",
                                         ".jsp", ".part", ".php", ".rss", ".xhtml", ".d"}; /*!< Extension of programming files */

    string          curDir; /*!< Curent directory */

    vector <CFile*> dirContent; /*!< Files from current directory */

    vector <CFile*> copyContent; /*!< Items to be copied */

    vector <CFile*> moveContent; /*!< Items to be moved */

    vector <string> fileInfo; /*!< File informations */
};
