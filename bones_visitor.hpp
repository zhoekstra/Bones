#ifndef BONES_VISITOR_H_INCLUDE

#define BONES_VISITOR_H_INCLUDE

#include "visitor.hpp"
#include "pool.hpp"
#include "symtable.hpp"

class bones_visitor: public visitor {

public:
	bones_visitor();

	void elseif_s_v(elseif_s* node);
	void block_s_v(block_s* node);
	void if_s_v(if_s* node);
	void for_s_v(for_s* node);
	void while_s_v(while_s* node);
	void vardecl_s_v(vardecl_s* node);
	void constvardecl_s_v(constvardecl_s* node);
	void explode_e_v(explode_e* node);
	void desplode_e_v(desplode_e* node);
	void rollagain_e_v(rollagain_e* node);
	void call_e_v(call_e* node);
	void id_e_v(id_e* node);
	void int_e_v(int_e* node);
	void union_e_v(union_e* node);
	void complement_e_v(complement_e* node);
	void intersect_e_v(intersect_e* node);
	void plus_e_v(plus_e* node);
	void minus_e_v(minus_e* node);
	void mult_e_v(mult_e* node);
	void div_e_v(div_e* node);
	void mod_e_v(mod_e* node);
	void gt_e_v(gt_e* node);
	void eqgt_e_v(eqgt_e* node);
	void lt_e_v(lt_e* node);
	void eqlt_e_v(eqlt_e* node);
	void eq_e_v(eq_e* node);
	void neq_e_v(neq_e* node);
	void not_e_v(not_e* node);
	void negative_e_v(negative_e* node);
	void func_gt_e_v(func_gt_e* node);
	void func_ge_e_v(func_ge_e* node);
	void func_lt_e_v(func_lt_e* node);
	void func_le_e_v(func_le_e* node);
	void func_eq_e_v(func_eq_e* node);
	void func_neq_e_v(func_neq_e* node);
	void func_highest_e_v(func_highest_e* node);
	void func_lowest_e_v(func_lowest_e* node);
	void func_pick_e_v(func_pick_e* node);
	void func_input_e_v(func_input_e* node);
	void func_sizeof_e_v(func_sizeof_e* node);
	void to_e_v(to_e* node);
	void roll_e_v(roll_e* node);
	void pool_e_v(pool_e* node);
	void param_b_v(param_b* node);
	void funcdecl_b_v(funcdecl_b* node);

private:
	symtable symbol_table;
	pool return_value;
	pool temporary_storage;
};

#endif

