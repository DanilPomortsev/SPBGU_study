[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7682443&assignment_repo_type=AssignmentRepo)
# Сжатие
Реализовать алгоритм сжатия Хаффмана и алгоритм сжатия LZW.

## Требования к реализации

* Название програмы: `compress`
* Вызов `compress -lzw input output` осуществляет сжатие файла *input* методом LZW и записывает результат в файл *output*.
* Вызов `compress -huffman input output` осуществляет сжатие файла *input* алгоритмом Хаффмана и записывает результат в файл *output*.
* Вызов `compress -d input output` осуществляет декомпрессию  файла *input* и записывает результат в файл *output*.
* Вызов `compress -h` или `compress ?` выводит на экран помощь по использованию программы.


## Дополнительная литература
* [Рафгарден Тим. Совершенный алгоритм. Жадные алгоритмы и динамическое программирование. — СПб.: Питер, 2020. — 256 с.](https://proxy.library.spbu.ru:2374/bookshelf/367982/reading) Глава 14. Коды Хаффмана.
* Кормен, Томас Х., Лейзерсон, Чарльз И., Ривест, Рональд Л., Штайн, Клиффорд. Алгоритмы: построение и анализ, 2-е издание. : Пер. с англ. — М. : Издательский дом “Вильямс”, 2011. — с. 459—466.
* [Ziv, J.; Lempel, A. (1978). Compression of individual sequences via variable-rate coding. IEEE Transactions on Information Theory. 24 (5): 530.](https://courses.cs.duke.edu/spring03/cps296.5/papers/ziv_lempel_1978_variable-rate.pdf)
* [Welch, Terry (1984). A Technique for High-Performance Data Compression. Computer. 17 (6): 8–19.](https://courses.cs.duke.edu/spring03/cps296.5/papers/welch_1984_technique_for.pdf) 

