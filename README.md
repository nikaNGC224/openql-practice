# openql-practice
Изучаю openGL совместно с GLUT на линуксе

## Для запуска программы рекомендуется сделать следующие шаги:
1. Установить библиотеки:
```
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

2. Создать директорию out и перейти в неё:
```
$ mkdir out
$ cd out
```

3. Собрать проект и скомпилировать его:
```
$ cmake ..
$ make
```

4. Запустить исполняемый файл:
```
$ ./build/opengl_practice
```

## Цели:
1. Создать 3d фигуру;
2. Создать 3d анимацию;
3. Изучить текстуры для фигуры/фона.

## Работа программы:
На данный момент можно наблюдать окно с треугольником.
