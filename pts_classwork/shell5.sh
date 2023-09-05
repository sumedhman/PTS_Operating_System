# calculator program...
echo -n "Please enter the first number: "
read num1
echo -n "Please enter the second number: "
read num2
echo "So user given numbers are $num1 and $num2..."
echo "M A I N  M E N U ..."
echo "--------------------"
echo "1 >  A D D I T I O N  O P E R A T I O N ..."
echo "2 >  S U B T R A C T I O N  O P E R A T I O N ..."
echo "3 >  M U L T I P L I C A T I O N  O P E R A T I O N ..."
echo "4 >  D I V I S I O N  O P E R A T I O N ..."
echo "5 >  M O D U L U S  O P E R A T I O N ..."
echo "6 >  Q U I T  O P E R A T I O N ..."
echo "Please enter your choice number: \c"
read choice
if [ $choice -eq 1 ] ; then
	echo "ADDITION Operations has been selected..."
    result=`expr $num1 + $num2`
    echo "So $num1 + $num2 = $result..."
elif [ $choice -eq 2 ] ; then
	echo "SUBTRACTION Operations has been selected..."
    result=`expr $num1 - $num2`
    echo "So $num1 - $num2 = $result..."
elif [ $choice -eq 3 ] ; then
    echo "MULTIPLICATION Operations has been selected..."
    result=`expr $num1 \* $num2`
    echo "So $num1 * $num2 = $result..."
elif [ $choice -eq 4 ] ; then
	echo "DIVISION Operations has been selected..."
    result=`expr $num1 / $num2`
    echo "So $num1 / $num2 = $result..."
elif [ $choice -eq 5 ] ; then
	echo "MODULUS Operations has been selected..."
    result=`expr $num1 % $num2`
    echo "So $num1 % $num2 = $result..."
elif [ $choice -eq 6 ];then
	echo "QUIT Operations has been selected..."
    echo "Exiting for the program..."
else
	echo "INVALID choice number has been provided..."
fi

echo "\nEnd of the program..."
