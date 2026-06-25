#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Process{
    private:
        int processID;
        int arrivalTime;
        int burstTime;
        int startTime;
        int completionTime;
        int waitingTime;
        int turnaroundTime;
        int priority;
    
    public:
        Process(){
            processID = 0;
            arrivalTime = 0;
            burstTime = 0;
            completionTime = 0;
            waitingTime = 0;
            turnaroundTime = 0;
            priority = 0;
        }
        Process(int MyprocessID, int MyarrivalTime, int MyburstTime, int Mypriority = 0){
            processID = MyprocessID;
            arrivalTime = MyarrivalTime;
            burstTime = MyburstTime;
            startTime = 0;
            completionTime = 0;
            waitingTime = 0;
            turnaroundTime = 0;
            priority = Mypriority;

        }

        int getarrivalTime(){
            return arrivalTime;
        }

        int getburstTime(){
            return burstTime;
        }
        
        int getprocessID(){
            return processID;
        }

        int getstartTime(){
            return startTime;
        }

        int getcompletionTime(){
            return completionTime;
        }

        int getwaitingTime(){
            return waitingTime;
        }

        int getturnaroundTime(){
            return turnaroundTime;
        }

        int getpriority(){
            return priority;
        }

        void setschedulingResults(int MystartTime, int MycompletionTime, int MywaitingTime, 
            int MyturnaroundTime){
                startTime = MystartTime;
                completionTime = MycompletionTime;
                waitingTime = MywaitingTime;
                turnaroundTime = MyturnaroundTime;

        }

        void displayProcess(){
            cout<<"ProcessID: "<< processID << endl;
            cout<<"Arrival Time: "<< arrivalTime << endl;
            cout<<"Burst Time: "<< burstTime << endl;
            cout<<"Start Time: "<< startTime << endl;
            cout<<"Completion Time: "<< completionTime << endl;
            cout<<"Waiting Time: "<< waitingTime << endl;
            cout<<"TurnaroundTime: "<< turnaroundTime << endl;

        }




};

class scheduling{
    private:
        struct ganttEntry
        {
            int processID;
            int startTime;
            int completionTime;
        };

        vector<ganttEntry> ganttEntries;

        
    public:

        void runFCFS(vector<Process> &processes){
            int currenttime = 0;
            int startTime = 0;
            int completionTime = 0;
            int waitingTime = 0;
            int turnaroundTime = 0;
            ganttEntries.clear();
            ganttEntry entry;
            for(int i = 0; i < processes.size(); i++){
                startTime = max(processes[i].getarrivalTime(),currenttime);
                completionTime = startTime + processes[i].getburstTime();
                waitingTime = startTime - processes[i].getarrivalTime();
                turnaroundTime = completionTime - processes[i].getarrivalTime();

                entry.processID = processes[i].getprocessID(); // gantt chart entries 
                entry.startTime = startTime;
                entry.completionTime = completionTime;

                ganttEntries.push_back(entry);
                processes[i].setschedulingResults(startTime, completionTime, waitingTime, turnaroundTime);
                currenttime = completionTime;
            }

        }

        void runSJN(vector<Process> &processes){

            vector <bool> completed(processes.size(), false); // Used to check what process have been completed
            int currenttime = 0;
            int numbercompleted = 0;
            ganttEntries.clear();
            ganttEntry entry;

            while(numbercompleted != processes.size()){
                int minburstime = 1000000;
                int selecetedindex = -1;
                int nextArrival = 10000000;
                for(int i = 0; i < processes.size(); i++){
                    if(processes[i].getarrivalTime() <= currenttime && completed[i] == false){
                       if(processes[i].getburstTime() < minburstime){
                                minburstime = processes[i].getburstTime();
                                selecetedindex = i;
                            }
                        }
                }
                if(selecetedindex == -1){ // jumping to the next arrival if no proceeses have arrived yet
                    for(int i = 0; i < processes.size(); i++){
                        if(completed[i] == false){
                             nextArrival = min(processes[i].getarrivalTime(),nextArrival);
                        }
                    }
                    currenttime = nextArrival;


                } else{
                    int startTime = max(processes[selecetedindex].getarrivalTime(),currenttime);
                    int completionTime = startTime + processes[selecetedindex].getburstTime();
                    int waitingTime = startTime - processes[selecetedindex].getarrivalTime();
                    int turnaroundTime = completionTime - processes[selecetedindex].getarrivalTime();

                    entry.processID = processes[selecetedindex].getprocessID(); // collecting entries
                    entry.startTime = startTime;
                    entry.completionTime = completionTime;
                    ganttEntries.push_back(entry);

                    processes[selecetedindex].setschedulingResults(startTime,completionTime,waitingTime,turnaroundTime);
                    currenttime = completionTime;

                    numbercompleted+= 1;

                    completed[selecetedindex] = true;

                }


            }

        }

        void displayGanttChart(){
            


            for(const auto &entry: ganttEntries){
                cout<<"P"<< entry.processID;
                cout<<": ";
                cout<<entry.startTime;
                cout<<"-";
                cout<< entry.completionTime << endl;
                
            }
            

        }



        void runRoundRobin(vector<Process> &processes, int timeQuantum){

            vector<int> remainingBurstTime(processes.size());
            int currentTime = 0;
            vector<bool> addedToQueue(processes.size(), false);
            queue<int> readyQueue;
            int numberCompleted = 0;
            vector<bool> hasStarted(processes.size(), false); // This vector will help us keep track of whether a process has started execution or not.
            int startTime = 0;
            ganttEntries.clear();
            ganttEntry entry;
            for(int i = 0; i < processes.size(); i++){ // We initialize the burst time of each process and store it in the vector remainingBurstTime. This will help us keep track of how much burst time is left for each process.
                remainingBurstTime[i] = processes[i].getburstTime();
            }

            while(numberCompleted != processes.size()){
                for(int i = 0; i < processes.size(); i++){
                    if(processes[i].getarrivalTime() <= currentTime && addedToQueue[i] == false){
                        readyQueue.push(i);
                        addedToQueue[i] = true;
                    }

                }

                if(readyQueue.empty()){ // If the ready queue is empty, we need to find the next process that will arrive and update the current time accordingly.
                    int nextArrival = 10000000;
                    for(int i = 0; i < processes.size(); i++){
                        if(addedToQueue[i] == false){
                            nextArrival = min(nextArrival, processes[i].getarrivalTime());
                        }
                    }
                    currentTime = nextArrival;
                    continue; // We continue to the next iteration of the while loop to check if any new processes have arrived.
                }

                int currentIndex = readyQueue.front();
                readyQueue.pop();

                if(hasStarted[currentIndex] == false){
                    startTime = currentTime;
                    hasStarted[currentIndex] = true;
                }
                entry.startTime = currentTime; // start time before execution 
                int executionTime = min(timeQuantum, remainingBurstTime[currentIndex]);
                currentTime += executionTime;
                remainingBurstTime[currentIndex] -= executionTime;
                entry.completionTime = currentTime; // completion time after execution
                entry.processID = processes[currentIndex].getprocessID();

                ganttEntries.push_back(entry); 


                for(int i = 0; i < processes.size(); i++){ // adding new processes to the queue that arrived during execution
                    if(processes[i].getarrivalTime() <= currentTime && addedToQueue[i] == false){
                        readyQueue.push(i);
                        addedToQueue[i] = true;
                    }
                }

                if(remainingBurstTime[currentIndex] > 0){
                    readyQueue.push(currentIndex); // pushing the current process back into the queue if it still has remaining burst time.
                } else {
                    int completionTime = startTime + processes[currentIndex].getburstTime();
                    int waitingTime = startTime - processes[currentIndex].getarrivalTime();
                    int turnaroundTime = completionTime - processes[currentIndex].getarrivalTime();

                    processes[currentIndex].setschedulingResults(startTime, completionTime, waitingTime, turnaroundTime);
                    currentTime = completionTime; 

                    numberCompleted += 1; // we only need this to keep track of the number of processes have been completed 

                    

                }


            }

        }


        void runPriority(vector<Process> &processes){
            vector <bool> completed(processes.size(), false); // pre set them all to false 
            int numbercompleted = 0;
            int currenttime = 0;
            ganttEntries.clear();
            ganttEntry entry;

            while(numbercompleted != processes.size()){
                int highestpriority = -1; // bigger numbers higher priority
                int selectedindex = -1;
                int nextarrivaltime = 10000;
                for(int i = 0; i < processes.size(); i++){
                    if(processes[i].getarrivalTime() <= currenttime && completed[i] == false){
                        if(processes[i].getpriority() > highestpriority){
                            highestpriority = max(highestpriority,processes[i].getpriority()); // keeping track of the processes with the highest priority
                            selectedindex = i; // and its index
                        }
                       
                    }
                    
                }

                if(selectedindex == -1){
                    for(int i = 0; i < processes.size(); i++){
                        if(completed[i] == false){
                            nextarrivaltime = min(nextarrivaltime,processes[i].getarrivalTime());
                        }
                    }
                    currenttime = nextarrivaltime;

                } else{
                    int startTime = max(processes[selectedindex].getarrivalTime(),currenttime);
                    int completionTime = startTime + processes[selectedindex].getburstTime();
                    int waitingTime = startTime - processes[selectedindex].getarrivalTime();
                    int turnaroundTime = completionTime - processes[selectedindex].getarrivalTime();

                    entry.processID = processes[selectedindex].getprocessID(); // updating gantt entry fields
                    entry.startTime = startTime;
                    entry.completionTime = completionTime;

                    ganttEntries.push_back(entry);

                    processes[selectedindex].setschedulingResults(startTime,completionTime,waitingTime,turnaroundTime);
                    currenttime = completionTime;

                    numbercompleted += 1;

                }
            }



        }




        void calculateAverages(vector<Process> &processes){
            int waitingTimesum = 0;
            int turnaroundTimesum = 0;

            for(int i =0; i < processes.size(); i++){
                waitingTimesum += processes[i].getwaitingTime();
                turnaroundTimesum += processes[i].getturnaroundTime();
            }
            double averagewaitingTime = static_cast<double>(waitingTimesum) / processes.size();
            double averageturnaroundTime = static_cast<double> (turnaroundTimesum)/ processes.size();
            cout<< "Average Waiting time: "<< averagewaitingTime << endl;
            cout<< "Average Turnaround time: "<< averageturnaroundTime << endl;


        }




};



int main(){
    vector<Process> processes;

    int processID;
    int arrivalTime;
    int BurstTime;
    int priority;

    
    int ans = 0;

    int algo = 0;

    cout<<"What algorithm do you want to use? " << endl;
    cout<<"Press 1 for FCFS or 2 for SJN 3 for Round Robin or 4 for Priority: ";
    cin>> algo;

    
    while(true){
        if(algo == 4){
            cout<<"Enter a processID: ";
            cin>> processID;
            cout<<"Enter a Arrival Time: ";
            cin>> arrivalTime;
            cout<<"Enter a Burst Time: ";
            cin>> BurstTime;
            cout<<"Enter the Priority: ";
            cin>> priority;
            processes.push_back(Process(processID,arrivalTime,BurstTime,priority));
            cout<<"Would you like to continue: Yes 1 /No 0: ";
            cin>>ans;
            if(ans == 0){
                break;
            } else{
                continue;
            }

        } else{
            cout<<"Enter a processID: ";
            cin>> processID;
            cout<<"Enter a Arrival Time: ";
            cin>> arrivalTime;
            cout<<"Enter a Burst Time: ";
            cin>> BurstTime;
            processes.push_back(Process(processID,arrivalTime,BurstTime));
            cout<<"Would you like to continue: Yes 1 /No 0: ";
            cin>>ans;
            if(ans == 0){
                break;
            } else{
                continue;
            }
        }
        
    }

    scheduling scheduler;



    switch(algo) {
        case 1:
            scheduler.runFCFS(processes);
            break;
        case 2:
            scheduler.runSJN(processes);
            break;
        case 3:
            scheduler.runRoundRobin(processes,3);
            break;
        case 4:
            scheduler.runPriority(processes);
            break;
        default:
            cout<<"Invalid algorithm input! " << endl;

    }
   
    
    
    

    scheduler.displayGanttChart();

    scheduler.calculateAverages(processes);




        

    


    
    return 0;

}




