echo "enter your number"
read num
i=1
fact=1
until [ $i -gt $num ]
do 
fact=`expr $fact \* $i`
i=`expr $i + 1`
done
echo "factorial of $num is $fact"
