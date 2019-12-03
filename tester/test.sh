#!/bin/bash

################################ Functions #####################################

function usage() {
	printf "\nusage: sh ./test_script_lem_in.sh [-n number of maps] [-m map_folder] [-e with_generator]\n\
	[-g generator][-o generator_opitons][-c checker][-t showtime][-p program][-po program options]\n\n"
	printf "Lemin map folder generator-tester\n\
	- till n maps\n\
	- in a folder of map (-m)\n\
	- with generator (-g)\n\
	- with generator options (-o)\n\
	- !!!-e for generator careful -m [map_folder] erased\n"
}

########################## Variables initialization ############################

generator_ex=./generator
options=--big-superposition
map_folder=./maps_tester
program=../lem-in
prog_options=
n_maps=100
i=1
max_step=100
no_gen=1
checker=./checker.sh
check=0
timer=0
utime_tot=0
average=0

############################# Options parser ###################################

while [ "$1" != "" ]; do
	OPT=$1
	case $OPT in
	-h | --help)
		usage
		exit 0
		;;
	-c)
		check=1
		;;
	-t)
		timer=1
		;;
	-e)
		no_gen=0
		;;
	-n)
		shift
		n_maps=$1
		;;
	-p)
		shift
		program=$1
		;;
	-m)
		shift
		map_folder=$1
		;;
	-g)
		shift
		generator_ex=$1
		;;
	-o)
		shift
		options=$1
		;;
	-po)
		shift
		prog_options=$1
		;;
	*)
		usage
		exit
		;;
	esac
	shift
done

################################ Main loop #####################################

echo "MAP FOLDER :\033[0;32m" $map_folder "\033[0m"

if [ $no_gen -eq 1 ]; then
	if test -f "$program"; then
		echo
	else
		echo "\033[0;31m$program absent\033[0m"
		exit 1
	fi
	for filename in $map_folder/*; do
		map_str=$filename
		turns=$(cat $map_str | grep "required" | head -1 | cut -d' ' -f8)
		resu=$($program $prog_options <$map_str | grep "^L" | wc -l | awk '{$1=$1;print}')
		if [ ! -z "$turns" ]; then
			average=$(($average + $resu - $turns))
			average_str=$(echo "scale=1; $average / $i" | bc)
			diff=$(echo "$resu-$turns" | bc)
			if [ $resu -eq $turns ]; then
				echo $map_str ": Required:" $turns "-" $resu "Achieved" \
					"Average:" $average_str
			else
				if [ $resu -gt $turns ]; then
					echo $map_str ": Required:" $turns "-\033[0;31m" $resu "\033[0mAchieved" \
						"- Average:" $average_str "- Diff:\033[0;31m" $diff "\033[0m"
				else
					echo $map_str ": Required:" $turns "-\033[0;32m" $resu "\033[0mAchieved" \
						"- Average:" $average_str "- Diff:\033[0;32m" $diff "\033[0m"
				fi
			fi
		else
			echo $map_str " : " $resu "Achieved"
		fi
		if [ "$resu" -eq 0 ]; then
			echo "\033[0;31mERROR\033[0m"
		fi
		if [ $timer -eq 1 ]; then
			if test -f "$program"; then
				utime="$(
					TIMEFORMAT='%R'
					time ($program $prog_options <$map_str) 2>&1 1>/dev/null
				)"
				utime_tot=$(echo "scale=3; $utime + $utime_tot" | bc)
				utime_av=$(echo "scale=3; $utime_tot / $i" | bc)
				echo "TIME OF EXECUTION" $utime "and average" $utime_av
			fi
		fi
		if [ $check -eq 1 ]; then
			if test -f "$checker"; then
				$program $prog_options <$map_str | $checker $program $filename
			fi
		fi
		if [ ! -z "$turns" ]; then
			if [ $resu -gt $(($turns + $max_step)) ]; then
				echo "NOOOOOOO"
				exit 1
			fi
		fi
		i=$(($i + 1))
		echo
	done
	if [ $timer -eq 1 ]; then
		echo "TOTAL LEMIN RUNTIME for $(($i - 1)) FILES" $utime_tot "seconds"
	fi
	exit 1
fi

rm -rf $map_folder
mkdir -p $map_folder

while [ $(($i)) -lt $(($n_maps + 1)) ]; do
	if [ $((i)) -lt 10 ]; then
		istr="0$((i))"
	else
		istr="$((i))"
	fi
	map_str="$generator_ex""$options"_round_"$istr"
	$generator_ex $options >$map_folder/$map_str
	turns=$(cat $map_folder/$map_str | grep "required" | head -1 | cut -d' ' -f8)
	resu=$($program $prog_options <$map_folder/$map_str | grep "^L" | wc -l | awk '{$1=$1;print}')
	average=$(($average + $resu - $turns))
	average_str=$(echo "scale=1; $average / $i * 100 /100" | bc)
	diff=$(echo "$resu-$turns" | bc)
	if [ $resu -eq $turns ]; then
		echo "Generating" $map_str "  Required :" $turns "-" $resu "Achieved" \
			" and Average" $average_str
	else
		if [ $resu -gt $turns ]; then
			echo "Generating" $map_str "  Required:" $turns "-\033[0;31m" $resu "\033[0mAchieved" \
				"- Average" $average_str "- Diff:\033[0;31m" $diff "\033[0m"
		else
			echo "Generating" $map_str "  Required:" $turns "-\033[0;32m" $resu "\033[0mAchieved" \
				"- Average" $average_str "- Diff:\033[0;32m" $diff "\033[0m"
		fi
	fi
	if [ $check -eq 1 ]; then
		if test -f "$checker"; then
			$program $prog_options <$map_folder/$map_str | $checker $program $map_folder/$map_str
		fi
	fi
	if [ $timer -eq 1 ]; then
		if test -f "$program"; then
			utime="$(
				TIMEFORMAT='%R'
				time ($program $prog_options <$map_str) 2>&1 1>/dev/null
			)"
			utime_tot=$(echo "scale=3; $utime + $utime_tot" | bc)
			utime_av=$(echo "scale=3; $utime_tot / $i " | bc)
			echo "TIME OF EXECUTION" $utime "and average" $utime_av
		fi
	fi
	if [ $resu -gt $(($turns + $max_step)) ]; then
		echo "NOOOOOOO"
		exit 1
	fi
	i=$(($i + 1))
	sleep 1
	echo
done
if [ $timer -eq 1 ]; then
	echo "TOTAL LEMIN RUNTIME for $(($i - 1)) FILES" $utime_tot "seconds"
fi
exit 0
