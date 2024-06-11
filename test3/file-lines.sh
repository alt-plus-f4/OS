if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <file1> [<file2> ...]"
    exit 1
fi

read -p "Enter search string: " search_string

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi
    
    echo "Number of lines containing '$search_string' in '$file': $(grep -c "$search_string" "$file")"
done