.data /* описываем сегмент кода */
hello_str:
.string "Hello, world!\n" /* строка для вывода */
.set hello_str_length, . - hello_str - 1 /* длина строки */
.text /* описываем сегмент кода */
.globl main /* main - глобальный символ */
.type main, @function /* main - функция */

main:
movl $4, %eax /* поместить номер системного вызова write=4 в регистр %eax */
movl $1, %ebx /* 1ый параметр - в регистр %ebx; номер файлового дескриптора stdout - 1 */
movl $hello_str, %ecx /* 2ой параметр - в регистр %ecx; указатель на строку */
movl $hello_str_length, %edx /* 3ий параметр - в регистр %edx; длина строки */

int $0x80 /*вызов прерывания 0x80, аналога 21h для DOS*/
movl $1, %eax /*номер системного вызова exit - 1 */
movl $0, %ebx /*передать 0 как значение параметра */
int $0x80 /*вызвать exit(0) */
.size main, . - main /* размер функции main */
