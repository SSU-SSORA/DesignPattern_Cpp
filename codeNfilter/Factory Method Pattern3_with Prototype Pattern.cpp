#include <iostream>
#include <string.h>

#define HPUX "HPUX"
#define SUNOS "SunOS"

class Scanner {
public:
	virtual Scanner * Clone() = 0;
};

class Parser {
public:
	virtual Parser * Clone() = 0;
};

class CodeGenerator {
public:
	virtual CodeGenerator * Clone() = 0;
};

class Optimizer {
public:
	virtual Optimizer * Clone() = 0;
};

class HPScanner : public Scanner {
public:
	Scanner * Clone() { return new HPScanner(*this); };
};

class HPParser : public Parser {
public:
	Parser * Clone() { return new HPParser; }
};

class HPCodeGenerator :public CodeGenerator{
public:
	CodeGenerator * Clone() { return new HPCodeGenerator(*this); }
};

class HPOptimizer : public Optimizer {
public:
	Optimizer * Clone() { return new HPOptimizer(*this); }
};

class SunScanner : public Scanner {
public:
	Scanner * Clone() { return new SunScanner(*this); };
};

class SunParser : public Parser {
public:
	Parser * Clone() { return new SunParser; }
};

class SunCodeGenerator :public CodeGenerator {
public:
	CodeGenerator * Clone() { return new SunCodeGenerator(*this); }
};

class SunOptimizer : public Optimizer {
public:
	Optimizer * Clone() { return new SunOptimizer(*this); }
};

class CompilerFactory {
public:
	CompilerFactory(Scanner *pScanner, Parser * pParser, CodeGenerator *
		pCodeGenerator, Optimizer * pOptimizer) :
		pScanner_(pScanner), pParser_(pParser), pCodeGenerator_(pCodeGenerator),
		pOptimizer_(pOptimizer) {}

	Scanner * CreateScanner() { return pScanner_->Clone(); }
	Parser * CreateParser() { return pParser_->Clone(); }
	CodeGenerator * CreateCodeGenerator() { return pCodeGenerator_->Clone(); }
	Optimizer * CreateOptimizer() { return pOptimizer_->Clone();}

private:
	Scanner * pScanner_;
	Parser * pParser_;
	CodeGenerator * pCodeGenerator_;
	Optimizer * pOptimizer_;
};

CompilerFactory * pFactory;

int main() {
	struct utsname sysInfo;

	if (uname(&sysInfo) < 0) {
		std::cout << "Error Occured!" << std::endl;
		return 0;
	}

	//HPUX
	if (stricmp(sysInfo.sysname, HPUX, strlen(HPUX)) == 0) {
		HPScanner scanner;
		HPParser parser;
		HPCodeGenerator codeGenerator;
		HPOptimizer optimizer;

		pFactory = new CompilerFactory(&scanner, &parser, &codeGenerator, &optimizer);
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

	Scanner *pScanner;
	pScanner = pFactory->CreateScanner();

	Parser * pParser = pFactory->CreateParser();
	CodeGenerator *pCodeGenerator = pFactory->CreateCodeGenerator();
	Optimizer *pOptimizer = pFactory->CreateOptimizer();


}