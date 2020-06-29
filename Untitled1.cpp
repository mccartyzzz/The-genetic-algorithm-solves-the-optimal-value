#include<iostream>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cstdlib> 
#include<iomanip> 
using namespace std;

/*
	Date: 14-April-2020
	Description:�궨һЩ����
				const double PI ���� ����ֵ 
				const double PRO_INHERITANCE ������� 
				const double PRO_VARIATION ������� 
				const double PRO_INTERACTION ���Ÿ��� 
				const int N ���ֵ����� 
*/
const double PI = M_PI;
const double PRO_INHERITANCE = 0.9;
const double PRO_VARIATION = 0.15;
const double PRO_INTERACTION = 0.5;
const int N = 25;

/* 
	Date: 14-April-2020
	Description:����һЩ����Ϳɱ�ı��� 
				double init[N] ��ʼ����ֵ������������ 
				double fitness[N] �洢��Ӧ�� 
				int array[N][22] �洢�������ļ� 
				double max_x ���ֵ��ֵ 
				double max_fitness �����Ӧ�� 
*/
double init[N] = {1.038745, 0.508504, 0.849797, -0.737197};//ǰ�ĸ�Ϊǰ��ѵ�����궨���� 
double fitness[N];
int array[N][22];
double max_x = -2;
double max_fitness = -2;

/*
	Date: 14-April-2020
	Description:��������
				double Rapid_power() �������㷨 
				void Todecimals() ��������ת��ΪС�� 
				void Tobinary() ��С��ת��Ϊ������ 
				void Initialize() ��ʼ������ 
				void Getfitness() ������Ӧ�� 
				void Selected() ѡ����Ⱥ 
				void Inheritance() ����̳� 
				void Variation() ������� 
				void Interaction() ���ű��� 
*/
double Rapid_power(double base, int exp);
void Todecimals();
void Tobinary();
void Initialize();
void Getfitness();
void Selected();
void Inheritance();
void Variation();
void Interaction();

/*
	Name: main() 
	Date: 14-April-2020
	Description:�����������ڵ��������������д�������
				���ȳ�ʼ��->��С��ת��Ϊ������->�����Ӧ��->ѭ�����ָ���->��ӡ��� 
				ѭ��100000�Σ����ﵽ�������ʱ�������� 
*/
int main()
{
	Initialize();
	Tobinary();
	Getfitness();
	for(int i=0;i<100000;i++){
		Selected();
		if(((rand() % 1000) / 1000.0) < PRO_INHERITANCE){
			Inheritance();
		}
		if(((rand() % 1000) / 1000.0) < PRO_VARIATION){
			Variation();
		}
		if(((rand() % 1000) / 1000.0) < PRO_INTERACTION){
			Interaction();
		}
		Todecimals();
		Getfitness();
	}
	cout<<"���� = "<<max_x<<endl;
	cout<<"���ֵ = "<<max_fitness<<endl;
	return 0;
}

/*
	Name: Rapid_power()
	Date: 14-April-2020
	Description:�������㷨�������ǿ��ٻ�� x^n���
	 			����ֵ��˫����С����������������ֵ��һ���ǵף�һ����ָ�� 
	 			sum�����ڱ������Ľ�� 
				�� Todecimals()ģ�������� 
*/
double Rapid_power(double base, int exp){
	double sum = 1;
	while(exp){
		if((exp & 1) == 1){
			sum = sum * base;
		}
		exp = exp >> 1;
		base = base * base;
	}
	return sum; 
} 

/*
	Name: Todecimals()
	Date: 14-April-2020
	Description:û�з���ֵ�������ǽ�������ת��ΪС��
				��ÿһ��С��������ת����22λ���ȣ���һλ������ţ��ڶ�λ�����������֣�ʣ�� 20λΪС������
				�Ƚ�С�����ն�������ʮ���ƽ���ת������ǰ����
				Ȼ����ϵ�һλ���������������õ�һλ�ķ��ţ����Ϊ���򽫽��ȡ�� 
*/
void Todecimals(){
	for(int i=0;i<N;i++){
		double n = 0;
		for(int j=2;j<22;j++){
			n = n + array[i][j]*Rapid_power(0.5 ,1+j-2);
		}
		for(int j=1;j<2;j++){
			if(array[i][j] == 1){ 
				n = n + 1;
			}
		}
		for(int j=0;j<1;j++){
			if(array[i][j] == 1){
				n = -n;
			}
		}
		init[i] = n;
	}
}

/*
	Name: Tobinary()
	Date: 14-April-2020
	Description:û�з���ֵ����С��ת��Ϊ������
				��ת��ΪСС���෴�������ж���ֵ�����������һλȡ 0����ȡ 1
				Ȼ��ͨ���ڶ�λ�ж��������֣��������ְ���ʮ�����������ת���������ת��
				���ϳ� 2ȡ�� 
*/
void Tobinary(){
	cout<<setiosflags(ios::fixed)<<setprecision(6);
	for(int i=0;i<N;i++){
		for(int j=0;j<1;j++){
			if(init[i] >= 0){
				array[i][j] = 0;
			}else{
				array[i][j] = 1;
			}
		}
		int integer = abs(init[i]);
		for(int j=1;j<2;j++){
			array[i][j] = integer % 2;
		}
		double temo = abs(init[i]);
		for(int j=2;j<22;j++){
			temo = (temo - floor(temo)) * 2.0;
			array[i][j] = floor(temo);
		}
	}
}

/*
	Name: Initialize()
	Date: 14-April-2020
	Description:û�з���ֵ����ʼ������ 
				ʹ�ú��� memset����ʼֵ����Ϊ 0���ҷ���ռ� 
				��ʼ����Ⱥ�����������[-1��2]��С�� 
*/
void Initialize(){
	memset(fitness,0,sizeof(fitness));
	memset(array,0,sizeof(array));
	for(int i=0;i<N;i++){
		double x = ((rand() % 100) / 100.0) * 3 - 1;
		init[i] = x;
	}
	cout<<"Total : "<<N<<endl; 
	cout<<"Please wait for the result !"<<endl; 
}

/*
	Name: Getfitness()
	Date: 14-April-2020
	Description:û�з���ֵ��������Ӧֵ 
				���չ�ʽ���� f(x) = x * sin(10 * PI * x) + 2.0
				������ж��Ƿ�ﵽ��ʷ���ţ������¼���������޲��� 
*/
void Getfitness(){
	//f(x) = x * sin(10 * PI * x) + 2.0
	double n;
	for(int i=0;i<N;i++){
		n = init[i] * sin( 10 * PI * init[i] ) + 2.0;
		//n = init[i] * init[i];
		fitness[i] = n; 
	}
	for(int i=0;i<N;i++){
		if(fitness[i] > max_fitness){
			max_fitness = fitness[i];
			max_x = init[i];
		}
	}
} 

/*
	Name: Selected()
	Date: 14-April-2020
	Description:û�з���ֵ��������ѡ����һ����Ⱥ
				���ȼ�������������Ӧ����ֵ������ÿ��������ռ�ٷֱ�
				���һ���ۼƵİٷֱȣ�����һ������������ĸ�����������ֱ�ѡ��
				��������׼���������У�ѡ����Ϻ󸲸ǳ�ʼ���鲢�����½���ת�������ƺͼ�����Ӧֵ���� 
*/
void Selected(){ 
	double possibility[N];
	double temporary_init[N];
	memset(possibility,0,sizeof(possibility));
	memset(temporary_init,0,sizeof(temporary_init));
	
	double all_pro = 0;
	for(int i=0;i<N;i++){
		all_pro = all_pro + fitness[i];
	}
	for(int i=0;i<N;i++){
		possibility[i] = fitness[i] / all_pro;
	}
	for(int i=1;i<N;i++){
		possibility[i] = possibility[i] + possibility[i-1];
	}
	for(int i=0;i<N;i++){
		double x = (rand() % 100) * 0.01;
		for(int j=0;j<N;j++){
			if(x < possibility[j]){
				temporary_init[i] = init[j];
				break;
			}
		}
	}
	for(int i=0;i<N;i++){
		init[i] = temporary_init[i];
	}
	Tobinary();
	Getfitness();
}

/*
	Name: Inheritance()
	Date: 14-April-2020
	Description:û�з���ֵ�������Ǽ̳н��� 
				�����������һ���ڵ� node��Ϊ����ĵ�λ
				�������һ�������Ϊ���֣�������һλ���ֽ��н��� 
				�����ڵ��Ժ������С������ 
*/
void Inheritance(){
	int node = rand() % 22;
	int a1 = rand() % N;
	int a2 = (a1 + 1) % N;
	int temp;
	for(int i=node+1;i<22;i++){
		temp = array[a1][i]; 
		array[a1][i] = array[a2][i]; 
		array[a2][i] = temp;
	}
}

/*
	Name: Variation()
	Date: 14-April-2020
	Description:û�з���ֵ��������������� 
				�������һ��������Ϊ�������
				�ٲ���һ���������ΪС�����ֵ� 0��1����
				ѡ�к󽫸õ�Ļ���λ���з�ת��1->0���� 0->1 
*/
void Variation(){
	int a1 = (rand() % N);
	int a2 = (rand() % 20) + 2;
	array[a1][a2] == 1 ? array[a1][a2] = 0:array[a1][a2] = 1;
}

/*
	Name: Interaction()
	Date: 14-April-2020
	Description:û�з���ֵ��������ǿ�Ƹ��� 
				����һ�����ֽ�������
				���ѡ��һ�����֣�����ѡ��һ������
				����������ָû���Ϊ 0���� 1�����ѡ��һ�����֣����û����Ϊ��ֵͬ 
				����в�ͬ�����޲��� 
*/
void Interaction(){
	int a1 = (rand() % N);
	int a2 = (rand() % 20) + 2;
	int s = array[0][a2];
	bool flag = 1;
	for(int i=1;i<N;i++){
		if(array[i][a2] != s){
			flag = 0;
			break;
		}
	}
	if(flag == 1){
		s == 1 ? s = 0:s = 1;
		array[a1][a2] = s;
	}
}
