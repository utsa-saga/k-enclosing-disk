#include<iostream>
#include<stdlib.h>
#include<unordered_map>
#include<vector>
#include<math.h>
#include<time.h>
using namespace std;
struct point{
	int x;
	int y;
	long long id;	
	void operator=(const point &other) {
    	x = other.x;
    	y = other.y;
    	id = other.id;
    }
};

struct gridID{
	int x;
	int y;

	bool operator==(const gridID &other) const{
		return x == other.x && y == other.y;
	}
};

namespace std{
	template<>
	struct hash<gridID>
	{
		size_t operator()(const gridID& g)const {
			return (hash<int>()(g.x)) ^ (hash<int>()(g.y) << 1);
		}
	};
}

void getGraduation(vector< vector<point> >& kGraduation, point* points, size_t n, size_t k);
double distance(point p1, point p2);
size_t select(vector<double>& vec, size_t k, size_t l, size_t r);
size_t partition(vector<double>& vec, size_t l, size_t r);
double slowCover(vector<point>& points, size_t k);

int main(){
	srand(time(NULL));
    size_t n, k;
   	cout << "Enter the number of points. "  << endl;
 	cin >> n;
	cout << "Enter k." << endl;
	cin >> k;
    
    point* points;
	points = new point[n];
   	vector<point> allPoints;
	for(int i=0; i<n; i++){
		points[i].x = rand()%100000;
		points[i].y = rand()%100000;
		points[i].id = i;
       	//cout << "Point " << i << ": (" << points[i].x << ", " << points[i].y << ")" << endl;
       	allPoints.push_back(points[i]);
	}
	vector<vector<point> > kGraduation;
	getGraduation(kGraduation, points,n, k);
	for(int i=kGraduation.size()-1; i>=0; i--){
    	cout << "Points in level " << i << ": " << kGraduation[i].size() << endl;
	}
    slowCover(allPoints,k);
    	
return 0;
}


double slowCover(vector<point>& points, size_t k){
	if(k >= points.size()){        
     	//Disc will be centered at points[0].
        double maxDist = 0;
        for(int i=1; i<points.size(); i++){
        	double d = distance(points[0],points[i]);
        	if(d > maxDist)
				maxDist = d;
        }
        return maxDist;	
	} else{
		size_t desiredIndex = k/4;
        vector<double> xCoords;
        for(int i=0; i<points.size(); i++){
        	xCoords.push_back(points[i].x);
        }
        size_t gridLine = xCoords[select(xCoords,desiredIndex,0,points.size()-1)];
        cout << "Grid line: " << gridLine;
	}
}

size_t select(vector<double>& vec, size_t k, size_t l, size_t r){    
    //cout << "Select: " << l << ", " << r << ", looking for rank " << k << endl;
	if(l>=r)
    	return l;
	size_t pivotI = partition(vec,l,r);
	size_t pivotRank = pivotI - l;
	//cout << "PivotI: " << pivotI << ", PivotRank: " << pivotRank << endl;
	if(pivotRank == k)
    	return k;
	else if(pivotRank > k)
    	return select(vec, k, l, pivotI-1);
	else
    	return select(vec, k-pivotRank, pivotI+1, r);
}

size_t partition(vector<double>& vec, size_t l, size_t r){
	size_t subproblemSize = r-l;
	size_t pivI = l + (rand()%subproblemSize);
    //cout << "pivI: " << pivI << endl;
    double temp = vec[l];
    vec[l] = vec[pivI];
    vec[pivI] = temp;
    size_t i = l;
    size_t j = i+1;
    while(j <= r){
        if(vec[j] <= vec[l]){
            i++;
            temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
        }
        j++;
    }
    temp = vec[l];
    vec[l] = vec[i];
    vec[i] = temp;
    /*cout << "Pivot is at index " << i << endl;
    for(int z=l; z<=r; z++)
        cout << vec[z] << '\t';
    cout << endl;*/
    return i;
}


double distance(point p1, point p2){
	return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
}

void getGraduation(vector< vector<point> >& kGraduation, point* points, size_t n, size_t k){
	vector<point> allPoints;
    for(int i=0; i<n; i++){
        allPoints.push_back(points[i]);
    }
    kGraduation.push_back(allPoints);
    int currentSize = n;
    int m = 0;
    while(currentSize > k){
        vector<point> nextLevel;
        for(int i=0; i<kGraduation[m].size(); i++){
            int flip = rand()%2;
            if(flip == 0){
             	nextLevel.push_back(kGraduation[m][i]);
                kGraduation[m][i] = kGraduation[m][kGraduation[m].size()-1]; 
                kGraduation[m].pop_back();
                i--;
            }
        }
        kGraduation.push_back(nextLevel);
        currentSize = nextLevel.size();
        m++;
    }
}















































