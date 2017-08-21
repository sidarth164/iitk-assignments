#!/bin/bash
if [ "$#" -ne 1 ]; then
	echo please specify EXACTLY 1 argument
elif ! [ -f $1 ]; then
	echo please choose file_name from current directory	
else
	awk -F, '
	{for(i=1;i<=NF-1;i+=2){
		t=$i;
		$i=$(i+1);
		$(i+1)=t;
	}
	print
	}
	' OFS=',' $1
fi
