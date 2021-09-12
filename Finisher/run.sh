PROGRAM_NAME="Finisher"
build=false

while getopts b flag
do
    case "${flag}" in
        b) build=true;;
    esac
done

if $build; then
    echo "Compiling $PROGRAM_NAME..."
    cd "./$PROGRAM_NAME/build"
    cmake ..
    make
    PATH="$PWD/$PROGRAM_NAME" 
else
    PATH="./$PROGRAM_NAME/build/$PROGRAM_NAME"
fi
    
"$PATH"