#ifndef TYPE_H
#define TYPE_H

#include <string>

class Type {
public:
	Type(std::string name);
	~Type();

	std::string getName();
private:
	std::string name_;
};

#endif // TYPE_H
