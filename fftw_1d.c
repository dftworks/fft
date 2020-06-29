#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>
#include<time.h>
#include<fftw3.h>

int main(int argc, char* argv[])
{
  if(argc < 2)
    {
      printf("Usage:\n\t fftw_1d.x npts\n");
      return 1;
    }
  
  int npts = atoi(argv[1]);
  int i;
  fftw_complex *in, *out;
  fftw_complex *in1, *out1;
  fftw_complex *in2, *out2;
  fftw_plan plan_bwd;
  fftw_plan plan_fwd;

  /* in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*npts);	 */
  /* out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*npts);	 */
  /* in1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*npts);	 */

  in = (fftw_complex*) malloc(sizeof(fftw_complex)*npts);
  out = (fftw_complex*) malloc(sizeof(fftw_complex)*npts);
  in1 = (fftw_complex*) malloc(sizeof(fftw_complex)*npts);
  
  plan_fwd = fftw_plan_dft_1d(npts, in, out, FFTW_FORWARD, FFTW_ESTIMATE); 	
  plan_bwd = fftw_plan_dft_1d(npts, in, out, FFTW_BACKWARD, FFTW_ESTIMATE); 	

  srand(time(NULL));
  
  for(i = 0; i < npts; i++)
    {
      in[i] = rand() / (RAND_MAX+1.);
      in1[i] = in[i];
    }
  
  fftw_execute(plan_fwd);				

  for(i = 0; i < npts; i++)
    {
      
      in[i] = out[i];
    }
  
  fftw_execute(plan_bwd); 				

  printf("%8s\t%16s\t%16s\n", "", "original_input", "fft_back");
  
  for(i = 0; i < npts; i++)
    {
      printf("%8d\t%16.12f\t%16.12f \n", i, creal(in1[i]), creal(out[i])/npts);
    }
	
  fftw_destroy_plan(plan_bwd);				
  fftw_destroy_plan(plan_fwd);				

  /* fftw_free(in);					 */
  /* fftw_free(in1);					 */
  /* fftw_free(out);					 */

  free(in);
  free(in1);
  free(out);
  
  fftw_cleanup();
  
  return 0;
}
