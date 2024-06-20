#include <iostream>
#include <bits/stdc++.h>
#include<vector>
#include<algorithm>
#include<cmath>
#include<string>
#include <numeric>
#include<map>
#include<iomanip>
using namespace std;
#define py cout << "YES" << endl
#define pn cout << "NO" << endl
#define ll int
typedef pair<ll, ll> pll;
#define forw(i, j, n) for (ll i = j; i < n; i++)
#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define pb push_back
#define ppb pop_back
#define all(x) x.begin(), x.end()
ll wait_time[100], burst_time[100], arr_t[100], turn_around_time[100], num_proc, process_id[100];
float avg_wait_time[5], avg_turn_around_time[5], idle_time[5];
vector<ll> start_state,finish_state;
vector<string> process_state;
void display(ll c) {
  printf("Average Waiting Time: %f\nAverage Turn Around Time: %f\nCPU Idleness Time: %f", avg_wait_time[c - 1], avg_turn_around_time[c - 1], idle_time[c-1]);
}
void intialise(ll c) {
    if(c == 0){
        
        ll x=100;
        cout<<"How many processes you have?(atmost 100 can only be queried) "<<endl;
        
        cin>>num_proc;
        int i;

        vector<pair<pair<ll,ll>,ll> > process_info(num_proc);

        forw(i,0,num_proc) {process_id[i] = i + 1;}

        forw(i,0,num_proc) {
            cout<<"Specify the execution time(in ms) needed for the process: "<<i+1<<" : "<<endl;
            cin>>burst_time[i];
            process_info[i].first.second=burst_time[i];
            cout<<"Specify the time(in ms) at which the process  "<<i+1<<"arrives: "<<endl;
            cin>>arr_t[i];
            process_info[i].first.first=arr_t[i];
            process_info[i].second=i+1;
        }
    }

    else{
        ll time;
        cout<<"What's the arrival time"<<endl;
        cin>>time;

        forw(i,0,time+1){
            ll val;
            cout<<"Enter the number of processes arriving at time "<<i<<":\t";
            cin>>val;
            num_proc += val;

            forw(j,1,val+1){
                ll idx;
                cout<<"Enter the process id for process arriving:"<<endl;
                cin>>idx;
                cout<<"Input the burst duration for process ID: "<<idx<<endl;
                cin>>burst_time[idx-1];
                arr_t[idx-1] = i;
            }
        }
    }

    vector<pair<pll,ll> > process_info(num_proc);
    for(int i = 0; i < num_proc; i++){
        process_info[i].first.first = arr_t[i];
        process_info[i].first.second = burst_time[i];
        process_info[i].second = i+1;
    }

    
    sort(all(process_info));
    forw(i,0,num_proc) process_id[i] = process_info[i].second;
    forw(i,0,num_proc) {
        burst_time[i]=process_info[i].first.second;
        arr_t[i]=process_info[i].first.first;
    }
    forw(i,0,5) {
        avg_wait_time[i] = 0.0;
        avg_turn_around_time[i] = 0.0;
    }
}
ll avg_burst_time_fun(ll burst_time[]){
    vector<int> temp;
    for(int i=0;i<num_proc;i++) if(burst_time[i]) temp.push_back(burst_time[i]);
    sort(all(temp));
    ll siz=temp.size();
    if(siz%2) return temp[siz/2];
    return (temp[siz/2]+temp[(siz/2)-1])/2;
}
void first_come_first_serve() {
    start_state.clear();
    finish_state.clear();
    process_state.clear();
    ll time = arr_t[0] + burst_time[0];
    idle_time[0]=arr_t[0];
    if(arr_t[0]){
        start_state.push_back(0);
        finish_state.push_back(arr_t[0]);
        process_state.push_back("Idle");
    }
    start_state.push_back(arr_t[0]);
    finish_state.push_back(time);
    process_state.push_back("Id["+to_string(process_id[0])+"]");
    wait_time[0] = 0;
    avg_turn_around_time[0] = turn_around_time[0] = burst_time[0];
    forw(i,1,num_proc) {
        if(arr_t[i]<=time){
            start_state.push_back(time);
            wait_time[i] = time - arr_t[i];
            time += burst_time[i];
            finish_state.push_back(time);
            process_state.push_back("Id["+to_string(process_id[i])+"]");
            avg_wait_time[0] += wait_time[i];
            turn_around_time[i] = wait_time[i] + burst_time[i];
            avg_turn_around_time[0] += turn_around_time[i];
        }
        else{
            start_state.push_back(time);
            finish_state.push_back(arr_t[i]);
            process_state.push_back("Idle");
            start_state.push_back(arr_t[i]);
            idle_time[0] += arr_t[i] - time;
            time = burst_time[i] + arr_t[i];
            finish_state.push_back(time);
            process_state.push_back("Id["+to_string(process_id[i])+"]");
            wait_time[i] = 0;
            avg_wait_time[0] += wait_time[i];
            turn_around_time[i] = wait_time[i] + burst_time[i];
            avg_turn_around_time[0] += turn_around_time[i];
        }
    }
  avg_turn_around_time[0] /= num_proc;
  avg_wait_time[0] /= num_proc;
  printf("SR.\tA.T.\tC.T.\tB.T.\tW.T.\tT.A.T.\n");
  forw(i,0,num_proc) {
    printf("%3d\t%3d\t%3d\t%3d\t%3d\t%4d\n", process_id[i], arr_t[i],arr_t[i]+turn_around_time[i], burst_time[i], wait_time[i], turn_around_time[i]);
  }
  cout<<endl;
  cout<<"Start Time \t";
  forw(i,0,start_state.size()) {
    cout<<start_state[i]<<endl;
  }
  cout<<endl;
  cout<<"Finish Time \t";
  forw(i,0,start_state.size()) {
    cout<<finish_state[i]<<endl;
  }
  cout<<endl;
  cout<<"State\t\t";
  forw(i,0,start_state.size()){
    cout<<process_state[i]<<endl;
  }
  cout<<endl;
  cout<<endl;
}
void Round_rob() {
    start_state.clear();
    finish_state.clear();
    process_state.clear();
    ll sumi = 0, x, ctr = 0, qt=0;
    ll wt = 0, tat = 0, temp[100];
    x = num_proc;
    for (int i = 0; i < num_proc; i++) {
        temp[i] = burst_time[i];
    } 
  printf("\nEnter Time Quantum:\t");
  scanf("%d", & qt);
  int i=0;
  printf("\nProcess ID\t\tArrivalTime\tCompletion Time\tBurst Time\t Turnaround Time\t Waiting Time\n");
  for (sumi = 0, i = 0; x != 0;) {
    if(arr_t[i]<=sumi){
        if (temp[i] <= qt && temp[i] > 0) {
        start_state.push_back(sumi);
        sumi = sumi + temp[i];
        finish_state.push_back(sumi);
        process_state.push_back("Id["+to_string(process_id[i])+"]");
          temp[i] = 0;
          ctr = 1;
        } 
        else if (temp[i] > 0) {
            start_state.push_back(sumi);
            temp[i] = temp[i] - qt;
            sumi = sumi + qt;
            finish_state.push_back(sumi);
            process_state.push_back("Id["+to_string(process_id[i])+"]");
        }
    }
    else{
        start_state.push_back(sumi);
        finish_state.push_back(arr_t[i]);
        process_state.push_back("Idle");
        if (temp[i] <= qt && temp[i] > 0) {
          idle_time[2] += arr_t[i] - sumi;
        start_state.push_back(arr_t[i]);
          sumi = temp[i]+arr_t[i];
        finish_state.push_back(sumi);
        process_state.push_back("Id["+to_string(process_id[i])+"]");
          temp[i] = 0;
          ctr = 1;
        } 
        else if (temp[i] > 0) {
          idle_time[2] += arr_t[i] - sumi;
        start_state.push_back(arr_t[i]);
          sumi = temp[i]+arr_t[i];
        finish_state.push_back(sumi);
        process_state.push_back("Id["+to_string(process_id[i])+"]");
          temp[i] = temp[i] - qt;
          sumi = arr_t[i] + qt;
        }
    }

    if (temp[i] == 0 && ctr == 1) {
      x--;
      cout<<"Process["<<process_id[i]<<"]\t\t\t"<<arr_t[i]<<"\t\t"<<arr_t[i]+ sumi - arr_t[i]<<"\t\t"<<burst_time[i]<<"\t\t"<<sumi - arr_t[i]<<"\t\t"<<sumi - arr_t[i] - burst_time[i]<<endl;
      wt = wt + sumi - arr_t[i] - burst_time[i];
      tat = tat + sumi - arr_t[i];
      ctr = 0;
    }
    if (i == num_proc - 1) i = 0;
    else i++;
  }
  avg_wait_time[2] = wt * 1.0 / num_proc;
  avg_turn_around_time[2] = tat * 1.0 / num_proc;
  cout<<endl;
  cout<<"Starting Time \t";
  forw(i,0,start_state.size()) {
    cout<<start_state[i]<<"\t";
  }
  cout<<endl;
  cout<<"Finishing Time \t";
  forw(i,0,start_state.size()) {
    cout<<finish_state[i]<<"\t";
  }
  cout<<endl;
  cout<<"State\t\t";
  forw(i,0,start_state.size()) {
    cout<<process_state[i]<<"\t";
  }
  cout<<endl;
  cout<<endl;
}
void short_rem_time_first() {
    start_state.clear();
    finish_state.clear();
    process_state.clear();
    int cnt = 0, time=0, sm=0;
    vector<int> temp(num_proc);
    double mean = 0, tt = 0, end;
    forw(i,0,num_proc) {
      temp[i] = burst_time[i];
    }
    printf("\nProcess ID\t\tArrivalTime\tCompletion Time\tBurst Time\t Turnaround Time\t Waiting Time\n");
    for (time = 0; cnt != num_proc; time++){
        int mnn = 1e9;
        int y = 0 , mn = 1e9;
        forw(i,0,num_proc) {
            if (arr_t[i] <= time && burst_time[i] > 0) y = 1;
        }
        if(y == 0){
            forw(i,0,num_proc) {
                if(burst_time[i] > 0)
                mn = min(mn , arr_t[i]);
            }
            start_state.push_back(time);
            process_state.push_back("Idle");
            idle_time[3] += mn - time;
            time = mn;
            finish_state.push_back(time);
        }
        forw(i,0,num_proc) {
            if (arr_t[i] <= time && burst_time[i] < mnn && burst_time[i] > 0) {mnn=burst_time[i];sm = i;}
        }
        burst_time[sm]--;
        start_state.push_back(time);
        finish_state.push_back(time+1);
        process_state.push_back("Id["+to_string(process_id[sm])+"]");
        if (burst_time[sm] == 0) {
            cnt++;
            end = time + 1;
            cout<<"Process["<<process_id[sm]<<"]\t\t\t"<<arr_t[sm]<<"\t\t"<<arr_t[sm] + end - arr_t[sm]<<"\t\t"<<temp[sm]<<"\t\t"<<end - arr_t[sm]<<"\t\t"<<end - arr_t[sm] - temp[sm]<<endl;
            mean = mean + end - arr_t[sm] - temp[sm];
            tt = tt + end - arr_t[sm];
        }
    }
    avg_wait_time[3] = mean / num_proc;
    avg_turn_around_time[3] = tt / num_proc;
    forw(i,0,num_proc) {
      burst_time[i]=temp[i];
    }
  cout<<endl;
  cout<<"Start Time \t";
  forw(i,0,start_state.size()) {
    cout<<start_state[i]<<"\t";
  }
  cout<<endl;
  cout<<"Finish Time \t";
  forw(i,0,start_state.size()) {
    cout<<finish_state[i]<<"\t";
  }
  cout<<endl;
  cout<<"State\t\t";
  forw(i,0,start_state.size()) {
    cout<<process_state[i]<<"\t";
  }
  cout<<endl;
  cout<<endl;
}
void innovated_fun() {
    start_state.clear();
    finish_state.clear();
    process_state.clear();
    int count = 0, time=0, sm = 0,wt=0,ta=0;
    vector<int> temp(num_proc);
    double mean = 0, tt = 0, end;
    for (int i = 0; i < num_proc; i++) {
      temp[i] = burst_time[i];
    }
    printf("\nProcess ID\t\tArrivalTime\tBurst Time\t Turnaround Time\t Waiting Time\n");
    for (time = 0; count != num_proc;){
        int mnn = 1e9,counter=0;
        int y = 0 , mn = 1e9;
        for (int i = 0; i < num_proc; i++) {
            if (arr_t[i] <= time && burst_time[i] > 0) y = 1;
        }
        if(y == 0){
            for (int i = 0; i < num_proc; i++) {
                if(burst_time[i] > 0)
                mn = min(mn , arr_t[i]);
            }
            start_state.push_back(time);
            process_state.push_back("Idle");
            idle_time[4] += mn - time;
            time = mn;
            finish_state.push_back(time);
        }
        for (int i = 0; i < num_proc; i++) {
            if (arr_t[i] <= time && burst_time[i] < mnn && burst_time[i] > 0) {mnn=burst_time[i];sm = i;}
        }
        int time_quantum = avg_burst_time_fun(burst_time);
        if (burst_time[sm] <= time_quantum && burst_time[sm] > 0) {
          start_state.push_back(time);
          time += burst_time[sm];
          finish_state.push_back(time);
          process_state.push_back("Id["+to_string(process_id[sm])+"]");
          burst_time[sm] = 0;
          counter = 1;
        } 
        else if (burst_time[sm] > 0) {
          start_state.push_back(time);
          burst_time[sm] -= time_quantum;
          time += time_quantum;
          finish_state.push_back(time);
          process_state.push_back("Id["+to_string(process_id[sm])+"]");
        }
    if (burst_time[sm] == 0 && counter == 1) {
      count++;
      cout<<"Process["<<process_id[sm]<<"]\t\t\t"<<arr_t[sm]<<"\t\t"<<temp[sm]<<"\t\t"<<time - arr_t[sm]<<"\t\t"<<time - arr_t[sm] - temp[sm]<<endl;
      wt = wt + time - arr_t[sm] - temp[sm];
      ta = ta + time - arr_t[sm];
      counter = 0;
    }
    }
  avg_wait_time[4] = wt * 1.0 / num_proc;
  avg_turn_around_time[4] = ta * 1.0 / num_proc;   
    for (int i = 0; i < num_proc; i++) {
      burst_time[i] = temp[i];
    }
  cout<<endl;
  cout<<"Start Time \t";
  forw(i,0,start_state.size()) {
    cout<<start_state[i]<<"\t";
  }
  cout<<endl;
  cout<<"Finish Time \t";
  forw(i,0,start_state.size()) {
    cout<<finish_state[i]<<"\t";
  }
  cout<<endl;
  cout<<"State\t\t";
  forw(i,0,start_state.size()) {
    cout<<process_state[i]<<"\t";
  }
  cout<<endl;
  cout<<endl;
}
void short_job_first() {
    start_state.clear();
    finish_state.clear();
    process_state.clear();
    int i, count = 0, time=0, sm=0;
    vector<int> temp(num_proc);
    double mean = 0, tt = 0, end;
    for (i = 0; i < num_proc; i++) {
      temp[i] = burst_time[i];
    }
    printf("\nProcess ID\t\tArrivalTime\tCompletion time\tBurst Time\t Turnaround Time\t Waiting Time\n");
    for (time = 0; count != num_proc;){
        int mnn = 1e9;
        int y = 0 , mn = 1e9;
        for (i = 0; i < num_proc; i++) {
            if (arr_t[i] <= time && burst_time[i] > 0) y = 1;
        }
        if(y == 0){
            for (i = 0; i < num_proc; i++) {
                if(burst_time[i] > 0)
                mn = min(mn , arr_t[i]);
            }
            start_state.push_back(time);
            process_state.push_back("Idle");
            idle_time[1] += mn - time;
            time = mn;
            finish_state.push_back(time);
        }
        for (i = 0; i < num_proc; i++) {
            if (arr_t[i] <= time && burst_time[i] < mnn && burst_time[i] > 0) {mnn=burst_time[i];sm = i;}
        }
        burst_time[sm]=0;
        if (burst_time[sm] == 0) {
            count++;
            start_state.push_back(time);
            process_state.push_back("Id["+to_string(process_id[sm])+"]");
            end = time + temp[sm];
            time=end;
            finish_state.push_back(time);
            cout<<"Process["<<process_id[sm]<<"]\t\t\t"<<arr_t[sm]<<"\t\t"<<arr_t[sm]+end - arr_t[sm]<<"\t\t"<<temp[sm]<<"\t\t"<<end - arr_t[sm]<<"\t\t"<<end - arr_t[sm] - temp[sm]<<endl;
            mean = mean + end - arr_t[sm] - temp[sm];
            tt = tt + end - arr_t[sm];
        }
    }
    avg_wait_time[1] = mean / num_proc;
    avg_turn_around_time[1] = tt / num_proc;
    for (i = 0; i < num_proc; i++) {
        burst_time[i] = temp[i];
    }
  cout<<endl;
  cout<<"Starting Time \t";
  forw(i,0,start_state.size()) {
    cout<<start_state[i]<<"\t";
  }
  cout<<endl;
  cout<<"Finishing Time \t";
  forw(i,0,start_state.size()) {
    cout<<finish_state[i]<<"\t";
  }
  cout<<endl;
  cout<<"State\t\t";
  forw(i,0,start_state.size()) {
    cout<<process_state[i]<<"\t";
  }
  cout<<endl;
  cout<<endl;
}

int main(){
 fastio(); 
 ll c;
    cout<<"For Online query enter 1,else 0"<<endl;
    cin>>c;
    intialise(c);
  int k, choice;
  printf("Choice\tAlgorithm used\n1\tFCFS Algorithm\n2\tSJF Algorithm\n3\tRound robin\n4\tSRTF Algorithm\n5\tOur innovative algorithm\n");
  do {
    printf("Enter your choice from the above table :");
    scanf("%d", & k);
    switch (k) {
    case 1:
      first_come_first_serve();
      break;  
    case 2:
      short_job_first();
      break;
    case 3:
      Round_rob();
      break;
    case 4:
      short_rem_time_first();
      break;
    case 5:
      innovated_fun();
      break;
    default:
      printf("Invalid entry \n");
      break;
    }
    display(k);
    printf("\n\nEnter 1 to continue 0 to stop");
    scanf("%d", & choice);
  } while (choice == 1);
//   getch();
  int a[5][2], i;
  for (i = 0; i < 5; i++) {
    a[i][0] = avg_wait_time[i];
    a[i][1] = avg_turn_around_time[i];
  }
  
  
 
  
  
   
 
    return 0;
} 