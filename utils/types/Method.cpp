#include "Method.hpp"

#include <algorithm>

#include "../trees/Block.hpp"
#include "../trees/Tree.hpp"

#include "Type.hpp"

Method::Method(bool override, const std::string &identifier, const std::vector<Parameter> &parameters, 
	const std::string &returnTypeIdentifier, Tree *body) : override(override), identifier(identifier), 
	parameters(parameters), returnTypeIdentifier(returnTypeIdentifier), body(body) {}

Method::Method(bool override, const std::string &identifier, const std::vector<Parameter> &parameters, 
	const std::string &returnTypeIdentifier, Block *body) : override(override), identifier(identifier), 
	parameters(parameters), returnTypeIdentifier(returnTypeIdentifier), body(body) {}

bool Method::isCorrect(const Type &parent, const Environment &env) const {
	if (!correctDecl())
		return false;
	if (std::holds_alternative<Block*>(body))
		return std::get<Block*>(body)->isCorrect(env);
	return std::get<Tree*>(body)->isCorrect(env);
}
	
bool Method::correctDecl(const Type &parent, const Environment &env) const {
	if (override) {
		if (!parent.hasSuper()) {
			std::cout << "\033[91merror:\033[0m '" << parent.identifier << "::" << *this 
				<< "' marked 'override', but does not override" << std::endl;
			return false;
		}
		/* On est suppos� d�j� avoir v�rifier l'existance de la super classe. */
		if (std::find(env.env.at(parent.super())->methods.begin(), env.env.at(parent.super())->methods.end(), *this) == 
			env.env.at(parent.super())->methods.end()) {
			std::cout << "\033[91merror:\033[0m '" << parent.identifier << "::" << *this 
				<< "' marked 'override', but does not override" << std::endl;
			return false;
		}
	}
	return true;
}

std::ostream &Method::print(std::ostream &os) const {
	os << identifier << '(';
	for (auto it = parameters.cbegin(); it != parameters.cend(); it++) {
		os << *it;
		if (it != parameters.cend() - 1)
			os << ", ";
	}
	os << ')';
	if (override)
		os << " override";
	if (!returnTypeIdentifier.empty())
		os << " : " << returnTypeIdentifier;
	return os;
}

std::ostream &operator<<(std::ostream &os, const Method &m) {
	return m.print(os);
}

/*
Method &operator+=(Method &lhs, const Variable &rhs) {
	lhs.parameters.push_back(rhs);
	return lhs;
}
	
Method operator+(const Method &lhs, const Variable &rhs) {
    Method result = lhs;
	result.parameters.push_back(rhs);
    return result;
}
*/

bool operator==(const Method &lhs, const Method &rhs) {
    if (lhs.parameters.size() != rhs.parameters.size())
        return false;
    if (lhs.identifier != rhs.identifier)
        return false;
    for (std::size_t i = 0; i < rhs.parameters.size(); i++)
        if (lhs.parameters[i].typeIdentifier != rhs.parameters[i].typeIdentifier)
            return false;
    return true;
}
