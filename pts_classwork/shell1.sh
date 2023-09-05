# this is a single line comment
# this is another comment line
echo -n "\t\tPlease enter the first number: "
read num1
echo "\t\tPlease enter the second number: \c"
read num2
total=`expr $num1 + $num2`
echo "\t\tSo the required $total = $num1 + $num2..."
echo "\t\tEnd of the program..."
