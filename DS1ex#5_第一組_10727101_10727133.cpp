// DS1ex_5_第一組_10727101陳則叡_10727133鄧陳得 
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sys/time.h>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

bool ishaveFile;

struct data{
	string schoolnum ;
	string school ;
	string subjectnum ;
	string subject ;
	string day ;
	string level ;
	int studentnum ;
	int teachernum ;
	int graduated ;
	string city ;
	string system ;
};

vector<data> output ;

long long getTime() {
    struct timeval time;
    gettimeofday( &time, NULL);
    return time.tv_sec * 1000 + time.tv_usec / 1000; // 轉成毫秒
}

class Chart{
	public:
		Chart() ;
		//void PrintList();
		void openFile( string filename );
		void closeFile();
		bool isEmpty();
		void mission1(string nowFileName);
		void mission2(string nowFileName);
		long long  SelectionSort(vector<data> tList) ;
		long long  BubbleSort(vector<data> tList) ;
		long long  MergeSort(vector<data> &tList, int &front, int &end) ;
		long long  MergeSort_f(vector<data> tList, int front, int end) ;
		void Merge( vector<data> &tList, int &front, int &mid, int &end ) ;
		long long  QuickSort(vector<data> &tList, int left, int right) ;
		long long  QuickSort_f(vector<data> tList, int left, int right) ;
		int partition( vector<data> &tList, int &left, int &right ) ;
		int WritingData( FILE *file, vector<data> tList );
		void Sort();
		bool enchart( data List_NTail,bool fullJudge ) ;
	private:
		FILE *file;
		string nowFileNum;
		vector<data> List ;
		vector<data> templist ;
	
};



Chart::Chart(){
}

void Chart::mission1(string nowFileName){
	long long sd, rd ;
	nowFileNum = nowFileName;
	
	sd = SelectionSort(List) ;
	cout << "SelectionSort " << sd << "ms" << endl ;

	sd = BubbleSort(List) ;
	cout << "BubbleSort " << sd << "ms" << endl ;
	
  	system("pause");
  	cout << endl;
  	// printf("Sorting data: %d clocks(%.2f).\n",sd,(float)sd);
	
}

int Chart::WritingData( FILE *nowFile, vector<data> tList ) {

    //fprintf( nowFile, "schoolnum\tschool\tsubjectnum\tsubject\tday\tlevel\tstudentnum\tteachernum\tgraduated\tcity\tsystem\n" );

    for ( int i = 0 ; i < tList.size() ; i++ ) {
      fprintf( nowFile, "%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\n", tList.at(i).schoolnum.c_str(), tList.at(i).school.c_str(), tList.at(i).subjectnum.c_str(), tList.at(i).subject.c_str(), tList.at(i).day.c_str(), tList.at(i).level.c_str(), 
	                                                                  tList.at(i).studentnum, tList.at(i).teachernum, tList.at(i).graduated, tList.at(i).city.c_str(), tList.at(i).system.c_str() ) ;
	}  
} // 


void Chart::mission2(string nowFileName) {
  long long sd, rd ;
  nowFileNum = nowFileName ;
  int initail = 0;
  
  sd = MergeSort_f(List, initail, List.size() - 1) ;
  cout << "MergeSort " << sd << "ms" << endl ;
  sd = QuickSort_f(List, initail, List.size() - 1) ;
  cout << "QuickSort" << sd << "ms" << endl ;
  
  system("pause") ;
  cout << endl ;
}

	
long long Chart::SelectionSort(vector<data> tList) {
	long long start = getTime();
    int i, j, max ;
    int themaxone ;
      for( i=0 ; i< tList.size() ; i++ )
    {
        for( j=i+1 ; j<tList.size() ; j++ )
        {
            if( tList[i].graduated < tList[j].graduated )
            {
            	swap( tList[i], tList[j]  );       
            }
        }
    }
    
	
    long long stop = getTime();


	string tempn = "select_sort"+nowFileNum+".txt";
    file = fopen( tempn.c_str() , "w" );
    WritingData(file, tList);
	fclose(file);
    return stop-start;
};

void Chart::Sort() {
	SelectionSort(List);
	cout << "done" << endl;
	BubbleSort(List);
	cout << "done" << endl ;
	//MergeSort(List, 0, List.size() - 1) ;
	cout << "done" << endl ;
	//QuickSort(List, 0, List.size() - 1) ;
};

long long Chart::BubbleSort(vector<data> tList) {
    long long start = getTime();
    bool noneed = false ;
	for ( int m = tList.size() - 1 ; m > 0 ; m-- ) {
	  noneed = false ;
      for ( int i = 0 ; i < m ; i++ ){
    	  if ( tList.at(i).graduated < tList.at( i+1 ).graduated )  {
    	    data nextItem = tList.at(i);
    	    tList.at(i) = tList.at(i+1) ;
    	    tList.at(i+1) = nextItem ;
    	    noneed = true ;
          } // if
	  } // for
	  if ( noneed == false  )
	    break ;
    } // for
    long long stop = getTime();
	string tempn = "bubble_sort"+nowFileNum+".txt";
    file = fopen( tempn.c_str() , "w" );
    WritingData(file, tList);
	fclose(file);
    return stop-start;
} // BubbleSort()

void Chart::Merge(vector<data> &tList, int &front, int &mid, int &end) {
  data max ;
  max.city = "" ;
  max.day = "" ;
  max.graduated = 0 ;
  max.level = "" ;
  max.school = "" ;
  max.schoolnum = "" ;
  max.studentnum = 0 ;
  max.subject = "" ;
  max.subjectnum = "" ;
  max.system = "" ;
  max.teachernum = 0 ;
  std::vector<data> LeftSub(tList.begin() + front, tList.begin() + mid + 1),
                    RightSub(tList.begin() + mid + 1, tList.begin() + end + 1) ;
        
  int idxLeft = 0, idxRight = 0 ;
		              
  LeftSub.insert(LeftSub.end(), max) ;      // 在LeftSub[]尾端加入值為 Max 的元素
  RightSub.insert(RightSub.end(), max); 
  
  for( int i = front ; i <= end ; i++ ) {
  	if ( LeftSub.at(idxLeft).graduated > RightSub.at(idxRight).graduated ) {
  		tList.at(i) = LeftSub.at(idxLeft) ;
  		idxLeft++ ;
	} // if
	else {
		tList.at(i) = RightSub.at(idxRight) ;
		idxRight++ ;
	} // else
  } // for
} // Merge()

long long Chart::MergeSort_f(vector<data> tList, int front, int end){
	long long start = getTime() ;
	MergeSort(tList, front, end);
	long long stop = getTime() ;
	string tempn = "Merge_sort"+nowFileNum+".txt" ;
	file = fopen( tempn.c_str(), "w" ) ;
    WritingData(file, tList);
	fclose(file);
    return stop-start;
}

long long Chart::MergeSort(vector<data> &tList, int &front, int &end) {
	
	if ( front < end ) {
	  int mid = ( front + end ) / 2 ;
	  int mida=mid+1;
	  MergeSort( tList, front, mid ) ;
	  MergeSort( tList, mida, end ) ;
	  Merge( tList, front, mid, end ) ;
    } // if
} // MergeSort()

int Chart::partition( vector<data> &tList, int &left, int &right ) {
  data pivot = tList.at(right) ;
  int i = left - 1 ;
  int j ;
  for( j = left ; j < right ; j++ ) {
  	if ( tList.at(j).graduated > pivot.graduated ) {
  		i++ ;
  		swap( tList.at(i), tList.at(j) ) ;
	} // if
  }  // for
  i++ ;
  swap( tList.at(i), tList.at(right) ) ;
  return i ;
} // partition()

long long Chart::QuickSort(vector<data> &tList, int left, int right) {
  long long start = getTime() ;
  if ( left < right ) {
  	int mid = partition( tList, left, right ) ;
  	QuickSort( tList, left, mid - 1 ) ;
  	QuickSort( tList, mid + 1, right ) ;
  	
  } // if
  long long stop = getTime();
	
  return stop-start;
}
long long Chart::QuickSort_f(vector<data> tList, int left, int right) {
	long long time = QuickSort(tList,left,right);
  string tempn = "Quick_sort"+nowFileNum+".txt";
  file = fopen( tempn.c_str() , "w" );
  WritingData(file, tList);
  fclose(file);
  return time;
  
} // QuickSort()

bool Chart::isEmpty(){
    return List.empty();
}	
	
/*void Chart::PrintList() {
    cout << "schoolnum\tschool\tsubjectnum\tsubject\tday\tlevel\tstudentnum\tteachernum\tgraduated\tcity\tsystem\n" ;
    for ( int i = 0 ; i < List.size() ; i ++ ) {
        fprintf( nowFile, "%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\n", List.at(i).schoolnum.c_str(), List.at(i).school.c_str(), List.at(i).subjectnum.c_str(), List.at(i).subject.c_str(), List.at(i).day.c_str(), List.at(i).level.c_str(), 
		                                                                  List.at(i).studentnum, List.at(i).teachernum, List.at(i).graduated, List.at(i).city.c_str(), List.at(i).system.c_str() );
	
    } // for
}*/ // Chart
	
class missionDeal{
	public:
		missionDeal(int type){
		cout << "\nInput a file number (e.g., 501, 502, 503, ...): ";
		List = new Chart();
		cin >> nowFileNum;
  		if(type==1){
	  		mission1(nowFileNum);
		}
	  	else if (type==2)
	  		mission2(nowFileNum);
		}
		void openFile( string filename );
		void closeFile();
		int WritingData( Chart *temp );
		void mission1(string name);
		void mission2(string name);
	    int AccessData() ;
	private:
		Chart *List;
		string nowFileNum ;
        FILE *nowFile ;
        vector<data> list ;
};	
	
void missionDeal::mission1(string name){
	long long rd;
	openFile(name);
	if(nowFile != NULL)
	  rd = AccessData() ;
	else
	  return ;
	closeFile();
	// List->PrintList();
	List->mission1(name);

  				
}	
	
void missionDeal::mission2(string name){
	long long rd ;
	openFile(name);
	
	if(nowFile != NULL)
	  rd = AccessData() ;
	else
	  return ;
	closeFile();
	// List->PrintList();
	List->mission2(name);
}	

int missionDeal::AccessData(){
    long long start = getTime();
    char initial,initial2;
    int i = 0 ;
    
	while(initial != '\n'){
		fscanf(nowFile,"%c", &initial);
	}
	fscanf(nowFile,"%c", &initial);
	while(initial != '\n'){
		fscanf(nowFile,"%c", &initial);
	}
	fscanf(nowFile,"%c", &initial);
	while(initial != '\n'){
		fscanf(nowFile,"%c", &initial);
	}	
	data temp ;

    char c ;
    while ( fscanf(nowFile,"%c", &c ) != EOF ) { 
    
      temp.schoolnum = temp.schoolnum + c ;
      while ( c != '\t') {
        temp.schoolnum = temp.schoolnum + c ;
        fscanf(nowFile,"%c", &c ) ;
	  }
	 
	  //cout << temp.schoolnum <<endl;
      fscanf(nowFile,"%c", &c ) ;
	  while ( c != '\t') {
        temp.school = temp.school + c ;
        fscanf(nowFile,"%c", &c ) ;
	  }
	  //cout << temp.school <<endl;
	  fscanf(nowFile,"%c", &c ) ;
	  while ( c != '\t') {
        temp.subjectnum = temp.subjectnum + c ;
        fscanf(nowFile,"%c", &c ) ;
	  }
	  //cout << temp.school <<endl;
	  fscanf(nowFile,"%c", &c ) ;
	  while ( c != '\t') {
        temp.subject = temp.subject + c ;
        fscanf(nowFile,"%c", &c ) ;
	  }
	  //cout << temp.subject <<endl;
	  fscanf(nowFile,"%c", &c ) ;
	  while (c != '\t') {
        temp.day = temp.day + c ;
        fscanf(nowFile,"%c", &c ) ;
	  }
	  
	  fscanf(nowFile,"%c", &c ) ;
	  //cout << temp.day <<endl;
	  while ( c != '\t') {
        temp.level = temp.level + c ;
        fscanf(nowFile,"%c", &c ) ;
	  }
	  //cout << temp.level <<endl;

      fscanf(nowFile,"%d", &temp.studentnum ) ;
      //cout << temp.studentnum <<endl;
      fscanf(nowFile,"%d", &temp.teachernum ) ;
      //cout << temp.teachernum <<endl;
      fscanf(nowFile,"%d", &temp.graduated  ) ;
      //cout << temp.graduated <<endl;
      fscanf(nowFile,"%c", &c ) ;
      while ( c != '\t') {
        temp.city = temp.city + c ;
        fscanf(nowFile,"%c", &c ) ;
	  }
	  //cout << temp.city <<endl;
	  
	  while ( fscanf(nowFile,"%c", &c ) != EOF && c != '\n' ) {
        temp.system = temp.system + c ;
	  }
      //cout << temp.system <<endl;

	  List -> enchart(temp,false);
   	  //initial = initial2;
   	  temp.schoolnum = "";
	  temp.school = "";
	  temp.subjectnum = "" ;
	  temp.subject = "";
	  temp.day = "";
	  temp.level = "";
	
	  temp.city = "";
	  temp.system = "";
	}

	
    long long stop = getTime();
    return stop-start;
} // 讀檔 

bool Chart::enchart( data List_NTail,bool fullJudge ){
	if ( fullJudge ) {
		if( templist.size() >=3 )
			return false;
		else{
			templist.push_back( List_NTail );
		}		
	} else
		List.push_back( List_NTail );
	return true;
}

void missionDeal::openFile( string filename ){
	nowFileNum = filename;
	filename = "input"+nowFileNum+".txt";
    nowFile = fopen(filename.c_str(), "r");

    if ( nowFile == NULL ) 
        cout << endl << " ### "<< filename <<" does not exist! ###" << endl;
    else if ( nowFile != NULL )
  		ishaveFile=true;
}

void missionDeal::closeFile(){
	fclose(nowFile);
}

int missionDeal::WritingData( Chart *temp ){
}


int main(int argc, char *argv[]){
	int OptionInput = -1;
	string str = "**** Sorting Algorithms *****\n";
	str += "* 0. Quit                            *\n";
	str += "* 1. Selection sort vs. Bubble sort  *\n";
	str += "* 2. Merge sort vs. Quick sort       *\n";
	str += "**************************************\n";
	str += "Input a command(0, 1, 2): ";
	cout << str ;
	cin >> OptionInput;
	while( OptionInput != 0 ){
		if( OptionInput == 1 )
			missionDeal(1);
		else if(OptionInput == 2 )
			missionDeal(2);
		else
			cout << "Command does not exist!\n";
		
		cout << endl;
		cout << str ;
		cin >> OptionInput;
	}

}
