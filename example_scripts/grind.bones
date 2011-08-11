const var white_die = [0,0,0,1,1,2];
const var blue_die =  [0,0,1,1,1,2];
const var red_die =   [0,1,1,1,1,2];

func grind(num_white, num_blue, num_red){
	return sum(
		[num_white:white_die] union
		[num_blue:blue_die] union
		[num_red:red_die]);
}

print "Jack makes smash attack with pulverizer and charged: ", grind(4,4,0), " successes rolled.";
