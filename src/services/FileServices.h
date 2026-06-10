#if !defined(FileServices_h)
#define FileServices_h

#include "FileRepository.h"
#include "FileMetaData.h"
#include <string>
#include <vector>

class FileService
{
public:
    FileService(FileRepository& repo);

    FileMetaData uploadFile(const std::string& name , const std::string& fileData);
    FileMetaData getById(const std::string& id);
    std::vector<FileMetaData> getAllFiles();
    void deleteFile(const std::string& id);
    void deleteAllFiles();

private:
    FileRepository& repo;

    std::string generateUniqueId();
    void writeToDisk(const std::string& path, const std::string& data);
};

#endif // FileServices_h