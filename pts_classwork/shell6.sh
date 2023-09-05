echo "Please enter number of times: \c"
read num
i=1
while [ $i -le $num ] ; do
	echo "Executing for i = $i..."
	i=`expr $i + 1`
done
echo "\nEnd of the program...\n"
