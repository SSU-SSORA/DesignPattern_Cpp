#pragma once
#include "item.h"

class Iterator;

class AbstractList {
public:
	virtual Iterator * CreateIterator() = 0;

	int Count();
	virtual void AddNext(Item *pNewItem, Item *pItem = 0) = 0;
	virtual void AddChild(Item *pNewItem, Item *pItem = 0) = 0;
	virtual void Remove(Item *pItem) = 0;
	virtual Item* GetItem(int pos) = 0;
protected:
	AbstractList() : totalCnt_(0) {}
	int totalCnt_;
};

class LinkedList : public AbstractList {
	LinkedList() : pFirst_(0) {}

	struct LinkedItem {
		LinkedItem(Item* pItem = 0, LinkedItem *pNext = 0)
			: pData_(pItem), pNext_(pNext) {}
		Item * pData_;
		LinkedItem* pNext_;
	};

	Iterator * CreateIterator();
	void AddNext(Item *pNewItem, Item* pItem = 0);
	void AddChild(Item* pNewItem, Item *pItem = 0);
	void Remove(Item *pItem);
	Item* GetItem(int pos);

private:
	LinkedItem *pFirst_;
};

class TreeList : public AbstractList {
public:
	TreeList() : pRoot_(0) {}

	struct TreeItem {
		TreeItem(Item* pItem = 0, TreeItem* pParent = 0,
			TreeItem *pFirstChild = 0, TreeItem* pSibling = 0)
			:pData_(pItem), pParent_(pParent), pFirstChild_(pFirstChild),
			pSibling_(pSibling) {}

		Item* pData_;
		TreeItem* pParent_;
		TreeItem* pFirstChild_;
		TreeItem* pSibling_;
	};

	Iterator *CreateIterator();
	void AddNext(Item * pNewItem, Item* pItem = 0);
	void AddChild(Item * pNewItem, Item * pItem = 0);
	void Remove(Item *pItem);
	Item* GetItem(int pos);

protected:
	TreeItem* GetNext(const TreeItem* pStart);
private:
	TreeItem* pRoot_;
};