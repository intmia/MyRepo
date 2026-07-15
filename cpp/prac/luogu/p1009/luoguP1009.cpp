#include<iostream>

int main(){
	long long s=0,n;
	std::cin>>n;
	for(int i=1;i<=n;i++){
		long long t=1;
		for(int j=2;j<=i;j++){
			t*=j;
		}
		s+=t;
	}
	std::cout<<s;
}
