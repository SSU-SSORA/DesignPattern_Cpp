#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class Document {
public:
	virtual bool Open(char * pFileName) = 0;
};

class HwpDocument : public Document {
public:
	bool Open(char *pFileName) {
		ifstream ifs(pFileName);
		if (!ifs)
			return false;
		//hwp ���� ���μ���
		return true;
	}
};

class MsWordDocument : public Document {
public:
	bool Open(char *pFileName) {
		ifstream ifs(pFileName);
		if (!ifs)
			return false;
		//hwp ���� ���μ���
		return true;
	}
};

class Application {
public:
	void NewDocument(char * pFileName) {
		Document *pDoc = CreateDocument();
		docs_[pFileName] = pDoc;
	}
	virtual Document * CreateDocument() = 0;
private:
	map<string, Document *> docs_;
};

class HwpApplication : public Application {
public:
	Document * CreateDocument() {
		return new HwpDocument;
	}
};

class MsWordApplication : public Application {
public:
	Document * CreateDocument() {
		return new HwpDocument;
	}
};

int main() {
	HwpApplication hwp;
	hwp.NewDocument("input.hwp");
}