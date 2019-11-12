#include <iostream>
using namespace std;

//��ͷ���ĵ������࣬ͷ����ŵ������� 
class Single_List{
	private:
		int data;
		Single_List* next;
	public:	
		//������Ĵ���������β�巨 
		Single_List* Create(int len){
			Single_List* prev,*head,*tail;
			head = new Single_List;
			head->data = len;
			head->next = NULL;
			prev = head;
			if(len == 0){
				goto end;
			}
			cout<<"���������������ֵ��"<<endl; 
			while(len--){
				int data;
				tail = new Single_List;
				cin>>data;
				this->attach(prev,tail,data); 
				prev = tail;
			}
			end:	return head;
		}
		
		void attach(Single_List* prev,Single_List* tail,int data){
			tail->next = NULL;
			tail->data = data;
			prev->next = tail;
		}
		
		int getLength(Single_List* list){
			return list->data;
		}
		
		//�жϵ������Ƿ�Ϊ�յĺ��� 
		bool Isempty(Single_List* list){
			return list->data == 0;
		}
		
		//������Ĵ�ӡ����
		void Print(Single_List* list){
			if(list->Isempty(list)){
				cout<<"������Ϊ��"<<endl;
				return;
			}
			Single_List* pre;
			pre = list->next;
			while(pre){
				cout<<pre->data<<" ";
				pre = pre->next;
			}
		}
		
		//�ڵ�index�������������ֵΪdata�Ľ��ĺ��� 
		Single_List* Insert(Single_List* list,int index ,int data){
			Single_List* prev = list;
			Single_List* insert;
			insert = new Single_List;
			int len = list->getLength(list);
			//����Ϊ��ʱ,����indexΪ���٣�ֻ�ܲ��ڵ�һ��λ�� 
			if(this->Isempty(list)){
				this->attach(prev,insert,data);
				list->data++;
				return list;
			}
			//��������λ�ô��ڵ���������ֱ�Ӳ嵽ĩβ�� 
			index = (list->data <= index)?list->data:index;
			for(int i = 0 ; i < index ; i++){
				prev = prev->next;
			}
			insert->data = data;
			insert->next = prev->next;
			prev->next = insert;
			list->data++;
			return list;
		}
		
		//Ѱ�ҵ�k�����ĺ���,ֻ��������Ϊ�յ���� 
		Single_List* Findkth(Single_List* list ,int k){
			Single_List* prev;
			prev = list;
			for(int i = 0 ; i < k ; i++){
				prev = prev->next;
			} 
			return prev;
		}
		
		//Ѱ����ֵΪN�Ľ��ĺ���
		int FindN(Single_List* list,int N){
			int result = -1;
			Single_List* prev;
			prev = list;
			int len = this->getLength(list); 
			for(int i = 0 ; i < len ; i++){
				prev = prev->next;
				if(prev->data == N){
					result = i;
					break;
				}
			}
			return result; 
		}
		
		//ɾ����ֵΪN�Ľ��ĺ��� 
		void DeleteN(Single_List* list,int N){
			int index = this->FindN(list,N);
			//��������ֵΪN����� 
			if(index == -1){
				cout<<"������������ֵΪ"<<N<<"�Ľ��"<<endl;
				return;
			}
			this->Deletekth(list,index+1);
		}
		
		//ɾ����k�����ĺ���
		void Deletekth(Single_List* list,int k){
			int len = list->data;
			if(this->Isempty(list)){
				cout<<"������Ϊ���޷�ɾ��"<<endl;
				return; 
			}
			Single_List* del_pre;
			del_pre = this->Findkth(list,k-1);
			del_pre->next = del_pre->next->next;
			list->data--;
		}
		
		//��ת������
		Single_List* Reverse(Single_List* list){
			//������Ϊ��ʱ 
			if(this->Isempty(list)){
				return list;
			}
			Single_List* head,*front,*rear,*tag;
			head = list;				//����ͷ��� 
			//front��rear������ת��tag���ڼ�¼δ��ת������ 
			front = list->next;			
			rear = front->next;
			front->next = NULL;
			while(rear){
				tag = rear->next;
				rear->next = front;
				front = rear;
				rear = tag;
			}
			head->next = front;
			return head;
		}
		
		//���������������������ϲ����� 
		Single_List* Merge(Single_List* list1,Single_List* list2){
			if(list1 == NULL){
				return list1;
			}
			if(list2 == NULL){
				return list2;
			}
			Single_List* list;			//�����ϲ������ͷ��㣬�������������֮�� 
			list = new Single_List;
			list->data = list1->data+list2->data;
			list->next = NULL;
			Single_List* prev1,*prev2,*tail,*head,*tag;
			prev1 = list1->next;		//ָ��list32�ĵ�һ����㣨���Ǵ�ų��ȵ�ͷ��㣬��ͷ���֮��Ľ�㣩
			prev2 = list2->next;
			head = new Single_List;		//����������Ŀ�ͷ��� 
			tag = head;					//�����ͷ���ĵ�ַ 
			head->next = NULL;			 
			while(prev1 && prev2){
				tail = new Single_List;
				if(prev1->data <= prev2->data){
					this->attach(head,tail,prev1->data);
					head = tail;
					prev1 = prev1->next;
				}else{
					this->attach(head,tail,prev2->data);
					head = tail;
					prev2 = prev2->next;
				}
			}
			if(prev1){
				head->next = prev1;
			}
			if(prev2){
				head->next = prev2;
			}
			list->next = tag->next;
			return list;					
		}
		
		//��������ð������
		Single_List* Sort(Single_List* list){
			Single_List* head,*prev1,*prev2;
			head = list;
			prev1 = list->next;
			while(prev1){
				prev2 = prev1->next;
				while(prev2){
					if(prev1->data > prev2->data){
						prev1->data += prev2->data;
						prev2->data = prev1->data - prev2->data;
						prev1->data -= prev2->data;
					}	
					prev2 = prev2->next;
				}
				prev1 = prev1->next;
			}
			return head;
		}
		
		//ɾ������ֵΪx�Ľ�� 
		Single_List* Delete_X(Single_List* list ,int data){
			Single_List* head,*front;
			front = list;
			while(front->next != NULL){
				/*cout<<"ɾ��ǰ��"<<endl;
				this->Print(list);
				cout<<endl;*/
				if(front->next->data == data){
					front->next = front->next->next;
					list->data--;
				}else{
					front = front->next;
				}
				/*cout<<"ɾ����"<<endl;
				this->Print(list);
				cout<<endl;*/ 
			}
			return list;
		}
		
		//ɾ����Сֵ��� 
		Single_List* Delete_min(Single_List* list){
			Single_List* front,*tmp;
			int min = list->next->data;
			tmp = list;
			front = list->next;
			while(front->next != NULL){
				/*cout<<"ɾ��ǰ��"<<endl;
				this->Print(list);
				cout<<endl;*/
				if(front->next->data < min){
					min = front->next->data;
					tmp = front; 
				}
				front = front->next;
				/*cout<<"ɾ����"<<endl;
				this->Print(list);
				cout<<endl;*/ 
			}
			front = tmp->next;
			tmp->next = front->next;
			list->data--;
			delete front;
			return list;
		}
		
		//ɾ��ֵ��strat��end֮��Ľ��
		Single_List* Delete_between(Single_List* list,int start ,int end){
			if(start > end){
				return list;
			}
			if(list->next == NULL){
				return list;
			}
			Single_List* front;
			front = list;
			while(front->next != NULL){
				if(front->next->data >= start && front->next->data <= end){
					Single_List* tmp;
					tmp = front->next;
					front->next = tmp->next;
					delete tmp;
					continue;		
				}else{
					front = front->next;
				} 
			}
			return list;
		}
		
		//������ӡ���н��
		void Print_increase(Single_List* list){
			Single_List* pre,*rear,*tmp;
			pre = list;
			while(pre->next != NULL){
				Single_List* min;
				min = pre;
				rear = pre->next;
				while(rear->next != NULL){
					if(rear->next->data < min->next->data){
						min = rear;
					}
					rear = rear->next;
				}
				tmp = min->next;
				//cout<<"fdsxc:"<<min->data<<endl; 
				cout<<tmp->data<<" ";
				min->next = tmp->next;
				delete tmp;
			}
		}
		
		//A��������㣬B��ż�����
		Single_List* Create_2(Single_List* A,Single_List* B){
			int cnt = 0;
			B = new Single_List;
			B->next = NULL;
			Single_List* pre,*even,*odd;
			pre = A->next;
			even = B;
			odd = A;
			A->next = NULL; 
			
			while(pre != NULL){
				cnt++;
				if(cnt % 2 == 0){
					//cout<<"dsah:"<<pre->data<<endl;
					even->next = pre;
					even = even->next;
				}else{
					//cout<<"gfdbghfn:"<<pre->data<<endl;
					odd->next = pre;
					odd = odd->next;
				}
				pre = pre->next;
			}
			even->next = NULL;
			odd->next = NULL;
			return B; 
		} 
};

int main()
{
	cout<<"�������ʼ��������ĳ���:"<<endl;
	int len;
	Single_List tmp; 
	Single_List* list1,*list2,*list;
	cin>>len;
	list1 = tmp.Create(len);
	cout<<"���������£�"<<endl; 
	tmp.Print(list1);
	cout<<endl;
	cin>>len;
	list2 = tmp.Create(len);
	cout<<"���������£�"<<endl; 
	tmp.Print(list2);
	cout<<endl;
	list = tmp.Merge(list1,list2);
	tmp.Print(list);
	cout<<endl;
	list = tmp.Reverse(list);
	tmp.Print(list );
	cout<<endl;
	
	/*cout<<"�����Ϊ:"<<endl;
	list = tmp.Sort(list);
	tmp.Print(list);
	cout<<endl;*/
	
	/*list = tmp.Delete_min(list);
	tmp.Print(list);*/
	/*list = tmp.Delete_between(list,5,8);
	tmp.Print(list);*/
	
	/* 
	cout<<"�������ʼ��������ĳ���:"<<endl;
	Single_List* list1;
	cin>>len;
	list1 = tmp.Create(len);
	cout<<"�ڶ������������£�"<<endl; 
	tmp.Print(list1);
	cout<<endl;
	cout<<"�����Ϊ:"<<endl;
	list1 = tmp.Sort(list1);
	tmp.Print(list1);
	cout<<endl;
	
	cout<<"�ϲ�������Ϊ:"<<endl;
	Single_List* merge_list = tmp.Merge(list,list1);
	tmp.Print(merge_list);
	cout<<endl;
	
	cout<<"������������λ�ã�"<<endl;
	int index,data;
	cin>>index;
	cout<<"����ǰ���������£�"<<endl; 
	tmp.Print(list);
	cout<<endl<<"��������������ֵ��"<<endl;
	cin>>data;
	list = tmp.Insert(list,index,data);
	cout<<"������������£�"<<endl; 
	tmp.Print(list);
	cout<<endl;
	
	
	cout<<"������ɾ������λ�ã�"<<endl;
	cin>>index;
	cout<<"ɾ��ǰ���������£�"<<endl; 
	tmp.Print(list);
	tmp.Deletekth(list,index);
	cout<<endl<<"ɾ�����������£�"<<endl; 
	tmp.Print(list);
	cout<<endl;
	
	cout<<"������ɾ��������ֵ��"<<endl;
	cin>>data;
	cout<<"ɾ��ǰ���������£�"<<endl; 
	tmp.Print(list);
	tmp.DeleteN(list,data);
	cout<<endl<<"ɾ�����������£�"<<endl; 
	tmp.Print(list);
	cout<<endl;

	cout<<"��ת������ǰ,���������£�"<<endl;
	tmp.Print(list);
	cout<<endl<<"��ת�������,���������£�"<<endl;
	list = tmp.Reverse(list); 
	tmp.Print(list); */
	
	return 0;
 } 
