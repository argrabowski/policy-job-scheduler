#ifndef __scheduler_h__
#define __scheduler_h__

//Constants
#define MAXCHAR 128

// Job Structure
struct job {
  int id;
  int length;
  struct job* next;
};

typedef struct job JOB;

// Function Prototypes
extern void fifo(JOB* curr, JOB* head); // first in first out scheduling
extern void sjf(JOB* curr, JOB* head); // shortest job first scheduling
extern void rr(JOB* curr, JOB* head, int time_slice); // round robin scheduling
extern void pexec(JOB* curr, JOB* head); // print the job execution sequence
extern void panal(JOB* curr, JOB* head); // print the policy analysis for fifo and sjf
extern void panalrr(JOB* curr, JOB* head); // print the policy analysis for rr

#endif
