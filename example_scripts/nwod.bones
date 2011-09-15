// very complicated WoD style dice rolls
func WoD(int_numdice, int_success_on, int_rollagain_on, int_subtract_on, bool_reroll_failiures, bool_verbose){
	var result = [int_numdice : d10 : rollagain [int_rollagain_on -> 10]];
	if (verbose) print "Rolled",result;
	if(bool_reroll_failiures){
		var numsucc = ge(result, int_success_on);
		var numfail = sizeof(result) - numsucc;
		result = highest(result,numsucc) //keep only dice that succeeded
			union
			[numfail : d10 : rollagain [int_rollagain_on -> 10]]; // plus our rerolled dice
		if(verbose) print "Rerolling failiures, new roll: ",result;
	}
	var toreturn = ge(result,int_success_on) - le(result,int_subtract_on);
	if(verbose) print "resulting successes: ", toreturn;
	return toreturn;
}
// new World of Darkness
func nWoD(numdice, rollagain_on, verbose){
	return WoD(numdice,8,rollagain_on,0,false,verbose);
}
// real World of Darkness (so sayeth the haters)
func oWoD(numdice, success_on, verbose){
	return WoD(numdice, success_on, 11, 0, false, verbose);
}

print "Number of Successes Rolled on 6 dice: ", nWoD(6,10,false);
