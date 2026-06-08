#if !defined(FileMetaData_h)
#define FileMetaData_h
#include <nlohmann/json.hpp>
#include <ctime>
#include <string>

struct FileMetaData
{
    std::string fileName;
    std::string filePath;
    std::string fileId;
    size_t fileSize;
    std::time_t uploadTime;
 
    using json = nlohmann::json;
    json toJson(const FileMetaData& file)
    {
        return json
        {
            {"Name",file.fileName},
            {"ID",file.fileId},
            {"Size",file.fileSize},
            {"Path",file.filePath},
            {"Date",file.uploadTime}
        };
    }

    FileMetaData toFile(const json& j)
    {
        FileMetaData file;
        file.fileName = j.at("Name").get<std::string>();
        file.fileId=j.at("ID").get<std::string>();
        file.filePath = j.at("Path").get<std::string>();
        file.fileSize = j.at("Size").get<std::size_t>();
        file.uploadTime = j.at("Date").get<std::time_t>();
        return file;
    }
};
#endif // FileMetaData_h
