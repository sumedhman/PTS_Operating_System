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
echo "6 >  E X P O N E N T I A T I O N  O P E R A T I O N..."
echo "7 >  Q U I T  O P E R A T I O N ..."
echo -e "Please enter your choice number: \c"
read choice
case $choice in
	1) echo "ADDITION Operations has been selected..."
	   # echo "$num1 + $num2"
       result=$((num1 + num2))
       echo "So $num1 + $num2 = $result..."
       ;;
	2) echo "SUBTRACTION Operations has been selected..."
       result=$(( $num1 - $num2 ))
       echo "So $num1 - $num2 = $result..."
       ;;
	3) echo "MULTIPLICATION Operations has been selected..."
       result=$(( num1 * num2 ))
       echo "So $num1 \* $num2 = $result..."
       ;;
	4) echo "DIVISION Operations has been selected..."
       result=$(($num1 / $num2))
       echo "So $num1 / $num2 = $result..."
       ;;
	5) echo "MODULUS Operations has been selected..."
       result=$(($num1 % $num2))
       echo "So $num1 % $num2 = $result..."
       ;;
	6) echo "EXPONENTIATION Operations has been selected..."
       result=$(($num1 ** $num2))
       echo "So $num1 ** $num2 = $result..."
       ;;
	7) echo "QUIT Operations has been selected..."
       echo "Exiting for the program..."
       ;;
	*) echo "INVALID choice number has been provided..."
       ;;
esac
echo -e "\nEnd of the program..."
