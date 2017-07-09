#include <iostream>
#include <string.h>

#define HPUX "HPUX"
#define SUNOS "Sunos"

class Scanner {
public:
	virtual ~Scanner() = 0;
};

class Parser {
public:
	virtual ~Parser() = 0;
};

class CodeGenerator {
public:
	virtual ~CodeGenerator() = 0;
};

class Optimizer {
public:
	virtual ~Optimizer() = 0;
};

Scanner::~Scanner() {}
Parser::~Parser() {}
CodeGenerator::~CodeGenerator() {}
Optimizer::~Optimizer() {}

class HPScanner :public Scanner {};
class HPParser : public Parser {};
class HPCodeGenerator :public CodeGenerator {};
class HPOptimizer :public Optimizer {};

class SunScanner :public Scanner {};
class SunParser : public Parser {};
class SunCodeGenerator :public CodeGenerator {};
class SunOptimizer :public Optimizer {};



class CompilerFactory {
public:
	virtual Scanner * CreateScanner() = 0;
	virtual Parser * CreateParser() = 0;
	virtual CodeGenerator * CreateCodeGenerator() = 0;
	virtual Optimizer * CreateOptimizer() = 0;
protected:
	CompilerFactory() {}
	CompilerFactory(const CompilerFactory&rhs);
	static CompilerFactory *pInstance_;
};

class HPCompilerFactory : public CompilerFactory {
public:

	//보통은 인스턴스생성함수를 Base클래스에서 작성해야 하나, 여기서는
	//자식 클래스에서만 작성함
	//자식 클래스가 새로 생겼을 때에 수정범위를 줄이기 위해서이다.
	//만약 부모클래스에 CreateInstance함수가 있다면 자식이 생길때마다 소스코드를
	//수정해야 하기 때문이다.
	static HPCompilerFactory * CreateInstance() {
		if (pInstance_ == nullptr)
			pInstance_ = new HPCompilerFactory;
		return (HPCompilerFactory *)pInstance_;
	}

	Scanner * CreateScanner() { new HPScanner; }
	Parser * CreateParser() { new HPParser; }
	CodeGenerator * CreateCodeGenerator() { new HPCodeGenerator; }
	Optimizer * CreateOptimizer() { new HPOptimizer; };
protected:
	HPCompilerFactory() {}
	HPCompilerFactory(const HPCompilerFactory & rhs);
};

class SunCompilerFactory : public CompilerFactory {
public:
	static SunCompilerFactory * CreateInstance() {
		if (pInstance_ == nullptr)
			pInstance_ = new SunCompilerFactory;
		return (SunCompilerFactory *)pInstance_;
	}

	Scanner * CreateScanner() { new SunScanner; }
	Parser * CreateParser() { new SunParser; }
	CodeGenerator * CreateCodeGenerator() { new SunCodeGenerator; }
	Optimizer * CreateOptimizer() { new SunOptimizer; };
protected:
	SunCompilerFactory() {}
	SunCompilerFactory(const SunCompilerFactory & rhs);
};

CompilerFactory * CompilerFactory::pInstance_ = nullptr;
CompilerFactory * pFactory;

int main() {
	typedef struct {
		char * sysname;
	}utsname;
	utsname sysInfo;

	// -- OS버전 및 하드웨어 타입 정보를 얻기 위한 시스템 함수
	//리눅스에서만 작동함
	/*if (uname(&sysInfo) < 0) {
	std::cout << "Error Occurred!" << std::endl;
	return -1;
	}*/

	if (stricmp(sysInfo.sysname, HPUX, strlen(HPUX)) == 0) {
		//HP 용 객체 생성 및 사용
		pFactory = new HPCompilerFactory();
	}

	if (stricmp(sysInfo.sysname, SUNOS, strlen(SUNOS)) == 0) {
		//Sun 용 객체 생성 및 사용
		pFactory = new SunCompilerFactory();
	}
	//지원하지 않는 시스템에 대하여
	else return 0;


	//Abstract Factory Pattern 핵심 파트
	Scanner * pScanner = pFactory->CreateScanner();
	Parser * pParser = pFactory->CreateParser();
	CodeGenerator * pCodeGenerator = pFactory->CreateCodeGenerator();
	Optimizer * pOptimizer = pFactory->CreateOptimizer();

}