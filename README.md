# Miscellaneous
These are just some random things I coded in my free time.

- Bash
  - `check_large_pack_files.sh`: I wrote a script to sort through large objects in the pack of Git repositories. It identifies the largest `NUMFILES` blobs in the pack,
    reports its size, commit hash it was introduced in, and checks their containment in the specified `BRANCH`. The default arguments are the 10 largest files and containment in `origin/main`. 
- C++
  - `quicksorter.cpp`: I coded the quicksort algorithm as my first C++ program. It takes in integers from the command line.
- C
  - `bootstrap.c`: I coded statistical bootstrapping to determine the distribution in which C picks values for its rand() function. 
    I sampled 100 values between 0 and 10000, bootstrapped 100000 times, and got a Gaussian distribution nearly perfectly centered 
    at 5000, as seen in the included graph.
  - `brainfuck.c`: This is an interpreter for the esoteric language Brainfuck. I included two sample programs, `hello.bf` which is a 
    Hello World program and `reverse.bf` which reads in a string from user input and prints its reverse. You can run programs like
    `./brainfuck filename`.
- JavaScript
  - `snake.html`: I coded a simple JavaScript snake game inspired by [this](https://www.youtube.com/watch?v=xGmXxpIj6vs) YouTube video. I       coded it with different data structures in my own style and added pause and     restart functionality, as well as other minor tweaks.     You can run it in a browser.
- Python
  - `SIR.py`: I used the classical fourth-order Runge-Kutta method to numerically solve the SIR epidemiological model. I became interested in this 
    because of the current COVID-19 pandemic. The computed solutions can be seen in the included diagram.
  - `denoising_images.ipynb`: A student asked for a little coding sample of what an autoencoder can do so I put it here so the class could easily see it. A deep ReLU autoencoder is used to denoise MNIST images with keras. The image `reconstructed.png` shows the noisy images on the left and denoised images on the right.
  - `gameoflife.py`: I implemented [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) using a SciPy backend and the `redirect` module to print outputs to the console. A `requirements.txt` file is included and can be installed with `pip`. To use: `python gameoflife.py n_rows n_cols n_alive` where `n_rows` and `n_cols` refer to the size of the board while `n_alive` refers to the initial number of living cells.
  - `death_probability.ipynb`: Based on the [actuarial life table](https://www.ssa.gov/oact/STATS/table4c6.html) published by the Social Security Administration, I wrote a method to calculate the probability an individual will die in the next given amount of years based on their age and sex.
