#if !defined(FileMetaData_h)
#define FileMetaData_h
#include <ctime>
#include <string>

struct FileMetaData
{
    std::string fileName;
    std::string filePath;
    std::string fileId;
    size_t fileSize;
    std::time_t uploadTime;
}
#endif // FileMetaData_h
