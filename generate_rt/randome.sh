#/bin/bash

echo "A 0.2 255,255,255"
echo "L 0,0,-5 0.7 255,255,255"
echo "C 0,0,-10 0,0,1 60"

echo "pl 0,0,100 0,0,1 255,255,255"
for i in `seq 1 20`;do
    echo "sp $(($RANDOM % 20 - 10)),$(($RANDOM % 20 - 10)),$(($RANDOM % 25)) 1.0 $(($RANDOM % 256)),$(($RANDOM % 256)),$(($RANDOM % 256))"
    echo "cy $(($RANDOM % 20 - 10)),$(($RANDOM % 20 - 10)),$(($RANDOM % 25)) $(($RANDOM % 3 - 1)),$(($RANDOM % 3 - 1)),$(($RANDOM % 3 - 1)) 1.0 2.0 $(($RANDOM % 256)),$(($RANDOM % 256)),$(($RANDOM % 256))"
done
