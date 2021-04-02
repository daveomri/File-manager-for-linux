/**
  @file CController.cpp
  Purpose: Declaration of CController method and functions working with them

  @author David Omrai
  @version 1.0
  @date 22/05/2019
*/

// My classes
#include "CController.hpp"
#include <unistd.h>
#include <sys/ioctl.h>  //Library for geting a terminal window size

using namespace std;

const int freeRows = 3;/*!< Constant stores number of rows that are reserved by program */

// -- Functions --
/**
    Function starts bold text in output.

    @param os Output ostream.
    @returns Ostream.
*/
ostream & boldOn(ostream & os){
  return os << "\033[1m";
}

/**
    Function ends bold text in output.

    @param os Output ostream.
    @returns Ostream.
*/
ostream & boldOff(ostream & os){
  return os << "\033[0m";
}

/**
    Function deletes spaces at the beginning

    @param text Text with some or none spaces at the beginning.
    @returns String without spaces at the beginning.
*/
string strBeg( const string & text ){
  size_t i = 0;
  for (i = 0; i < text.length(); i++ )
    if (text[i]!=' ')
      break;
  return text.substr(i);
}

// -- CController methods --
CController::CController() : fileSys(new CData){
  //Loads terminal proportion
  setTerminalSize();
  oldRows = rows;
  oldColumns = columns;
  contentFrom = 0;
  contentTo = (rows<freeRows)?(0):(rows-freeRows);
  numberFiles = 0;
}

CController::~CController(){
  delete fileSys;
}

void CController::setTerminalSize(){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  rows = w.ws_row;
  columns = w.ws_col;
}

bool CController::testTerminalSize() const {
  return oldRows == rows;
}

void CController::setNewTeminalSize(){
  oldRows = rows;
  oldColumns = columns;
  contentFrom = 0;
  contentTo = (rows<freeRows)?(0):(rows-freeRows);
}

int CController::getRows()const{
  return rows;
}

void CController::clearScrean()const{
  for ( int i = 0; i < rows; i++)
    cout << endl;
}

void CController::moveText()const{
  int lastFileIndex = (contentTo>itemsNumber)?(itemsNumber):(contentTo);
  for (int i = (lastFileIndex-contentFrom); i<(rows-freeRows); i++)
    cout<<endl;
}

void CController::loadFiles(const string & dirName){
  fileSys->cleanFiles();
  fileSys->loadFiles(dirName);
  fileSys->sortByName();
  numberFiles = fileSys->getDirContentSize();
}

void CController::printCon(){
  fileSys->printFiles(contentFrom, contentTo);
}

void CController::nextPage(){
  contentFrom = (contentTo >= itemsNumber)?(contentFrom):(contentTo);
  contentTo = (contentTo==contentFrom)?(contentTo+(rows-freeRows)):(contentTo);
}

void CController::prevPage(){
  contentTo = (contentFrom==0)?(contentTo):(contentFrom);
  contentFrom = (contentFrom <= (rows-freeRows))?(0):(contentFrom-(rows-freeRows));
}

void CController::swipeCon( int codePre, int codeNe ) const{
  if (contentFrom!=0)
    cout << " \\" << codePre << "|Previous|";
  if ( contentTo < itemsNumber )
    cout << " \\"<<codeNe<<"|Next|";
  cout << endl;
}

void CController::cleanInfo(){
  fileSys->cleanInfo();
}

bool CController::fileInDir( const string & fileName )const{
  return fileSys->fileInDir( fileName );
}

bool CController::loadFileInfoDir( const string & fileName ){
  return fileSys->loadFileInfoDir(fileName);
}

bool CController::loadFileInfoCopy( const string & fileName ){
  return fileSys->loadFileInfoCopy(fileName);
}

bool CController::loadFileInfoMove( const string & fileName ){
  return fileSys->loadFileInfoMove(fileName);
}

void CController::infoMode( const string & message, const string & commands, int prevPage, int nextPage){
  string controlPanel = commands;
  string modeName = message + " | " + fileSys->getCurDir();
  itemsNumber = 6;
  if (getRows() < freeRows){
    cout << "Resize your window please."<< endl;
  }
  else{
  clearScrean();
  cout << boldOn << modeName << boldOff << endl;
  fileSys->printInfo(contentFrom, contentTo);
  moveText();
  cout << controlPanel;
  swipeCon(prevPage, nextPage);
  }
}

void CController::renameModeSelect(const string & message, const string & commands, int prevPage, int nextPage){
  string controlPanel = commands;
  string modeName = message + " | " + fileSys->getCurDir();

  itemsNumber = numberFiles;
  if (getRows() <freeRows){
    cout << "Resize your window please."<< endl;
  }
  else{
  clearScrean();
  cout << boldOn << modeName << boldOff << endl;
  printCon();
  moveText();
  cout << controlPanel;
  swipeCon(prevPage, nextPage);
  }
}

void CController::renameModeConfirm( const string & message, const string & commands, int nextPage, int prevPage ){
  string controlPanel = commands;
  string modeName = message + " | " + fileSys->getCurDir();

  itemsNumber = 6;
  if (getRows() <freeRows){
    cout << "Resize your window please."<< endl;
  }
  else{
  clearScrean();
  cout << boldOn << modeName << boldOff << endl;
  fileSys->printInfo(contentFrom, contentTo);
  moveText();
  cout << controlPanel;
  swipeCon(prevPage, nextPage);
  }
}

bool CController::renameFile(const string & prevName, const string & newName){
  return fileSys->renameFile(prevName, newName);
}

void CController::printMessage(const string & message){
  string controlPanel = "\\1|Back| \\2|Quit|";
  string modeName = "Message";

  itemsNumber = 1;
  if (getRows() <freeRows){
    cout << "Resize your window please."<< endl;
  }
  else{
  clearScrean();
  cout << boldOn << modeName << boldOff << endl;
  cout << message << endl;
  moveText();
  cout << controlPanel;
  swipeCon(3, 4);
  }
}

bool CController::deleteFile( const string & input, bool regExp, string & errFiles ){
  switch (regExp){
    case false: (fileSys->norDeleteFile(input))?(errFiles=errFiles):(errFiles+="File/s, " + input + ", could not be deleted."); break;
    case true: (fileSys->regDeleteFile(input, errFiles))?(errFiles=errFiles):(errFiles+="Program could not resolve regular expresion: " + input); break;
  }
  if (errFiles!="")
    return false;
  return true;
}

vector<string> CController::extractInputFiles( const string & input ){
  vector <string> inputFiles;
  string inputText = strBeg(input);
  string fileName;
  int ingnoreSpace = 1;

  for ( size_t i = 0; i < inputText.length(); i++ ){
    (inputText[i]=='\\' && ingnoreSpace!=0)?(ingnoreSpace=0):(ingnoreSpace=1);
    if ( (inputText[i]!=' ' && inputText[i]!='\\' ) || ingnoreSpace==0){
      fileName+=inputText[i];
      ingnoreSpace = 1;
    }
    else if (inputText[i]==' ' && ingnoreSpace==1){
      inputFiles.emplace_back(fileName);
      fileName="";
    }
  }
  inputFiles.emplace_back(fileName);

  return inputFiles;
}

bool CController::createFile(const string & fileName){
  return fileSys->createFile(fileName);
}

bool CController::createDir(const string & dirName){
  return fileSys->createDir(dirName);
}

bool CController::createLink(const string & linkName, const string & linkPath){
  return fileSys->createLink(linkName, linkPath);
}

void CController::templateFilesMode( const string & message, const string & commands, int prevPage, int nextPage ){
  string controlPanel = commands;
  string modeName = message + " | " + fileSys->getCurDir();
  itemsNumber = numberFiles;
  if (getRows() <freeRows){
    cout << "Resize your window please."<< endl;
  }
  else{
  clearScrean();
  cout << boldOn << modeName << boldOff << endl;
  printCon();
  moveText();
  cout << controlPanel;
  swipeCon(prevPage, nextPage);
  }
}

void CController::clearCopy(){
  fileSys->cleanCopy();
}
void CController::clearMove(){
  fileSys->cleanMove();
}

void CController::printCopy(){
  fileSys->printCopy(contentFrom, contentTo);
}

void CController::printMove(){
  fileSys->printMove(contentFrom, contentTo);
}

void CController::showCopy( const string & message, const string & commands, int prevPage, int nextPage ){
  string controlPanel = commands;
  string modeName = message;
  itemsNumber = fileSys->getCopyContentSize();
  if (getRows() <freeRows){
    cout << "Resize your window please."<< endl;
  }
  else{
  clearScrean();
  cout << boldOn << modeName << boldOff << endl;
  printCopy();
  moveText();
  cout << controlPanel;
  swipeCon(prevPage, nextPage);
  }
}

void CController::showMove( const string & message, const string & commands, int prevPage, int nextPage ){
  string controlPanel = commands;
  string modeName = message;
  itemsNumber = fileSys->getMoveContentSize();
  if (getRows() <freeRows){
    cout << "Resize your window please."<< endl;
  }
  else{
  clearScrean();
  cout << boldOn << modeName << boldOff << endl;
  printMove();
  moveText();
  cout << controlPanel;
  swipeCon(prevPage, nextPage);
  }
}

bool CController::copyFile( const string & fileName, bool regExp ){
  if (regExp)
    return fileSys->regAddCopyFile(fileName);
  fileSys->norAddCopyFile(fileName);
  return true;
}

bool CController::moveFile( const string & fileName, bool regExp ){
  if (regExp)
    return fileSys->regAddMoveFile(fileName);
  fileSys->norAddMoveFile(fileName);
  return true;
}

bool CController::copyFiles( string & errMes ){
  fileSys->copyCopyContent(errMes);
  fileSys->cleanCopy();
  if (errMes=="")
    return true;
  return false;
}

bool CController::moveFiles( string & errMes){
  fileSys->copyMoveContent(errMes);
  fileSys->deleteMoveContent(errMes);
  fileSys->cleanMove();
  if (errMes=="")
    return true;
  return false;
}

bool CController::changeCurDir( const string & dirName ){
  return fileSys->changeCurDir( dirName );
}

string CController::gcw(){
  return fileSys->gcw();
}
