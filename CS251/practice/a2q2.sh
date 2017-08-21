#!/bin/sh

read -p "n = " n
read -p "m = " m
read -p "d = " d
read -p "File f: " f
read -p "t = " t
read -p "g = " g

if ! [ -f $f ]; then
	echo "file not present"
	exit
fi

i=1
while [ $i -le $d ];
do
	> d$i.txt
	> dk$i.txt
	let i=i+1
done

min1=$(echo $t| cut -d: -f2)
hr1=$(echo $t| cut -d: -f1)
gap=$(echo $g| cut -d' ' -f1)

wi=$((n/m))

shuf -i 1-$n > s.txt
shuf -i 1-$m > t.txt

let i=1
j=0
k=0
while IFS= read num;
do
	_n=$((num*n/100))
	_m=$((num*m/100))
	sed -n "$((j+1)),$((j+_n)) p" s.txt > s$i.txt
	sed -n "$((k+1)),$((k+_m)) p" t.txt > t$i.txt
	let i=i+1
	let j=j+_n
	let k=k+_m
done < $f

let i=1
while [ $j -lt $n ];
do
	sed -n "$((j+1)) p" s.txt >> s$i.txt
	let i=i+1;
	let j=j+1;
done



let i=1
while [ $k -lt $m ];
do
	sed -n "$((k+1)) p" t.txt >> t$i.txt
	let i=i+1;
	let k=k+1;
done

let i=1
 
while [ $i -le $d ];
do	
	let j=1
	x=1
	mi=$(grep -c ^ t$i.txt)
	ni=$(grep -c ^ s$i.txt)
	
	hr2=$hr1
	min2=$min1	
	
	while [ $j -le $ni ];
	do
		let k=$((j%mi+1))
		sed -n "$k p" t$i.txt >> d$i.txt
		sed -n "$j p" s$i.txt >> d$i.txt
		
		echo $hr2:$min2 >> d$i.txt
		
		if [ $k -eq 1 ]
		then
			if [ $j -ge $mi ]
			then
				let min2=min2+gap
				if [ $min2 -ge 60 ]
				then
					let hour2=hour2+$((min2/60))
					let min2=$((min2%60))
				fi
			fi
		fi		

		let j=j+1
	done 		

	sed 'N;N;s/\n/ /g' d$i.txt > dk$i.txt
	let i=i+1
done

let i=1
while [ $i -le $d ];
do
	sort -n dk$i.txt > d$i.txt
	let i=i+1
done

