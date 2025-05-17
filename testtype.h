#ifndef TESTTYPE_H
#define TESTTYPE_H

#pragma once

enum class TestType {
    SystemSch,      // тест 1 Системы счисления
    Mov,            // тест 2 Режимы адресации, команда mov
    Arifmetic,      // тест 3 Команды арифметики и памяти
    Logic,          // тест 4 команды логики и сдвинов
    Stack,          // тест 5 Команды работы со стеком
    Coding,         // тест 7 Кодирование команд
    Decoding        // тест 8 Декодирование команд
};


#endif // TESTTYPE_H
