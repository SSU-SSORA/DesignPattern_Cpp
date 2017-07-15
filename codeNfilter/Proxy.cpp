#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sys\stat.h>
#include <sys\types.h>
#include <fcntl.h>

using namespace std;


#define MAX_CACHE_COUNT		50

class File {
public:
	virtual int GetFile(string fn, void* pOut) = 0;
};

class ImageFile : public File {
public:
	int GetFile(string fn, void *pOut) {
		struct stat statBuf;
		if (stat(fn.data(), &statBuf) < 0) {
			cout << "File not Found ! " << endl;
			return 0;
		}
		
		int fd = _open(fn.data()), _O_RDONLY);
		if (fd < 0) {
			cout << "File open error !" << endl;
			return 0;
		}

		pOut = new char[statBuf.st_size];
		ssize_t byteCnt = _read(fd, pOut, statBuf.st_size);
		close(fd);

		if (byteCnt != statBuf.st_size) {
			cout << "Error while File Reading" << endl;
			return 0;
		}
		return byteCnt;
	}
};

class ImageFileCache : public File {
public:
	int GetFile(string fn, void *pOut) {
		pOut = fileCache_[fn];

		struct stat realStat;
		if (stat(fn.data(), &realStat) < 0) {
			cout << "File Not Found " << endl;
			return 0;
		}
		struct stat *pFileStat = fileStat_[fn];
		if (pOut == NULL || pFileStat == 0 || realStat.st_mtime != pFileStat->st_mtime) {
			ImageFile f;
			void *pFileOut;
			int fileSize = f.GetFile(fn, pFileOut);

			if (fileSize <= 0) {
				pOut = nullptr;
				return 0;
			}

			RegisterCache(fn, &realStat, pFileOut);
			pOut = pFileOut;
		}
		else {
			for(int i = 0 ; i < )
		}

	}
private:
	class LRUInfo {
	public:
		LRUInfo() { lastReadTime_ = 0;}
		string fn_;
		time_t lastReadTime_;
	};

	LRUInfo lruInfo_[MAX_CACHE_COUNT];
	map<string, struct stat*> fileStat_;
	map<string, char *>fileCache_;
};