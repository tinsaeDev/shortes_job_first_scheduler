
    /*
     program feature
            - SJF Calculator

     feature we have added
            - virtual SJF Simulator ( Works on windows OS only) ,
                process name should be a program name ex. cmd, notepad, calc.
                we will demonstrate how to use this on presentation day


    Group Members

        - Mikiyas Wondimneh
        - Tesfa Shibesh
        - Tamiru Agalneh
        - Hilina Buzuneh
        - Tinsae Belay
        - Zowditu Tilahun


    Important Tip
        - code successfully compiled with mingw32-gcc.exe compiler.
        - program is tested and verified to work on windows 7 64bit OS
        - processor : Intel64 Family 6 Model 37 Stepping 5 GenuineIntel ~1849 Mhz


    */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

    struct Process{

    // givens
    char name[100];
    int cpu_time;
    int arrival_time;

    //required

    int starting_time;
    int finish_time;
    int waiting_time;
    int reponse_time;
    int turnaround_time;

    // states

    int NEW;
    int READY;
    int TERMINATED;

    };


    struct Process proces[1000];
    int stack[1000];
    int stackSize =0;
    int top;


    int number_of_process;
    int number_of_process_terminated = 0;
    int all_process_are_run=0;
    int system_time;

    int total_waiting_time=0;
    int total_turnaround_time=0;
    float average_waiting_time=0.0;
    float average_turnaround_tim=0.0;
    //


    int use_virtual_scheduler = 0;




    void submitProcess();
    void LongTermScheduler();
    void shortTermScheduler();
    void dispacher();
    void displayExcutionLog();



int main(){



    system("color 9f");

    system_time = 0;

    printf("\t\t\t Shortest Job First\n\n\n");

    int program_type;
    printf("Press 1 to use this program as virtual SJF scheduler  \n");
    printf("Press 2 to use this program as simple SJF calculator!\n");
    scanf("%d",&program_type);

            if(program_type == 1){

                use_virtual_scheduler = 1;
                system("cls");
                printf("\t\tRegistered to be used as virtual SJF scheduler\n");
                getch();
                system("cls");
            }

            else{


                use_virtual_scheduler = 0;
            }

    submitProcess();


    while( ! all_process_are_run ==1){

        LongTermScheduler();

    }//

    printf("\n\n\nPress any key to see detailed log\n");
    getch();
    displayExcutionLog();

    return 0;

    }

void submitProcess(){

    system("cls");
    printf("Enter number of process: \n");
    scanf("%d",&number_of_process);
    system("cls");

     char temp[100];
     int x=0;
     for(x;x<number_of_process;x++){

         printf("\t\t\tEnter data fro process %d \n",(x+1));

                printf("Name\n");
                scanf("%s",&proces[x].name);

                printf("Arrival Time\n");
                scanf("%d",&proces[x].arrival_time);

                printf("CPU Time\n");
                scanf("%d",&proces[x].cpu_time);
                system("cls");

            }

}

void push(int index){


top++;
stackSize++;
stack[top] = index;


}

void makeEmpty(){


top =-1;
stackSize = 0;

}

void LongTermScheduler(){ // (Marks a process if it is never executed ) This must have a problem

// -------------------Short Term Scheduler -----------------------------------------

            makeEmpty();


            int i = 0;
            for(i; i<number_of_process;i++){ //for all process

                if( proces[i].arrival_time <=system_time && proces[i].TERMINATED != 1  ){ // if the process arrival time is less than or equal to current system time and a process is not terminated

                    proces[i].NEW = 1; // if above condition filled the process is TAGED as new
                    push(i);

                    }

            } // iteration ends here

            if(stackSize<=0){ // if no process are TAGED new


                system_time++; // increment system time
                LongTermScheduler(); // try for process to meet NEW condition

            }

            else if(stackSize > 0){ // if number of process are greater than 0

                    shortTermScheduler();

            }






}

void shortTermScheduler(){

        int processWithSameCPUtime = 0; // used if process with equal CPU_time exists
        int repeatedProces[1000];       // used if process with equal CPU_time exists
        int repeatedProcessSize = 0;    // used if process with equal CPU_time exists
        int repeatedProcessTop =-1;     // used if process with equal CPU_time exists


        int selectee = stack[0];// (This is giving me an error)// index: used to hold index of process to be run
        int x=0;
        for(x; x< stackSize ; x++){ // iterates for number of new process


                     if(selectee == stack[x]){

                        continue;

                     }


                     if( proces[selectee].cpu_time > proces[stack[x]].cpu_time ){

                           processWithSameCPUtime=0;
                           selectee = stack[x];

                     }

                     else if( proces[selectee].cpu_time < proces[stack[x]].cpu_time ){

                        continue;

                     }

                     else if( proces[selectee].cpu_time == proces[stack[x]].cpu_time ){


                        printf("Process have same cpu\n");
                        processWithSameCPUtime++;
                        repeatedProcessSize++;
                        repeatedProcessTop++;
                        repeatedProces[ repeatedProcessTop ] = x;


                     }


        } // iteration ends here


        int selecteeOfSelectees = repeatedProces[0];
        if(processWithSameCPUtime>0){

                int a=0;
                for(a; a<repeatedProcessSize;a++){

                        if( proces[selecteeOfSelectees].arrival_time > proces[ repeatedProces[a] ].arrival_time ){

                            selecteeOfSelectees = repeatedProces[a];
                        }

                }

                selectee = selecteeOfSelectees;


        }
        dispacher(selectee); // this is sending the same program
        return;


            }

void dispacher(int indexOfProcesToRun){ // run the Ready process



    if( use_virtual_scheduler == 0 ){


            proces[indexOfProcesToRun].starting_time = system_time;
            printf("Process %s started at %d second\n",proces[indexOfProcesToRun].name,proces[indexOfProcesToRun].starting_time);
            proces[indexOfProcesToRun].waiting_time = proces[indexOfProcesToRun].starting_time - proces[indexOfProcesToRun].arrival_time;
            proces[indexOfProcesToRun].reponse_time = proces[indexOfProcesToRun].starting_time - proces[indexOfProcesToRun].arrival_time;
            proces[indexOfProcesToRun].finish_time = proces[indexOfProcesToRun].starting_time + proces[indexOfProcesToRun].cpu_time;
            proces[indexOfProcesToRun].turnaround_time = proces[indexOfProcesToRun].finish_time - proces[indexOfProcesToRun].arrival_time;
            proces[indexOfProcesToRun].TERMINATED = 1;
            number_of_process_terminated++;


            total_waiting_time = total_waiting_time + proces[indexOfProcesToRun].waiting_time;
            total_turnaround_time = total_turnaround_time + proces[indexOfProcesToRun].turnaround_time;
            printf("Process %s terminated at %d second\n",proces[indexOfProcesToRun].name,proces[indexOfProcesToRun].finish_time);


            system_time = system_time + proces[indexOfProcesToRun].cpu_time;

            if( number_of_process == number_of_process_terminated ){

                all_process_are_run = 1;
            }


        }

    else if(use_virtual_scheduler == 1){


            char processName[100] = ""; // holds the name of a a program to launch

            strcat(processName, proces[indexOfProcesToRun].name );

            char start[200] = ""; // holds a start command
            char stop[200] = ""; // holds a  stop command

            int timeout = proces[indexOfProcesToRun].cpu_time; // hold the CPU time of process

            strcat(start,"start ");
            strcat(start,processName);

            strcat(stop,"taskkill /im ");
            strcat(stop,processName);
            strcat(stop,".exe /f |clip");



            system(start);     // starting  the  program via windows shell
            printf("Process %s started at %d second\n",proces[indexOfProcesToRun].name,system_time);

                time_t secondBefore = time(0);
                time_t newtime;
                while(1==1){  // waits until processor burst time ends
                    if( (int)secondBefore + timeout < (int) time(0)  ){ // casting time to integer for comparison
                        break; // time over, leave the loop
                    }
                    else{
                        newtime = time(0); // update to current time
                        }
                    }



            proces[indexOfProcesToRun].starting_time = system_time;
            proces[indexOfProcesToRun].waiting_time = proces[indexOfProcesToRun].starting_time - proces[indexOfProcesToRun].arrival_time;
            proces[indexOfProcesToRun].reponse_time = proces[indexOfProcesToRun].starting_time - proces[indexOfProcesToRun].arrival_time;
            proces[indexOfProcesToRun].finish_time = proces[indexOfProcesToRun].starting_time + proces[indexOfProcesToRun].cpu_time;
            proces[indexOfProcesToRun].turnaround_time = proces[indexOfProcesToRun].finish_time - proces[indexOfProcesToRun].arrival_time;
            proces[indexOfProcesToRun].TERMINATED = 1;
            number_of_process_terminated++;

            system_time = system_time + proces[indexOfProcesToRun].cpu_time;

            total_waiting_time = total_waiting_time + proces[indexOfProcesToRun].waiting_time;
            total_turnaround_time = total_turnaround_time + proces[indexOfProcesToRun].turnaround_time;

            system(stop); // stopping  the starting program via windows shell
            printf("Process %s terminated at %d second\n",proces[indexOfProcesToRun].name,proces[indexOfProcesToRun].finish_time);


            if( number_of_process == number_of_process_terminated ){

                all_process_are_run = 1;
            }




    }


 return;

}

void displayExcutionLog(){


system("cls");
printf("\t This is a log of process executed based on SJF scheduling \n\n\n");



int x=0;
for( x; x<number_of_process; x++ ){


printf("Name ----------------- %s \n",proces[x].name);
printf("CPU time ------------- %d \n",proces[x].cpu_time);
printf("Starting time--------- %d \n",proces[x].starting_time);
printf("Finish time ---------- %d \n",proces[x].finish_time);
printf("Waiting Time --------- %d \n",proces[x].waiting_time);
printf("Turn Around Time ----- %d \n",proces[x].turnaround_time);

printf("------------------------------------------------------------\n\n");

}
printf("*************************************************************\n");
printf("*************************************************************\n");


printf("total waiting  %d \n",total_waiting_time);
printf("total turnaround time %d \n",total_turnaround_time);

average_turnaround_tim = (float) total_turnaround_time / (float) number_of_process;
average_waiting_time = (float) total_waiting_time /(float) number_of_process;


printf("Average waiting time------   %f : \n", average_waiting_time );
printf("Average Turnaround time---   %f : \n\n\n",average_turnaround_tim);

printf("*************************************************************\n");
printf("*************************************************************\n");


printf("-----//-----//------//-------//-----//-------//---------//--------//--------//\n");

}
