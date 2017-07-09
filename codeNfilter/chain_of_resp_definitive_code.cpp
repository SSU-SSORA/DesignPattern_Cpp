#include <iostream>
using namespace std;

#define DEFAULT_REQUEST 0
#define HELP_REQUEST 1
#define PRINT_REQUEST 2

class Request {
public:
	virtual int GetKind() { return DEFAULT_REQUEST; }
};
class HelpRequest : public Request {
public:
	virtual int GetKind() { return HELP_REQUEST; }
};

class PrintRequest :public Request {
public:
	virtual int GetKind() { return PRINT_REQUEST; }
};

class Handler {
public:
	Handler(Handler * pObj) : pSuccessor_(pObj) {}
	virtual void HandleRequest(Request *pReq) {
		switch (pReq->GetKind()) {
		case HELP_REQUEST:
			cout << "HelpRequest Processing" << endl;
			break;
		case PRINT_REQUEST:
			cout << "printRequest Processing" << endl;
			break;
		default:
			cout << "Default Processing " << endl;
		}
	}

private:
	Handler * pSuccessor_;
};

int main() {
	Handler hdlr(0);
	Request *pReq = new PrintRequest;

	hdlr.HandleRequest(pReq);
}