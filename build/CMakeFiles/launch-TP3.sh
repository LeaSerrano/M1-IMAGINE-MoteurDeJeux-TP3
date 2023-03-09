#!/bin/sh
bindir=$(pwd)
cd /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/TP3/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/TP3 
	else
		"/home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/TP3"  
	fi
else
	"/home/lea/M1-IMAGINE/S2/MoteurJeux/M1-IMAGINE-MoteurDeJeux-TP3/build/TP3"  
fi
