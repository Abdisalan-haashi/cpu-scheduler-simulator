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

        void displayGanttChart(vector<Process> &processes){

            for(int i = 0; i < processes.size(); i++){
                cout<< "P" << processes[i].getprocessID()<< ": " << processes[i].getstartTime() << "-" << processes[i].getcompletionTime() << endl;
            }
        }

                

        void calculateAverages(vector<Process> &processes){
            int waitingTimesum = 0;
            int turnaroundTimesum = 0;

            for(int i =0; i < processes.size(); i++){
                waitingTimesum += processes[i].getwaitingTime();
                turnaroundTimesum += processes[i].getturnaroundTime();
            }

            cout<< "Average Waiting time: "<< waitingTimesum / processes.size() << endl;
            cout<< "Average Turnaround time: "<< turnaroundTimesum / processes.size() << endl;


        }




};



int main(){
    vector<Process> processes;

    int processID;
    int arrivalTime;
    int BurstTime;

    
    int ans = 0;

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
            break;
        }else if (ans == 1)
        {
            continue;
        }
        
    }

    scheduling scheduler;
    scheduler.runFCFS(processes);
    

    scheduler.displayGanttChart(processes);

    scheduler.calculateAverages(processes);




        

    


    
    return 0;

}




