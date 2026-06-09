#include "FileRepository.h"
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <algorithm>


std::vector<FileMetaData> FileRepository::loadAll()
{
    std::ifstream file("metadata.json");
    if(!file.is_open())
    {
        throw std::runtime_error("Can not open the file ");
    }

    using json = nlohmann::json;
    json data;
    try
    {
        file >> data;
    }
    catch(...)
    {
        return {};
    }
    

    std::vector<FileMetaData> records;
    for(const auto& rec : data)
    {
        records.push_back(FileMetaData::toFile(rec));
    }

    return records;
}

std::vector<FileMetaData> FileRepository::findAll()
{
    return loadAll();
}

FileMetaData FileRepository::findById(const std::string& id)
{
    for(const auto& record : loadAll())
    {
        if(record.fileId==id)
        return record;
    }
    throw std::runtime_error("File not found " + id);

}


void FileRepository::saveFiles(const std::vector<FileMetaData>& files)
{
    using json = nlohmann::json;
    json jsonArray = json::array();
    
    for(const auto& file : files)
    {
        jsonArray.push_back(file.toJson());
    }
    
    std::ofstream file("metadata.json");
    if(file.is_open())
    {
        file << jsonArray.dump(4);
    }
}

void FileRepository::save(const FileMetaData& file)
{
    auto files = loadAll();
    files.push_back(file);
    saveFiles(files);
}

void FileRepository::deleteAll()
{
    saveFiles({});
}


void FileRepository::deleteById(const std::string& id)
{
    auto files = loadAll();
    files.erase(
        std::remove_if(files.begin(), files.end(),[&id](const FileMetaData& f) { return f.fileId == id; }),
        files.end()
    );
    saveFiles(files);
}


