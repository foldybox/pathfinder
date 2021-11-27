#ifndef LIBMX
#define LIBMX

#include <wchar.h>
#include <unistd.h>
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


/* ============
 *  PRINT PACK
*/

/// Функция, что выводит символ в стандартный текстовый вывод.
/// \param c символ
void mx_printchar(char c);

/// Функция, что выводит UNICODE символ в стандартный текстовый вывод.
/// \param c UNICODE символ
void mx_print_unicode(wchar_t c);

/// Функция, что выводит строку в стандартный текстовый вывод. Строка - массив символов произвольной длины, что обязательно заканчивается терминатором "\\0".
/// \param *s указатель на строку
void mx_printstr(const char *s);

/// Функция, что выводит массив строк в стандартный текстовый вывод разделяя их строкой-разделителем. Строка - массив символов произвольной длины, что обязательно заканчивается терминатором "\\0".
/// \param **arr указатель на массив строк
/// \param *delim указатель на строку-разделитель
void mx_print_strarr(char **arr, const char *delim);

/// Функция, что выводит целое число в стандартный текстовый вывод.
/// \param n целое число
void mx_printint(int n);


/* ============
 *  MATH PACK
*/

/// Функция, что возводит число в указанную степень.
/// \param n число двойной точности, возводится в степень
/// \param pow беззнаковое целое число, степень
/// \return Функция возвращает число двойной точности, равное результату возведения в степень.
double mx_pow(double n, unsigned int pow);

/// Функция, что вычисляет квадратный корень положительного целого числа.
/// \param x целое положительное число
/// \return Функция возвращает целое число, равное квадратному корню указанного параметра. При неверном параметре, функция возвращает 0.
int mx_sqrt(int x);


/* ============
 *  CONVERT PACK
*/

/// Функция, что преобразует беззнаковое целое положительное число десятичной системы в шестнадцатеричную.
/// \param nbr беззнаковое длинное целое положительное число
/// \return Функция возвращает указатель на строку, что содержит шестнадцатеричное представление указанного параметра.
char *mx_nbr_to_hex(unsigned long nbr);

/// Функция, что преобразует строку шестнадцатеричного числа в беззнаковое целое положительное число десятичной системы.
/// \param *hex строка шестнадцатеричного числа
/// \return Функция возвращает беззнаковое длинное целое положительное число.
unsigned long mx_hex_to_nbr(const char *hex);

/// Функция, что конвертирует целое число в строку.
/// \param number целое число
/// \return Функция возвращает указатель на строку, что содержит конвертированное целое число.
char *mx_itoa(int number);

/// Функция, что конвертирует строку в целое число.
/// \param *str указатель на строку
/// \return Функция возвращает целое число, что равно конвертированному целому числу.
int mx_atoi(const char *str);


/* ============
 *  UTILS PACK
*/

void mx_foreach(const int *arr, int size, void (*f)(int));
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);


/* ============
 *  STRING PACK
*/

int mx_strlen(const char *s);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);
int mx_get_char_index(const char *str, char c);
char *mx_strdup(const char *s1);
char *mx_strndup(const char *s1, size_t n);
char *mx_strndup(const char *s1, size_t n);
char *mx_strcpy(char *dst, const char *src);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_strcmp(const char *s1, const char *s2);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strstr(const char *haystack, const char *needle);
int mx_get_substr_index(const char *str, const char *sub);
int mx_count_substr(const char *str, const char *sub);
int mx_count_words(const char *str, char c);
char *mx_strnew(const int size);
char *mx_strtrim(const char *str);
char *mx_del_extra_spaces(const char *str);
char **mx_strsplit(const char *s, char c);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_file_to_str(const char *file);
int mx_file_len(const char *file);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);
int mx_strncmp(const char *s1, const char *s2, int n);
char *mx_strchr(const char *s, int c);


/* ============
 *  MEMORY PACK
*/

void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_realloc(void *ptr, size_t size);


/* ============
 *  LINKED LIST PACK
*/

typedef struct s_list
{
    void *data;
    struct s_list *next;
} t_list;

t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);
int mx_list_size(t_list *list);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));


/* ============
 *  ADDITIONAL PACK
*/

bool mx_isnum(const char *s);
bool mx_isspace(char c);
bool mx_isdigit(char c);
bool mx_isalpha(int c);
bool mx_isupper(int c);
bool mx_islower(int c);

void mx_printerr(const char *s);

#endif /* LIBMX */
