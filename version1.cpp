#include <iostream>
#include <vector>
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
    
    public:
        Process(){
            processID = 0;
            arrivalTime = 0;
            burstTime = 0;
            completionTime = 0;
            waitingTime = 0;
            turnaroundTime = 0;
        }
        Process(int MyprocessID, int MyarrivalTime, int MyburstTime){
            processID = MyprocessID;
            arrivalTime = MyarrivalTime;
            burstTime = MyburstTime;
            startTime = 0;
            completionTime = 0;
            waitingTime = 0;
            turnaroundTime = 0;

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
    public:

        void runFCFS(vector<Process> &processes){
            int currenttime = 0;
            int startTime = 0;
            int completionTime = 0;
            int waitingTime = 0;
            int turnaroundTime = 0;

            for(int i = 0; i < processes.size(); i++){
                startTime = max(processes[i].getarrivalTime(),currenttime);
                completionTime = startTime + processes[i].getburstTime();
                waitingTime = startTime - processes[i].getarrivalTime();
                turnaroundTime = completionTime - processes[i].getarrivalTime();

                processes[i].setschedulingResults(startTime, completionTime, waitingTime, turnaroundTime);
                currenttime = completionTime;
            }

        }

        void runSJN(vector<Process> &processes){

            vector <bool> completed(processes.size(), false); // Used to check what process have been completed
            int numbercompleted = 0;
            int currenttime = 0;
            int startTime = 0;
            int completionTime = 0;
            int waitingTime = 0;
            int turnaroundTime = 0;
            

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
                if(selecetedindex == -1){
                    for(int i = 0; i < processes.size(); i++){
                        if(completed[i] == false){
                             nextArrival = min(processes[i].getarrivalTime(),nextArrival);
                        }
                    }
                    currenttime = nextArrival;


                } else{
                    startTime = max(processes[selecetedindex].getarrivalTime(),currenttime);
                    completionTime = startTime + processes[selecetedindex].getburstTime();
                    waitingTime = startTime - processes[selecetedindex].getarrivalTime();
                    turnaroundTime = completionTime - processes[selecetedindex].getarrivalTime();

                    processes[selecetedindex].setschedulingResults(startTime,completionTime,waitingTime,turnaroundTime);
                    currenttime = completionTime;

                    numbercompleted+= 1;

                    completed[selecetedindex] = true;

                }


            }

        }

        void displayGanttChart(vector<Process> &processes){
            vector<Process> sortedProcesses = processes;
            
            for(int i = 0; i < sortedProcesses.size(); i++){
                int minstatTime = sortedProcesses[i].getstartTime();
                int selectedIndex = i;
                for(int j = i+1; j < sortedProcesses.size(); j++){
                    if(sortedProcesses[j].getstartTime() < minstatTime){
                        selectedIndex = j;
                        minstatTime = sortedProcesses[j].getstartTime();
                    }
                }

                swap(sortedProcesses[i],sortedProcesses[selectedIndex]);
                
            }

            for(int i = 0; i < sortedProcesses.size(); i++){
                cout<<"| P"<< sortedProcesses[i].getprocessID() << " ";
            }
            cout<<"|"<< endl;
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

    
    int ans = 0;

    int algo = 0;

    while(true){
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
            cout<<"What algorithm do you want to use? " << endl;
            cout<<"Press 1 for FCFS or 2 for SJN: ";
            cin>> algo;
            break;
        }else if (ans == 1)
        {
            continue;
        }
        
    }

    scheduling scheduler;

    if(algo == 1){
        scheduler.runFCFS(processes);
    } else if (algo == 2)
    {
        scheduler.runSJN(processes);
    } else{
        cout<<"Invalid algorithm input! " << endl;
        
    }
    
    
    

    scheduler.displayGanttChart(processes);

    scheduler.calculateAverages(processes);




        

    


    
    return 0;

}




