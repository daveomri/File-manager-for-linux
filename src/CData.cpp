/**
  @file CData.cpp
  Purpose: Declaration of CData method and functions working with them

  @author David Omrai
  @version 1.0
  @date 26/05/2019
*/
#include "CData.hpp"

#include <iostream>
#include <regex>
#include <dirent.h>
#include <fstream>
#include <unistd.h>   //library for creation of symbolic link and changing current directory
#include <sys/stat.h> //library for mkdir function
#include <pwd.h>
#include <grp.h>
using namespace std;

/**
    Function checks if given word match with regular expression.

    @param regexExp Regular expression.
    @param testWord Name of file.
    @returns True if it match, false otherwise.
*/
bool matchRegExp( regex & regexExp, const string & testWord ){
  return regex_match(testWord, regexExp);
}

/**
    Function deletes file given by name.

    @param fileName Name of file.
    @returns True if file was successfully deleted, false otherwise.
*/
bool deleteFileByAddress( const string & fileName ){
  if (remove(fileName.c_str())!=0)
    return false;
  return true;
}

/**
    Function deletes directory given by name.

    @param dirName Name of directory.
    @returns True if directory is deleted, false otherwise.
*/
bool deleteDir( const string & dirName ){
  DIR *dr = opendir(dirName.c_str());
  string fileName;
  bool output = true;
  if ( dr ){
    cout << "here" << endl;
    struct dirent * dp = 0;
    while ( (dp = readdir(dr)) ){
      fileName = dp->d_name;
      if (fileName!= "." && fileName!=".."){

        if (dp->d_type == DT_DIR)
        if ( !deleteDir(dirName+"/"+fileName) ){
          output=false;
          break;
        }
        if (!deleteFileByAddress(dirName+"/"+fileName)){
          output = false;
          break;
        }
      }
    }
    closedir(dr);
    return output;
  }
  return false;
}

/**
    Function translates integer to string.

    @param number Given number.
    @returns String with translated integer.
*/
string intToString( int number ){
  string output = "";
  string tmp    = "";
  if (  number == 0 )
    return "0";
  else if (number < 0){
    output += "-";
    number*=-1;
  }
  while (number){
    tmp += (char)(number%10+'0');
    number/=10;
  }
  for (int i = tmp.length()-1; i >= 0; i--){
    output+=tmp[i];
  }
  return output;
}

/**
    Function returns name of file from filename with extension.

    @param name Name with possible extension.
    @returns Name of file, without extension.
*/
string getFileName( const string & name ){
  if (name=="")
    return name;
  size_t from = 0;
  size_t to = (name[0]=='.')?(1):(0);
  for (; to < name.length(); to++)
    if (name[to]=='.')
      break;
  return name.substr(from, to);
}

/**
    Function returns extension of file.

    @param name Name of file.
    @returns Extension of file.
*/
string getFileExtension( const string & name ){
  if (name=="")
    return "";
  size_t i;
  for ( i = name.size()-1; i > 0; i--){
      if (name[i]=='.')
          return name.substr(i);
  }
  return "";
}

/**
    Function checks if given file is a regular file.

    @param fileName Name of the file.
    @returns True if file is a regular file, false if isn't.
*/
bool isFile( const string & fileName ){
  DIR *dr = opendir(".");
  string cmpName, srcName = fileName;
  int output = 0;
  if ( dr ){
    struct dirent * dp = 0;
    while ( (dp = readdir(dr)) ){
      cmpName = dp->d_name;
      if (cmpName == srcName){
        if (dp->d_type == DT_REG)
          output = 1;
        break;
      }
    }
    closedir(dr);
    return output;
  }
  else{
    return false;
  }
  /*
  struct stat test;
  if ( stat(fileName, &test) == -1)
    return false;
  return S_ISREG(test.st_mode);
  */
}

/**
    Function checks if given file is a directory.

    @param dirName Name of the file.
    @returns True if file is a directory, false if isn't.
*/
bool isDir( const string & dirName ){
  DIR *dr = opendir(".");
  string cmpName, srcName = dirName;
  int output = 0;
  if ( dr ){
    struct dirent * dp = 0;
    while ( (dp = readdir(dr)) ){
      cmpName = dp->d_name;
      if (cmpName == srcName){
        if (dp->d_type == DT_DIR)
          output = 1;
        break;
      }
    }
    closedir(dr);
    return output;
  }
  else{
    return false;
  }
  /*
  struct stat test;
  if ( stat(dirName, &test) == -1)
    return false;
  return S_ISDIR(test.st_mode);
  */
}

/**
    Function checks if given file is a link.

    @param linkName Name of the link.
    @returns True if file is a link, false if isn't.
*/
bool isLink( const string & linkName ){
  DIR *dr = opendir(".");
  string cmpName, srcName = linkName;
  int output = 0;
  if ( dr ){
    struct dirent * dp = 0;
    while ( (dp = readdir(dr)) ){
      cmpName = dp->d_name;
      if (cmpName == srcName){
        if (dp->d_type == DT_LNK)
          output = 1;
        break;
      }
    }
    closedir(dr);
    return output;
  }
  else{
    return false;
  }
  /*
  struct stat test;
  if ( stat(linkName, &test) == -1)
    return false;
  cout << "I tried " << boolalpha << S_ISLNK(test.st_mode) << endl;
  return S_ISLNK(test.st_mode);
  */
}

/**
    Function translates given string to lowercase.

    @param text Text to translate to lowercase.
    @returns String with lowercase text.
*/
string lowerCase( const string & text ){
  string lowerText = text ;
  for ( size_t i = 0; i < lowerText.size(); i++){
    if (lowerText[i] >= 'A' && lowerText[i] <= 'Z'){
      lowerText[i] = 'a' + (lowerText[i]-'A');
    }
  }
  return lowerText;
}

/**
    Function returns file size.

    @param fileName Name of file.
    @returns Size of file if it could be successfully read, else -1.
*/
int gfs( const string & fileName ){
  struct stat buf;
  int rc = stat(fileName.c_str(), &buf);
  return (rc==0)?(buf.st_size):(-1);
}

/**
    Function copies source file to target file.

    @param source Source file.
    @param target Target file.
    @returns True if file is copied, false otherwise.
*/
bool copyFile( const string & source, const string & target ){
  ifstream src(source, ios::binary);
  if (src.bad())
    return false;
  ofstream trg(target, ios::binary);
  if ( trg.bad() )
    return false;
  trg<<src.rdbuf();
  return true;
}

/**
    Function returns where link points.

    @param link Name of link.
    @returns Nothing if reading of link is unsuccessful, path of link otherwise.
*/
string getLinkPath(const string & link){
  string output = "";
  try{
    char * linkPath=realpath(link.c_str(), NULL);
    if (linkPath!=NULL)
    output=linkPath;
    free(linkPath);
  }
  catch(...){
    return output;
  }
  return output;
}



//  - - CData methods - -
CData::CData(){
}

CData::~CData(){
  cleanFiles();
  cleanCopy();
  cleanMove();
}

bool CData::isPhoto( const string & extension ){
  return isIn(extension, photoextension);
}

bool CData::isText( const string & extension ){
  return isIn(extension, textextension);
}

bool CData::isVideo( const string & extension ){
  return isIn(extension, videoextension);
}

bool CData::isAudio( const string & extension ){
  return isIn(extension, audioextension);
}

bool CData::isCompressed( const string & extension ){
  return isIn(extension, compressedextension);
}

bool CData::isDiskMedia( const string & extension ){
  return isIn(extension, diskMediaextension);
}

bool CData::isDatabase( const string & extension){
  return isIn(extension, databaseextension);
}

bool CData::isExe( const string & extension ){
  return isIn(extension, exeextension);
}

bool CData::isProgramming( const string & extension ){
  return isIn(extension, programmingextension);
}



bool CData::isIn(const string & extension, const vector<string> &extensionVector){
  string tmp = lowerCase(extension);
  for ( auto iter : extensionVector ){
    if ( iter == tmp )
      return true;
  }
  return false;
}

void CData::loadFiles(const string & dirName){
  DIR * dir;
  dirent * pdir;
  string owner = "";
  string fileName = "";

  dir = opendir(dirName.c_str());

  while ( (pdir = readdir(dir)) ){
    fileName = pdir->d_name;
    owner = getFileOwner(pdir->d_name);

    if (isLink(pdir->d_name)){
      addFile(CLink(fileName, getCurDir(), getCreationDate(pdir->d_name), owner,  gfs(fileName) )); //buf.st_size
    }
      else if (isDir(pdir->d_name)){
        if (fileName!="." && fileName!="..")
          addFile(CFolder(fileName, getCurDir(), getCreationDate(pdir->d_name), owner,  gfs(fileName) )); //buf.st_size
      }
      else if (isFile(pdir->d_name)){

        if(isPhoto(getFileExtension(fileName))){
          addFile(CPhoto(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
        else if(isText(getFileExtension(fileName))){
          addFile(CText(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
        else if(isVideo(getFileExtension(fileName))){
          addFile(CVideo(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
        else if(isAudio(getFileExtension(fileName))){
          addFile(CAudio(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
        else if(isCompressed(getFileExtension(fileName))){
          addFile(CCompressed(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
        else if(isDiskMedia(getFileExtension(fileName))){
          addFile(CDiskMedia(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
        else if(isDatabase(getFileExtension(fileName))){
          addFile(CDatabase(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
        else if(isExe(getFileExtension(fileName))){
          addFile(CExe(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
        else if(isProgramming(getFileExtension(fileName))){
          addFile(CProgramming(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
        else{
          addFile(CUnknown(getFileName(fileName), getCurDir(),  getCreationDate(pdir->d_name), owner, gfs(fileName), getFileExtension(fileName) ));
        }
      }
  }
  closedir(dir);
}

bool CData::loadFileInfoDir  ( const string & fileName ){
  CFile * tmp = findFile( fileName, dirContent );
  if (!tmp)
    return false;
  loadInfo(tmp);
  return true;
}

bool CData::loadFileInfoCopy ( const string & fileName ){
  CFile * tmp = findFile( fileName, copyContent );
  if (!tmp)
    return false;
  loadInfo(tmp);
  return true;
}

bool CData::loadFileInfoMove ( const string & fileName ){
  CFile * tmp = findFile( fileName, moveContent );
  if (!tmp)
    return false;
  loadInfo(tmp);
  return true;
}

void CData::loadInfo( const CFile * file ){
  cleanInfo();
  fileInfo.emplace_back("Name: " + file->getName());

  fileInfo.emplace_back("Type: " + file->getType());

  fileInfo.emplace_back("Location: "+file->getLocation());

  fileInfo.emplace_back("Creation: "+file->getCreation());

  fileInfo.emplace_back("Owner: "+file->getOwner());

  fileInfo.emplace_back("Size: "+ intToString(file->getSize()) + " B");
}

void CData::printInfo( size_t from, size_t to ){
  size_t printFrom = (from > fileInfo.size())?(fileInfo.size()):(from);
  size_t printTo = (to > fileInfo.size())?(fileInfo.size()):(to);
  for (size_t i = printFrom; i < printTo; i++)
    cout << fileInfo[i] << endl;
}

void CData::cleanInfo(){
  fileInfo.clear();
}

bool CData::regDeleteFile(const string & input, string & errFiles){
  try{
    regex fileRegex(input);
    string fileName;
    for ( auto iter : dirContent ){
      fileName = iter->getFullName();
      if (matchRegExp(fileRegex, fileName)){
        if (iter->getType() == "Folder")
        if ( !deleteDir(iter->getLocation()+"/"+fileName) )
        errFiles+=" ," + fileName;

        if ( remove(fileName.c_str())!=0 )
        errFiles+=" ," + fileName;
      }
    }
  }
  catch(...){
    return false;
  }
  return true;
}

bool CData::norDeleteFile( const string & input ){
  string fileName;
  for ( auto iter : dirContent ){
    fileName = iter->getFullName();
    if (input == fileName){
      if (iter->getType() == "Folder")
        if ( !deleteDir(iter->getLocation()+"/"+fileName) )
          return false;
      if ( remove(fileName.c_str())!=0 )
        return false;
      else
        return true;
    }
  }
  return false;
}

string CData::getCreationDate( const string & fileName){
  string output;
  int x = 0;
  struct stat buf;
  x = stat ( fileName.c_str(), &buf);
  if ( x == -1)
    return "";
  output = ctime(&buf.st_atim.tv_sec);
  return output.substr(0, output.length()-1);
}

string CData::getFileOwner( const string & fileName ){
  struct stat inf;
  if ( stat(fileName.c_str(), &inf) != -1 ){
    struct passwd *pw = getpwuid(inf.st_uid);
    return (pw!=0)?(pw->pw_name):("");
  }
  return "";
}

bool CData::createDir( const string & dirName ){
  if (mkdir(dirName.c_str(), 0777) == -1)
    return false;
  return true;
}

bool CData::createFile(const string & fileName){
  bool output;
  ofstream newFile;
  newFile.open(fileName.c_str());
  (newFile.bad())?(output=false):(output=true);
  newFile.close();
  return output;
}


bool CData::createLink(const string & linkName, const string & linkPath){
  if (symlink(linkPath.c_str(), linkName.c_str()) == -1 )
    return false;
  return true;
}

bool CData::renameFile(const string & prevName, const string & newName){
  int stat = 0;
  stat = rename(prevName.c_str(), newName.c_str());

  if ( stat != 0)
  return false;
  return true;
}

bool CData::copyDirFiles( const string & sourceDir, const string & targetDir ){
  DIR *dr = opendir(sourceDir.c_str());
  string fileName;
  bool output = true;

  if ( dr ){
    struct dirent * dp = 0;
    while ( (dp = readdir(dr)) ){
      fileName = dp->d_name;
      if (fileName!= "." && fileName!=".."){
        if (dp->d_type == DT_DIR){
          if (!createDir(targetDir+"/"+fileName)){
            output = false;
            break;
          }
          if ( !copyDirFiles(sourceDir+"/"+fileName, targetDir+"/"+fileName) ){
            output=false;
            break;
          }
        }
        else if (dp->d_type == DT_LNK){
          string linkPath = getLinkPath(sourceDir+"/"+fileName);
          if ( linkPath=="" ){
            output = false;
            break;
          }
          if (!createLink(targetDir+"/"+fileName, linkPath)){
            output = false;
            break;
          }
        }
        else{

          if (!createFile(targetDir+"/"+fileName)){
            output = false;
            break;
          }
          else
            if (!copyFile(sourceDir+"/"+fileName, targetDir+"/"+fileName)){
                output = false;
                break;
            }
        }
      }
    }
    closedir(dr);
    return output;
  }
  return false;
}

void CData::copyMoveContent( string & errMes ){
  string fileName;
  for ( auto iter : moveContent ){
    fileName = iter->getFullName();

    if ( typeid(*iter) == typeid(CFolder) ){
      if (!createDir(fileName))
        errMes+= ", " + fileName;
      else
        if (!copyDirFiles(iter->getLocation()+"/"+fileName, curDir+"/"+fileName) )
          errMes += ", " + fileName;
    }
    else if (typeid(*iter)==typeid(CLink)){
      string linkPath = getLinkPath(curDir+"/"+fileName);
      if ( linkPath == "" )
        errMes += ", " + fileName;

      else if ( !createLink(iter->getLocation()+"/"+fileName, linkPath) )
        errMes += ", " + fileName;
    }
    else{
      if(!createFile(fileName))
        errMes+=", "+fileName;
      else
        if (!copyFile(iter->getLocation()+"/"+fileName, curDir+"/"+fileName))
          errMes+=", "+fileName;
    }
  }
}

void CData::copyCopyContent( string & errMes ){
  string fileName;
  for ( auto iter : copyContent ){
    fileName = iter->getFullName();

    if ( typeid(*iter) == typeid(CFolder) ){
      if (!createDir(fileName))
        errMes+= ", " + fileName;
      else
        if (!copyDirFiles(iter->getLocation()+"/"+fileName, curDir+"/"+fileName))
          errMes += ", " + fileName;
    }
    else if (typeid(*iter)==typeid(CLink)){
      string linkPath = getLinkPath(curDir+"/"+fileName);
      if ( linkPath == "" )
        errMes += ", " + fileName;

      else if ( !createLink(iter->getLocation()+"/"+fileName, linkPath) )
        errMes += ", " + fileName;
    }
    else{
      if(!createFile(fileName))
        errMes+=", "+fileName;
      else
        if (!copyFile(iter->getLocation()+"/"+fileName, curDir+"/"+fileName))
          errMes+=", "+fileName;
    }
  }
}

void CData::deleteMoveContent(string & errMes){
  string fileName;
  string fullPath;
  for ( auto iter : moveContent ){
    fileName = iter->getFullName();
    fullPath = iter->getLocation()+"/"+fileName;
      if ( typeid(*iter) == typeid(CFolder) ){
        if ( !deleteDir(fullPath) )
          errMes+=", "+fileName;
        else if (remove(fullPath.c_str())!=0)
          errMes+=", "+fileName;
      }
      else if ( remove(fullPath.c_str())!=0 )
          errMes+=", "+fileName;
    }
}

int CData::getDirContentSize(){
  return dirContent.size();
}

int CData::getCopyContentSize(){
  return copyContent.size();
}

int CData::getMoveContentSize(){
  return moveContent.size();
}

bool CData::changeCurDir( const string & newCurDir ){
  if (chdir(newCurDir.c_str())!=0)
    return false;
  cleanFiles();
  curDir = gcw();
  return true;
}

string CData::getCurDir() const{
  return curDir;
}

void CData::addFile( const CFile & newFile ){
  CFile * newClone = newFile.clone();
  dirContent.emplace_back(newClone);
}

bool CData::fileInDir( const string & fileName ){
  if ( findFile(fileName, dirContent) != NULL )
    return true;
  return false;
}

bool CData::regAddCopyFile( const string & newFile ){
  try{
    regex fileRegex(newFile.c_str());
    string fileName;
    for ( auto iter : dirContent ){
      fileName = iter->getFullName();
      if (matchRegExp(fileRegex, fileName)){
        cout << "and it made it here" << endl;
        if (!findFile(fileName, copyContent))
          copyContent.emplace_back(iter->clone());
      }
    }
  }
  catch(...){
    return false;
  }
  return true;
}

void CData::norAddCopyFile( const string & newFile ){
  CFile * fileOrig = findFile(newFile, dirContent);
  if ( fileOrig != NULL  && findFile(fileOrig->getFullName(), copyContent) == NULL ){
      CFile * file = fileOrig->clone();
      copyContent.emplace_back(file);
  }
}

bool CData::regAddMoveFile( const string & newFile ){
  try{
    regex fileRegex(newFile.c_str());
    string fileName;
    for ( auto iter : dirContent ){
      fileName = iter->getFullName();
      if (matchRegExp(fileRegex, fileName))
      if (!findFile(fileName, moveContent))
        moveContent.emplace_back(iter->clone());
    }
  }
  catch(...){
    return false;
  }
  return true;
}

void CData::norAddMoveFile( const string & newFile ){
  CFile * fileOrig = findFile(newFile, dirContent);
  if ( fileOrig != NULL && findFile(fileOrig->getFullName(), moveContent) == NULL ){
      CFile * file = fileOrig->clone();
      moveContent.emplace_back(file);
  }
}

void CData::cleanFiles(){
  for ( auto iter : dirContent )
    delete iter;
  dirContent.clear();
}

void CData::cleanCopy(){
  for ( auto iter : copyContent )
    delete iter;
  copyContent.clear();
}

void CData::cleanMove(){
  for ( auto iter : moveContent )
    delete iter;
  moveContent.clear();
}


CFile * CData::findFile( const string & fileName, vector<CFile*> &vecContent ) const{
  for ( auto iter : vecContent){
    if ( iter->getFullName() == fileName )
      return iter;
  }
  return NULL;
}


template <class _T>
void CData::sortFiles( _T compare ){
  std::sort(dirContent.begin(), dirContent.end(), compare);
}


void CData::sortByName(){
 sortFiles([] ( const CFile* a, const CFile* b){ return a->getFullName() < b->getFullName(); } );
}

void CData::sortBySize(){
 sortFiles([] ( const CFile* a, const CFile* b){ return (a)->getSize ()< (b)->getSize(); } );
}

void CData::sortByDate(){
 sortFiles([] ( const CFile* a, const CFile* b){ return (a)->getCreation() < (b)->getCreation(); } );
}

void CData::printFiles(size_t from, size_t to){
  size_t vectorFrom = (dirContent.size() < from )?(dirContent.size()):(from);
  size_t vectorTo = (dirContent.size() < to )?(dirContent.size()):(to);
  for ( size_t i = vectorFrom ; i < vectorTo; ++i ){
    dirContent[i]->printCFile();
    cout << endl;
  }
}

void CData::printCopy(size_t from, size_t to){
  size_t vectorFrom = (copyContent.size() < from )?(copyContent.size()):(from);
  size_t vectorTo = (copyContent.size() < to )?(copyContent.size()):(to);
  for ( size_t i = vectorFrom ; i < vectorTo; ++i ){
    copyContent[i]->printCFile();
    cout << endl;
  }
}

void CData::printMove(size_t from, size_t to){
  size_t vectorFrom = (moveContent.size() < from )?(moveContent.size()):(from);
  size_t vectorTo = (moveContent.size() < to )?(moveContent.size()):(to);
  for ( size_t i = vectorFrom ; i < vectorTo; ++i ){
    moveContent[i]->printCFile();
    cout << endl;
  }
}

string CData::gcw()
{
  size_t size=0;
  string out = "";
  char *path = NULL;
  path=getcwd(path,size);
  out = path;
  if (path)
    free(path);
  return out;
}
