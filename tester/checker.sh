#!/bin/bash

if [ -f commons.sh ]; then
	. commons.sh
fi

case `uname` in
	"Linux")
		WORD_BOUNDARY_OPEN="\b"
		WORD_BOUNDARY_CLOSE="\b"
		;;
	"Darwin")
		WORD_BOUNDARY_OPEN="[[:<:]]"
		WORD_BOUNDARY_CLOSE="[[:>:]]"
		;;
esac

print_separator()
{
	printf "\n    >>> "
}

print_test()
{
	printf "* %-*s  " 70 "$1"
}

print_usage_and_exit()
{
	printf "%s\n" "Usage:  $0 [-ch] <lem-in> <map>"
	printf "\n"
	printf "%s\n" "   -c        clean the directory first"
	printf "%s\n" "   -h        print this message and exit"
	printf "%s\n" "   lem-in    path to your lem-in executable"
	printf "%s\n" "   map       map to test"
	exit 1
}

rm_tmp_files()
{
	for file in $@
	do
		[ -f "$file" ] && rm $file
	done
}

check_usr_output()
{
	local nb_empty_line

	print_test "Check output format"
	nb_empty_line=`grep -E "^$" $OUTPUT | wc -l | bc`
	if [ "$nb_empty_line" -eq 0 ]; then
		print_error "Missing empty line between map and solution"
		return 1
	elif [ "$nb_empty_line" -ne 1 ]; then
		print_error "Too many empty lines"
		return 1
	else
		print_ok "success"
	fi
	return 0
}

extract_usr_output()
{
	local usr_map=$1
	local usr_sol=$2

	check_usr_output
	[ $? -eq 1 ] && return 1
	grep -vE "(^$|^L)" $OUTPUT > $usr_map
	grep "^L" $OUTPUT > $usr_sol
	return 0
}

check_diff_output_map()
{
	local usr_map=$1
	local tmp_diff=".diff_tmp"
	local diff_file=$DIR_DIFF/`create_filename ${usr_map:1} "diff"`

	print_test "Check output map"
	diff $MAP $usr_map > $tmp_diff
	if [ -s $tmp_diff ]; then
		diff -y $MAP $usr_map > $diff_file
		print_error "Output map is different from input"
		print_separator
		printf "see $YELLOW$diff_file$RESET\n"
		rm $tmp_diff
		return 1
	else
		print_ok "success"
		return 0
	fi
}

extract_room_command()
{
	local room=$1

	grep -A 1 "##$room" $MAP | tail -n 1 | cut -d ' ' -f 1
}

check_only_one_move_per_ant()
{
	local line_nbr=$1
	shift
	local line=$@
	local duplicate

	duplicate=`echo "$line" | grep -Eo "L[0-9]+" | sort | uniq -d`
	if [ "$duplicate" ]; then
		print_error "Too many moves for at least an ant"
		print_separator
		printf "ant nbr {$YELLOW`echo $duplicate | tr -d 'L' | tr ' ' ','`$RESET} in line {$YELLOW$line_nbr$RESET}\n"
		echo "$line" | grep --color=auto "$duplicate"
		return "1"
	fi
	return "0"
}

check_only_one_ant_per_room()
{
	local line_nbr=$1
	local room_end=$2
	shift 2
	local line=$@
	local duplicate

	duplicate=`echo "$line" | grep -Eo "\-[A-Za-z0-9_]+${WORD_BOUNDARY_CLOSE}" | cut -c 2- | sort | grep -v "$room_end" | uniq -d`
	if [ "$duplicate" ]; then
		print_error "Too many ants in one room"
		print_separator
		printf "room: {`echo $duplicate | tr -d 'L' | tr ' ' ','`} in line {$line_nbr}\n"
		echo "$line" | grep --color=auto "$duplicate"
		return "1"
	fi
	return "0"
}

check_usr_solution()
{
	local file_sol=$1
	local room_end=$2

	print_test "Check one ant per line and one room per line (beside room_end)"
	local i=0
	while read line
	do
		((i++))
		check_only_one_ant_per_room $i $room_end $line
		[ $? -eq 1 ] && return "1"
		check_only_one_move_per_ant $i $line
		[ $? -eq 1 ] && return "1"
	done < $file_sol
	print_ok "success"
	return 0
}

extract_path_ant()
{
	local usr_solution=$1
	local ant=$2

	grep -Eo "$WORD_BOUNDARY_OPEN$ant$WORD_BOUNDARY_CLOSE-[A-Za-z0-9_]+" $usr_solution | cut -d '-' -f 2 | tr '\n' ' ' | sed 's/ $//'
}

check_path_exists()
{
	local room_start=$1
	local room_end=$2
	shift 2
	local path=$@
	local prev_room=$room_start

	for room in $path
	do
		grep -E "(^$prev_room-$room$|^$room-$prev_room$)" $MAP > /dev/null
		if [ $? -ne 0 ]; then
			print_error "Path does not exist"
			print_separator
			printf "Link between rooms {$YELLOW$prev_room$RESET-$YELLOW$room$RESET} does not exist\n"
			echo $path
			return 1
		fi
		prev_room=$room
	done
	if [ "$room" != "$room_end" ]; then
		print_error "Path does not exist"
		print_separator
		printf "Path does not end on room_end {$YELLOW$room_end$RESET}\n"
		echo $path
		return 1
	fi
	return 0
}

extract_paths()
{
	local usr_solution=$1
	local usr_paths=$2
	local room_start=$3
	local room_end=$4
	local ants_first_line=`head -n 1 $usr_solution | tr ' ' '\n' | cut -d '-' -f 1`

	print_test "Check paths"
	#echo "`echo $ants_first_line | wc -w | bc` paths found"
	echo "" > $usr_paths
	local i=0
	#echo "paths found: {id: (length) path}"
	for ant in $ants_first_line
	do
		local path=`extract_path_ant $usr_solution $ant`
		check_path_exists $room_start $room_end $path
		if [ $? -eq 1 ]; then
			return 1
		fi
		local length=`echo $path | wc -w | bc`
		#printf " %2d: (%2d)  %s\n" $i $length "$path"
		echo "$i:$length:$path" >> $usr_paths
		((i++));
	done
	print_ok "success"
	return 0
}

check_path_ants()
{
	local usr_solution=$1
	local usr_paths=$2
	local nb_ants=$3

	print_test "Check path for each ant"
	for i in `seq $nb_ants`
	do
		local ant="L$i"
		local path=`extract_path_ant $usr_solution $ant`
		grep -E ":$path$" $usr_paths > /dev/null
		if [ $? -ne 0 ]; then
			print_error "Path does not exist"
			print_separator
			printf "Path followed by ant $YELLOW$ant$RESET does not exist\n"
			echo "$path"
			return 1
		fi
	done
	print_ok "success"
	return 0
}

check_all_ants_reach_end()
{
	local usr_solution=$1
	local room_end=$2
	local nb_ants=$3

	print_test "Check all ants reach room_end"
	local nb_ants_in_end=`grep -Eo "${WORD_BOUNDARY_OPEN}${room_end}${WORD_BOUNDARY_CLOSE}" $usr_solution | wc -l | bc`
	if [ $nb_ants -ne $nb_ants_in_end ]; then
		local txt=`[ $nb_ants_in_end -lt $nb_ants ] && printf "few" || printf "many"`
		print_error "Too $txt ants reach room_end"
		print_separator
		printf "nbr of ants in room_end ($YELLOW$room_end$RESET): $YELLOW$nb_ants_in_end$RESET, expected: $YELLOW$nb_ants$RESET"
		return 1
	fi
	print_ok "success"
	return 0
}

run_main()
{
	local usr_map=".usr_map"
	local usr_solution=".usr_solution"
	local usr_paths=".usr_paths"
	local files="$usr_map $usr_solution $usr_paths"
	local room_start=`extract_room_command "start"`
	local room_end=`extract_room_command "end"`
	local nb_ants=`head -n 1 $MAP`
	local map_failure=0

	extract_usr_output $usr_map $usr_solution
	[ $? -eq 1 ] && map_failure=1
	printf "\n"
	check_diff_output_map $usr_map
	[ $? -eq 1 ] && map_failure=1
	printf "\n"

	check_usr_solution $usr_solution $room_end
	[ $? -eq 1 ] && map_failure=1
	printf "\n"

	extract_paths $usr_solution $usr_paths $room_start $room_end
	[ $? -eq 1 ] && map_failure=1
	printf "\n"
	check_path_ants $usr_solution $usr_paths $nb_ants
	[ $? -eq 1 ] && map_failure=1
	printf "\n"

	check_all_ants_reach_end $usr_solution $room_end $nb_ants
	[ $? -eq 1 ] && map_failure=1
	printf "\n"

	if [ $map_failure -eq 1 ]; then
		local map_file_copy=$DIR_MAP_ERR/`create_filename $MAP "err"`
		cp $MAP $map_file_copy
		((count_failure++))
	else
		((count_success++))
	fi

	if [ $DEBUG -eq 0 ]; then
		rm_tmp_files $OUTPUT $files
	fi
}

DEBUG=0
CLEAN_FIRST=0

EXEC=""
MAP=""
OUTPUT=".out_checker"

DIR_DIFF=".diff"
DIR_MAP_ERR=".map_err"
DIRS="$DIR_DIFF $DIR_MAP_ERR"

while getopts "ch" opt
do
	case $opt in
		c)
			CLEAN_FIRST=1
			;;
		h|*)
			print_usage_and_exit
			;;
	esac
done
shift $((OPTIND - 1))

if [ $# -ne 2 ]; then
   print_usage_and_exit
fi

check_executable $1 || exit
check_valid_file $2 || exit

EXEC="`add_prefix_if_current_dir $1`"
MAP="$2"

if [ $CLEAN_FIRST -eq 1 ]; then
	clean_dir $DIRS
fi
initialize_dir $DIRS

if [ $DEBUG -eq 0 ]; then
	$EXEC < $MAP > $OUTPUT
	if [ $? -eq 0 ]; then
		run_main
	else
		printf "%s\n" "Error: the following command return an error '$EXEC < $MAP'"
		exit 1
	fi
else
	run_main
fi
