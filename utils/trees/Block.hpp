#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <vector>
#include <map>

#include "../variables/Parameter.hpp"
#include "../Environment.hpp"

struct Type;
struct Tree;

struct Block {
	std::vector<Parameter> varDecls;
	std::vector<Tree*> insts;

	Block(const std::vector<Parameter> &varDecls, const std::vector<Tree*> &insts);
	~Block() = default;

	bool correctDecl(Environment env) const;
}; 

#endif