# Wordle_Solver

Solver of [Wordle](https://www.nytimes.com/games/wordle/index.html).

If OpenMP can be used, high-speed processing is possible.

## Usage

### Build

```bash
git clone https://github.com/shinmai1054/wordle_solver.git
cd wordle_solver
cmake -B build
cmake --build build
```

### Run solver

```bash
build/wordle
```

### Search for the optimal solution

```bash
build/wordle --solution
```

## Example

```bash
$ build/wordle
OpenMP : Enabled (Max # of threads = 8)
----------------------------------------
try 'roate'
 green=1, orange=2, gray=3
>> 22322

candidates: 6
290 / 12947, average: 6, word: icily
1429 / 12947, average: 4.33333, word: fuzzy
1432 / 12947, average: 3, word: lumpy
1476 / 12947, average: 2, word: ulmin
5130 / 12947, average: 1.33333, word: munch
12830 / 12947
----------------------------------------
try 'munch'
 green=1, orange=2, gray=3
>> 33332

candidates: 1
----------------------------------------
ans: other
```

## License

[MIT](LICENSE)
