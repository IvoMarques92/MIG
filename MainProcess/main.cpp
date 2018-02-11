/******************************************************* MIG ********************************************************************************************************
 * by Cristiano Rodrigues and Ivo Marques
 *
 * Project features:
 *
 * - Produce sound based on patterns that are made in a touch matrix;
 * - React to some hands slide gestures;
 * - Show a pattern in a matrix of leds, created by the user in touch inputs;
 * - Detect pattern from touch matrix;
 * - Create a musical effect according with the matrix pattern;
 * - Produce melody.
 *
 *********************************************************************************************************************************************************************/

#include <iostream>
#include "CMig.h"

#include "vector"
#include "time.h"


using namespace std;

#include "CTouchMatrix.h"
#include "CHandSlideSensor.h"

#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <stdio.h>



char shm_fn[] = "shmDaemon";
char sem_fn[] = "semaphoreDaemon";


int main()
{
    CMig* Mig = CMig::getInstance();

    Mig->initMigAtuators();
    Mig->initMigSensors();
    Mig->initQueue();
    Mig->initSemaphores();
    Mig->run();



    /**+++++++++++++++++test of the CGenerateSound+++++++++++++++++*/
//    CGenerateSound * sound = new CGenerateSound();

//    vector<vector<char>> absoluteMatrix;

//    absoluteMatrix.resize(8);
//    for ( int i = 0 ; i < 8 ; i++ )
//        absoluteMatrix[i].resize(8);

//    for(int i = 0; i < 8; i++)
//        for(int j = 0; j < 8; j++)
//        {
//            if(i==j)
//            absoluteMatrix[i][j] = 1;
//        }



//    sound->setAbsolutePattern(absoluteMatrix);

//    sound->generateSound(1);

    /**+++++++++++++END of test of the CGenerateSound+++++++++++++++++*/
    /**+++++++++++++++++++ test of the Shared Memory++++++++++++++++++*/
//    CConvertWav wav;

//    wav.convertWavFile("/root/sounds/absoluteMatrixSounds/l.wav");
//    wav.convertWavFile( sound->changeSpeed(0));
//    cout << sound->getPathGeneratedSound() << endl;
//    cout << sound->getPathTempoEffect() << endl;

//    char* shmptr, *pt;
//        unsigned int mode;
//        unsigned int shmdes;
//        sem_t *sem_des;
//        int index, size, SHM_SIZE;

//        size = wav.getSubChunk();
//        cout << "SubChunk " << size << endl;
//        pt = (char *) &size;
//        mode = S_IRWXU|S_IRWXG;
//        /* Open the shared memory object */
//        if ( (shmdes = shm_open(shm_fn,O_CREAT|O_RDWR|O_TRUNC, mode)) == -1 ) {
//             perror("shm_open failure");
//             exit(-1);
//        }
//        /* Preallocate a shared memory area by determine the current
//        value of a configurable system limit for pagesize*/
//        SHM_SIZE = 10000 * sysconf(_SC_PAGE_SIZE);
//        if(ftruncate(shmdes, SHM_SIZE) == -1){
//            perror("ftruncate failure");
//            exit(-1);
//        }
//        if((shmptr =(char *)mmap(0, SHM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED,shmdes,0)) == (caddr_t) -1) {
//            perror("mmap failure");
//            exit(-1);
//        }
//        /* Create a semaphore in locked state */
//        sem_des = sem_open(sem_fn, O_CREAT, 0644, 0);
//        if(sem_des == (void*)-1) {
//          perror("sem_open failure");
//          exit(-1);
//        }

//        /*Passar este size primeiro que é o chunk e depois ler a data corresponde a esse size*/
//        shmptr[0] = *pt++;
//        shmptr[1] = *pt++;
//        shmptr[2] = *pt++;
//        shmptr[3] = *pt;

//        char *bufferOut = (char *) wav.getPCM();

//        /* Access to the shared memory area */
//        for(index = 4; index < size + 4; index++) {
//            shmptr[index]=bufferOut[index - 4];
//         //   cout << "test " << index << endl;
//        }

//        /* Release the semaphore lock */
//        sem_post(sem_des);
//        munmap(shmptr, SHM_SIZE);
//        /* Close the shared memory object */
//        close(shmdes);
//        /* Close the Semaphore */
//        sem_close(sem_des);
//        /* Delete the shared memory object */
//        //shm_unlink(shm_fn);

    /**+++++++++++++END of test of the Shared Memory++++++++++++++++++*/

    /**++++++++++++++++ of test of the Touch Matrix ++++++++++++++++++*/

    char * buffer = new char [4];

    CTouchMatrix* touch = CTouchMatrix::getInstance();

static int a = 0;

    while(1)
    {
        usleep(250000); // substituir por um signal
        if(touch->openTouchMatrix() < 0)
            cout << "erro open the matrix" << endl;
        buffer = touch->readTouchMatrix();
        for(int i = 0; i < 4; i++)
            buffer[i] = buffer[i]+48;
        a++;
        cout << buffer[0] << buffer[1] << buffer[2] <<  buffer[3] << endl;
        if(a == 4){
        cout << endl;
            a = 0;
        }
        touch->closeTouchMatrix();
    }

    /**+++++++++++++END of test of the Touch Matrix++++++++++++++++++*/

    /**++++++++++++++++ test of the capacitive Sensors ++++++++++++++*/

//    char * buffer = new char [4];

//    CHandSlideSensor *caps = CHandSlideSensor::getInstance();

//   while (1) {
//        if(caps->openHandSlideSensor() < 0)
//            cout << "Error Open Capacitive Sensors" << endl;
//        buffer = caps->readHandSlideSensor();
//        for(int i = 0; i < 4; i++)
//            buffer[i] = buffer[i]+48;
//        cout << buffer[0] << buffer[1] << buffer[2] <<  buffer[3] << endl << endl;
//        caps->closeHandSlideSensor();
//        usleep(250000); // substituir por um signal); // substituir por um signal
//    }
    /**++++++++++++ End test of the capacitive Sensors ++++++++++++++*/

    cout << "Mig was initialize" << endl;
    return 0;
    //while(1);
}
