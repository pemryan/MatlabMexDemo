#include "mex.h"

int myadd(double* x, double* y, double v, mwSize l) {
    for(;l+1>0;l--)
    {
        y[l] = x[l] + v;
    }
    return 0;
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *x; 
    double *y;   
    double v;                          
    size_t l;                   
  
    /* check for proper number of arguments */
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:myadd:nrhs","Two inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:myadd:nlhs","One output required.");
    }

    /* make sure the second input argument is type double */
    if( !mxIsDouble(prhs[0]) ||  mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("MyToolbox:myadd:notDouble","Input vector must be type double.");
    }

    /* check that number of rows in second input argument is 1 */
    if(mxGetM(prhs[0])!=1) {
        mexErrMsgIdAndTxt("MyToolbox:myadd:notRowVector","Input must be a row vector.");
    }
    
    /* make sure the 2nd input argument is scalar */
    if( !mxIsDouble(prhs[1]) || mxIsComplex(prhs[1]) || mxGetNumberOfElements(prhs[1])!=1 ) {
        mexErrMsgIdAndTxt("MyToolbox:myadd:notScalar","Input value must be a scalar.");
    }

    /* create a pointer to the real data in the input matrix  */
    x = mxGetPr(prhs[0]);

    /* get dimensions of the input matrix */
    l = mxGetN(prhs[0]);
    
    /* get the value of the scalar input  */
    v = mxGetScalar(prhs[1]);

    /* create the output vector */
    plhs[0] = mxCreateDoubleMatrix(1, (mwSize)l, mxREAL);

    /* get a pointer to the real data in the output matrix */
    y = mxGetPr(plhs[0]);

    /* call the computational routine */
    myadd(x, y, v, (mwSize)l);
}