#ifndef LIBMX
#define LIBMX

#include <wchar.h>
//#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdint.h>

#ifdef __APPLE__
#include <malloc/malloc.h>
#elif __linux__
#include <malloc.h>
#endif

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#ifndef INT_MIN
#define INT_MIN -2147483648
#endif

// UTILS PACK

/// Функция для вывода символов
/// \param c - символ, которы печатается
void mx_printchar(char c);

/// Функция для вывода символов ASCII и  многобайтовых символов
/// \param c - символ, которы печатается
void mx_print_unicode(wchar_t c);

/// Функция для вывода строки
/// \param s - строка
void mx_printstr(const char *s);

/// Функция для вывода массива строк с разделителем
/// \param arr - массив строк
/// \param delim - разделитель
void mx_print_strarr(char **arr, const char *delim);

/// Функция для вывода целочисленного значения (не доконца правильно работает)
/// \param n - число в int пределе
void mx_printint(int n);

/// Функция для возведения числа в степень
/// \param n - число, которое возводится в степень
/// \param pow - степень, в которое возведется число
double mx_pow(double n, unsigned int pow);

/// Функция для вычисления неотрицательного квадратного корня
/// \param x - число, из которого будет извлекатся квадратный корень
int mx_sqrt(int x);

/// Функция преобразования безнакового числа в шестинадцатеричную систему
/// \param nbr - беззнаковое длинное число
char *mx_nbr_to_hex(unsigned long nbr);

/// Функция преобразования шестнадцатеричной строки в беззнаковое длинное число
/// \param hex - шестнадцатиричная строка
unsigned long mx_hex_to_nbr(const char *hex);

/// Функция преобразования целого числа в строку
/// \param number - число
char *mx_itoa(int number);

/// Функция, которая пременяет функцю f для каждого элемента массива
/// \param arr - массив
/// \param f - функция
void mx_foreach(const int *arr, int size, void (*f)(int));

/// Функция, которая ищет строку s в массиве и возвращает ее позицию в массиве и количество итераций
/// \param arr - массив
/// \param size - длина массива
/// \param s - строк, которую ищем
/// \param count - счетчик количества итераций
int mx_binary_search(char **arr, int size, const char *s, int *count);

/// Функция, которая сортирует массив в лексикографическом порядке при помощи сортировки пузырьком
/// \param arr - массив
/// \param size - длина массива
int mx_bubble_sort(char **arr, int size);

//STRING PACK

/// Функция для подсчета длины строки
/// \param s - строка
int mx_strlen(const char *s);

/// Функция, которая еняет местами символы строки с помощью указателей
/// \param s1 - укзательна номер символа
/// \param s2 - укзатель на номер символа с которым менчется первый указанный символ.
void mx_swap_char(char *s1, char *s2);

/// Функция, которая переворачивает строку с помощбю укзателей.
/// \param s - строка
void mx_str_reverse(char *s);

/// Функция, которая принимает укзатель на строку и особождает память, устанавливая для строки значение NULL
/// \param str - строка
void mx_strdel(char **str);

/// Функция, которая принимает укзатель на  массив строк и удаляет содержимое массива особождая память, устанавливая значение NULL
/// \param str - строка
void mx_del_strarr(char ***arr);

/// Функция, которая находит индекс первого входжения символа с в строке
/// \param c - символ
int mx_get_char_index(const char *str, char c);

/// Функция для которая выделяет память, достаточную для хранения дубликата строки.
/// \param s1 - изначальная строка
char *mx_strdup(const char *s1);

/// Функция для которая выделяет память, и капирует по n байтов строку.
/// \param s1 – указатель на дублируемую строку.
/// \param n – ограничение длины дублируемой строки.
char *mx_strndup(const char *s1, size_t n);

/// Функция для которая выделяет память, и капирует по n байтов строку.
/// \param s1 – указатель на дублируемую строку.
/// \param n – ограничение длины дублируемой строки.
char *mx_strndup(const char *s1, size_t n);

/// Функция для копирования содержимого второй строки в первую
/// \param dst - строка, в которую копируют содержимое второй
/// \param src - указатель на строку
char *mx_strcpy(char *dst, const char *src);

/// Функция для копирования содержимого строки до len символа, на которую указывает src, в строку, на которую указывает dst
/// \param dst - строка, в которую копируют содержимое второй
/// \param src - указатель на строку
/// \param len - длина строки
char *mx_strncpy(char *dst, const char *src, int len);

/// Функция побайтового сравнения двух строк
/// \param s1 - первая строка
/// \param s2 - вторая строка
int mx_strcmp(const char *s1, const char *s2);

/// Функция для конкотенации(соединени) строки s1 и копии строки s2
/// \param s1 - первая строка
/// \param s2 - вторая строка
char *mx_strcat(char *restrict s1, const char *restrict s2);

/// Функция, котора возвращает укзатель на первое вхождение в строку, на которую указывает haystack, строки, укзанной needle
/// \param haystack - первая строка
/// \param needle - вторая строка
char *mx_strstr(const char *haystack, const char *needle);

/// Функция, котора находит индекс подстроки  и возвращает его поицию
/// \param str - строка в которой ищут
/// \param sub - сподстрока, которую ищут
int mx_get_substr_index(const char *str, const char *sub);

/// Функция, котора находит количество повторений подтроки
/// \param str - строка в которой ищут
/// \param sub - сподстрока, которую ищут
int mx_count_substr(const char *str, const char *sub);

/// Функция, котора считате количество сов по разделителям
/// \param str - строка в которой ищут
/// \param c - разделитель
int mx_count_words(const char *str, char c);

/// Функция для выделения памяти
/// \param size - размер новой херни
char *mx_strnew(const int size);

/// Функция, которая принимает строку и создает из нее новую без пробелов в начале и в конце строки. Освобождает всю неиспользуемую память
/// \param str - строка
char *mx_strtrim(const char *str);

/// Функция, которая принимает строку и создает из нее новую без пробелов в начале и / или в конце строки, разделяет слова в новой строке ровно одним пробелом. Освобождает всю неиспользуемую память
/// \param str - строка
char *mx_del_extra_spaces(const char *str);

/// Функция, котора преобразует строку в массив слов с завершающим NULL и освобождает всю неиспользуемую память
/// \param s - строка
/// \param c - разделитель
char **mx_strsplit(const char *s, char c); //тут доп функция вынести ее в отдельную

/// Функция, которая объединяет строки s1 и s2 в новую строку и завершает новую строку символом '\ 0'
/// \param s1 - строка
/// \param s2 - строка
char *mx_strjoin(const char *s1, const char *s2);

/// Функция, которая принимает имя файла в качестве параметра и считывает данные из файла в строку
/// \param file - строка
char *mx_file_to_str(const char *file);

/// Функция, которая заменяет все вхождения sub и str на replace.
/// \param str - строка исходник
/// \param sub - часть строки которую будем заменять
/// \param replace - строка которая будет выступать заменой sub
char *mx_replace_substr(const char *str, const char *sub, const char *replace);

/// Функция, которая считывает строку из заданного fd в lineptr до тех пор, пока она не достигнет delimc и разделитель не должен быть возвращен с lineptr. Достигает конца файла (EOF)
/// \param lineptr - строка  изначально занная
/// \param buf_size - размер
/// \param delim - разделитель
/// \param fd - файл
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);

/// Функция для сравнение строк с ограничением количества сравниваемых символов.
/// \param s1 -  указатели на сравниваемые строки.
/// \param s2 -  указатели на сравниваемые строки.
/// \param n - количество символов для сравнения.
int mx_strncmp(const char *s1, const char *s2, int n);

//MEMORY PACK

/// Функция, которая заполнения массива указанными символами.
/// \param b - указатель на заполняемый массив
/// \param c - код символа для заполнения
/// \param len - размер заполняемой части массива в байтах
void *mx_memset(void *b, int c, size_t len);

/// Функция, которая копирует непересекающихся массивов.
/// \param b - указатель на массив в который будут скопированы данные.
/// \param c - указатель на массив источник копируемых данных.
/// \param len -  количество байт для копирования.
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);

/// Функция, которая копирует непересекающихся массивов.
/// \param b - указатель на массив в который будут скопированы данные.
/// \param c - указатель на массив источник копируемых данных.
/// \param len -  количество байт для копирования.
/// \param c -  код символа, при встрече которого копирование завершается.
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);

/// Функция, которая сравневает  массивы
/// \param s1 - указатели на сравниваемые массивы.
/// \param s2 - указатели на сравниваемые массивы.
/// \param n -  размер сравниваемой части массива в байтах.
int mx_memcmp(const void *s1, const void *s2, size_t n);

/// Функция поиска первого вхождения указанного символа в массиве.
/// \param s - указатель на массив, в котором будет осуществляться поиск.
/// \param с - код искомого символа.
/// \param n - размер сравниваемой части массива в байтах.
void *mx_memchr(const void *s, int c, size_t n);

/// Функция поиска первого вхождения указанного символа в массиве, за исключением того, что поиск ведется в обратном направлении, вместо начала, с конца n байт, на которые указывает s.
/// \param s - указатель на массив, в котором будет осуществляться поиск.
/// \param с - код искомого символа.
/// \param n - размер сравниваемой части массива в байтах.
void *mx_memrchr(const void *s, int c, size_t n);

/// Функция ведет поиск подстроки
/// \param big - область памяти
/// \param big_len - длина области памяти
/// \param little - подстрока
/// \param little - длина подстроки
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len);

/// Функция копирование массивов (в том числе пересекающихся).
/// \param dst - указатель на массив в который будут скопированы данные.
/// \param src - указатель на массив источник копируемых данных.
/// \param len - количество байт для копирования.
void *mx_memmove(void *dst, const void *src, size_t len);

/// Функция изменяет величину выделенной памяти
/// \param ptr указатель на память
/// \param size нова величина памяти
void *mx_realloc(void *ptr, size_t size);

//LIST PACK

/// Linked list structure
typedef struct s_list
{
    void *data;
    struct s_list *next;
} t_list;

/// Функция,которая создает новый узел связанного listt_list. Она принимает параметр данных списку переменных данных и присваивает следующий за NULL.
t_list *mx_create_node(void *data);

/// Функция,которая вставляет новый узел типа t_list с заданными данными параметров в начало связанного списка
void mx_push_front(t_list **list, void *data);

/// Функция,которая вставляет узел типа t_list с заданными данными параметра в конец связанного списка
void mx_push_back(t_list **list, void *data);

/// Функция,которая вставляет новый узел типа t_list с заданными данными параметров в начало связанного списка
void mx_pop_front(t_list **head);

/// Функция,которая ввставляет узел типа t_list с заданными данными параметра в конце связанного списка.
void mx_pop_back(t_list **head);

/// Функция,которая вычисляет количество узлов в связанном списке
int mx_list_size(t_list *list);

/// Функция,которая сортирует содержимое списка в порядке возрастания
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));

// not requested?

//additional functions: 7
bool mx_isspace(char c); // +
bool mx_isdigit(char c); // +
bool mx_isalpha(int c); // +
bool mx_isupper(int c); // +
bool mx_islower(int c); // +
int mx_strncmp(const char *s1, const char *s2, int n); // +
char *mx_strchr(const char *s, int c); // +
void mx_printerr(const char *s);

#endif /* LIBMX */
