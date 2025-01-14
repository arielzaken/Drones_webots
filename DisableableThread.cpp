#include "DisableableThread.h"

DisableableThread::DisableableThread()
{
	if (!running) {
		pThread = new thread(&DisableableThread::task, this);
	}
}

DisableableThread::~DisableableThread()
{
}
