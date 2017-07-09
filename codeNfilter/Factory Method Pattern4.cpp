#include <iostream>
#include <strings.h>
#include <sys/utsname.h>
#define HPUX "HPUX"
#define SUNOS "SunOS"

class Product {
public:
	virtual Product * Clone() = 0;
};

class HPScanner : public Product {
public:
	Product * Clone() { return new HPScanner(*this); }
};

class HPParser : public Product {
public:
	Product * Clone() { return new HPParser(*this); }
};
class HPCodeGenerator : public Product {
public:
	Product * Clone() { return new HPCodeGenerator(*this); }
};
class HPOptimizer : public Product {
public:
	Product * Clone() { return new HPOptimizer(*this); }
};

class SunScanner : public Product {
public:
	Product * Clone() { return new SunScanner(*this); }
};

class SunParser : public Product {
public:
	Product * Clone() { return new SunParser(*this); }
};
class SunCodeGenerator : public Product {
public:
	Product * Clone() { return new SunCodeGenerator(*this); }
};
class SunOptimizer : public Product {
public:
	Product * Clone() { return new SunOptimizer(*this); }
};

//추가로 필요한 부분
class HPErrorHandler :public Product {
public:
	Product * Clone() { return new HPErrorHandler(*this); }
};

class SunErrorHandler : public Product {
public:
	Product * Clone() { return new SunErrorHandler(*this); }
};

////////////////most important
class CompilerFactory {
public:
	virtual Product * CreateProduct(Product *p) = 0;
};

class HPCompilerFactory : public CompilerFactory {
public:
	Product * CreateProduct(Product *p) {
		return p->Clone();
	}
};

class SunCompilerFactory : public CompilerFactory {
public:
	Product * CreateProduct(Product *p) {
		return p->Clone();
	}
};
CompilerFactory * pFactory = nullptr;
int main() {
	Product *pScanner, *pParser, *pCodeGenerator, *pOptimizer;
	Product *pErrorHandler; // 추가됨


	struct utsname sysInfo;

	if (uname(&sysInfo) < 0) {
		std::cout << "Error Occured!" << std::endl;
		return 0;
	}

	//HPUX
	if (stricmp(sysInfo.sysname, HPUX, strlen(HPUX)) == 0) {
		pScanner = new HPScanner;
		pParser = new HPParser;
		pCodeGenerator = new HPCodeGenerator;
		pOptimizer = new HPOptimizer;
		pErrorHandler = new HPErrorHandler;

		pFactory = new HPCompilerFactory;
	}//SUNOS
	else if (stricmp(sysInfo.sysname, SUNOS, strlen(SUNOS)) == 0) {
		SunScanner scanner;
		SunParser parser;
		SunCodeGenerator codeGenerator;
		SunOptimizer optimizer;

		pFactory = new CompilerFactory(&scanner, &parser, &codeGenerator, &optimizer);
	}
	else {
		//지원하지 않는 시스템 환경
	}

	Product * pNewScanner = pFactory->CreateProduct(pScanner);

}