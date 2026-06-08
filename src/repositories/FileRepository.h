if (!defined(FileRepository_h))
#define FileRepository_h
#include "FileMetaData.h"
#include<vector>
#include<string>
{
class FileRepository
{
public:

void save(const FileMetaData& file);
FileMetaData findById(const std::string& id);
std::vector<FileMetaData> findAll();
void deleteById(const std::string& id);
void deleteAll();
void update(const FileMetaData& file);

}
}
endif // FileRepository_h