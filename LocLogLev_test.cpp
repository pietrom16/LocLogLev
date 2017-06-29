/// LocLogLev_test.cpp

// Ref.: http://en.cppreference.com/w/cpp/language/operators

#include <iostream>
#include "LocLogLev.h"


static const LogLevel localThreshold  = verbose;


// Test log class; it should work with every logger

class TestLog
{
	bool ignore;

public:
	TestLog& operator()(LogLevel _level) {
		if(_level >= globalThreshold)
			ignore = false;
		else
			ignore = true;
		return *this;
	}

	template<typename T>
	TestLog& operator<<(T const& _token) {
		if(ignore == false)
			std::cout << _token << std::flush;
		return *this;
	}
};


int main()
{
	TestLog log;
	int j = int(localThreshold);

	for(int i = nolog; i <= fatal; ++i)
	{
		LogLevel level = LogLevel(i);

		log(level) << "Test message, level: " << level << "\n";
		log(Level(i, j)) << "Function | Test message, level: " << level << " Local threshold: " << localThreshold << "\n";
		log(level | localThreshold) << "Operator | Test message, level: " << level << " Local threshold: " << localThreshold << "\n";
	}

	return 0;
}
