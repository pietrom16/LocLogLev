/// LocLogLev_test.cpp

// Ref.: http://en.cppreference.com/w/cpp/language/operators

#include <iostream>
#include "LocLogLev.h"


static const LogLevel cLocalThreshold  = verbose;


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
	TestLog  log;
	LogLevel localThreshold    = cLocalThreshold;
	int      intLocalThreshold = int(cLocalThreshold);

	std::cout << "\nGlobal threshold = " << globalThreshold;
	std::cout << "\nLocal threshold  = " << intLocalThreshold << "\n";

	for(int intLevel = nolog; intLevel <= fatal; ++intLevel)
	{
		LogLevel level = LogLevel(intLevel);

		std::cout << "\nLevel = " << level << ":\n";

		log(level) << "Test message, level: " << level << "\n";
		log(Level(intLevel, intLocalThreshold)) << "Function Level()  Test message, level: " << level << " Local threshold: " << localThreshold << "\n";
		log(level | localThreshold)             << "Operator |        Test message, level: " << level << " Local threshold: " << localThreshold << "\n";
	}

	return 0;
}
