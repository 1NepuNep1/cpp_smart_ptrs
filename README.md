# C++ Smart Pointers Implementation

## Eng 
### Description
This project provides the implementation of smart pointers in C++: `UniquePtr`, `SharedPtr`, `WeakPtr`, and auxiliary classes such as `CompressedPair` and `ControlBlock`. Smart pointers ensure efficient dynamic memory management, automatic resource release, and prevention of memory leaks.

### Key Features
* __UniquePtr__: Ensures unique ownership of an object, guaranteeing that only one pointer can own the object at any given time.
* __SharedPtr__: Provides shared ownership of an object through reference counting. The object will be deleted when the last `SharedPtr` is destroyed or reassigned.
* __WeakPtr__: Provides a non-owning reference to an object managed by `SharedPtr` without affecting the reference count.
* __CompressedPair__: Optimizes memory usage when storing a pair of values, one of which is often a pointer.
* __ControlBlock__: Manages reference counting and stores information about the deleter, serving as the foundation for the implementation of all smart pointers in the project.

### Project Structure
* __unique_ptr.h__: Basic implementation of `UniquePtr`. 
* __shared_ptr.h__: Basic implementation of `SharedPtr`. 
* __weak_ptr.h__: Basic implementation of `WeakPtr`. 
* __compressed_pair.h__: Implementation of the `CompressedPair` class, which is used for memory optimization. 
* __control_block.h__: Implementation of the `ControlBlock` class, which manages reference counting and object deletion.

### Useful Materials
* https://en.cppreference.com/w/cpp/memory/shared_ptr
* https://en.cppreference.com/w/cpp/memory/unique_ptr
* https://en.cppreference.com/w/cpp/memory/weak_ptr

## Rus
### Описание
Этот проект предоставляет реализацию умных указателей на языке C++: `UniquePtr`, `SharedPtr`, `WeakPtr` и вспомогательных классов, таких как `CompressedPair` и `ControlBlock`. Умные указатели обеспечивают эффективное управление динамической памятью, автоматическое освобождение ресурсов и предотвращение утечек памяти.

### Основные возможности
* __UniquePtr__: Обеспечивает уникальное владение объектом, гарантируя, что только один указатель может владеть объектом в любой момент времени.
* __SharedPtr__: Обеспечивает совместное владение объектом через подсчет ссылок. Объект будет удален, когда последний `SharedPtr` будет уничтожен или переназначен.
* __WeakPtr__: Предоставляет неблокирующую ссылку на объект, управляемый `SharedPtr`, не влияя на счетчик ссылок.
* __CompressedPair__: Оптимизирует использование памяти при хранении пары значений, одним из которых часто является указатель.
* __ControlBlock__: Управляет подсчетом ссылок и хранит информацию о деструкторе, являясь основой для реализации всех умных указателей в проекте.

### Структура проекта
* __unique_ptr.h__: Базовая реализация `UniquePtr`.
* __shared_ptr.h__: Базовая реализация `SharedPtr`.
* __weak_ptr.h__: Базовая реализация `WeakPtr`.
* __compressed_pair.h__: Реализация класса `CompressedPair`, который используется для оптимизации памяти.
* __control_block.h__: Реализация класса `ControlBlock`, который управляет подсчетом ссылок и удалением объектов.

### Материалы:
* https://en.cppreference.com/w/cpp/memory/shared_ptr
* https://en.cppreference.com/w/cpp/memory/unique_ptr
* https://en.cppreference.com/w/cpp/memory/weak_ptr
