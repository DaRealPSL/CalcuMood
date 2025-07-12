# CalcuMood

**CalcuMood** is a sarcastic, emotional calculator that reacts to your inputs with mood-based responses, making math a little more entertaining (and a bit existential).

---

## Features

- Mood-based responses to inputs
- Basic math evaluation (with emotional flair)
- Sarcastic replies to kind words or gibberish
- Easter eggs for famous numbers like 42
- Cross-platform: macOS, Windows, Linux (compile it yourself!)

---

## Getting Started

### Build From Source

We don’t currently provide prebuilt binaries; but compiling CalcuMood is quick and easy.

#### Requirements

- A C++17-compatible compiler (`g++`, `clang++`, or MSVC)
- Terminal or command prompt access

---

### macOS / Linux

#### 1. Clone the repository:
```bash
git clone https://github.com/DaRealPSL/CalcuMood.git
cd CalcuMood/src
```

2. Build using make (optional):
```bash
make
```

Or manually:
```bash
g++ -std=c++17 -o CalcuMood main.cpp MoodManager.cpp Calculator.cpp Utils.cpp
```

3. Run it:
```bash
./CalcuMood
```


### Windows (with g++ / MinGW)
1.	Open Command Prompt or PowerShell
2.	Navigate to the src folder
3.	Compile:
	```bash
	g++ -std=c++17 -o CalcuMood.exe main.cpp MoodManager.cpp Calculator.cpp Utils.cpp
	```
4.	Run:
	```bash
	CalcuMood.exe
	```
Or use Visual Studio:

- Create a new C++ Console project
	
- Add all .cpp and .h files from src/
	
- Enable C++17 (/std:c++17)
	
- Build and run

## Usage
- Type math expressions like 2 + 2

- Say nice things to lift CalcuMood's spirit

- Try easter eggs like 42, 69, or 01134

- Type exit to quit (might need to type multiple times if the calculator is too sad...)


## Contributing

Feel free to open issues or submit pull requests, improvements and jokes welcome.


## License

MIT License.
See LICENSE for details.

## Author

Created by DaRealPSL.
