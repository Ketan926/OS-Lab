echo "enter your number:"
read number
x=1
num=1
until [ $x -gt $number ]
do 
echo "odd number $x: $num"
x=`expr $x + 1`
num=`expr $num + 2`
done
