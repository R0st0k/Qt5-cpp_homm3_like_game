## ANNOTATION

In this work, a program was created in the C++ programming language using the Qt5 framework. The program is part of the teaching of the OOP paradigm and may be improved in the future. The MVC design pattern and the following patterns were used:

- Singleton (when creating a field)
- Iterator (for traversing the field)
- Factory Method/Abstract Factory (for creating field elements)
- Strategy (to change the principles of character interaction with the environment)
- Observer/Bridge (for logging player actions)
- Command (for player interaction)
- Facade (for interacting with components)
- State (to pass the move between player and opponent)
- Snapshot (for saving and loading the game)

The Qt multimedia library was also used to add sound (single-channel so far) and a wave algorithm was implemented to calculate the nearest path to the cell (displayed by arrows on the field)

## Run instructions

Being in the directory with the program, perform the following actions:

1) $ qmake (Automatically generates a Makefile)
2) $ make (Heroes executable is created)
3) $ ./Heroes (The program starts) 

## Launch example

You can see the program launch record below:

https://drive.google.com/file/d/1Z5YNVvp-KhFsDEgC7HPPo36DMP3pyfRa/view?usp=sharing

---

## АННОТАЦИЯ

В данной работе была создана программа на языке программирования С++, используя фреймворк Qt5. Программа является частью обучения ООП парадигме и в будущем может быть доработана. Был использован шаблон проектирования MVC и следующие паттерны:

- Синглтон (при создания поля)
- Итератор (для обхода по полю)
- Фабричный метод/Абстрактная фабрика (для создания элементов поля)
- Стратегия (для изменения принципов взаимодействия персонажа с окружением)
- Наблюдатель/Мост (для логгирования действий игрока)
- Команда (для взаимодействия игрока)
- Фасад (для взаимодействия с компонентами)
- Состояние (для передачи хода между игроком и противником)
- Снимок (для сохранения и загрузки игры)

Также была использована библеотека Qt multimedia для добавления звука (пока что одноканального) и реализован волновой алгоритм для расчета ближайшего пути до клетки (отображается стрелками на поле)

## Инструкция по запуску

Находясь в директории с программой, выполняем следующие действия:

1) $ qmake        (Автоматически генерирует Makefile)
2) $ make         (Создается исполняемый файл Heroes)
3) $ ./Heroes (Запускается программа)

## Пример запуска

Запись запуска программы можно увидеть ниже:

https://drive.google.com/file/d/1Z5YNVvp-KhFsDEgC7HPPo36DMP3pyfRa/view?usp=sharing
