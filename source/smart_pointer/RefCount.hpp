#ifndef REFCOUNT_H_
#define REFCOUNT_H_


class RefCount {
	private:
		int count {};
		
	public:
		RefCount(){
			count = 0;
			
		}
		RefCount(const RefCount&)=delete;
		RefCount& operator=(const RefCount&) = delete;


		void operator++(){
			count++;
		}
		void operator--(){
			count--;
		}
		void operator++(int){
			count++;
		}
		void operator--(int){
			count--;
		}
		
		int getCount(){
			return count;
		}
		
		~RefCount(){

		}

};

#endif 