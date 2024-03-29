#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include<algorithm>

using namespace std;



const int maxi=100;

pair<double,double> polyg[maxi];
pair<double,double> rpoint[maxi];
pair<double,double> bpoint[maxi];
pair<double,double> cartesianToPolar(double x, double y) {
    
    double r = sqrt(x * x + y * y); // Calculate the magnitude
    double theta = atan2(y, x) ; // Calculate the angle in degrees
     if (theta <0) 
        theta += 2*M_PI;
    
    return make_pair(r,theta);
}

bool tag[maxi];
bool tag2[maxi];
pair<double,double> red[maxi];
pair<double,double> blue[maxi];
int ptr[maxi];
int ptr2[maxi];
int sum1[maxi];
int sum2[maxi];
pair<double,double> bpol[maxi];
pair<double,double> rpol[maxi];




pair<int,int>  vts[maxi];
// Function to compute distance between two points
double distance(pair<double,double> x, pair<double,double> y) {
    return sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
}

int findFloor(pair<double, double> A[], int siz, double theta) {
    int low = 0, high = siz - 1;
    int floorIndex = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (A[mid].second == theta) {
            return mid; // theta is found in the array.
        } else if (A[mid].second < theta) {
            low = mid + 1;
        } else {
            floorIndex = mid; // Update floorIndex to the last known larger value.
            high = mid - 1;
        }
    }
    
    return floorIndex;
}

int findCeiling(pair <double,double> A[], int siz, double theta) {
    int low = 0, high = siz - 1;
    int ceilIndex = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (A[mid].second == theta) {
            return mid; // theta is found in the array.
        } else if (A[mid].second < theta) {
            low= mid + 1;
        } else {
            ceilIndex = mid; // Update ceilIndex to the last known larger value.
            high = mid - 1;
        }
    }
    
    return ceilIndex;
}


// Function to find two farthest points in a convex polygon
void diameter(int n) {
   
    double maxDistance = 0.0;
 //   cout<<"aval"<<' '<<n<<endl;
    // Parallel section for tagging and rotating vectors
  //  #pragma omp parallel for
    for (int i = 0; i < n; i++) {
     //   cout<<"salam";
      //  cout<<(i-1+n)%n<<" "<<"inja"<<endl;
     //   cout<<"salam"<<endl;
      //  cout<<polyg[i].first<<' ';
        vts[i]=make_pair(polyg[i].first-polyg[(i-1+n)%n].first,polyg[i].second-polyg[(i-1+n)%n].second);
       // cout<<i<<' '<<vts[i].first<<' '<<vts[i].second<<endl;
        if(vts[i].second<0){
            vts[i].first=-vts[i].first;
            vts[i].second=-vts[i].second;
            tag[i]=1;
        }
        // Tag vectors above x-axis as "red" and below as "blue"
        // Rotate blue vectors by 180 degrees
        // Implementation omitted for brevity
    }
    cout<<"these are vectors"<<endl;
    for(int i=0;i<n;i++)
        cout<<vts[i].first<<' '<<vts[i].second<<endl;
  //  cout<<"ok"<<endl;
    #pragma omp parallel for
    for(int i=0;i<n;i++)
        ptr[i]=i-1;
    for(int i=0;i<n;i++)
        sum1[i]=tag[i];
    for(int i=1;i<n;i*=2){
        #pragma omp parallel for
            for(int j=1;j<n;j++)
            if(ptr[j]>=0){
                sum1[j]=sum1[j]+sum1[ptr[j]];
                ptr[j]=ptr[ptr[j]];
            }
     /*       for(int k=0;k<n-1;k++)
                cout<<sum1[k]<<' ';
            cout<<sum1[n-1]<<endl;*/
    }
    #pragma omp parallel for
    for(int i=0;i<n;i++)
        if(tag[i]){
            red[sum1[i]-1]=vts[i];
            rpoint[sum1[i]-1]=polyg[i];
        }
    cout<<"these are red vectors"<<endl;
    for(int i=0;i<sum1[n-1];i++){
        rpol[i]=cartesianToPolar(red[i].first,red[i].second);
        cout<<"cartesian point= "<<rpoint[i].first<<' '<<rpoint[i].second<<" ";
        cout<<"cartesian= "<<red[i].first<<' '<<red[i].second<<" ";
        cout<<"polar = "<<rpol[i].first<<' '<<rpol[i].second<<endl;
    }
    #pragma omp parallel for
    
    for(int i=0;i<n;i++)
        tag2[i]=1-tag[i];
    #pragma omp parallel for
    for(int i=0;i<n;i++)
        ptr2[i]=i-1;
    #pragma omp parallel for
    for(int i=0;i<n;i++)
        sum2[i]=tag2[i];
    for(int i=1;i<n;i*=2){
        #pragma omp parallel for
            for(int j=1;j<n;j++)
            if(ptr2[j]>=0){
                sum2[j]=sum2[j]+sum2[ptr2[j]];
                ptr2[j]=ptr2[ptr2[j]];
            }
          /*  for(int k=0;k<n-1;k++)
                cout<<sum1[k]<<' ';
            cout<<sum1[n-1]<<endl;*/
    }

     #pragma omp parallel for
    for(int i=0;i<n;i++)
        if(tag2[i]){
            blue[sum2[i]-1]=vts[i];
            bpoint[sum2[i]-1]=polyg[i];
        }
   /* cout<<"tag = ";
    for(int i=0;i<n-1;i++)
        cout<<tag[i]<<' ';
    cout<<tag[n-1]<<endl;
    cout<<"sum1 = ";
    for(int i=0;i<n-1;i++)
        cout<<sum1[i]<<' ';
    cout<<sum1[n-1]<<endl;
    cout<<"tag2 = ";
    for(int i=0;i<n-1;i++)
        cout<<tag2[i]<<' ';
    cout<<tag2[n-1]<<endl;
    cout<<"sum2 = ";
    for(int i=0;i<n-1;i++)
        cout<<sum2[i]<<' ';
    cout<<sum2[n-1]<<endl;*/
    cout<<"these are blue vectors"<<endl;
    double maxdis=0;
    pair<double,double> a=make_pair(-1,-1);
    pair<double,double> b=make_pair(-1,-1);
    for(int i=0;i<sum2[n-1];i++){
        bpol[i]=cartesianToPolar(blue[i].first,blue[i].second);
        cout<<"cartesian point= "<<bpoint[i].first<<' '<<bpoint[i].second<<" ";
        cout<<"cartesian vector= "<<blue[i].first<<' '<<blue[i].second<<" ";
        cout<<"polar vector= "<<bpol[i].first<<' '<<bpol[i].second<<endl;
    }
    #pragma omp parallel for
    
    for(int i=0;i<sum1[n-1];i++){
        int in1=findFloor(bpol,sum2[n-1],rpol[i].second);
        if(in1=-1){
            double dis=distance(bpoint[in1],rpoint[i]);
            if(dis>maxdis){
                maxdis=dis;
                a=bpoint[in1];
                b=rpoint[i];
            }

        }
        int in2=findCeiling(bpol,sum2[n-1],rpol[i].second);
        if(in2=-1){
            double dis=distance(bpoint[in2],rpoint[i]);
            if(dis>maxdis){
                maxdis=dis;
                a=bpoint[in1];
                b=rpoint[i];
            }

        }
    }
    #pragma omp parallel for
    for(int i=0;i<sum2[n-1];i++){
        int in1=findFloor(rpol,sum1[n-1],bpol[i].second);
        if(in1=-1){
            double dis=distance(rpoint[in1],bpoint[i]);
            if(dis>maxdis){
                maxdis=dis;
                a=rpoint[in1];
                b=bpoint[i];
            }

        }
        int in2=findCeiling(rpol,sum1[n-1],bpol[i].second);
        if(in2=-1){
            double dis=distance(rpoint[in2],bpoint[i]);
            if(dis>maxdis){
                maxdis=dis;
                a=rpoint[in2];
                b=bpoint[i];
            }

        }
    }
    cout << "Farthest points: (" << a.first << ", " << a.second << ") and (" << b.first << ", " << b.second << ")\n";


    // Parallel section for merging sorted lists
 /*   #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        // Use a fast parallel merging algorithm to merge sorted lists
        // Implementation omitted for brevity
    }

    // Sequential section to find farthest points
    for (int i = 0; i < n; ++i) {
        // Find the distance between antipodal vertices
        // Implementation omitted for brevity
        // Update maxDistance and corresponding points if needed
    }*/
}

int main() {
    polyg[0]=make_pair(0,0);
    polyg[1]=make_pair(0,2);
    polyg[2]=make_pair(1,3);
    polyg[3]=make_pair(2,2);
    polyg[4]=make_pair(2,0);

    diameter(5);
    double maxam=0;
    


    //std::cout << "Farthest points: (" << p.x << ", " << p.y << ") and (" << q.x << ", " << q.y << ")\n";

    return 0;
}
