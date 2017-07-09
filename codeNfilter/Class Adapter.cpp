#include <iostream>

using namespace std;

class Rectangle {
public:
	Rectangle(int x1, int y1, int x2, int y2) :
		x1(x1), x2(x2), y1(y1), y2(y2) {}
	void Draw() {}
private:
	int x1, x2, y1, y2;
};

class TextView {
public:
	Rectangle GetExtent() {
		return Rectangle(x1, y1, x1 + width, y1 + height);
	}
private:
	int x1, y1, width, height;
};

class Shape {
public:
	virtual Rectangle boundingBox() = 0;
};

class LineShape :public Shape {
public:
	Rectangle BoundingBox() {
		return Rectangle(x1, y1, x2, y2);
	}
private:
	int x1, x2, y1, y2;
};

class TextShape :public Shape ,private TextView{
public:
	Rectangle boundingBox() override {
		return GetExtent();
	}
};

void DisplayBoundingBox(Shape *pSelectedShape) {
	(pSelectedShape->boundingBox()).Draw();
}

int main() {
	TextShape text;
	DisplayBoundingBox(&text);
}