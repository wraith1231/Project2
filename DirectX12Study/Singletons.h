#pragma once
class Singletons
{
public:
	Singletons() {}
	virtual ~Singletons() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual ULONG Release() = 0;

protected:

};

