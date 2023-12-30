#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scheduler.h" // include scheduler.h file for job struct, constants, and prototypes

int main(int argc, char **argv)
{
    char job_length[MAXCHAR]; // length of the job in file
    JOB *current, *head; // declare job structure
    head = current = NULL; // initialize job structure
    int job_id = 0; // initialize job identification
    if(argc < 4 || argc > 5) // if there are more or less than 3 arguments
    {
      printf("Enter 3 command line arguments.\n");
      return 0;
    }
    int time_slice = atoi(argv[3]); // get the time slice as the third argument
    FILE* workload_file; // declare the workload file
    workload_file = fopen(argv[2], "r"); // open the workload file as the second argument to read
    if(workload_file == NULL) // if fopen failed
    {
      printf("Cannot open file for reading.\n");
      fclose(workload_file); // close the workload file
      return 0;
    }
    while(fgets(job_length, sizeof(job_length), workload_file)) // get each line in the workload file
    {
      JOB* node = malloc(sizeof(JOB)); // make a new node
      node->id = job_id; // set the identification of the node
      node->length = atoi(job_length); // set the length of the node
      node->next = NULL; // next node doesn't exist
      job_id++; // increment the job identification
      if(head == NULL) // if the head doesn't exist
      {
        current = head = node; // set the current and head to the new node
      }
      else
      {
        current = current->next = node; // set current and next to the new node
      }
    }
    if(strcmp(argv[1], "FIFO") == 0) // if the first argument is FIFO
    {
      fifo(current, head); // run FIFO scheduling policy
    }
    else if(strcmp(argv[1], "SJF") == 0) // if the first argument is SJF
    {
      sjf(current, head); // run SJF scheduling policy
    }
    else if(strcmp(argv[1], "RR") == 0) // if the first argument is RR
    {
      rr(current, head, time_slice); // run RR scheduling policy
    }
    fclose(workload_file); // close the workload file
    return 0;
}

void fifo(JOB* curr, JOB* head) // FIFO scheduling policy
{
  printf("Execution trace with FIFO:\n");
  pexec(curr, head); // print the job execution
  printf("End of execution with FIFO.\n");
  printf("Begin analyzing FIFO:\n");
  panal(curr, head); // print the job analysis
  printf("End analyzing FIFO.\n");
}

void sjf(JOB* curr, JOB* head) // SJF scheduling policy
{
  printf("Execution trace with SJF:\n");
  curr = head; // set current node to head node
  JOB* index = NULL; // set index node to NULL
  int temp_id; // initialize temporary identification
  int temp_length; // initialize temporary length
  while(curr) // while current node is not NULL
  {
    index = curr->next; // index node is next node
    while(index) // while index node is not NULL
    {
      if(curr->length > index->length) // if the current length is greater than the index length
      {
        temp_id = curr->id; // set temorary id to current id
        temp_length = curr->length; // set temporary length to current length
        curr->id = index->id; // set current id to index id
        curr->length = index->length; // set current length to index length
        index->id = temp_id; // set index id to temporary id
        index->length = temp_length; // set index length to temporary length
      }
      else if(curr->length == index->length && curr->id > index->id) // if current length equals index length
      // and current id is greater than index id
      {
        temp_id = curr->id; // set temorary id to current id
        temp_length = curr->length; // set temporary length to current length
        curr->id = index->id; // set current id to index id
        curr->length = index->length; // set current length to index length
        index->id = temp_id; // set index id to temporary id
        index->length = temp_length; // set index length to temporary length
      }
      index = index->next; // set index node to next
    }
    curr = curr->next; // set current node to next
  }
  pexec(curr, head); // print the job execution
  printf("End of execution with SJF.\n");
  printf("Begin analyzing SJF:\n");
  panal(curr, head); // print the job analysis
  printf("End analyzing SJF.\n");
}

void rr(JOB* curr, JOB* head, int time_slice) // RR scheduling policy
{
  printf("Execution trace with RR:\n");
  curr = head; // set current node to head node
  int temp_id; // declare temporary identification
  int temp_length; // declare temporary length
  while(curr) // while current node is not NULL
  {
    if(curr->length > time_slice) // if the current length is greater than the time slice
    {
      temp_id = curr->id; // set temporary id to current id
      temp_length = curr->length; // set temporary length to current length
      curr->length = time_slice; // set current length to time slice
      while(curr->next) // go to end of list
      {
        curr = curr->next; // set current node to next node
      }
      curr->next = malloc(sizeof(JOB)); // make a new node at the end
      curr->next->id = temp_id; // set the id to temp id
      curr->next->length = temp_length-time_slice; // set the length to temp length minus time slice
      curr = head; // reset the current pointer to head
    }
    curr = curr->next; // current node is next
  }
  pexec(curr, head); // print the job execution
  printf("End of execution with RR.\n");
  printf("Begin analyzing RR:\n");
  panalrr(curr, head); // print the job analysis
  printf("End analyzing RR.\n");
}

void pexec(JOB* curr, JOB* head) // print the job execution
{
  curr = head; // set the current node to the beginning
  while(curr) // for every job in the list
  {
    printf("Job %d ran for: %d\n", curr->id, curr->length); // execution statement
    curr = curr->next; // current node is next
  }
}

void panal(JOB* curr, JOB* head) // policy analysis for fifo and sjf
{
  curr = head; // set the current node to the beginning
  int resp = 0; // response time
  int turn; // turnaround time
  int wait = 0; // wait time
  int total = 0; // total time since beginning
  int total_resp = 0; // total response time
  int total_turn = 0; // total turnaround time
  int total_wait = 0; // total wait time
  int count = 0; // count of total jobs
  while(curr) // for every node in the list
  {
    turn = total + curr->length; // turnaround is total time plus current length
    total_resp += resp; // increment total response time
    total_turn += turn; // increment total turnaround time
    total_wait += wait; // increment total wait time
    printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", curr->id, resp, turn, wait); // analysis statement
    resp += curr->length; // increment response time by current length
    total += curr->length; // increment total time by current length
    wait = total; // set wait time to total time
    count++; // increment count of jobs
    curr = curr->next; // set current to next
  }
  float av_resp = (float)total_resp / count; // get the average response time
  float av_turn = (float)total_turn / count; // get the average turnaround time
  float av_wait = (float)total_wait / count; // get the average wait time
  printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n", av_resp, av_turn, av_wait); // average analysis statement
}

void panalrr(JOB* curr, JOB* head) // policy analysis for rr
{
  curr = head;
  int resp = 0; // response time
  int turn = 0; // turnaround time
  int wait = 0; // wait time
  int start = 0; // keeps track of the time since the job started
  int end = 0; // keeps track of when the job finished
  int total = 0; // total time since beginning
  int temp_total = 0; // temporary total
  int total_resp = 0; // total response time
  int total_turn = 0; // total turnaround time
  int total_wait = 0; // total wait time
  int count = 0; // count of total jobs
  int prev_id = -1; // keeps track of the previous job's id number
  while(curr && curr->id > prev_id) // for every job if current id is greater than previous id
  {
    total += curr->length; // increment total time by current length
    resp = start; // set response time to the start of job
    end = total; // set end to the total time elapsed
    JOB* temp = curr->next; // temporary pointer
    while(temp) // for every job in the rest of the list
    {
      temp_total += temp->length; // increment temporary total by node length
      if(temp->id == curr->id) // if the temp id equals the current id
      {
        end = total + temp_total; // set end point to total time plus temporary total
        wait -= temp->length; // decrement the wait by temp length
      }
      temp = temp->next; // temp node is next
    }
    turn = end; // set the turnaround time to the end time
    wait += end-total; // increment the wait time by the end time minus total time
    temp_total = 0; // reset the temporary total
    total_resp += resp; // increment total response time
    total_turn += turn; // increment total turnaround time
    total_wait += wait; // increment total wait time
    printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", curr->id, resp, turn, wait); // analysis statement
    start += curr->length; // increment the start time
    wait = start; // reset the wait time
    count++; // increment the count of jobs
    prev_id = curr->id; // set the previous id to the current id
    curr = curr->next; // current node is next
  }
  float av_resp = (float)total_resp / count; // get the average response time
  float av_turn = (float)total_turn / count; // get the average turnaround time
  float av_wait = (float)total_wait / count; // get the average wait time
  printf("Average -- Response: %.2f  Turnaround %.2f  Wait %.2f\n", av_resp, av_turn, av_wait); // average analysis statement
}
