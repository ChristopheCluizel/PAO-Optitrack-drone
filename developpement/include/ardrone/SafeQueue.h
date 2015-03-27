#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <windows.h>

template<class T, unsigned max = 256>
class SafeQueue { 
    HANDLE space_avail; // at least one slot empty
    HANDLE data_avail;  // at least one slot full
    CRITICAL_SECTION mutex; // protect buffer, in_pos, out_pos

    T buffer[max];
    long in_pos, out_pos;
	int queueSize;
public:
	SafeQueue() : in_pos(0), out_pos(0), queueSize(0) { 
        space_avail = CreateSemaphore(NULL, max, max, NULL);
        data_avail = CreateSemaphore(NULL, 0, max, NULL);
        InitializeCriticalSection(&mutex);
    }

    void push(T data) { 
        WaitForSingleObject(space_avail, INFINITE);       
        EnterCriticalSection(&mutex);
        buffer[in_pos] = data;
        in_pos = (in_pos + 1) % max;
		queueSize++;
        LeaveCriticalSection(&mutex);
        ReleaseSemaphore(data_avail, 1, NULL);
    }

    T pop() { 
        WaitForSingleObject(data_avail,INFINITE);
        EnterCriticalSection(&mutex);
        T retval = buffer[out_pos];
        out_pos = (out_pos + 1) % max;
		queueSize--;
        LeaveCriticalSection(&mutex);
        ReleaseSemaphore(space_avail, 1, NULL);
        return retval;
    }

	int size(){
		return queueSize;
	}

    ~SafeQueue() { 
        DeleteCriticalSection(&mutex);
        CloseHandle(data_avail);
        CloseHandle(space_avail);
    }
};

#endif