# hostctl
**Инструкции  по  установке:**

  #  Скачайте  исходный  код  пакета.
  #  Откройте  терминал  в  каталоге  с  исходным  кодом.
  #  Запустите  команду  `make`  для  сборки  пакета.
  #  Переместите  исполняемый  файл  `hosts`  в  каталог  `/usr/local/bin`  (или  в  любой  другой  каталог  в  пути  `PATH`).

**Использование:**

  *  **Добавить  запись:**  `./hosts add example.com 192.168.1.100`
  *   **Удалить  запись:**  `./hosts delete example.com`
  *   **Изменить  запись:**  `./hosts edit example.com 192.168.1.200`
  *   **Список  всех  записей:**  `./hosts list`
