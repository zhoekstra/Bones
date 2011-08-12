/*
 * dice.cpp
 *
 *  Created on: Jul 18, 2011
 *      Author: Alex Norton
 */

#include <basic_visitor.hpp>
#include <node.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

extern int yyparse(void);
extern FILE* yyin;

po::variables_map vm;

_i_stmt*    stmt;
funcdecl_b* func;
bool        closing;

int interpret() {
  bool visit_ast = false;
  line_visitor line;
  dot_visitor  ast;

  yyin = stdin;

  if(vm.count("ast")) {
    ast.open(vm["ast"].as<std::string>());
    visit_ast = true;
  }

  while(!closing) {
    std::cout << ">>> " << std::flush;
    yyparse();



    ast.clear();

    if(stmt) {
      if(visit_ast)
        stmt->accept(&ast);
    }

    if(func) {
      if(visit_ast)
        func->accept(&ast);
    }
  }

  if(vm.count("ast")) {
    ast.close();
  }

  return 0;
}

int main(int argc, char** argv) {

  /* command line parsing */
  po::options_description desc("Allowed options");
  desc.add_options()
      ("help,h", "produce help message")
      ("verbose,v", "turns the verbose flag on")
      ("file,f", po::value<std::string>(), "specify input file")
      ("ast,a",  po::value<std::string>(), "print the ast to a file")
  ;

  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  /* check help message first */
  if(vm.count("help")) {
    std::cout << desc << std::endl;
    return 1;
  }

  /* check to see if we are being run with a file */
  if(vm.count("file")) {
    std::ostringstream sostr;
    sostr << argv[0] << " < " << vm["file"].as<std::string>();
    return system(sostr.str().c_str());
  }

  return interpret();
}

