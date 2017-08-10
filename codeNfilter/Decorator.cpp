#include <iostream>
using namespace std;

class Airplane {
public:
	virtual void Attack() = 0;
};

class FrontAttackAirplane : public Airplane {
public:
	void Attack() {
		cout << "���� ����" << endl;
	}
};

class Decorator : public Airplane {
public:
	Decorator(Airplane* pObj) { pComponent_ = pObj; }
	virtual ~Decorator() = 0;

	virtual void Attack() {
		if (pComponent_ != 0)
			pComponent_->Attack();
	}
private:
	Airplane * pComponent_;
};

Decorator::~Decorator() {}

class SideAttackAirplane : public Decorator {
public:
	SideAttackAirplane(Airplane *pObj) : Decorator(pObj) {}

	void Attack() {
		Decorator::Attack();

		cout << "�������" << endl;
	}
};

class RearAttackAirplane : public Decorator {
public:
	RearAttackAirplane(Airplane *pObj) : Decorator(pObj) {}

	void Attack() {
		Decorator::Attack();

		cout << "�Ĺ����" << endl;
	}
};

int main() {
	Airplane * pFrontAttackAirplane = new FrontAttackAirplane;
	Airplane * pSideAttackAirplane = new SideAttackAirplane(pFrontAttackAirplane);
	Airplane * pRearAttackAirplane = new RearAttackAirplane(pSideAttackAirplane);

	pRearAttackAirplane->Attack();
	delete pRearAttackAirplane;

	pSideAttackAirplane->Attack();

}