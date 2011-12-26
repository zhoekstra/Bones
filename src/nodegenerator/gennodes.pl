#!perl

use warnings;
use strict;
use Cwd;

my $home_directory = cwd()."/..";
my $curr_folder;


while (<STDIN>){
	my $line = $_;
	chomp($line);
	if ($line =~ /^#/){
		$line =~ s/#//;
		$curr_folder = $line;
		print "changing to $curr_folder";
		mkdir($home_directory.'/'.$curr_folder) if not -d $curr_folder;
	}
	else{
		my @arr = split /\s+/,$line;
		my $name = shift @arr;
		my @types = ();
		for my $token (@arr){
			if ($token =~ /\$\*/){
				$token =~ s/\$\*//;
				push @types,'ArrayList<String>';
				push @types,$token;
			}
			elsif($token =~ /@\*/){
				$token =~ s/@\*//;
				push @types,'ArrayList<Node>';
				push @types,$token;
			}
			elsif($token =~ /\$/){
				$token =~ s/\$//;
				push @types,'String';
				push @types,$token;
			}
			elsif($token =~ /@/){
				$token =~ s/@//;
				push @types,'Node';
				push @types,$token;
			}
			else{
				print "We shoulnt get here\n";
			}
		}
		print "printing file $curr_folder/$name.java\n";
		open FILE, ">$home_directory/$curr_folder/$name.java";
		print FILE "package $curr_folder;\n";
		print FILE "import util.*;\n";
		print FILE "class $name extends Node{\n";
		for (my $i = 0; $i < scalar @types; $i+=2){
			print FILE "\t$types[$i] $types[$i+1];\n";
		}
		print FILE "\tpublic $name(";
		for (my $i = 0; $i < scalar @types; $i+=2){
			print FILE "$types[$i] $types[$i+1]";
			print FILE "," if $i+2 < scalar @types;
		}
		print FILE "){\n";
		for(my $i = 1; $i < scalar @types; $i+=2){
			print FILE "\t\tthis.$types[$i] = $types[$i];\n";
		}
		print FILE "\t}\n";
		print FILE "\tpublic Pool visit(State state){\n";
		print FILE "\t}\n";
		print FILE "}\n";
		
		close FILE;
		
		
	}
}

