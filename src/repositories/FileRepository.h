#if !defined(FileRepository_h)
#define FileRepository_h
#include"FileMetaData.h"
#include <vector>
#include <string>

class FileRepository
{
public:

void save(const FileMetaData& file);
FileMetaData findById(const std::string& id);
std::vector<FileMetaData> findAll();
void deleteById(const std::string& id);
void deleteAll();

private:
std::vector<FileMetaData> loadAll();
void saveFiles(const std::vector<FileMetaData>& files);
};

#endif // FileRepository_h
