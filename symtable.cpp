/*
 * symtable.cpp
 *
 *  Created on: Jun 14, 2011
 *      Author: norton
 */

#include <symtable.hpp>

#define ptrs(ptr) (unsigned long)ptr

int symtable::label_gen = 0;

/* ************************************************************************** */
/* *** STE functions ******************************************************** */
/* ************************************************************************** */

int unamed_STE::dot(std::ostream& ostr) {
  int label = symtable::label_gen++;
  int target;

  ostr << "  " << label << "[label=\"";
  ostr << " <f0> unnamed scope" <<
        " | <f1> mScope \"];" << std::endl;

  target = _scope->dot(ostr);
  ostr << "  " << label << ":<f3> -> " << target << ":<f0>;" << std::endl;

  return label;
}

int variable::dot(std::ostream& ostr) {
  int label = symtable::label_gen++;

  ostr << "  " << label << "[label=\"";
  ostr << " <f0> variable" <<
        " | <f1> mName = " << _name <<
        " | <f2> value = " << _val << "\"];" << std::endl;

  return label;
}

int function::dot(std::ostream& ostr) {
  int label = symtable::label_gen++;
  int target = 0;

  ostr << "  " << label << "[label=\"";
  ostr << " <f0> function" <<
        " | <f1> mName = " << _name <<
        " | <f2> mSigniture = ( ";

  for(auto iter = _params.begin(); iter != _params.end(); iter++) {
    ostr << iter->second->name() << " ";
  }

  ostr << ") " <<
      " | <f3> mScope \"];" << std::endl;

  target = _scope->dot(ostr);
  ostr << "  " << label << ":<f3> -> " << target << ":<f0>;" << std::endl;

  return label;
}

/* ************************************************************************** */
/* *** symbol table functions *********************************************** */
/* ************************************************************************** */

void symtable::clean() {
  _global->clean();
}

void symtable::dot(std::ostream& ostr) {
  ostr << "digraph SymTable {\n" <<
      "  graph [rankdir=\"LR\"];\n" <<
      "  node [shape=record];" << std::endl;
  _global->dot(ostr);
  ostr << "}" << std::endl;
}

/* ************************************************************************** */
/* *** visitor functions **************************************************** */
/* ************************************************************************** */

void sym_table_creator::param_b_v(param_b* node) {
  if(_table->current()->contains(node->name()->txt()) != NULL) {
    _dup = true;
    std::cerr << "[" << node->line() << "," << node->poss() << "]" <<
        " Redefined symbol " << node->name()->txt() << std::endl;
  }

  variable* v = new variable(
      node->name()->txt());

  _current->get(v->name()) = v;
  _table->insert(v);
}

void sym_table_creator::vardecl_s_v(vardecl_s* node) {
  if(_table->current()->contains(node->name()->txt()) != NULL) {
    _dup = true;
    std::cerr << "[" << node->line() << "," << node->poss() << "]" <<
        " Redefined symbol " << node->name()->txt() << std::endl;
  }

  _table->insert(
      new variable(
          node->name()->txt()));
}

void sym_table_creator::constvardecl_s_v(constvardecl_s* node) {
  if(_table->current()->contains(node->name()->txt()) != NULL) {
    _dup = true;
    std::cerr << "[" << node->line() << "," << node->poss() << "]" <<
        " Redefined symbol " << node->name()->txt() << std::endl;
  }

  _table->insert(
      new variable(
          node->name()->txt()));
}

void sym_table_creator::block_s_in(block_s* node) {
  unamed_STE* ste = new unamed_STE(_table->current());
  _table->insert(ste);
  _table->push(ste->g_scope());
}

void sym_table_creator::block_s_out(block_s* node) {
  _table->pop();
}

void sym_table_creator::funcdecl_b_in(funcdecl_b* node) {
  if(_table->current()->contains(node->name()->txt()) != NULL) {
    _dup = true;
    std::cerr << "[" << node->line() << "," << node->poss() << "]" <<
        " Redefined symbol " << node->name()->txt() << std::endl;
  }

  _current = new function(node->name()->txt(), _table->current());
  _table->insert(_current);
  _table->push(_current->g_scope());
}

void sym_table_creator::funcdecl_b_out(funcdecl_b* node) {
  _table->pop();
}





