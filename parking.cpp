#include<cmath>
#include<fstream>
#include<iostream>
#include<cstdlib>
#include<iomanip>

using namespace std;

const int MAXSIZE=51;

void parkingdata(ifstream&fin, int status[MAXSIZE], string name[MAXSIZE])
{
	int personstatus=0;
	string personname="";
	int index=0;
	for(int value=0;value<=50;value++)
	{
		status[value]=-1;
		name[value]="";
	}
	while(fin>>personstatus>>personname>>index)
	{
		status[index]=personstatus;
		name[index]=personname;
	}
}

int dataparkingaddremove(ifstream&fin, int statuschange[MAXSIZE], string namechange[MAXSIZE])
{
	int status=0;
	string name="";
	int index=0;
	while(fin>>status>>name)
	{
		statuschange[index]=status;
		namechange[index]=name;	
		index++;
	}
	return index;
}
//part d
void parkingleft(int status[MAXSIZE],string name[MAXSIZE], string personname, int personstatus)
{
	for(int index=1;index<=50;index++)
	{
		
		if (personname==name[index]&&personstatus==status[index])
		{
			name[index]="";
			status[index]=-1;
		}	
	}

}

int availableparkingspot(int status[MAXSIZE],string name[MAXSIZE])
{
	int spot=-1;
	for(int index=1; index<=50&&spot==-1;index++)
	{
		if(status[index]==-1&&name[index]=="")
		spot=index;
	
	}
	
	return spot;
}

void whichspot(int status[MAXSIZE],string name[MAXSIZE], string personname, int personstatus)
{
	if(availableparkingspot(status,name)!=-1)
	{

		if(personstatus==0)
		{	
			bool found=false;
			for(int index=26; index<=50&&!found;index++)
			{
				if(status[index]==-1&&name[index]=="")
				{
					status[index]=personstatus;
					name[index]=personname;
					found=true;
			
				}	
			}
		}		
		else
		{	
			bool found=false;
			for(int index=1; index<=50&&!found;index++)
			{
				if(status[index]==-1&&name[index]=="")
				{
					status[index]=personstatus;
					name[index]=personname;
					found=true;
				}	
			}
		}
	}
}
//part g
void facultystaffmembers(int status[MAXSIZE], string name[MAXSIZE])
{

	for(int index=26;index<=50;index++)
	{
		if(status[index]==1)
		{
		string savename="";
		savename=name[index];
		parkingleft(status, name, savename, 1);
		whichspot(status, name, savename, 1);

		}
	}
}

void outputParkingData(ofstream&fout,int status[MAXSIZE],string name[MAXSIZE])
{

	for(int index=1;index<=50;index++)
	{
		if(status[index]!=-1&&name[index]!="")
		fout<<status[index]<<" "<<name[index]<<" "<<index<<endl;
	}	
}

int main()
{
	ifstream fin("parking_current.txt");
	if(!fin)
	{
		cout<<"no file";
		system("PAUSE");
		return EXIT_FAILURE; 
	}
	ifstream readinremove("parking_remove.txt");
	if(!readinremove)
	{
		cout<<"no file";
		system("PAUSE");
		return EXIT_FAILURE; 
	}
	ifstream readinadd("parking_add.txt");
	if(!readinadd)
	{
		cout<<"no file";
		system("PAUSE");
		return EXIT_FAILURE; 
	}
	ofstream fout("parkingW19.txt");
	int status[MAXSIZE]={0};
	int statuschange[MAXSIZE]={0};
	string namechange[MAXSIZE]={""};
	string name[MAXSIZE]={""};
	int count=0;
	int countremove=0;
	int countadd=0;
	
	parkingdata(fin,status,name);
	countremove=dataparkingaddremove(readinremove,statuschange,namechange);
	for(int index=0;index<countremove;index++)
	{
		parkingleft(status,name,namechange[index],statuschange[index]);
	}
	facultystaffmembers(status,name);
	countadd=dataparkingaddremove(readinadd,statuschange,namechange);
	for(int index=0;index<countadd;index++)
	{
		whichspot(status,name,namechange[index],statuschange[index]);
	}
	outputParkingData(fout,status,name);
	return 0; 
	
	
	fin.close();
	readinremove.close();
	readinadd.close();
	fout.close();
	system("PAUSE");
	return EXIT_SUCCESS; 
}
