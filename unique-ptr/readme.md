# UniquePtr
## Eng
### Description
This part of the project contains the implementation of `UniquePtr`. Smart pointers in general provide efficient dynamic memory management, ensuring automatic resource release and preventing memory leaks. The main distinction of `UniquePtr` lies in its unique ownership of an object and its non-copyable nature.

### Project Structure
* __unique_ptr.h__: Contains the basic implementation of `UniquePtr`.
* __compressed_pair.h__: Contains the implementation of the `CompressedPair` class, which is used for memory optimization when storing pointers and related data.
### Files
#### unique_ptr.h
This file contains the implementation of `UniquePtr`, which ensures unique ownership of an object. Key features:

* Constructors and assignment operators for copying and moving.
* Functions to access the object: `Get()`, `operator*()`, `operator->()`.
* The `Release()` function, which releases ownership of the object without deleting it.

#### compressed_pair.h
This file contains the implementation of the `CompressedPair` class, which is used for memory optimization when storing a pair of values, one of which is often a pointer. It is used as a base class for storing data in `UniquePtr`. Key features:

* Efficient use of memory by eliminating the empty base class.
* Support for various data types, including pointers and objects.
* Constructors and assignment operators for copying and moving.
* Support for custom deleters to manage how memory is freed.
## Rus
### Описание
Эта часть проекта содержит реализацию `UniquePtr`. Умные указатели в целом предоставляет эффективное управление динамической памятью, обеспечивая автоматическое освобождение ресурсов и предотвращение утечек памяти. Основное отличие `UniquePtr` заключается в уникальном владении объектом и невозможности копирования.
### Cтруктура проекта
* __unique_ptr.h__: Содержит базовую реализацию `UniquePtr`.
* __compressed_pair.h__: Содержит реализацию класса `CompressedPair`, который используется для оптимизации памяти при хранении указателей и связанных с ними данных.
### Файлы
#### unique_ptr.h
Этот файл содержит реализацию `UniquePtr`, который обеспечивает уникальное владение объектом. Основные возможности:

* Конструкторы и операторы присваивания для копирования и перемещения.
* Функции доступа к объекту: `Get()`, `operator*()`, `operator->()`.
* Функция `Release()`, которая освобождает владение объектом без его удаления.

#### compressed_pair.h
Этот файл содержит реализацию класса `CompressedPair`, который используется для оптимизации памяти при хранении пары значений, одним из которых часто является указатель. Он используется как базовый класс для хранения данных в `UniquePtr`. Основные возможности:

* Эффективное использование памяти за счет устранения пустого базового класса.
* Поддержка различных типов данных, включая указатели и объекты.
* Конструкторы и операторы присваивания для копирования и перемещения.
* Поддержка пользовательских удалителей для управления способом освобождения памяти.