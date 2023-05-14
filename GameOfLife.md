*Estimated duration*: 2 to 3 hours

Create a program that will take an initial board for the [game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) and apply the rule for n iterations and output the board or each iteration board according to the command line.

# Board format

Input and output board will have the same format.
One empty (dead) cell is encoded with an `_`, one living cell is encoded by a `*`.

The whole grid is encoded as a text file, for example:

```
____*_*_*____
______*______
_____________
```

Lines are terminated by `\n`. For the file to be valid, all the lines must have the same length.
No character other then the aforementioned can be in the file.

An empty file is valid.

# Input

The program shall be run on the command line with the following parameters:
- `--input`: A string representing the input file path, that should refer to a file using the board format. This parameter is mandatory.
- `--iterations`: A positivie integer representing the number of iterations to apply the rules. This parameter is mandatory (can be default valued, up to the applicant).
- `--all`: Print all the iterations. This parameter is optional. If absent, only the last step is printed.

Here is an example of command line:

```
$  game_of_life --input initial.txt --iterations 2000
```

Invalid files of parameters should display an explicit error.

# Output

The output files shall also use the board format and display the smallest possible board containing all the living cells.
The file name format should be, for a given input `input_name.extension`, `input_name_iteration.extension` where `iteration` is the iteration number. Extension is optional.

# Rules

The program should apply the [Game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) rules to the board in order to obtain the next iteration:

1. Any live cell with two or three live neighbors survives.
2. Any dead cell with three live neighbors becomes a live cell.
3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.

The board is supposed infinite in all directions.

# Submission

The program shall be provided as source code and instruction about how to compile. Ideally compilation should be one command to launch.

3rd party libraries can be used, but instructions about how to retrieve and use them shall also be provided.
Target shall be Windows or Linux.

The code shall be standard [C++17](https://en.cppreference.com/w/cpp/17) conformant.

The submission can be hosted on any code-sharing platform or an archive.

# Goal

The goal of this exercise is to show us what you think is **production ready code** and to provide basis for discussion at the interview.

Feel free to improve things if you want, but do not overwork, small and tidy is better than big and complex.