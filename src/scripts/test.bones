func nWod(numdice,rollagainon,rerollmisses){
	var roll = [numdice:d10:rollagain rollagainon];
	if(rerollmisses)
		roll = roll union [lt(roll,8):d10:rollagain rollagainon];
	var nums = ge(roll,8);
	if(nums >= 5)
		print "Exceptional success with ",nums," successes!";
	elseif(nums < 1)
		print "Failed with a roll of ",roll;
	else
		print "Succeeded with ",nums," successes.";
}

for (j in [1->100])
	nWod(5,10,[]);
