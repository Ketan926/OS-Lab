echo "enter coefficients a, b, c"
read a b c
discriminant=$(( b * b - 4 * a * c ))
case $discriminant in 
	[1-9]*)
	root1=$(echo "(-$b + sqrt( $discriminant )) / ( 2 * $a )" | bc)
	root2=$(echo "(-$b - sqrt( $discriminant )) / ( 2 * $a )" | bc)
	echo "roots are real and different"
	echo "root 1 is $root1"
	echo "root 2 is $root2"
	;;
	0)
	root=$(echo "-$b / (2 * $a )" | bc)
	echo "roots are real and equal"
	echo "root is $root"
	;;
	*)
	real=$(echo "-$b / (2 * $a)" | bc)
	img=$(echo "sqrt(-$discriminant) / ( 2 * $a )" | bc)
	echo "roots are real and complex"
	echo "root 1 = $real + i$img"
	echo "root 1 = $real - i$img"
	;;
esac