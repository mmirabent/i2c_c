#include "moving.h"

#define BUFFER_SIZE 10

Euler moving_avg(Euler angle) {
    static double phi_buf[BUFFER_SIZE];
    static double theta_buf[BUFFER_SIZE];
    static double psi_buf[BUFFER_SIZE];
    static int first_run = 1;
    int i;

    Euler avg;
    avg.phi   = 0;
    avg.theta = 0;
    avg.psi   = 0;

    if(first_run) {
        for(i = 0; i < BUFFER_SIZE; i++) {
            phi_buf[i] = angle.phi;
            theta_buf[i] = angle.theta;
            psi_buf[i] = angle.psi;
        }
        first_run = 0;
    }

    for(i = 0; i < BUFFER_SIZE-1; i++) {
        phi_buf[i]   = phi_buf[i+1];
        theta_buf[i] = theta_buf[i+1];
        psi_buf[i]   = psi_buf[i+1];
    }

    phi_buf[BUFFER_SIZE-1] = angle.phi;
    theta_buf[BUFFER_SIZE-1] = angle.theta;
    psi_buf[BUFFER_SIZE-1] = angle.psi;

    for(i = 0; i < BUFFER_SIZE; i++) {
        avg.phi += phi_buf[i];
        avg.theta += theta_buf[i];
        avg.psi +=  psi_buf[i];
    }
    avg.phi /= BUFFER_SIZE;
    avg.theta /= BUFFER_SIZE;
    avg.psi /= BUFFER_SIZE;

    return avg;
}

