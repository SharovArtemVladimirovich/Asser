# Asser Turbo - Программа для тестирования знаний

<img src="images/Asser_Turbo_logo1.png" alt="Главный экран Asser Turbo" width="300">

**Asser Turbo** - уникальное и неповторимое приложение для проведения тестирования по _Ассемблеру_ с поддержкой различных тем оформления и функций управления тестами.

## 📋 Системные требования
- **Операционные системы:** Windows 10+, Linux, macOS 12+
- **Qt версия:** 6.5 или выше
- **Компилятор:** Поддержка C++17 (MSVC, GCC, Clang)
- **Библиотеки:**
  - Qt Multimedia (для аудиофункций)
  - SQLite (для хранения истории тестов)

### Сборка с помощью CMake
```bash
git clone https://github.com/yourusername/asser-turbo.git
cd asser-turbo
mkdir build
cd build

# Для Windows
cmake -G "NMake Makefiles" ..
nmake

# Для Linux/macOS
cmake ..
make -j4

# Запуск приложения
./Asser
