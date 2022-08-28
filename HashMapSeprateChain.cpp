#include<bits/stdc++.h>
using namespace std ;

template<typename V>
class mapNode {
    public :
            string key ;
            V value ;
            mapNode * next ;
            mapNode(string key, V value){
                this->key = key ;
                this->value = value ;
                next = NULL ;
            }
            ~mapNode(){
                delete next ;
            }
} ;

template<typename V> 
class mymap{
    private :
            mapNode<V> ** buckets ;
            int count ;
            int numBuckets ;

            int getBucketIndex(string key){
                int hashcode = 0 ;
                int base = 1 ; int prime = 37 ;
                for(int i = key.size()-1; i>= 0; i--){
                    hashcode += key[i]*base ;
                    base *= prime ;
                    hashcode = hashcode % numBuckets ;  // Modulus property operator 
                    base = base % numBuckets ;          // (n1*n2*n3)%r = ((n1%r)*(n2%r)*(n3%r))%r ;
                }
                return hashcode % numBuckets ;
            }
            void rehash(){
                mapNode<V> ** temp = buckets ;
                buckets = new mapNode<V>*[2*numBuckets] ;
                for(int i=0; i<(2*numBuckets); i++) buckets[i] = NULL ;
                int oldBucketSize = numBuckets ;
                numBuckets *= 2 ; count = 0 ;
                for(int i=0; i<oldBucketSize; i++){
                    mapNode<V>* head = temp[i] ;
                    while(head){
                        string key = head->key ;
                        V value = head->value ;
                        insert(key, value) ;
                        head = head-> next ;
                    }
                }
                for(int i=0; i<oldBucketSize; i++) delete temp[i] ;
                delete []temp ;
            }
    public  :
            mymap(){
                count = 0 ;
                numBuckets = 5 ;
                buckets = new mapNode<V>*[numBuckets] ;
                for(int i=0; i<numBuckets; i++) buckets[i] = NULL ;
            }
            ~mymap(){
                for(int i=0; i<numBuckets; i++) delete buckets[i] ;
                delete []buckets ;
            }
            int size() {
                return count ;
            }
            V getValue(string key){
                int bucketIndex = getBucketIndex(key) ;
                mapNode<V> *head = buckets[bucketIndex] ;
                while(head != NULL){
                    if(head->key == key) {
                        return head->value ;
                    }
                    head = head->next ;
                }
                return 0 ;
            }
            void insert(string key, V value){
                int bucketIndex = getBucketIndex(key) ;
                mapNode<V> *head = buckets[bucketIndex] ;
                while(head != NULL){
                    if(head->key == key) {
                        head->value = value ; return ;
                    }
                    head = head->next ;
                }

                mapNode<V>* node = new mapNode<int>(key,value) ;
                node->next = buckets[bucketIndex] ;
                buckets[bucketIndex] = node ;
                count ++ ; //since new value added with key 
                double loadFactor = (1.0*count)/numBuckets ;
                rehash() ;
            }
            V remove(string key){
                int bucketIndex = getBucketIndex(key) ;
                mapNode<V> *head = buckets[bucketIndex] ;
                mapNode<V> *prev = NULL ;
                while(head){
                    if(head->key == key){
                        if(prev == NULL) buckets[bucketIndex] = head->next ;
                        else prev->next = head->next ;
                        V value = head->value ;
                        head->next = NULL ;
                        delete head ;
                        count -- ; return value ;
                    }
                    prev = head ;
                    head = head->next ;
                }
                return 0 ;
            }
            double getLoadFactor(){
                return (1.0*count)/numBuckets ;
            }
} ;

int main()
{
    cout << "Hello World ! " << endl ;
    mymap<int> ourmap ;
    for(int i=0; i<10; i++){
        char c = '0'+i ;
        string key = "abc" ; key = key + c ;
        int value = i+1 ;
        ourmap.insert(key, value) ;
        cout << "LoadFactor : " << ourmap.getLoadFactor() << endl ;
    }
    cout << ourmap.size() << endl ;
    ourmap.remove("abc1") ;
    ourmap.remove("abc6") ;
    for(int i=0; i<10; i++){
        char c = '0'+i ;
        string key = "abc" ; key = key + c ;
        cout << key << " " << ourmap.getValue(key) << endl ;
        
    }
    cout << ourmap.size() << endl ;
    return 0 ;
}