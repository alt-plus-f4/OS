# Example usage for the programs with the example files:  

> # 1 -> C shell
Предишния shell с pipes..
```sh
└─$ make sh && ./sh
user$ ls -la | grep sh

 17:00 c-lister.sh
 16:57 line-count.sh
 01:16 sh
 01:04 sh.c
```

> # 2 -> ls-grep
Да се състави програма на C, която получава 2 командни аргумента - символен низ (string) за търсене и име на файл. Програмата трябва да изпълни командата cat с името на подадения файл. След това изхода от grep трябва да се пренасочи към командата grep посредством тръби. Изхода на grep да се изведе на стандартния изход. Програмата да поддържа подаването на много имена на файлове.

```sh
└─$ make ls-grep && ./ls-grep
└─$ ./ls-grep sh search_files/file1.txt search_files/file2.txt

This is file1 sh is a shell
sh
This is file2sh
I have a sh here the search string "sh"
sh
```

> # 3 -> Line-count
Да се състави shell script командна процедура, която получава като командни параметри параметри в командния ред имена на съществуващи текстови файлове. Прочита от стандартния вход символен низ и за всеки от зададените файлове извежда по подходяш начин на стандартния изход броя на редовете които съдържат низа.
```sh
└─$ sh line-count.sh search_files/file1.txt search_files/file2.txt 
Enter search string: sh
Number of lines containing 'sh' in 'search_files/file1.txt': 2
Number of lines containing 'sh' in 'search_files/file2.txt': 3
```

> # 4 -> C-lister
Да се състави shell script командна процедура, която получава при стартиране в командния ред два параметъра – имена на съществуващи директории. В случай че общият брой на файловете, с разширение .c в двете директории надвишава 3, процедурата създава в текушата директория файл – sources.txt, съдържащ имената им, който да е достъпен само за четене на всички потребители. В противен случай извежда с подходящо съобщение този брой на стандартния изход.
```sh
└─$ sh c-lister.sh dir1 dir2
sources.txt created.

└─$ cat sources.txt 
filler-file-2.c
filler-file-4.c
filler-file.c
filler-file3.c
dir-2-filler-file-2.c
dir-2-filler-file-4.c
dir-2-filler-file.c
dir-2-filler-file3.c
```

> Накрая :)
```
make clean
```