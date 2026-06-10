#include "FileServices.h"
#include <fstream>
#include <filesystem>
#include <random>
#include <stdexcept>
#include <ctime>
#include<algorithms>
#include<string>


FileMetaData FileServices::getById(const std::string& id)
{
  try
  {
    repo.findById();
  }
  throw std::runtime_error("File not Found "+id);
  
}

std::vector<FileMetaData> FileServices::getAllFiles()
{
  return repo.findAll();
}

FileServices::FileService(FileRepository& repo)
{
    std::filesystem::create_directories("Uploads");
}

FileMetaData FileServices::uploadFile(const std::string& name , const std::string& fileData)
{
    if(name.empty())
    {
        throw std::runtime_error("File name can't be empty");
    }

    if(fileData.empty())
    {
        throw std::runtime_error("File can't be empty");
    }

    FileMetaData file;
    file.fileName = name ;
    file.filePath = "uploads/" + file.fileId + "_" + name;;
    file.fileSize = file.size();
    file.fileId = generateUniqueId();
    file.uploadTime = std::time(nullptr);

    writeToFolder(file.filePath,fileData);
    repo.save(file);

    return file;
}

void FileServices::deleteFile(const std::string& id)
{}
void FileServices::deleteAllFiles()
{}


std::string FileServices::generateUniqueId()
{}
void FileServices::writeToFolder(const std::string& path, const std::string& data)
{}
