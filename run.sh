echo "Initiator: "
./Initiator/run.sh "$@"
wait
echo "Productor: "
./Productor/run.sh "$@"
wait
echo "Consumer: "
./Consumer/run.sh "$@" 
wait
echo "Finisher: "
./Finisher/run.sh "$@"
wait

cd ./build
./run.sh -n 'other_buffer' -s '10' -t '3'
wait