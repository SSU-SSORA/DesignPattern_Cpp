#include <iostream>
using namespace std;

class Request {
public:
	virtual ~Request() {}
};

class HelpRequest :public Request {};
class PrintRequest : public Request {};

class Handler {
public:
	Handler(Handler * pObj) : pSuccessor_(pObj) {}
	virtual void HandleRequest(Request * pReq) {
		if (dynamic_cast<HelpRequest *>(pReq) != NULL) {
			//helpRequest에 대한 처리
			cout << "HelpRequest Processing" << endl;
		}
		else if (dynamic_cast<PrintRequest *>(pReq) != NULL) {
			cout << "PrintRequest Processing" << endl;
		}
		else cout << "Default Processing";
	}

private:
	Handler * pSuccessor_;
};

int main() {
	Handler hdlr(0);
	Request * pReq = new PrintRequest;

	hdlr.HandleRequest(pReq);
}