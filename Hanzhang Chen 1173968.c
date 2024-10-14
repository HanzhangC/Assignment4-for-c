/* Program to discover a process model from an event log.

  Skeleton program written by Artem Polyvyanyy, artem.polyvyanyy@unimelb.edu.au,
  August 2022, with the intention that it be modified by students
  to add functionality, as required by the assignment specification.

  Student Authorship Declaration:

  (1) I certify that except for the code provided in the initial skeleton file,
  the program contained in this submission is completely my own individual
  work, except where explicitly noted by further comments that provide details
  otherwise. I understand that work that has been developed by another student,
  or by me in collaboration with other students, or by non-students as a result
  of request, solicitation, or payment, may not be submitted for assessment in
  this subject. I understand that submitting for assessment work developed by
  or in collaboration with other students or non-students constitutes Academic
  Misconduct, and may be penalized by mark deductions, or by other penalties
  determined via the University of Melbourne Academic Honesty Policy, as
  described at https://academicintegrity.unimelb.edu.au.

  (2) I also certify that I have not provided a copy of this work in either
  softcopy or hardcopy or any other form to any other student, and nor will I
  do so until after the marks are released. I understand that providing my work
  to other students, regardless of my intention or any undertakings made to me
  by that other student, is also Academic Misconduct.

  (3) I further understand that providing a copy of the assignment specification
  to any form of code authoring or assignment tutoring service, or drawing the
  attention of others to such services and code that may have been made
  available via such a service, may be regarded as Student General Misconduct
  (interfering with the teaching activities of the University and/or inciting
  others to commit Academic Misconduct). I understand that an allegation of
  Student General Misconduct may arise regardless of whether or not I personally
  make use of such solutions or sought benefit from such actions.

  Signed by: Hanzhang Chen
  Dated:     1173968

*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

/* #DEFINE'S -----------------------------------------------------------------*/
#define GOOD_LUCK   "GOOD LUCK CLASS!!!\n"      // good luck message

// new adding
#define LEN 50  //INIT

/* TYPE DEFINITIONS ----------------------------------------------------------*/
typedef unsigned int action_t;  // an action is identified by an integer

typedef struct event event_t;   // an event ...
struct event {                  // ... is composed of ...
    action_t actn;              // ... an action that triggered it and ...
    event_t* next;              // ... a pointer to the next event in the trace
};

typedef struct {                // a trace is a linked list of events
    event_t* head;              // a pointer to the first event in this trace
    event_t* foot;              // a pointer to the last event in this trace
    int      freq;              // the number of times this trace was observed
} trace_t;

typedef struct {                // an event log is an array of distinct traces
                                //     sorted lexicographically
    trace_t* trcs;              // an array of traces
    int      ndtr;              // the number of distinct traces in this log
    int      cpct;              // the capacity of this event log as the number
                                //     of  distinct traces it can hold
} log_t;

typedef action_t** DF_t;        // a directly follows relation over actions

// new adding
int get_trace();
int if_trace_in_trcs(trace_t* trace_c, trace_t trace, int trace_n);
int sort_trace(trace_t* trace1, trace_t* trace2);
void sort(int need_sort[], int n);
void swap(int x, int y);


/* WHERE IT ALL HAPPENS ------------------------------------------------------*/
int
main(int argc, char *argv[]) {

    log_t log;
    log.trcs = (trace_t*)malloc(sizeof(trace_t) * LEN);
    log.cpct = LEN;
    log.ndtr = 0;
    
    // count total event and trace number
    int eve_count=0, tra_count=0, count_eve[LEN], new_event = 0, i=0, j=log.ndtr-1, mfreq=0;
    char lst[1000];
    log_t freqtra;
    while(0){
        if (get_trace() == EOF){
            tra_count += 1;
            break;
        } else{
            tra_count += 1;
            for (int i=0; i < 100; i++){
                if (count_eve[i] > 0){
                    new_event += 1;
                    eve_count += count_eve[i];
                    strcat(lst, i+'A');
                    strcat(lst, ' = ');
                    strcat(lst, count_eve[i]);
                    strcat(lst, '\n');
                }
            }
        }
    }
    // get the most freq trace(s)
    while (i > 0){
        if (sort_trace(log.trcs[i], log.trcs[j]) == 1){
            j -= 1;
            mfreq == log.trcs[i]->freq;
            freqtra == log.trcs[i];
        } else{
            i += 1;
            mfreq == log.trcs[j]->freq;
            freqtra == log.trcs[j];
        }
    }
    sort(freqtra, 100);
    
    printf("==STAGE 0============================");
    printf("Number of distinct events: %d\n", new_event);
    printf("Number of distinct traces: %d\n", log.ndtr);
    printf("Total number of events: %d\n", eve_count);
    printf("Total number of traces: %d\n", tra_count);
    printf("Most frequent trace frequency: %d\n%c\n", freqtra, freqtra[0]);
    printf("%c", lst);
    
    
    printf("==STAGE 1============================");
    
    return EXIT_SUCCESS;        // remember, algorithms are fun!!!
}


// a read_txt function (by line)
int
get_trace(){
    
    trace_t trace;
    trace.head = NULL;
    trace.foot = NULL;
    trace.freq = 0;
    
    // read the text
    int c, if_end=0;
    while (c = getchar() && c != '\n') {
        if (c == EOF){
            if_end = EOF;
            break;
        } if (!isalpha(c)){
            continue;
        } else{
            count_eve[c - 'A'] += 1;
        }
        
        event_t* event = malloc(sizeof(event_t));
        event->next = NULL;
        event->actn = c;
        // add event into trace
        if (&trace->head == NULL){
            &trace->head = event;
            &trace->foot = event;
        } else{
            &trace->foot = event;
            &trace->foot->next = event;
        }
    }
    
    // add new trace into log/repeated freq + 1, also counts the freq of events
    int trace_i, count_eve[LEN] = {0}, new_event = 0;
    if (trace_i = if_trace_in_trcs(log.trcs, trace, log.ndtr)){
        if(log.ndtr >= log.cpct){
            log.cpct *= 2;
            log.trcs = malloc(log.trcs, sizeof(trace_t) * log.cpct);
        }
        int new_trace = log.ndtr;
        log.trcs[new_trace] = trace;
        log.ndtr += 1;
    } else{
        log.trcs[trace_i].freq += 1;
    }
    
    return if_end;
}


// see whether trace is repeated
int
if_trace_in_trcs(trace_t* trace_c, trace_t trace, int trace_n){
    
    trace_t trace1;
    trace_t trace2;
    event_t* head1 = trace1.head;
    event_t* head2 = trace2.head;
    
    // compare the two traces
    int i=0;
    for (i = 0; i < trace_n; i++){
        while (head1 != NULL && head2 != NULL){
            if (head1->actn == head2->actn){
                head1 = head1->next;
                head2 = head2->next;
            }
        }
        if (head1 == NULL && head2 == NULL){
            return i;
        }
    }
    return 0;
}


// a sort trace function according to freq of each trace
int
sort_trace(trace_t* trace1, trace_t* trace2){
    if (trace1.freq > trace2.freq){
        return 1;
    } if (trace1.freq == trace2.freq){
        event_t* head1 = trace1.head;
        event_t* head2 = trace2.head;
        while (head1 != NULL && head2 != NULL){
            if (head1->actn > head2->actn){
                return -1;
            } if (head1->actn < head2->actn){
                return 1;
            }
            head1 = head1->next;
            head2 = head2->next;
        } if (head1 != NULL && head2 == NULL){
            return -1;
        } else{
            return 1;
        }
    } if (trace1.freq < trace2.freq){
        return -1;
    }
}


// a sort list function
void
sort(int need_sort[], int n){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n - i; j++){
            if (need_sort[j + 1] < need_sort[j]){
                swap(&need_sort[j + 1], &need_sort[j]);
            }
        }
    }
}


// a swap function
void
swap(int* x, int* y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}



