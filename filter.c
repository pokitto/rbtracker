#include <stdio.h>
#include <stdlib.h>
#include "pablio.h"
#include <sndfile.h>

#define SAMPLE_RATE          (44100)
#define SAMPLES_PER_FRAME        (1)
#define FRAMES_PER_BLOCK        (128)

/* Select whether we will use floats or shorts. */
#if 1
#define SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#else
#define SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#endif


#define    BUFFER_LEN      128

static void process_data (float *data, float *y_data, int count) ;
void filter(int,float *,float *,int,float *,float *);

float final[4]=3D{0, 0, 0, 0};


int =20
main (void)
{
	static float data [BUFFER_LEN] ;
	float y_data [BUFFER_LEN] ;
    SNDFILE      *infile, *outfile ;
    SF_INFO      sfinfo ;
    int          readcount ;
    char         *infilename =3D "input.wav" ;
    char         *outfilename =3D "output.wav" ;


	PaError  err;
    PABLIO_Stream     *aStream;

=09
	if (! (infile =3D sf_open (infilename, SFM_READ, &sfinfo)))
    {   /* Open failed so print an error message. */
        printf ("Not able to open input file %s.\n", infilename) ;
        /* Print the error message from libsndfile. */
        puts (sf_strerror (NULL)) ;
        return  1 ;
        } ;

    /* Open the output file. */
    if (! (outfile =3D sf_open (outfilename, SFM_WRITE, &sfinfo)))
    {   printf ("Not able to open output file %s.\n", outfilename) ;
        puts (sf_strerror (NULL)) ;
        return  1 ;
        } ;

    fflush(stdout);
    /* Open simplified blocking I/O layer on top of PortAudio. */
    err =3D OpenAudioStream( &aStream, SAMPLE_RATE, SAMPLE_TYPE,
                           (PABLIO_WRITE | PABLIO_MONO) );
    if( err !=3D paNoError ) goto error;
    fflush(stdout);
	=09
=09
	/* While there are.frames in the input file, read them, process
    ** them and write them to the output file.
    */
    while ((readcount =3D sf_read_float (infile, data, BUFFER_LEN)))
    {   process_data (data, y_data, readcount) ;
        sf_write_float (outfile, y_data, readcount) ;
        WriteAudioStream( aStream, data, FRAMES_PER_BLOCK );
    } ;

    /* Close input and output files. */
    sf_close (infile) ;
    sf_close (outfile) ;
    CloseAudioStream( aStream );
	return 0 ;

error:
  Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio =
stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return -1;

} /* main */



static void
process_data (float *data, float *y_data, int count)
{
	float a[4];
	float b[4];
	b[0]=3D0.0007;
	b[1]=3D0.0021;
	b[2]=3D0.0021;
	b[3]=3D0.0007;
	a[1]=3D-2.6236;
	a[2]=3D2.3147;
	a[3]=3D-0.6855;

	filter(3,a,b,128,data,y_data);
	return ;
} /* process_data */



void filter(int ord, float *a, float *b, int np, float *x, float *y)
{
    int i,j;
	//y[0]=3Dfinal[0];
	y[0]=3Db[0]*x[0];
	for (i=3D1;i<ord+1;i++)
	{
        //y[i]=3Dfinal[i];
		y[i]=3D0.0;
		for (j=3D0;j<i+1;j++)
        	y[i]+=3Db[j]*x[i-j];
        for (j=3D0;j<i;j++)
        	y[i]-=3Da[j+1]*y[i-j-1];
	}
	/* end of initial part */
=09
	for (i=3Dord+1;i<np+1;i++)
	{
		y[i]=3D0.0;
        for (j=3D0;j<ord+1;j++)
		    y[i]+=3Db[j]*x[i-j];
        for (j=3D0;j<ord;j++)
			y[i]-=3Da[j+1]*y[i-j-1];
	}
	final[0]=3Dy[125];
	final[1]=3Dy[126];
	final[2]=3Dy[127];
	final[3]=3Dy[128];

} /* end of filter */
