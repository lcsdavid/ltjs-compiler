#include "Type.hpp"

Type::Type(const std::string &identifier, const std::vector<Variable> &fields, Constructor &constructor,
	const std::vector<Method> &methods) : identifier(identifier), fields(fields), constructor(constructor),
	methods(methods) {}
	
Type::~Type() {
	delete &constructor;
}

bool Type::isCorrect(Environment &env) const {
	/* Vérifie la déclaration de la classe. */
	if (!correctDecl(env))
		return false;
	/* Vérifie la validité du constructeur. */
	if (!constructor.isCorrect(*this, env))
		return false;
	/* Vérifie la validité des méthodes. */
	for (const Method &method : methods)
		if (!method.isCorrect(*this, env))
			return false;	
	/* ??? */
	/* On ajoute les variables au scope si elles existent, sinon on retourne une erreur. */
	/*for(std::size_t i = 0; i < parameters.size; i++){
		if(env.env.find(parameters.at(i).identifier) == env.env.end)
			return false;
		env.fields.push_back(parameters.at(i));
	}
	//en sortie de la classe on supprimer les variables locales
	for(size_t i; i<parameters.size(); i++){
		env.fields.pop_back();
	}*/
}

bool Type::correctDecl(const Environment &env) const {
    /* Cas où le nom de la classe est déjà pris. */
	if (env.env.count(identifier)) {
		std::cout << "\033[91merror:\033[0m redéfinition de '" << identifier << '\'' << std::endl;
        return false;
	}
	/* Vérifie la déclaration des champs. */
	for (auto it = fields.cbegin(); it != fields.cend(); it++) {
		if (!env.env.count((*it).typeIdentifier)) {
			std::cout << "\033[91merror:\033[0m ‘" << (*it).typeIdentifier << "’ was not declared in this scope" << std::endl;
			return false;
		}
	}
	return true;
}

Method &Type::know(const std::string &methodIdentifier) {
	for(auto it = methods.begin(); it != methods.end(); it++){
		if((*it).identifier == methodIdentifier)
			return *it;
	throw std::logic_error(identifier + "::" + methodIdentifier + " was not declared in this scope");
}

std::ostream &operator<<(std::ostream &os, const Type &t) {
	return t.print(os);
}

