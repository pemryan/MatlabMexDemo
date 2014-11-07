#include "mex.h"

/** function myconv
 * c = conv(x, y) where x and y are 1D row vectors.
 * Nx = length(x), Ny = length(y)
 */
#define MYCONV_MAX(a,b) (a)>(b)?(a):(b)
#define MYCONV_MIN(a,b) (a)<(b)?(a):(b)

int myconv(const double* x, const size_t Nx, const double* y, const size_t Ny, double* c) {

    size_t k, j, L, R;
	double s;

    for(k=0; k<Nx+Ny-1; k++) {
        L = MYCONV_MAX(0, (int)(k-Ny+1)); 
        R = MYCONV_MIN(k+1, Nx);
		s = 0;
        for(j=L; j<R; j++) {
            s += x[j] * y[k-j];
        }
        c[k] = s;
    }
    return 0;
}

/** Matlab driver routine */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *x;   
    double *y;   
    double *c; 
    size_t Nx, Ny, Nc;

    x = mxGetPr(prhs[0]);
    y = mxGetPr(prhs[1]);
	
	Nx = mxGetN(prhs[0]);
	Ny = mxGetN(prhs[1]);
    Nc = Nx + Ny - 1;

    plhs[0] = mxCreateDoubleMatrix(1, Nc, mxREAL);
    c = mxGetPr(plhs[0]);

    /* call the computational routine */
    myconv(x, Nx, y, Ny, c);
}
