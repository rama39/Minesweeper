# Minesweeper

Command line minesweeper in C

```
   +--+--+--+--+--+--+--+--+
   | 0| 1| 2| 3| 4| 5| 6| 7|
+--+--+--+--+--+--+--+--+--+
| 0|  |  |  |  |1 |1 |2 |# |
| 1|  |  |  |  |1 |# |2 |1 |
| 2|1 |1 |1 |  |1 |2 |3 |2 |
| 3|2 |# |1 |  |  |1 |# |# |
| 4|# |2 |2 |1 |1 |1 |2 |2 |
| 5|1 |1 |1 |# |1 |  |  |  |
| 6|  |  |1 |2 |2 |1 |1 |1 |
| 7|  |  |  |1 |# |1 |1 |# |
+--+--+--+--+--+--+--+--+--+
```

# Usage

Without arguments, width and height of board will be requested:

    ./minesweeper
        Width: [board width]
        Height: [board height]

With width and height of board as arguments:

    ./minesweeper [board width] [board height]

Obs: minimun board size = 8

# Playing

Board will be printed with labeled columns and rows. Terminal will prompt as "x y: ", type in values for x and y to reveal, or 'X' followed by values for x and y to flag a position. Flagged cells will be marked with a 'Q'

Press enter to confirm and game will continue until you reveal a bomb (lose) or reveal all cells that are not bombs (win). If you win, victories will be recorded in wins.txt as ([w], [h]): [time]s