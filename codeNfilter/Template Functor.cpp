#include <iostream>
using namespace std;

class FunctorBase {
public:
	typedef void (FunctorBase::_MemFunc) ();
	
	FunctorBase() : callee(0), func(0) {}
	FunctorBase(const void * c, const void *f, size_t sz) {
		if (c) {
			callee = (void *)c;
			memcpy(memFunc, f, sz);
		}
		else {
			func = f;
		}
	}

	operator int() const { return func || callee; }
	class DummyInit {};

	union {
		const void * func;
		char memFunc[sizeof(_MemFunc)];

		void *callee;
	};
};

class Functor0 : protected FunctorBase {
public:
public:
	Functor0(DummyInit * = 0) {}
	void operator()() const { thunk(*this); }
	FunctorBase::operator int;

protected:
	typedef void(*Thunk)(const FunctorBase&);
	Functor0(Thunk t, const void *c, const void *f, size_t sz)
		:FunctorBase(c, f, sz), thunk(t) {}
private:
	Thunk thunk;
};

template<class P1>
class Functor1 : protected FunctorBase {
public:
	Functor1(DummyInit * = 0) {}
};

//fail to understand this pattern...
