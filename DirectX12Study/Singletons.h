#pragma once
class Singletons
{
public:
	Singletons() {}
	virtual ~Singletons() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Delete() = 0;

protected:

};

