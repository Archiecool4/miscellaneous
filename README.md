# Miscellaneous
These are just some random things I coded in my free time.

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
