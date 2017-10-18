#!  /bin/bash 
count=1
cat xixi|while read line
do 
	echo "$count:$line"
	count=$[ $count+1 ]
done
#echo -p "enter"
#while read file
#do
#	echo "fjdlfj  $file"
#done

#把从xixi里面读出的每一行赋值给line