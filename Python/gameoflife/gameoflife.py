'''
filename:    gameoflife.py
description: Renders Conway's Game of Life in console.

(C) 2021 Archie Shahidullah
'''

import sys
import time
import numpy as np
from scipy.signal import convolve2d
from reprint import output

class Game:

    def __init__(self, n_rows, n_cols, n_alive):
        self.n_rows = n_rows
        self.n_cols = n_cols
        
        # Generate random board configuration
        # 1 marks living cells while 0 marks dead cells
        board = np.zeros(n_rows * n_cols)
        board[:n_alive] = 1
        np.random.shuffle(board)
        self.board = board.reshape((n_rows, n_cols))

        # This kernel will return the number of neighbours in a convolution
        self.kernel = np.array([[1, 1, 1], [1, 0, 1], [1, 1, 1]])

    def __str__(self):
        # Create string of * and . from board
        rep = ''.join(map(lambda x: '*' if x == 1 else '.', 
                          self.board.flatten()))
        # Insert newline to mark rows
        return '\n'.join(rep[i:i+self.n_cols] for i in 
                         range(0, len(rep), self.n_cols))

    def iterate(self):
        # Convolution with same padding gives number of neighbours of each cell
        neighbours = convolve2d(self.board, self.kernel, 'same')
        for row in range(self.n_rows):
            for col in range(self.n_cols):
                b = self.board[row, col]
                n = neighbours[row, col]
                if b == 1:
                    # If a living cell has less than 2 neighbours, or more than
                    # 3, it dies of underpopulation or overpopulation 
                    # respectively. Otherwise, it survives.
                    if n < 2 or n > 3:
                        self.board[row, col] = 0
                else:
                    # If a dead cell has 3 neighbours, it comes alive by 
                    # reproduction. Otherwise, it remains dead.
                    if n == 3:
                        self.board[row, col] = 1


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print(f'Usage: python {sys.argv[0]} n_rows n_cols n_alive')
        sys.exit(1)

    game = Game(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))

    with output(initial_len=game.n_rows) as output_lines:
        while True:
            s = str(game).split('\n')
            for i in range(game.n_rows):
                output_lines[i] = s[i]
            game.iterate()
            time.sleep(0.01)
