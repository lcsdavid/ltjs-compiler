#include "Parameter.hpp"

Parameter::Parameter(std::string const &identifier, std::string const &typeIdentifier, bool var) : Variable(identifier,
	typeIdentifier), var(var) {}

bool operator==(Parameter const &lhs, Parameter const &rhs) {
    return lhs.identifier == rhs.identifier && lhs.typeIdentifier == rhs.typeIdentifier && lhs.var == rhs.var;
}

bool operator!=(Parameter const &lhs, Parameter const &rhs) {
    return !(lhs == rhs);
}