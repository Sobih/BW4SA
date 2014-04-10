#!/bin/bash
all_passed=0
for s in os/*.sh
do
	$s
	if [ $? -eq 1 ]
	then
		all_passed=1
	fi
	
done

exit $all_passed

