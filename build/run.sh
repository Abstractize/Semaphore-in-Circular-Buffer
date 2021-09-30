while getopts n:s:t: flag
do
    case "${flag}" in
        n) name=${OPTARG};;
        s) size=${OPTARG};;
        t) time=${OPTARG};;
    esac
done

if [ -d "./$PROGRAM_NAME" ]; then
 cd "./$PROGRAM_NAME"
fi

echo ""
echo "Initiator: "
./Initiator -n "$name" -s "$size"
echo ""
wait
#echo "Productor and Consumer: "
#./Productor -n "$name" -t "$time" &
#sleep 5 && ./Consumer -n "$name" -t "$time"
echo ""
wait

#echo "Finisher: "
#./Finisher -n "$name"
#wait