/*
 * basic_visitor.hpp
 *
 *  Created on: Jun 7, 2011
 *      Author: norton
 */

#ifndef BASIC_VISITOR_HPP_INCLUDE
#define BASIC_VISITOR_HPP_INCLUDE

#include <visitor.hpp>

#include <iostream>
#include <fstream>

class line_visitor : public reverse_first_visitor {
  public:

    line_visitor() :
      line(0), poss(0) { }
    virtual ~line_visitor() { }

    virtual void default_in(__node* node);
    virtual void token_in(token* node);

  private:
    int line;
    int poss;
};

class dot_visitor : public depth_first_visitor {
  public:

    dot_visitor() :
      count(0), ostr(), node_stack() { }
    virtual ~dot_visitor() { }

    virtual void default_in (__node* node);
    virtual void default_out(__node* node);

    inline void open(const std::string& str)
      { fname = str; ostr.open(str.c_str(), std::ios::trunc); }
    inline void close()
      { fname = "";  ostr.close(); }
    inline void clear()
      { ostr.close(); ostr.open(fname.c_str(), std::ios::trunc); }

  private:

    int              count;
    std::string      fname;
    std::ofstream     ostr;
    std::vector<int> node_stack;
};

#endif /* BASIC_VISITOR_HPP_INCLUDE */
