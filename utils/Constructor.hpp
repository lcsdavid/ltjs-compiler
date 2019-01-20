#ifndef CONSTRUCTOR_HPP
#define CONSTRUCTOR_HPP

#include <string>
#include <vector>

#include "Parameter.hpp"

struct Constructor {
	std::string identifier;            /* Identifiant. */
	std::vector<Parameter> parameters; /* Liste de paramètre. */
    // Tree tree;

    Constructor(std::string const &identifier, std::vector<Parameter> const &parameters);
	virtual ~Constructor() = default;
	
    virtual bool correctDecl() const;
};

struct ClassConstructor : Constructor {
	std::string *superIdentifier;              /* Identifiant du super constructeur appelé [optionnel]. */
	std::vector<std::string> *superParameters; /* Paramètres du super constructeur appelé [optionnel]. */
	
	ClassConstructor(std::string const &identifier, std::vector<Parameter> const &parameters,
		std::string *superIdentifier, std::vector<std::string> *superParameters);
		
	bool correctDecl() const override;
};

#endif