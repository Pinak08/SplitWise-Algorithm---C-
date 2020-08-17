#include<iostream>
#include<set>
#include<map>
using namespace std;
class person_compare{
public:
    bool operator()(pair<string,int> p1, pair<string,int> p2){
        return p1.second < p2.second;
    }
};
int main(){
	int transactions,friends;
	cin>>transactions>>friends;
	string person1,person2;
	int amt;
	map<string,int>net;
	while(transactions--){
        cin>>person1>>person2>>amt;
        if(net.count(person1)==0){
            net[person1] = 0;
        }
        if(net.count(person2)==0){
            net[person2] = 0;
        }
        net[person1] -= amt;
        net[person2] += amt;
    }

    multiset<pair<string,int>, person_compare> m;

    for(auto p:net){
        string person = p.first;
        int amt = p.second;

        if(net[person]!=0){
            m.insert(make_pair(person,amt));
        }
    }
    int cnt = 0;
    while(!m.empty()){
        auto low = m.begin();
        auto high = prev(m.end());

        int debit = low->second;
        string debit_person = low->first;

        int credit = high->second;
        string credit_person = high->first;
        m.erase(low);
        m.erase(high);

        int settled_amt = min(-debit,credit);
        debit += settled_amt;
        credit -= settled_amt;
        cout<<debit_person<<" will pay "<<settled_amt<<" to "<<credit_person<<endl;
        if(debit!=0){
            m.insert(make_pair(debit_person,debit));
        }
        if(credit!=0){
            m.insert(make_pair(credit_person,credit));
        }
        cnt += 1;
    }
    cout<<cnt<<endl;
return 0;
}
