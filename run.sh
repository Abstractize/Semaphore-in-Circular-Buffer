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