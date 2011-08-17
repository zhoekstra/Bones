#include "bones_visitor.hpp"

/**
 * Constructor
 */
bones_visitor::bones_visitor() {
  // Initialize global const variable d4, d6, d8, d10, and d20
  symbol_table.insert(new variable("d4", pool(pool(1), pool(4)), true));
  symbol_table.insert(new variable("d6", pool(pool(1), pool(6)), true));
  symbol_table.insert(new variable("d8", pool(pool(1), pool(8)), true));
  symbol_table.insert(new variable("d10", pool(pool(1), pool(10)), true));
  symbol_table.insert(new variable("d12", pool(pool(1), pool(12)), true));
  symbol_table.insert(new variable("d20", pool(pool(1), pool(20)), true));
}
// Else if statement
void bones_visitor::elseif_s_v(elseif_s* node) {
  node->expr()->accept(this);
  if (return_value.boolean()) {
    node->body()->accept(this);
    return_value = pool::TRUE;
  } else
    return_value = pool::FALSE;
}
// Block statement. Allocate a new scope onto the stack, execute my statements, then release it. TODO
void bones_visitor::block_s_v(block_s* node) {
  scope* myscope = new scope(symbol_table.current());
  symbol_table.push(myscope);
  for (auto iter = node->stmts()->begin(); iter != node->stmts()->end(); iter++)
    (*iter)->accept(this);
  symbol_table.pop();
  delete myscope;
}
// if statement
void bones_visitor::if_s_v(if_s* node) {
  node->expr()->accept(this);
  if (return_value.boolean()) {
    node->body()->accept(this);
    return;
  }
  for (auto iter = node->elifs()->begin(); iter != node->elifs()->end(); iter++) {
    (*iter)->accept(this);
    if (return_value.boolean())
      return;
  }
  node->elses()->accept(this);
}
//for statement TODO
void bones_visitor::for_s_v(for_s* node) {
  variable* var = symbol_table[node->iter()->txt()];
  node->over()->accept(this);
  pool to_iterate = return_value;
  for (auto i = to_iterate.begin(); i != to_iterate.end(); ++i) {
    var->value() = pool(*i);
    node->body()->accept(this);
  }
}
// while loop
void bones_visitor::while_s_v(while_s* node) {
  while (true) {
    node->expr()->accept(this);
    if (!return_value.boolean())
      break;
    node->body()->accept(this);
  }
}
//TODO
void bones_visitor::vardecl_s_v(vardecl_s* node) {
  vardecl_s_in(node);
  if (node->name())
    node->name()->accept(this);
  if (node->asn())
    node->asn()->accept(this);
  vardecl_s_out(node);
}
//TODO
void bones_visitor::constvardecl_s_v(constvardecl_s* node) {
  constvardecl_s_in(node);
  if (node->name())
    node->name()->accept(this);
  if (node->asn())
    node->asn()->accept(this);
  constvardecl_s_out(node);
}

void bones_visitor::explode_e_v(explode_e* node) {
  pool dietype = temporary_storage;
  pool pool_to_modify = return_value;
  node->pool()->accept(this);
  return_value = pool_to_modify.explode(dietype, return_value);
  temporary_storage = dietype;
}

void bones_visitor::desplode_e_v(explode_e* node) {
  pool dietype = temporary_storage;
  pool pool_to_modify = return_value;
  node->pool()->accept(this);
  return_value = pool_to_modify.desplode(dietype, return_value);
  temporary_storage = dietype;
}

void bones_visitor::rollagain_e_v(rollagain_e* node) {
  pool dietype = temporary_storage;
  pool pool_to_modify = return_value;
  node->pool()->accept(this);
  return_value = pool_to_modify.rollagain(dietype, return_value);
  temporary_storage = dietype;
}
//TODO
void bones_visitor::call_e_v(call_e* node) {
  call_e_in(node);
  if (node->name())
    node->name()->accept(this);
  for (auto iter = node->params()->begin(); iter != node->params()->end(); iter++)
    (*iter)->accept(this);
  call_e_out(node);
}
//TODO
void bones_visitor::id_e_v(id_e* node) {
  id_e_in(node);
  if (node->name())
    node->name()->accept(this);
  id_e_out(node);
}
// int node
void bones_visitor::int_e_v(int_e* node) {
  stringstream str(node->value()->txt());
  int a;
  str >> a;
  return_value = pool(a);
}
// union node
void bones_visitor::union_e_v(union_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value.expr_union(temporary_storage);
}
// complement
void bones_visitor::complement_e_v(complement_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value.expr_complement(temporary_storage);
}
//intersect node
void bones_visitor::intersect_e_v(intersect_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value.expr_intersect(temporary_storage);
}
// plus
void bones_visitor::plus_e_v(plus_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value + temporary_storage;
}
// minus
void bones_visitor::minus_e_v(minus_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value - temporary_storage;
}
// multiply
void bones_visitor::mult_e_v(mult_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value * temporary_storage;
}
// divide
void bones_visitor::div_e_v(div_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value / temporary_storage;
}
// modular
void bones_visitor::mod_e_v(mod_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value % temporary_storage;
}
// gt
void bones_visitor::gt_e_v(gt_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value.expr_gt(temporary_storage);
}
// ge
void bones_visitor::eqgt_e_v(eqgt_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value > temporary_storage;
}
// lt function
void bones_visitor::lt_e_v(lt_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value < temporary_storage;
}
// le function
void bones_visitor::eqlt_e_v(eqlt_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value <= temporary_storage;
}
// equal function
void bones_visitor::eq_e_v(eq_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value == temporary_storage;
}
// neq func
void bones_visitor::neq_e_v(neq_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value != temporary_storage;
}
// not function
void bones_visitor::not_e_v(not_e* node) {
  node->expr()->accept(this);
  temporary_storage = return_value;
  return_value = !temporary_storage;
}
// negative
void bones_visitor::negative_e_v(negative_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = return_value * pool(-1);
}
void bones_visitor::func_gt_e_v(func_gt_e* node) {
  node->pool_expr()->accept(this);
  temporary_storage = return_value;
  node->val_expr()->accept(this);
  return_value = temporary_storage.expr_gt(return_value);
}
void bones_visitor::func_ge_e_v(func_ge_e* node) {
  node->pool_expr()->accept(this);
  temporary_storage = return_value;
  node->val_expr()->accept(this);
  return_value = temporary_storage.expr_ge(return_value);
}
void bones_visitor::func_lt_e_v(func_lt_e* node) {
  node->pool_expr()->accept(this);
  temporary_storage = return_value;
  node->val_expr()->accept(this);
  return_value = temporary_storage.expr_lt(return_value);
}
void bones_visitor::func_le_e_v(func_le_e* node) {
  node->pool_expr()->accept(this);
  temporary_storage = return_value;
  node->val_expr()->accept(this);
  return_value = temporary_storage.expr_le(return_value);
}
void bones_visitor::func_eq_e_v(func_eq_e* node) {
  node->pool_expr()->accept(this);
  temporary_storage = return_value;
  node->val_expr()->accept(this);
  return_value = temporary_storage.expr_eq(return_value);
}
void bones_visitor::func_neq_e_v(func_neq_e* node) {
  node->pool_expr()->accept(this);
  temporary_storage = return_value;
  node->val_expr()->accept(this);
  return_value = temporary_storage.expr_neq(return_value);
}
void bones_visitor::func_highest_e_v(func_highest_e* node) {
  node->pool_expr()->accept(this);
  temporary_storage = return_value;
  node->val_expr()->accept(this);
  return_value = temporary_storage.expr_highest(return_value);
}
void bones_visitor::func_lowest_e_v(func_lowest_e* node) {
  node->pool_expr()->accept(this);
  temporary_storage = return_value;
  node->val_expr()->accept(this);
  return_value = temporary_storage.expr_lowest(return_value);
}
void bones_visitor::func_pick_e_v(func_pick_e* node) {
  node->pool_expr()->accept(this);
  temporary_storage = return_value;
  node->val_expr()->accept(this);
  return_value = temporary_storage.expr_pick(return_value);
}
void bones_visitor::func_input_e_v(func_input_e* node) {
  cin >> return_value;
}
void bones_visitor::func_sizeof_e_v(func_sizeof_e* node) {
  node->pool_expr()->accept(this);
  return_value = return_value.expr_sizeof();
}
void bones_visitor::to_e_v(to_e* node) {
  node->l_expr()->accept(this);
  temporary_storage = return_value;
  node->r_expr()->accept(this);
  return_value = pool(temporary_storage, return_value);
}
void bones_visitor::roll_e_v(roll_e* node) {
  node->num()->accept(this);
  pool numdice = return_value;
  node->dice()->accept(this);
  temporary_storage = return_value;
  return_value = pool::roll(numdice, temporary_storage);
  // each roll mod takes the following variables:
  /*
   * return_value: The Dice pool being modified.
   * temporary_storage: die type being rolled
   */
  for (auto iter = node->rollmods()->begin(); iter != node->rollmods()->end(); iter++)
    (*iter)->accept(this);
}
void bones_visitor::pool_e_v(pool_e* node) {
  pool toreturn;
  for (auto iter = node->body()->begin(); iter != node->body()->end(); iter++) {
    (*iter)->accept(this);
    toreturn = toreturn.expr_union(return_value);
  }
  return_value = toreturn;
}
// TODO
void bones_visitor::param_b_v(param_b* node) {
  param_b_in(node);
  if (node->name())
    node->name()->accept(this);
  param_b_out(node);
}
// TODO
void bones_visitor::funcdecl_b_v(funcdecl_b* node) {
  funcdecl_b_in(node);
  if (node->name())
    node->name()->accept(this);
  for (auto iter = node->params()->begin(); iter != node->params()->end(); iter++)
    (*iter)->accept(this);
  for (auto iter = node->body()->begin(); iter != node->body()->end(); iter++)
    (*iter)->accept(this);
  if (node->ret())
    node->ret()->accept(this);
  funcdecl_b_out(node);
}
