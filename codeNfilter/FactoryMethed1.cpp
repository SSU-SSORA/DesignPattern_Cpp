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
};

class HPCompilerFactory : public CompilerFactory {
public:
	Scanner * CreateScanner() { new HPScanner; }
	Parser * CreateParser() {new HPParser;}
	CodeGenerator * CreateCodeGenerator(){ new HPCodeGenerator; }
	Optimizer * CreateOptimizer() {new HPOptimizer;};
};

class SunCompilerFactory : public CompilerFactory {
public:
	Scanner * CreateScanner() { new SunScanner; }
	Parser * CreateParser() { new SunParser; }
	CodeGenerator * CreateCodeGenerator() { new SunCodeGenerator; }
	Optimizer * CreateOptimizer() { new SunOptimizer; };
};

CompilerFactory * pFactory;

int main() {
	typedef struct {
		char * sysname;
	}utsname;
	utsname sysInfo;

	// -- OS���� �� �ϵ���� Ÿ�� ������ ��� ���� �ý��� �Լ�
	//������������ �۵���
	/*if (uname(&sysInfo) < 0) {
		std::cout << "Error Occurred!" << std::endl;
		return -1;
	}*/

	if (stricmp(sysInfo.sysname, HPUX, strlen(HPUX)) == 0) {
		//HP �� ��ü ���� �� ���
		pFactory = new HPCompilerFactory();
	}

	if (stricmp(sysInfo.sysname, SUNOS, strlen(SUNOS)) == 0) {
		//Sun �� ��ü ���� �� ���
		pFactory = new SunCompilerFactory();
	}
	//�������� �ʴ� �ý��ۿ� ���Ͽ�
	else return 0;
	

	//Abstract Factory Pattern �ٽ� ��Ʈ
	Scanner * pScanner = pFactory->CreateScanner();
	Parser * pParser = pFactory->CreateParser();
	CodeGenerator * pCodeGenerator = pFactory->CreateCodeGenerator();
	Optimizer * pOptimizer = pFactory->CreateOptimizer();

}