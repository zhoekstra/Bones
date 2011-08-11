/*
 * basic_visitor.cpp
 *
 *  Created on: Jun 7, 2011
 *      Author: norton
 */

#include <basic_visitor.hpp>

void line_visitor::default_in(__node* node) {
  node->line() = line;
  node->poss() = poss;
}

void line_visitor::token_in(token* node) {
  line = node->line();
  poss = node->poss();
}

void dot_visitor::default_in(__node* node) {
  token* tok;

  if(node_stack.empty()) {
    ostr << "digraph ASTGraph {" << std::endl;
  }

  ostr << count << " [ label=\"";
  ostr << node->name();
  if((tok = dynamic_cast<token*>(node)) != NULL)
    ostr<< "\\n" << tok->txt();
  ostr << "\\nLine = " << node->line();
  ostr << "\\nPoss = " << node->poss();
  ostr << "\" ];" << std::endl;
  if(!node_stack.empty())
    ostr << node_stack.back() << " -> " << count << std::endl;
  count++;

  node_stack.push_back(count - 1);
}

void dot_visitor::default_out(__node* node) {
  node_stack.pop_back();
  if(node_stack.empty()) {
    ostr << "}" << std::endl;
  }
  ostr << std::flush;
}

