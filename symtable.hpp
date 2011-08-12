/*
 * symtable.hpp
 *
 *  Created on: Jun 13, 2011
 *      Author: norton
 */

#ifndef SYMTABLE_HPP_INCLUDE
#define SYMTABLE_HPP_INCLUDE

#include <node.hpp>
#include <scope.hpp>
#include <visitor.hpp>

#include <iostream>
#include <map>
#include <string>
#include <vector>

/* TODO, this needs to be replaced with the actual pool class */
class pool {

};

inline std::ostream& operator<<(std::ostream& ostr, const pool& p) {
  return (ostr << "[not implemented]");
}

/* end stuff that needs to be gone */

class STE {
  public:

    STE() :
      _name() { }
    STE(std::string& name) :
      _name(name) { }
    virtual ~STE() { }

    inline std::string  name() const { return _name; }
    inline std::string& name()       { return _name; }

    virtual int dot(std::ostream& ostr) = 0;

  protected:

    std::string _name;
};

class unamed_STE : public STE {
  public:
    unamed_STE(scope* _scope) :
      STE(), _scope(new scope(_scope)) { }
    virtual ~unamed_STE() { delete _scope; }

    inline scope* g_scope() const
      { return _scope; }

    virtual int dot(std::ostream& ostr);

  protected:
    scope* _scope;
};

class variable : public STE {
  public:
    variable(std::string name) :
      STE(name), _val() { }
    virtual ~variable() { }

    pool  value() const { return _val; }
    pool& value()       { return _val; }

    virtual int dot(std::ostream& ostr);

  protected:

    pool _val;
};

class function : public STE {
  public:

    typedef std::map<std::string, variable*> param_m;
    typedef param_m::              iterator               iterator;
    typedef param_m::        const_iterator         const_iterator;
    typedef param_m::      reverse_iterator       reverse_iterator;
    typedef param_m::const_reverse_iterator const_reverse_iterator;

    function(std::string name, scope* _scope) :
      STE(name), _scope(new scope(_scope)), _params() { }
    virtual ~function() { delete _scope; }

    virtual int dot(std::ostream& ostr);

    inline scope*       g_scope() const        { return _scope; }
    inline variable*&   get(std::string& name) { return _params[name]; }
    inline funcdecl_b*& ast()                  { return _ast; }

    inline               iterator begin()        { return _params.begin();  }
    inline               iterator end()          { return _params.end();    }
    inline         const_iterator begin()  const { return _params.begin();  }
    inline         const_iterator end()    const { return _params.end();    }
    inline       reverse_iterator rbegin()       { return _params.rbegin(); }
    inline       reverse_iterator rend()         { return _params.rend();   }
    inline const_reverse_iterator rbegin() const { return _params.rbegin(); }
    inline const_reverse_iterator rend()   const { return _params.rend();   }

    pool operator()();

  protected:
    scope*      _scope;
    param_m     _params;
    funcdecl_b* _ast;
};

class symtable {
  public:
    static int label_gen;

    symtable() :
      _global(new scope(NULL)), _stack() { push(_global); }
    virtual ~symtable() { delete _global; }

    inline scope* current() const { return _stack.back(); }
    inline scope* global() { return _global; }
    inline void insert(STE* new_ste) { _stack.back()->insert(new_ste); }
    inline void push(scope* _scope) { _stack.push_back(_scope); }
    inline void pop() { _stack.pop_back(); }

    void clean();

    STE* operator[](std::string name) { return _stack.back()->get(name); }

    void dot(std::ostream& ostr);

  protected:
    scope*                   _global;
    std::vector<scope*>      _stack;
};

class sym_table_creator : public depth_first_visitor {
  public:
    sym_table_creator(symtable* table) :
      _current(NULL), _table(table), _dup(false) { }
    virtual ~sym_table_creator() { }

    inline symtable* table() const { return _table; }

    virtual void        param_b_v(       param_b* node);
    virtual void      vardecl_s_v(     vardecl_s* node);
    virtual void constvardecl_s_v(constvardecl_s* node);

    virtual void    block_s_in (   block_s* node);
    virtual void    block_s_out(   block_s* node);
    virtual void funcdecl_b_in (funcdecl_b* node);
    virtual void funcdecl_b_out(funcdecl_b* node);

  protected:

    function*                      _current;
    symtable*                      _table;
    bool                           _dup;

};

#endif /* SYMTABLE_HPP_ */





