/**
  @file CController.hpp

  @author David Omrai
  @version 1.0
  @date 21/05/2019
*/
#pragma  once
#include <iostream>
#include "CData.hpp"
using namespace std;

/**
      \section CController class
      This class makes interface between user and filesystem, all commands that user type are send to this class and based on them
      this class may sends tasks to CData class to work with filesystem. Besides this comunation, this class also offers methods to
      make text user interface in modes as copy, move etc.. This class allocates in constructor CData class and dealocates it in destructor.

*/
class CController{
  public:
    /**
        Class contructor loads terminal proporces and save rows and columns to variables,
        also sets variables oldRows and oldColumns, these variables are use in program
        to indicate, if user changed terminal size.
        Variables contentFrom and contentTo indicates awailable rows in terminal, where
        the content of file is printed.
        Variable numberFiles will later saves number of files in directory, but now is set
        to zero.


        @returns None
    */
    CController         ();
    /**
        Class destructor deletes alocated CData class.


        @returns None
    */
    ~CController        ();

    /**
        Method setTerminalSize loads the proportions of terminal, where output is printed.
        It's using structure winsize and function ioctl() from sys/ioctl.h library.


        @returns None
    */
    void            setTerminalSize();
    /**
        Method tests if user changed size of terminal window by comparing oldRows and rows


        @returns True if oldRows == rows, false otherwise.
    */
    bool            testTerminalSize()const;
    /**
        Method sets new value of rows and columns of terminal window to oldRows and
        newRows variables.
        Method also sets contentTo and contentFrom variables for indication where
        will be output printed.


        @returns None
    */
    void            setNewTeminalSize();
    /**
        This is basic get method returning value of rows variable.


        @returns Integer value of rows variable.
    */
    int             getRows()const;
    /**
        Method clear content from terminal by printing "\n" rows times,
        rows variable represents terminal rows.


        @returns None
    */
    void            clearScrean()const;
    /**
        Method moves text in terminal by printing "\n".
        Method prints "\n" (lastFileIndex-contentTo) times,
        value of this suma is index of last printed item in current print,
        contentTo is genericly increasing/decreasing index of last item in vector,
        contentFrom is genericly increasing/decreasing index of first item in current print.

        Method also checks if contentTo is not larger then last index of vector,
        if it is, then lastFileIndex is set to last vector index + 1, last index is not printed.


        @returns None
    */
    void            moveText()const;
    /**
        Method calls methods of CData class to loads current directory files into directory vector.

        @param dirName Name of directory to save its content.
        @returns None.
    */
    void            loadFiles( const string & dirName);
    /**
        Method calls CData method to print current directory files.


        @returns None
    */
    void            printCon();
    /**
        Method sets new indexes for next page, moves from and to indexes of printed files.


        @returns None
    */
    void            nextPage();
    /**
        Method sets new indexes for previous page, moves from and to indexes of printed files.


        @returns None
    */
    void            prevPage();
    /**
        Method checks if whole content can be displayed in terminal,
        if not then it adds possible listing through this content.
        Before this method is control panel printed to terminal,
        |   control pane  ||         Listing          |
        \\1|..| ... \\n|..| \\n+1|Previous| \\n+2|Next|


        @returns None
    */
    void            swipeCon( int codePre, int codeNe )const;

    /**
        Method cleans info vector, where are stored information about file


        @returns None
    */
    void            cleanInfo();
    /**
        Method checks if file given by it's name is in dirContent vector
        (there are stored files from current directory)

        @param fileName Name of searching file.
        @returns True if file is in vector, false otherwise.
    */
    bool            fileInDir( const string & fileName )const;
    /**
        Method loads information about given file, stored in dirContent vector, to fileInfo vector

        @param fileName Name of file to store its info.
        @returns True if file exists and was stored, false if file is not stored in vector
    */
    bool            loadFileInfoDir( const string & fileName );
    /**
        Method loads information about given file, stored in copyContent vector, to fileInfo vector

        @param fileName Name of file to store its info.
        @returns true if file exists in copyContent vector, false otherwise.
    */
    bool            loadFileInfoCopy( const string & fileName );
    /**
        Method loads information about given file, stored in moveContent vector, to fileInfo vector

        @param fileName Name of file to store its info
        @returns true if file exists in moveContent vector, false otherwise
    */
    bool            loadFileInfoMove( const string & fileName );

    /**
        Method creates information page by setting and printing all neccesarry things.
        If size of window is smaller then freeRows, that's constant representing number of
        columns reserved for program, then it asks user to resize window.

        @param message Contains message for user, telling what to do, or in what mode he is.
        @param commands Contains all possible commands for user to enter.
        @param prevPage Number representing Previous page command.
        @param nextPage Number representing Next page command.
        @returns None
    */
    void            infoMode( const string & message, const string & commands, int prevPage, int nextPage);
    /**
        Method creates rename mode page by setting and printing all neccesarry things.
        This method is a first phase of renaming file, where user select file from directory

        @param message Contains message for user, telling what to do, or in what mode he is.
        @param commands Contains all possible commands for user to enter.
        @param prevPage Number representing Previous page command.
        @param nextPage Number representing Next page command.
        @returns None
    */
    void            renameModeSelect(const string & message, const string & commands, int prevPage, int nextPage);
    /**
        Method creates rename mode page by setting and printing all neccesarry things.
        This method is a second phase of renaming file, where user enter new file name

        @param message Contains message for user, telling what to do, or in what mode he is.
        @param commands Contains all possible commands for user to enter.
        @param prevPage Number representing Previous page command.
        @param nextPage Number representing Next page command.
        @returns None
    */
    void            renameModeConfirm( const string & message, const string & commands, int nextPage, int prevPage );
    /**
        Method changes previous file name to new one

        @param prevName Name representing file.
        @param newName New name for file.
        @returns true If file could be renamed, false otherwise.
    */
    bool            renameFile(const string & prevName, const string & newName);
    /**
        Method creates message page by setting and printing all neccesarry things.
        This method prints message page with given message.

        @param message Contains message for user, telling what to do, or in what mode he is.
        @returns None
    */
    void            printMessage(const string & message);
    /**
        Method deletes given file by file name or regular expresion.

        @param input Represents name of file or regular expresion.
        @param regExp Indicates if input parameter is name of file or regular expresion.
        @param errFiles Program saves files, that can't be deleted to this string.

        @returns True if all file/s is/are deleted, false otherwise.
    */
    bool            deleteFile( const string & input, bool regExp, string & errFiles );
    /**
        Method extracts file names from string and saves it to inputFiles vector

        @param input Input string containing none, one or more filenames.
        @returns vector<string> This vector contains extracted files.
    */
    vector<string>  extractInputFiles( const string & input );
    /**
        Method creates file given by name.

        @param fileName Name of file to create.
        @returns True if file is created, false otherwise.
    */
    bool            createFile(const string & fileName);
    /**
        Method creates directory given by name.

        @param dirName Name of directory to create.
        @returns True if directory is created, false otherwise.
    */
    bool            createDir(const string & dirName);
    /**
        Method creates link given by name.

        @param linkName Name of link to create.
        @param linkPath Path of link, where it points to.
        @returns True if link is created, false otherwise.
    */
    bool            createLink(const string & linkName, const string & linkPath);
    /**
        Method creates template for mode pages by setting and printing all neccesarry things.
        This method prints directory content, given message and given control panel.

        @param message Contains message for user, telling what to do, or in what mode he is.
        @param commands Contains all possible commands for user to enter.
        @param prevPage Number representing Previous page command.
        @param nextPage Number representing Next page command.
        @returns None
    */
    void            templateFilesMode( const string & message, const string & commands, int prevPage, int nextPage);
    /**
        Method cleans vector containing files to copy.


        @returns None
    */
    void            clearCopy();
    /**
        Method cleans vector containing files to move.


        @returns None
    */
    void            clearMove();
    /**
        Method prints files in vector that contains files to move.


        @returns None
    */
    void            printMove();
    /**
        Method prints files in vector that contains files to copy.


        @returns None
    */
    void            printCopy();
    /**
        Method creates pages for showing files to copy by setting and printing all neccesarry things.

        @param message Contains message for user, telling what to do, or in what mode he is.
        @param commands Contains all possible commands for user to enter.
        @param prevPage Number representing Previous page command.
        @param nextPage Number representing Next page command.
        @returns None
    */
    void            showCopy( const string & message, const string & commands, int prevPage, int nextPage );
    /**
        Method creates page for showing files to move by setting and printing all neccesarry things.

        @param message Contains message for user, telling what to do, or in what mode he is.
        @param commands Contains all possible commands for user to enter.
        @param prevPage Number representing Previous page command.
        @param nextPage Number representing Next page command.
        @returns None
    */
    void            showMove( const string & message, const string & commands, int prevPage, int nextPage );
    /**
        Method saves file/s passed by fileName or regular expresion to copy vector.

        @param fileName Represents name of file or regular expresion.
        @param regExp Indicates if regular expresion is passed.
        @returns True if copy could be copied, false otherwise.
    */
    bool            copyFile( const string & fileName, bool regExp );
    /**
        Method saves file/s passed by fileName or regular expresion to move vector.

        @param fileName Represents name of file or regular expresion.
        @param regExp Indicates if regular expresion is passed.
        @returns True if copy could be copied, false otherwise.
    */
    bool            moveFile( const string & fileName, bool regExp );
    /**
        Method finishes copying files and then clean copy vector.

        @param errMes Files that couldn't be copied are saved here.
        @returns True if all files were copied, false otherwise.
    */
    bool            copyFiles( string & errMes );
    /**
        Method finishes moving files and then clean copy vector.

        @param errMes Files that couldn't be copied are saved here.
        @returns True if all files were copied, false otherwise.
    */
    bool            moveFiles( string & errMes);
    /**
        Method returns full path of current directory.


        @returns None
    */
    string          gcw();
    /**
        Method changes current working directory.

        @param dirName Name of directory.
        @returns True if directory is changed, false otherwise.
    */
    bool            changeCurDir( const string & dirName );

  private:
    CData *             fileSys;/*!< Pointer to new CData class */

    int             rows;/*!< Rows of terminal window */

    int             columns;/*!< Columns of terminal window */

    int             oldRows;/*!< Contains value of rows variable */

    int             oldColumns;/*!< Contains value of columns variable */

    int             itemsNumber;/*!< Number of items to be printed */

    int             contentFrom;/*!< Index of first item to be printed from vector */

    int             contentTo;/*!< Index of last item to be printed from vector */

    int             numberFiles;/*!< Number of files in directorys */
};
