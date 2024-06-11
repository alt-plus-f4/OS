if [ "$#" -ne 3 ]; then
    echo "Usage: $0 numberOfSessions userName files<file1, file2.... filen>"
    exit 1
fi

# who -> name

for file in "$3"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi
    # Number of files..

    # Number of lines 
    echo "Number of lines: $(wc "$file")"
done