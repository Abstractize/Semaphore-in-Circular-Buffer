while getopts n:s: flag
do
    case "${flag}" in
        n) name=${OPTARG};;
        s) size=${OPTARG};;
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
echo "Productor and Consumer: "
./Productor -n "$name" & ./Consumer -n "$name"
echo ""
wait

echo "Finisher: "
./Finisher -n "$name"
wait