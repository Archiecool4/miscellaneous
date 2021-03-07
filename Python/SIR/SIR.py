import numpy as np 
import matplotlib.pyplot as plt 

#############
# Equations #
#############

def dS_dt(beta, I, S, N):
    return (-beta * I * S) / N

def dI_dt(beta, I, S, N, gamma):
    return (beta * I * S) / N - gamma * I

def dR_dt(gamma, I):
    return gamma * I

###############
# Runge-Kutta #
###############

def runge_kutta(h, n, beta, I, S, N, gamma, R):
    '''
    Classical 4th Order Runge-Kutta Method

    y' = f(x, y) with initial conditions y(x0) = y0 and step size h

    k1 = h * f(x, y)
    k2 = h * f(x + h / 2, y + k1 / 2)
    k3 = h * f(x + h / 2, y + k2 / 2)
    k4 = h * f(x + h, y + k3)

    x = x + h
    y = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6
    '''
    
    j = 0 
    s, i, r = np.zeros(n + 1), np.zeros(n + 1), np.zeros(n + 1)
    s[0], i[0], r[0] = S, I, R
    while j < n:
        S_k1 = h * dS_dt(beta, i[j], s[j], N)
        I_k1 = h * dI_dt(beta, i[j], s[j], N, gamma)
        R_k1 = h * dR_dt(gamma, i[j])

        S_k2 = h * dS_dt(beta, i[j] + h / 2, s[j] + S_k1 / 2, N)
        I_k2 = h * dI_dt(beta, i[j] + I_k1 / 2, s[j] + h / 2, N, gamma)
        R_k2 = h * dR_dt(gamma, i[j] + h / 2)

        S_k3 = h * dS_dt(beta, i[j] + h / 2, s[j] + S_k2 / 2, N)
        I_k3 = h * dI_dt(beta, i[j] + I_k2 / 2, s[j] + h / 2, N, gamma)
        R_k3 = h * dR_dt(gamma, i[j] + h / 2)

        S_k4 = h * dS_dt(beta, i[j] + h, s[j] + S_k3, N)
        I_k4 = h * dI_dt(beta, i[j] + I_k3, s[j] + h, N, gamma)
        R_k4 = h * dR_dt(gamma, i[j] + h)

        s[j+1] = s[j] + (S_k1 + 2 * S_k2 + 2 * S_k3 + S_k4) / 6
        i[j+1] = i[j] + (I_k1 + 2 * I_k2 + 2 * I_k3 + I_k4) / 6
        r[j+1] = r[j] + (R_k1 + 2 * R_k2 + 2 * R_k3 + R_k4) / 6

        j += 1

    return s, i, r


h = 0.05
n = 5000
# Step-size of 0.05, 5000 iterations, 0.2 contact rate, 1 infected, 
# 9999 susceptible, 10000 population, 0.042 transition rate, 0 recovered
s, i, r = runge_kutta(h, n, 1 / 5, 1, 9999, 10000, 1 / 24, 0)

# Plot values
t = np.linspace(0, h * n, len(s))
plt.plot(t, s, 'g-')
plt.plot(t, i, 'r-')
plt.plot(t, r, 'b-')
plt.legend(['Susceptible', 'Infected', 'Recovered'])
plt.xlabel('Time (Days)')
plt.ylabel('Number of People')
plt.title(r'SIR Model: $\beta=0.2, \gamma=0.042$')
plt.show()
