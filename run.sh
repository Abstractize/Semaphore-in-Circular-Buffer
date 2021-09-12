./Initiator/run.sh "$@" &
./Consumer/run.sh "$@" & 
./Productor/run.sh "$@" &
./Finisher/run.sh "$@"

wait