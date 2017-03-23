#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

template<class T>
class Thread
{
public:
	Thread()
		:m_eState(FINISH)
		,m_pT(nullptr){}
	virtual ~Thread()
	{
		m_pT = nullptr;
	}
public:
	bool Init(T *pT)
	{
		if (m_eState != FINISH)
			return false;

		m_eState = INIT;
		return true;
	}
	int Start()
	{
		if (m_eState != INIT && m_eState != STOP)
			return -1;
		pthread_create(&m_pthread, nullptr, ThreadRun, this);
		m_eState = START;
		return 0;
	}
	void Wait()
	{
		if (m_eState == START && m_pthread != pthread_self())
		{
			pthread_join(m_pthread, nullptr);
		}
	}
	bool IsRuning()
	{
		return m_eState==START;
	}
	void Stop()
	{
		if (m_eState == START)
			m_eState = STOP;
	}
	void Finish()
	{
		if (m_eState==START)
		{
			Stop();
			Wait();
		}
		m_eState = FINISH;
	}
private:
	virtual void Run(T *pT) = 0;
private:
	static void *ThreadRun(void *arg)
	{
		Thread *pThread = reinterpret_cast<Thread*>(arg);
		if (pThread == nullptr)
			return nullptr;
		pThread->Run(pThread->m_pT);
	}
private:
	enum State
	{
		INIT,
		START,
		STOP,
		FINISH,
	};
private:
	State m_eState;
	bool m_bIsQuit;
	pthread_t m_pthread;
	int m_iPid;
	T *m_pT;
};




#endif // __THREAD_H__
