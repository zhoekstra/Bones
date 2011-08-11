func SW_Wildcard(skill_die_type,wild_die_type,bonus){
	var result = 
		[1:skill_die_type:explode highest(skill_die_type)]
		union
		[1:wild_die_type:explode highest(wild_die_type)];
	return highest(result) + bonus;
}

func SW_Extras(skill_die_type,numdice,bonus,target){
	var result = [numdice:skill_die_type:explode highest(skill_die_type)];
	var total = 0;
	for each(i in result){
		if(i + bonus >= target){
			total = total+1;
		}
	}
	return total;
}

print "Wildcard rolls a skill of d8: result is ", SW_Wildcard(d8,d6,0);
print "10 extras attack with shootings of d6, " SW_Extras(d6,10,0,4), " of them hit.";

