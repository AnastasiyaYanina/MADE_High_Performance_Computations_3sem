1. Программы с багами – примеры программ, которые надо починить.

2. omp_bugreduction.c – Код для скалярного произведения двух векторов. 
Дополнить функцию dotprod, проверить баги, проверить результат.

3. omp_bugparfor.c –Найти и устранить ошибки.

4. Написать параллельную программу, использующую метод Монте-Карло для оценки числа pi.

Note: clock() measures the sum of wall clocks across all threads. Use omp_get_wtime() instead (it returns value in seconds).