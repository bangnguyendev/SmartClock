#!bin/bash
read -p "Nhap ten file c (vd: atest_zxc): " name_file
rm -rf log_change.txt
touch log_change.txt
temp_count=1

echo -e 'Search for the word \e[30;48;5;82m"START_TEST("test_"    \e[0m'
echo 'Search for the word "START_TEST("test_" ' >> log_change.txt
# Search for the word "START_TEST("test_" 
grep 'START_TEST(".*\_' $name_file.c| cut -d '_' -f2 > temp_out1
# Search for [line numbers] containing the word "START_TEST("test_" 
# [cut -d ':' -f1] >> Filter the line numbers
grep -n 'START_TEST(".*\_' $name_file.c| cut -d ':' -f1 > temp_out2

for i in `cat temp_out2`
do
	Str_Pattern=`printf 'START_TEST("test_'`
	Str_Replace=`printf 'START_TEST("%s: ' $temp_count`
	
	echo Line $i: $Str_Pattern >> log_change.txt
	echo "===========> $Str_Replace" >> log_change.txt
	echo Line $i: $Str_Pattern 
	echo "===========> $Str_Replace"
	echo thay tai dong $i
	sed -i "$i s/$Str_Pattern/$Str_Replace/" $name_file.c
	((temp_count++))
	
done 
echo ...
temp_count=1
echo -e 'Search for the word \e[30;48;5;82m"START_TEST("[0-9]*:"  \e[0m'

echo 'Search for the word "START_TEST("[0-9]*:" ' >> log_change.txt
grep 'START_TEST("[0-9]' $name_file.c| cut -d ' ' -f5 > temp_out1
# Search for [line numbers] containing the word "START_TEST("[0-9]*:" 
# [cut -d ':' -f1] >> Filter the line numbers
grep -n 'START_TEST("[0-9]' $name_file.c| cut -d ':' -f1 > temp_out2

for i in `cat temp_out2`
do

	temp_awk=`awk "{if(NR==$temp_count){print $1;}}" temp_out1`
	Str_Pattern=`printf '%s' $temp_awk`
	Str_Replace=`printf 'START_TEST("%s:' $temp_count`
	
	echo Line $i: $Str_Pattern >> log_change.txt
	echo "===========> $Str_Replace" >> log_change.txt
	echo Line $i: $Str_Pattern 
	echo "===========> $Str_Replace"
	sed -i "$i s/$Str_Pattern/$Str_Replace/" $name_file.c
	((temp_count++))
	
done 
echo -e "\e[30;48;5;82m ===============Done============== \e[0m"
rm -rf temp_out1
rm -rf temp_out2
read -p "Close sau 3s... Xem lai o log_change.txt" -t 3


