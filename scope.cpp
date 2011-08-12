/*
 * scope.cpp
 *
 *  Created on: Jun 14, 2011
 *      Author: norton
 */

#include <scope.hpp>
#include <symtable.hpp>

scope::~scope() {
  for(auto iter = _map.begin(); iter != _map.end(); iter++) {
    delete iter->second;
  }
}

STE* scope::get(const std::string& ste_name) {
  if(_map.find(ste_name) != _map.end())
    return _map[ste_name];
  if(_enclosing != NULL)
    return _enclosing->get(ste_name);
  return NULL;
}

STE* scope::contains(const std::string& ste_name) {
  if(_map.find(ste_name) != _map.end())
    return _map[ste_name];
  return NULL;
}

void scope::insert(STE* new_ste) {
  _map[new_ste->name()] = new_ste;
}

void scope::clean() {
  for(auto iter = _map.begin(); iter != _map.end(); iter++) {
    if(dynamic_cast<unamed_STE*>(iter->second) != NULL) {
      _map.erase(iter);
    }
  }
}

int scope::dot(std::ostream& ostr) {
  int label = symtable::label_gen++;
  int field_label = 1;
  int target = 0;

  ostr << "  " << label << "[label =\" <f0> Scope";
  for(auto iter = _map.begin(); iter != _map.end(); iter++)
    ostr << "| <f" << field_label++ << "> mDict\\[" << iter->first << "\\] ";
  ostr << "\"];" << std::endl;

  field_label = 1;
  for(auto iter = _map.begin(); iter != _map.end(); iter++) {
    target = get(iter->first)->dot(ostr);
    ostr << "  " << label << ":<f" << field_label++ << "> -> " << target << ":<f0>;" << std::endl;
  }

  return label;
}
