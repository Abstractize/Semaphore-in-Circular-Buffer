while getopts n: flag
do
    case "${flag}" in
        n) name=${OPTARG};;
    esac
done

if [ -d "./$PROGRAM_NAME" ]; then
 cd "./$PROGRAM_NAME"
fi

echo ""
echo "Initiator: "
./Initiator -n "$name"
echo ""
wait
echo "Productor: "
./Productor -n "$name"
echo ""
wait
echo "Consumer: "
./Consumer -n "$name"
echo ""
wait
echo "Finisher: "
./Finisher -n "$name"
wait