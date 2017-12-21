Мы задаем массив длин текста (изменяемое), на которых будет прогоняться алгоритм. 
Затем задаем количество ключей (изменяемое) и потом задаем количество прогонов (m, изменяемое). 
После этого мы генерируем размерность ключей (изменяемое), в зависимости от индекса (по магической придуманной формуле - key_index * 3 + 1). 
Затем мы по очереди берем каждый размер текста, который мы задали и для него выполняем m раз следующие действия:
  Генерируем случайный индекс, с которого будем читать тест с заранее заданного файла и читаем текст. 
  Затем генерируем случайный ключ заданной длинны. Затем шифруем наш текст. С помощью алгоритма анализируем длину ключа. 
  Если полученная длина ключа = заданной нами, то мы пытаемся с помощью этого ключа расшифровать текст. 
  Если расшифрованный текст и который задан изначально совпадают - попытка удачна.
После прогонки этого m раз - вычисляем средний успех.

Алгоритм Касиски - берем так называемую l-грамму (= длинне 3 в коде) и запихиваем в массив индексы где она встречается. 
Затем считаем расстояние между ними и от этих расстояний находим НОД-ы. (т.е. два раза проходим по массиву дистанций и считаем НОД каждой с каждой) 
Потом находим самый встречаемый НОД - и этот НОД и есть длина нашего ключа.

Алгорим расшифровки текста - считаем частоту встечаемости каждой буквы алфавита относительно длины ключа. 
Затем сверяем наши полученные частоты с заданными (идеальными). 
В цикле находим ближайшую заданную частоту к нашей полученной - это соответствует букве. Получаем предполагаемый "ключ" (массив moove) и пробуем расшифровать текст.
