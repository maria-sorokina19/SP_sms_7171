.data
print:
.string "Исходный элемент массива: %d\n"
print_:
.string "Преобразованный элемент: %d\n"
message:
.string "Число элементов, меньших 128: %d\n"
arr:
.short 117, 200, 5, 30, 56
arr_end:
.text
.global main
.type main, @function
main:
movl $0, %eax
movl $0, %ebp
movl $arr, %ebx
movw (%ebx), %ax

jmp check

loop_start:
pushl %eax
pushl $print
call printf
popl %edx
popl %eax

or $107, %ax

pushl %eax
pushl $print_
call printf
popl %edx
popl %eax

cmpw $128, %ax
jge next

inc %ebp
next:
addl $2, %ebx
movw (%ebx), %ax

check:
cmpl $arr_end, %ebx
jne loop_start

pushl %ebp
pushl $message
call printf
addl $8, %esp
movl $0, %ecx
movl $0, %ebx
movw $0, %ax
ret
