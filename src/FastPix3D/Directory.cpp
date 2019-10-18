#include "FastPix3D.h"

bool Directory::Exists(string path)
{
	//uint32 attr = GetFileAttributes(path.c_str());
	//return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY);
	return true; // This can't be done on V5 yet
}
void Directory::Create(string path)
{
	//if (!Exists(path) && !CreateDirectory(path.c_str(), NULL)) throw std::runtime_error("");
}
void Directory::Delete(string path)
{
	//if (Exists(path) && !RemoveDirectory(path.c_str())) throw std::runtime_error("");
	throw std::runtime_error("");
}