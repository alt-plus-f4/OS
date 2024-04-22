if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory1> <directory2>"
    exit 1
fi

dir1="$1"
dir2="$2"

count1=$(find "$dir1" -maxdepth 1 -type f -name "*.c" | wc -l)
count2=$(find "$dir2" -maxdepth 1 -type f -name "*.c" | wc -l)

if [ "$count1" -gt 3 ] && [ "$count2" -gt 3 ]; then
    touch sources.txt
    
    find "$dir1" -maxdepth 1 -type f -name "*.c" -exec basename {} \; >> sources.txt
    find "$dir2" -maxdepth 1 -type f -name "*.c" -exec basename {} \; >> sources.txt
    
    chmod a+r sources.txt
    echo "sources.txt created."
else
    echo "Not enough .c files in one or both directories."
fi