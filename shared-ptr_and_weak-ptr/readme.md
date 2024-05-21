# Shared Ptr & Weak Ptr
## Eng
### Description
This part of the project contains the implementation of smart pointers in C++: `shared_ptr`, `weak_ptr`, and auxiliary classes. Smart pointers provide efficient dynamic memory management using reference counting, ensuring automatic resource release and preventing memory leaks.

### Project Structure
* __shared.h__: Contains the basic implementation of `shared_ptr` and the `shared_from_this` functionality.
* __weak.h__: Contains the basic implementation of `weak_ptr`.
* __sw_fwd.h__: Contains the `ControlBlock` class, which is the foundation for the implementation of both shared and weak_ptr.

### Files
#### shared.h
This file contains the implementation of `shared_ptr`, which provides shared ownership of an object through reference counting. Key features:

* Constructors and assignment operators for copying and moving.
* Functions to access the object: `Get()`, `operator*()`, `operator->()`.
* The `shared_from_this` function, allowing an object to create a `shared_ptr` to itself.

#### weak.h
This file contains the implementation of `weak_ptr`, which provides a non-owning reference to an object managed by `shared_ptr`. Key features:

* Constructors and assignment operators for copying and moving.
* The `Lock()` function, returning a `shared_ptr` if the object still exists.

#### sw_fwd.h
This file contains the implementation of the `ControlBlock class`, which manages reference counting and stores information about the deleter. Key features:

* Managing strong and weak reference counts. 
* Automatically releasing resources when the reference count reaches zero. 
* Supporting custom deleters for managing how memory is freed.


## Rus
### Описание
Эта часть проекта содержит реализацию умных указателей на языке C++: `shared_ptr`, `weak_ptr` и вспомогательных классов для них. Умные указатели предоставляет эффективное управление динамической памятью с использованием подсчета ссылок, обеспечивая автоматическое освобождение ресурсов и предотвращение утечек памяти.

### Структура проекта
* __shared.h__: Содержит базовую реализацию `shared_ptr` и функционал `shared_from_this`.
* __weak.h__: Содержит базовую реализацию `weak_ptr`.
* __sw_fwd.h__: Содержит класс `ControlBlock`, который является основой для реализации всех умных указателей в проекте.

### Файлы
#### shared.h
Этот файл содержит реализацию `shared_ptr`, который обеспечивает совместное владение объектом через подсчет ссылок. Основные возможности:

* Конструкторы и операторы присваивания для копирования и перемещения.
* Функции доступа к объекту: `Get()`, `operator*()`, `operator->()`.
* Функция `shared_from_this`, позволяющая объекту создавать `shared_ptr` на самого себя.

#### weak.h
Этот файл содержит реализацию `weak_ptr`, который предоставляет неблокирующую ссылку на объект, управляемый `shared_ptr`. Основные возможности:

* Конструкторы и операторы присваивания для копирования и перемещения.
* Функция `Lock()`, возвращающая `shared_ptr`, если объект все еще существует.

#### sw_fwd.h
Этот файл содержит реализацию класса `ControlBlock`, который управляет подсчетом ссылок и хранит информацию о деструкторе. Основные возможности:

* Управление подсчетом сильных и слабых ссылок.
* Автоматическое освобождение ресурсов при достижении нулевого счетчика ссылок.
* Поддержка пользовательских деструкторов для управления способом освобождения памяти.