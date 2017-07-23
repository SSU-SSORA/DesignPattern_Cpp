#include <iostream>
#include <list>
#include <iterator>
#include <map>
using namespace std;

class Position {
public:
	Position() {}
	Position(int x, int y) {
		x_ = x, y_ = y;
	}
	int x_, y_;
};

class Graphic {
public:
	virtual void Draw(Position& pos) = 0;
	virtual Graphic * Clone() = 0;
};

class Triangle : public Graphic {
public:
	void Draw(Position& pos) {}
	Graphic * Clone() { return new Triangle(*this); }
};

class Rectangle : public Graphic {
public:
	void Draw(Position& pos) {}
	Graphic* Clone() { return new Rectangle(*this); }
};

class GraphicComposite : public Graphic {
public:
	void Draw(Position& pos) {}
	Graphic* Clone() {
		GraphicComposite *pGraphicComposite = new GraphicComposite(*this);
		list<Graphic*>::iterator iter2;
		iter2 = pGraphicComposite->components_.begin();
		for (auto& a : components_) {
			Graphic* pNewGraphic = a->Clone();
			*iter2 = pNewGraphic;
			iter2++;
		}
		return pGraphicComposite;
	}

private:
	list<Graphic*> components_;
};

class Document {
public:
	void Add(Graphic* pGraphic) {}
};

class Mouse {
public:
	bool IsLeftButtonPushed() {
		bool isPushed;
		//GUI�Լ��� Ȱ���Ͽ� Button ���¸� üũ�Ѵ�.
		return isPushed;
	}

	Position GetPosition() {
		Position pos;
		//GUI�Լ��� Ȱ���� ���� ���콺 ��ġ�� �ľ��Ѵ�.
		return pos;
	}
};

Mouse _mouse;

class GraphicEditor {
public:
	void AddNewGraphics(Graphic* pSelected) {
		Graphic* pObj = pSelected->Clone();
		while (_mouse.IsLeftButtonPushed()) {
			Position pos = _mouse.GetPosition();
			pObj->Draw(pos);
		}

		curDoc_.Add(pObj);
	}
private:
	Document curDoc_;
};

class Palette {
public:
	Palette() {
		Graphic* pGraphic = new Triangle;
		items_[1] = pGraphic;

		pGraphic = new Rectangle;
		items_[2] = pGraphic;

		//�ʿ��� ��ŭ ���
	}

	void RegisterNewGraphic(Graphic* pGraphic) {
		items_[items_.size() + 1] = pGraphic;
	}

	Graphic* GetSelectedObj() {
		return items_[GetItemOrder()];
	}

	int GetItemOrder() {
		int i;
		Position curPos = _mouse.GetPosition();

		//���� ���콺 ��ġ�� �� ��° �׸��� �����ϴ��� �Ǻ�
		return i;
	}
private:
	map<int, Graphic *> items_;
};

int main() {
	Palette palette;
	GraphicEditor ged;

	ged.AddNewGraphics(palette.GetSelectedObj());
}