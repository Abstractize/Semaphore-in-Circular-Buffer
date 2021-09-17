PROGRAM_NAME="Consumer"
build=false

while getopts b flag
do
    case "${flag}" in
        b) build=true;;
    esac
done

if [ -d "./$PROGRAM_NAME" ]; then
 cd "./$PROGRAM_NAME"
fi

if $build; then
    echo "Compiling $PROGRAM_NAME..."
    mkdir -p "./build"
    cd "./build"
    cmake ..
    make
    PATH="$PWD/$PROGRAM_NAME" 
else
    PATH="./build/$PROGRAM_NAME"
fi
    
"$PATH"