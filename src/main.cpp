/**
  File Manager
  @file main.cpp
  \mainpage File Manager
  \section Purpose
  This program allows user to walk through filesystem and make basic tasks as creating and deleting files, directories and links.
  Moving, copying and renaming files. All these tasks can user make just by typing commands into terminal. There are two types of
  commands. First ones are those from command panel. These are construct from character '\'+number. I used this character so my commands
  are not missunderstood as second type of commands. This second type of commands are just names of files printed in terminal window.
  If user type name of directory, program will change the current directory. If user enters name of file, program will show basic informations
  about this file.

  \section Deleting_files
  By entering a name of file, or names of files, or regular expressiong, program tries to delete this file. If some problem occours, a message will show up.
  In this mode, if name of file contains space, then use '\' to inform the program. User can type more than one file to delete in a row
  separated by spaces.

  \section Creating_files
  Be entering a name of file, or files, program will try to create them. If he fails, a message with list of files will shows up. If name of file contains spaces,
  use character '\' before them. User can type more than one file in a row, separated by space.

  \section Copying_files
  By entering a name, or names of files, or regular expresion, program will save them into copying vector, where these files rest until user pastes them to some directory.
  User can clear copying vector and also view it and see the files informations in this vector by typing their names. If some problem occours, a message with list of files will shows up.

  \section Moving_files
  By entering a name, or names of files, or regular expression, program will save them into moving vector, where these files rest until user pastes them to some directory,
  and then program will delete these files from source directory. User can also clears this vector, see it and see file info of files in this vector. If some problem occours, a message with list of files will shows up.

  \section Renaming_files
  User enters name of file, then a new name, and program will try to rename this file. If it fails, a message will shows up.

  @author David Omrai
  @version 1.0
  @date 21/5/2019
*/
#include "CController.hpp"
using namespace std;


/**
    Function translates string command to integer.

    @param command String containing command.
    @param maxCodeNum Represents maximal posible code number.
    @returns False if user wants to quit, true otherwise.
*/
int getCommandCode( const string & command, int maxCodeNum ){
  string tmp = "\\";
  if (command.length() > 2)
    return -1;
  for (int i = 0; i <= maxCodeNum; i++ ){
    if ( command == (tmp + (char)(i+'0')) )
      return i;
  }
  return -1;
}

/**
    Function print-message-mode prints and shows given message.

    @param progCont Interface between user and filesystem.
    @param message Message to show.
    @returns False if user wants to quit, true otherwise.
*/
bool printMessage(CController & progCont, const string & message){
  int commandCode = 0;
  string input;

  const int backC = 1;
  const int quitC = 2;
  const int numCom = 2;

  while (true){
    progCont.printMessage(message);
    getline(cin, input);
    if (cin.eof() || cin.bad())
      return false;
    commandCode = getCommandCode(input, numCom);
    switch(commandCode){
      case backC: return true;
      case quitC: return false;
    }
  }
}

/**
    Function info-mode shows informations of file.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool infoMode( CController & progCont ){
  string input;
  int commandCode = 1;

  const int backC   = 1;
  const int quitC   = 2;
  const int prevC   = 3;
  const int nextC   = 4;
  const int numCom  = 4;
  const string message = "File Information";
  const string commands = "\\1|Back| \\2|Quit|";

  progCont.setNewTeminalSize();

  while (commandCode!=quitC){
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() ){
      progCont.setNewTeminalSize();
    }

    progCont.infoMode( message, commands, prevC, nextC );

    getline(cin, input);
    if (cin.eof() || cin.bad()){
      progCont.cleanInfo();
      return false;
    }

    commandCode = getCommandCode(input, numCom );
    switch ( commandCode ){
      case backC: progCont.cleanInfo(); return true;
      case quitC: progCont.cleanInfo(); return false;
      case prevC: progCont.prevPage(); break;
      case nextC: progCont.nextPage(); break;
    }
  }
  return false;
}

/**
    Function paste-mode copies files from copy and move vectors to current directory,
    and delete files that are being moved.
    Files that can't be moved are printed.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool pasteMode( CController & progCont ){
  string errMes = "";
  if (!progCont.copyFiles(errMes))
    if (!printMessage(progCont, "File/s"+errMes+"could't be copied."))
      return false;
  if (!progCont.moveFiles(errMes))
    if (!printMessage(progCont, "File/s"+errMes+"could't be moved."))
      return false;
  return true;
}

/**
    Function show-copy-mode shows files to move,
    user can also in this mode access file informations.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool showMove( CController & progCont ){
  int commandCode = 0;
  string input;

  const int backC = 1;
  const int quitC = 2;
  const int prevC = 3;
  const int nextC = 4;
  const int numCom = 4;
  const string message = "Files to move";
  const string commands = "\\1|Back| \\2|Quit|";

  progCont.setNewTeminalSize();

  while (commandCode!=quitC){
    progCont.showMove(message, commands, prevC, nextC);

    getline(cin, input);
    if (cin.eof() || cin.bad())
      return false;
    commandCode = getCommandCode(input, numCom);
    if ( commandCode == -1 )
      if ( progCont.loadFileInfoMove( input ))
        if (!infoMode(progCont))
          commandCode = quitC;


    switch(commandCode){
      case backC: return true;
      case quitC: return false;
      case prevC: progCont.prevPage(); break;
      case nextC: progCont.nextPage(); break;
    }
  }
  return false;
}


/**
    Function copy-mode leads user through copying of files, dirs or links.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool moveMode( CController & progCont ){
  string input;
  vector <string> moveFiles;
  int commandCode = 1;
  bool regExp = false;

  const int backC   = 1;
  const int clearC  = 2;
  const int showC   = 3;
  const int quitC   = 4;
  const int regC    = 5;
  const int prevC   = 6;
  const int nextC   = 7;
  const int numCom  = 7;
  const string message = "Enter file/s to move";
  const string commands = "\\1|Back| \\2|Clear| \\3|Show| \\4|Quit|";

  progCont.setNewTeminalSize();

  while (commandCode!=quitC){
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() )
      progCont.setNewTeminalSize();

    progCont.templateFilesMode( message, commands + " \\6|" + ( (regExp)?("Normal"):("Regular") ) + "|", prevC, nextC );

    getline(cin, input);
    if (cin.eof() || cin.bad())
      return false;

    commandCode = getCommandCode(input, numCom);
    if (commandCode == -1){
      moveFiles = progCont.extractInputFiles(input);

      for (auto iter : moveFiles)
        if (!progCont.moveFile(iter, regExp))
          printMessage(progCont, "Regular expresion could not been translated.");

      moveFiles.clear();
    }
    else{
      switch ( commandCode ){
        case backC:   return true;
        case clearC:  progCont.clearMove(); break;
        case showC:   (!showMove(progCont))?(commandCode=quitC):(commandCode=commandCode); break;
        case quitC:   return false;
        case regC:    (regExp)?(regExp=false):(regExp=true); break;
        case prevC:   progCont.prevPage(); break;
        case nextC:   progCont.nextPage(); break;
      }
    }
  }
  return false;
}

/**
    Function show-copy-mode shows files to copy,
    user can also in this mode access file informations

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool showCopy( CController & progCont ){
  int commandCode = 0;
  string input;

  const int backC = 1;
  const int quitC = 2;
  const int prevC = 3;
  const int nextC = 4;
  const int numCom = 4;
  const string message = "Files to copy";
  const string commands = "\\1|Back| \\2||Quit|";

  progCont.setNewTeminalSize();

  while (commandCode!=quitC){
    progCont.showCopy(message, commands, prevC, nextC);

    getline(cin, input);
    if (cin.eof() || cin.bad())
      return false;
    commandCode = getCommandCode(input, numCom);
    if ( commandCode == -1 )
      if ( progCont.loadFileInfoCopy( input ))
        if (!infoMode(progCont))
          commandCode = quitC;

    switch(commandCode){
      case backC: return true;
      case quitC: return false;
      case prevC: progCont.prevPage(); break;
      case nextC: progCont.nextPage(); break;
    }
  }
  return false;
}

/**
    Function copy-mode leads user through copying of files, dirs or links.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool copyMode( CController & progCont ){
  string input;
  vector <string> copyFiles;
  int commandCode = 1;
  bool regExp = false;

  const int backC   = 1;
  const int clearC  = 2;
  const int showC   = 3;
  const int quitC   = 4;
  const int regC    = 5;
  const int prevC   = 6;
  const int nextC   = 7;
  const int numCom  = 7;
  const string message = "Enter file/s to copy";
  const string commands = "\\1|Back| \\2|Clear| \\3|Show| \\4|Quit|";

  progCont.setNewTeminalSize();

  while (commandCode!=quitC){
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() )
      progCont.setNewTeminalSize();

    progCont.templateFilesMode( message, commands + " \\6|" + ( (regExp)?("Normal"):("Regular") ) + "|", prevC, nextC );

    getline(cin, input);
    if (cin.eof() || cin.bad())
      return false;

    commandCode = getCommandCode(input, numCom);
    if (commandCode == -1){
      copyFiles = progCont.extractInputFiles(input);

      for (auto iter : copyFiles)
        if (!progCont.copyFile(iter, regExp))
          printMessage(progCont, "Regular expresion could not been translated.");

      copyFiles.clear();
    }
    else{
      switch ( commandCode ){
        case backC:   return true;
        case clearC:  progCont.clearCopy(); break;
        case showC:   (!showCopy(progCont))?(commandCode=quitC):(commandCode=commandCode); break;
        case quitC:   return false;
        case regC:    (regExp)?(regExp=false):(regExp=true); break;
        case prevC:   progCont.prevPage(); break;
        case nextC:   progCont.nextPage(); break;
      }
    }
  }
  return false;
}


/**
    Function create-file leads user through process to create a file.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool createFile(CController & progCont){
  string input;
  vector <string> crtFiles;
  int commandCode = 1;

  const int backC = 1;
  const int quitC = 2;
  const int prevC = 3;
  const int nextC = 4;
  const int numCom = 4;
  const string message = "Enter file/s to create";
  const string commands = "\\1|Back| \\2|Quit|";


  while (commandCode!=quitC){
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() ){
      progCont.setNewTeminalSize();
    }

    progCont.templateFilesMode( message, commands, prevC, nextC );

    getline(cin, input);
    if (cin.eof() || cin.bad())
      return false;

    commandCode = getCommandCode(input, numCom);
    if (commandCode == -1){
      crtFiles = progCont.extractInputFiles(input);

      for (auto iter : crtFiles)
        if (!progCont.createFile(iter))
          if (!printMessage(progCont, "File "+iter+" could not be created.")){
            commandCode = quitC;
            break;
          }

      crtFiles.clear();
      progCont.loadFiles(progCont.gcw());
    }
    else{
      switch ( commandCode ){
        case backC: return true;
        case quitC: return false;
        case prevC: progCont.prevPage(); break;
        case nextC: progCont.nextPage(); break;
      }
    }
  }
  return false;
}

/**
    Function get-link-mode asks user for link path

    @param progCont Interface between user and filesystem.
    @param linkPath Path of the link, place where it points to.
    @returns False if user wants to quit, true otherwise.
*/
bool getLinkPath(CController & progCont, string & linkPath){
  int commandCode = 0;
  string input;

  const int backC = 1;
  const int quitC = 2;
  const int prevC = 3;
  const int nextC = 4;
  const int numCom = 4;
  const string message = "Enter link path";
  const string commands = "\\1|Back| \\2|Quit|";

  while (true){
    progCont.templateFilesMode( message, commands, prevC, nextC );

    getline(cin, input);
    if (cin.eof() || cin.bad())
      return false;

    commandCode = getCommandCode(input, numCom);
    if (commandCode == -1){
      linkPath = input;
      return true;
    }
    switch(commandCode){
      case backC: return true;
      case quitC: return false;
      case prevC: progCont.prevPage(); break;
      case nextC: progCont.nextPage(); break;
    }
  }
  return false;
}

/**
    Function create-link leads user through creating of links.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool createLink(CController & progCont){
  string linkName = "";
  string linkPath = "";
  int commandCode = 1;

  const int backC = 1;
  const int quitC = 2;
  const int prevC = 3;
  const int nextC = 4;
  const int numCom = 4;
  const string message = "Enter link name";
  const string commands = "\\1|Back| \\2|Quit|";


  while (commandCode!=quitC){
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() ){
      progCont.setNewTeminalSize();
    }

    progCont.templateFilesMode( message, commands, prevC, nextC );

    getline(cin, linkName);
    if (cin.eof() || cin.bad())
      return false;

    commandCode = getCommandCode(linkName, numCom);
    if (commandCode == -1){
      if (!getLinkPath(progCont, linkPath) )
        break;

      if (linkPath != ""){
        if (!progCont.createLink(linkName, linkPath))
          printMessage(progCont, "Link: " + linkName + " -> " + linkPath + ", could not be created.");
        progCont.loadFiles(progCont.gcw());
      }

      linkName = "";
      linkPath = "";
    }
    else{
      switch ( commandCode ){
        case backC: return true;
        case quitC: return false;
        case prevC: progCont.prevPage();  break;
        case nextC: progCont.nextPage(); break;
      }
    }
  }
  return false;
}

/**
    Function create-direcory leads user through process to create a directory.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool createDir(CController & progCont){
  string input;
  vector <string> crtDirs;
  int commandCode = 1;

  const int backC = 1;
  const int quitC = 2;
  const int prevC = 3;
  const int nextC = 4;
  const int numCom = 4;
  const string message = "Enter directory name";
  const string commands = "\\1|Back| \\2|Quit|";


  while (commandCode!=quitC){
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() ){
      progCont.setNewTeminalSize();
    }

    progCont.templateFilesMode( message, commands, prevC, nextC  );

    getline(cin, input);
    if (cin.eof() || cin.bad())
      return false;

    commandCode = getCommandCode(input, numCom);
    if (commandCode == -1){
      crtDirs = progCont.extractInputFiles(input);

      for (auto iter : crtDirs)
        if (!progCont.createDir(iter))
          if (!printMessage(progCont, "Dir "+iter+" could not be created.")){
            commandCode = quitC;
            break;
          }

      crtDirs.clear();
      progCont.loadFiles(progCont.gcw());
    }
    else{
      switch ( commandCode ){
        case backC: return true;  break;
        case quitC: return false; break;
      }
    }
  }
  return false;
}

/**
    Function create-mode leads user through creating of file, dir and links.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to quit, true otherwise.
*/
bool createMode ( CController & progCont ){
  string input;
  int commandCode = 1;

  const int backC   = 1;
  const int fileC   = 2;
  const int dirC    = 3;
  const int linkC   = 4;
  const int quitC   = 5;
  const int prevC   = 6;
  const int nextC   = 7;
  const int numCom  = 7;
  const string & commands = "\\1|Back| \\2|File| \\3|Dir| \\4|Link| \\5|Quit|";
  const string & message = "Create Mode";


  progCont.setNewTeminalSize();

  while (commandCode!=quitC){
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() ){
      progCont.setNewTeminalSize();
    }

    progCont.templateFilesMode( message, commands, prevC, nextC );

    getline(cin, input);
    if (cin.eof() || cin.bad()){
      progCont.cleanInfo();
      return false;
    }

    commandCode = getCommandCode(input, numCom);

      switch ( commandCode ){
        case backC: return true; // back
        case fileC: (!createFile(progCont))?(commandCode = quitC):(commandCode = commandCode); break; // file
        case dirC:  (!createDir(progCont)) ?(commandCode = quitC):(commandCode = commandCode); break; // dir
        case linkC: (!createLink(progCont))?(commandCode = quitC):(commandCode = commandCode); break; // link
        case quitC: return false;
        case prevC: progCont.prevPage(); break; // next
        case nextC: progCont.nextPage(); break; // prev
      }
  }
  return false;
}



/**
    Function  deletes file/s by given name or regular expresion.

    @param progCont Interface between user and filesystem.
    @param fileName Name of file.
    @param regExp True if given fileName is regular expresion, or false if not.
*/
bool deleteFile( CController & progCont, const string & fileName, bool regExp ){
  string errorFiles;
  if ( ! progCont.deleteFile(fileName, regExp, errorFiles) )
    if (!printMessage(progCont, errorFiles))
      return false;
  return true;
}

/**
    Function prints delete-mode page that leads user through deleting files in current directory.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to end program, true otherwise.
*/
bool deleteMode(CController & progCont){
  string input;
  bool regExp = false;
  int commandCode = 1;
  vector <string> filesToDel;

  const int backC   = 1;
  const int quitC   = 2;
  const int modeC   = 3;
  const int prevC   = 4;
  const int nextC   = 5;
  const int numCom  = 5;
  const string message = "Delete File/s";
  const string commands = "\\1|Back| \\2|Quit|";

  progCont.setNewTeminalSize();

  while (commandCode!=quitC){
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() ){
      progCont.setNewTeminalSize();
    }

    progCont.templateFilesMode( message, commands+"\\3|"+( (regExp)?("Regular"):("Normal") )+"|", prevC, nextC );

    getline(cin, input);
    if (cin.eof() || cin.bad()){
      progCont.cleanInfo();
      return false;
    }

    commandCode = getCommandCode(input, numCom);

    if (commandCode == -1){
      filesToDel = progCont.extractInputFiles(input);

      for (auto iter : filesToDel){
        if(!deleteFile(progCont, iter, regExp)){
          filesToDel.clear();
          return false;
        }
      }
      filesToDel.clear();
      progCont.loadFiles(progCont.gcw());
    }
    else{
      switch ( commandCode ){
        case backC: return true;
        case modeC: (regExp==0)?(regExp=1):(regExp=0); break;
        case quitC: return false;
        case prevC: progCont.prevPage(); break;
        case nextC: progCont.nextPage(); break;
      }
    }
  }
  return false;
}

/**
    Function loads which file in directory should be renamed.

    @param progCont Interface between user and filesystem.
    @param prevName Previous name of file.
    @returns False if user wants to quit, true otherwise.
*/
bool renameModeSelect(CController & progCont, string & prevName){
  string input;
  int commandCode = 1;

  const int backC   = 1;
  const int quitC   = 2;
  const int prevC   = 3;
  const int nextC   = 4;
  const int numCom  = 5;
  const string message = "Select File to Rename";
  const string commands = "\\1|Back| \\2|Quit|";

  progCont.setNewTeminalSize();

  while (true){
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() ){
      progCont.setNewTeminalSize();
    }

    progCont.renameModeSelect(message, commands, prevC, nextC);

    getline(cin, input);
    if (cin.eof()){
      progCont.cleanInfo();
      return false;
    }
    else if (cin.bad()){
      progCont.cleanInfo();
      return false;
    }

    commandCode = getCommandCode(input, numCom);

    if (commandCode == -1){
      if (! progCont.fileInDir(input))
        continue;
      prevName = input;
      return true;
    }
    else{
      switch ( commandCode ){
        case backC: progCont.cleanInfo(); return true;
        case quitC: progCont.cleanInfo(); return false;
        case prevC: progCont.prevPage(); break;
        case nextC: progCont.nextPage(); break;
      }
    }
  }
  return false;
}

/**
    Function loads new name of file.

    @param progCont Interface between user and filesystem.
    @param prevName Previous name of file.
    @param newName String where function saves new name of file.
    @returns False if user wants to end program, true otherwise.
*/
bool renameModeConfirm(CController & progCont, const string & prevName, string & newName){
  //User input
  string input;
  //Command
  int commandCode = 1;

  const int backC   = 1; //back to previous mode
  const int quitC   = 2; //quit program
  const int prevC   = 3; //previous page
  const int nextC   = 4; //next page
  const int numCom  = 4; //number of commands
  //Message
  const string message = "Enter new name";
  //Commands
  const string commands = "\\1|Back| \\2|Quit|";

  progCont.setNewTeminalSize();
  progCont.loadFileInfoDir( prevName );

  while (true){
    //Check if terminal window was changed
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() ){
      progCont.setNewTeminalSize();
    }

    progCont.renameModeConfirm(message, commands, prevC, nextC);

    getline(cin, input);
    if (cin.eof()){
      progCont.cleanInfo();
      return false;
    }
    else if (cin.bad()){
      progCont.cleanInfo();
      return false;
    }

    commandCode = getCommandCode(input, numCom);

    if (commandCode == -1){
      if (input=="")
        continue;
      newName = input;
      return true;
    }
    else{
      switch ( commandCode ){
        case backC: return true;
        case quitC: return false;
        case prevC: progCont.prevPage(); break;
        case nextC: progCont.nextPage(); break;
      }
    }
  }
  return false;
}

/**
    Function leads user through renaming process.

    @param progCont Interface between user and filesystem.
    @returns False if user wants to exit program, true otherwise.
*/
bool renameMode(CController & progCont){
  string prevName = "", newName = "";
  string input, message;

  if (!renameModeSelect(progCont, prevName))
    return false;
  if (prevName == "")
    return true;

  if (!renameModeConfirm(progCont, prevName, newName))
    return false;

  progCont.setNewTeminalSize();

  if (progCont.renameFile(prevName, newName))
    message = "File is successfuly renamed.";
  else
    message = "File could not been renamed.";

  progCont.loadFiles(progCont.gcw());

  if (!printMessage(progCont, message))
    return false;
  return true;
}


/**
    Main part of program lies here, user enters input command and this function redirect his demands to other functions.
    CController is interface between user and filesystem.
    This function itself allows user to change directory by typing direcory name to terminal,
    or shows file information by typing file name.
    Besides these two functions user can change mode by entering code composed with '\' + 'number' representing mode in command panel.

    @returns 0 at the end of this function.
*/
int main (void)
{
  //Interface between user and filesystem
  CController progCont;
  //Variable represents command
  int commandCode = 1;
  //User input
  string input = ".";

  const int copyC   = 1; //copy files mode
  const int moveC   = 2; //move files mode
  const int pasteC  = 3; //paste files from move and copy vectors
  const int createC = 4; //create file/direcory/link
  const int deleteC = 5; //delete file/directory/link
  const int renameC = 6; //reaname file/direcory/link
  const int quitC   = 7; //end program
  const int prevC   = 8; //previous page
  const int nextC   = 9; //next page

  const int numCom = 9; //number of commands
  //Command panel
  const string commands = "\\1|Copy| \\2|Move| \\3|Paste| \\4|Create| \\5|Delete| \\6|Rename| \\7|Quit|";
  //Message of this mode
  const string message = "File Manager";

  //Change directory
  if ( !progCont.changeCurDir(progCont.gcw()) ){
    cout << "Program can't open current directory.";
    return 1;
  }

  //Loads files from current directory
  progCont.loadFiles(input);

  //Main loop
  while (commandCode!=quitC){

    //Checks if window is resized
    progCont.setTerminalSize();
    if ( ! progCont.testTerminalSize() ){
      progCont.setNewTeminalSize();
    }
    //Print whole page (message+files+commands) of this mode
    progCont.templateFilesMode( message, commands, prevC, nextC );

    //Loads user input, exit if something went wrong
    getline(cin, input);
    if (cin.eof() || cin.bad()){
      break;
    }

    //translate input to command code
    commandCode = getCommandCode(input, numCom);

    //If input is not command, then it is equal to -1
    if (commandCode == -1){
      //If input is directory, user wants to change directory
      if ( progCont.changeCurDir( input ) ){
        input = progCont.gcw();
        progCont.loadFiles(input);
        progCont.setNewTeminalSize();
      }
      //If input is file, it shows its informations
      else
        if ( progCont.loadFileInfoDir( input )){
          if (!infoMode(progCont))
            commandCode = quitC;
        }

    }
    else{
      //Command executor
      switch ( commandCode ){
        case copyC:    (!copyMode(progCont))   ?(commandCode=quitC):(commandCode=commandCode); break;
        case moveC:    (!moveMode(progCont))   ?(commandCode=quitC):(commandCode=commandCode); break;
        case pasteC:   (!pasteMode(progCont))  ?(commandCode=quitC):(commandCode=commandCode);progCont.loadFiles(progCont.gcw()); break;
        case createC:  (!createMode(progCont)) ?(commandCode=quitC):(commandCode=commandCode); break;
        case deleteC:  (!deleteMode(progCont)) ?(commandCode=quitC):(commandCode=commandCode); break;
        case renameC:  (!renameMode(progCont)) ?(commandCode=quitC):(commandCode=commandCode); break;
        case quitC:    break;
        case prevC:    progCont.prevPage(); break;
        case nextC:    progCont.nextPage(); break;
      }
    }
  }
  return 0;
}
