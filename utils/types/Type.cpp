#include "Type.hpp"

Type::Type(std::string const &identifier, std::vector<Variable> const &fields, Constructor &constructor,
	std::vector<Method> const &methods) : identifier(identifier), fields(fields), constructor(constructor),
	methods(methods) {}

Type::Type(Type const &other) : identifier(other.identifier), fields(other.fields), constructor(other.constructor),
	methods(other.methods) {}

Type::Type(Type &&other) : identifier(other.identifier), fields(other.fields), constructor(other.constructor),
	methods(other.methods) {}
	
Type::~Type() {
	delete &constructor;
}
	
bool Type::correctDecl(std::map<std::string, Type*> &env) const {
	//le vecteur qui contient toutes les variables connues dans ce type
	std::vector<Variable> envVar;
	
    /* Cas où le nom de la classe est déjà pris. */
	if (env.find(identifier) != env.end())
        return false;
	/* Vérifie la validité du constructeur. */
	/*if(this->fields != constructor.parameters)//si les paramètres de la classe et du constructeur ne sont pas les mêmes
		return false;*/
	if (!constructor.correctDecl(env, envVar))
		return false;
	/* Vérifie la validité des méthodes. */
	for (Method const &method : methods)
		if (!method.correctDecl(env, envVar))
			return false;
    return true;
}

