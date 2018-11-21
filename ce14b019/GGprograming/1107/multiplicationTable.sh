#! /bin/bash

read -p "Input :" num

while [[ $num != 'q' ]]
do
  if (( $num < 10 && $num > 0 ))
  then
  for num in $num
  do
    for param in 1 2 3 4 5 6 7 8 9
      do
       	echo $num \* $param \= $(( $num * $param )) 
      done
  done
  
  else
    echo "number must 1~9 range"
  fi

read -p "Input :" num
done
