fndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

//PriorityQueue -- класс, реализующий очередь по приоритетам с выборкой минимального элемента
//элемент Item должен поддерживать операции сравнения ( >, <, == ) (достаточно только <)
// и операцию копирующего присваивания

template <class Item>  class PriorityQueue
{
    Item* queue;
    int N;

    void fixUp(Item a[], int k)
    {
        while( (k > 1) && (a[k/2] > a[k]) ){
            exchange(a[k], a[k/2]);
            k = k/2;
        }
    }

    void fixDown(Item a[], int k, int N)
    {
        while( 2*k <= N ){
            int j = 2*k;
            if ( (j < N) && (a[j] > a[j+1]) ){
               j++;
            }
            if ( !( a[k] > a[j] ) ){
                break;
            }
            exchange(a[k], a[j]);
            k = j;
        }
    }

    void exchange(Item &left, Item &right)
    {
        Item temp = left;
        left = right;
        right = temp;
    }
public:
    PriorityQueue(int MaxElemCount)
    {
        queue = new Item[MaxElemCount + 1];
        N = 0;
    }

    ~PriorityQueue()
    {
        delete[] queue;
    }

    bool isEmpty() const
    {
        return N == 0;
    }

    void insert(Item item)
    {
        queue[++N] = item;
        fixUp(queue, N);
    }

    Item GetMin()
    {
        exchange(queue[1], queue[N]);
        fixDown(queue, 1, N-1);
        return queue[N--];
    }
};

#endif // PRIORITYQUEUE_H
