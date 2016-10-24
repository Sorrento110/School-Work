package osp.Threads;
import java.util.Vector;
import java.util.Enumeration;
import osp.Utilities.*;
import osp.IFLModules.*;
import osp.Tasks.*;
import osp.EventEngine.*;
import osp.Hardware.*;
import osp.Devices.*;
import osp.Memory.*;
import osp.Resources.*;

/**
	Powell Fendley 
	fendleyp@email.sc.edu

   This class is responsible for actions related to threads, including
   creating, killing, dispatching, resuming, and suspending threads.

   @OSPProject Threads
*/
public class ThreadCB extends IflThreadCB 
{
	private static Vector<ThreadCB> threadsrq;
    /**
       The thread constructor. Must call 

       	   super();

       as its first statement.

       @OSPProject Threads
    */
    public ThreadCB()
    {
        super();

    }

    /**
       This method will be called once at the beginning of the
       simulation. The student can set up static variables here.
       
       @OSPProject Threads
    */
    public static void init()
    {
        threadsrq =  new Vector<ThreadCB>(); //This will hold threads like a ready queue.

    }

    /** 
        Sets up a new thread and adds it to the given task. 
        The method must set the ready status 
        and attempt to add thread to task. If the latter fails 
        because there are already too many threads in this task, 
        so does this method, otherwise, the thread is appended 
        to the ready queue and dispatch() is called.

	The priority of the thread can be set using the getPriority/setPriority
	methods. However, OSP itself doesn't care what the actual value of
	the priority is. These methods are just provided in case priority
	scheduling is required.

	@return thread or null

        @OSPProject Threads
    */
    static public ThreadCB do_create(TaskCB task)
    {
        if(task.getThreadCount() >= MaxThreadsPerTask)
		{
			//if there are too many threads, call dispatch and return null
			dispatch();
			return null;
		}
		
		//if not, Create a thread
		ThreadCB thread= new ThreadCB();
		
		//Thread Priority and status
		thread.setPriority(task.getPriority()); //Sets to corresponding task priority
		thread.setStatus(GlobalVariables.ThreadReady); //Sets to ready
		
		//using setTask(task) associates task with thread
		thread.setTask(task);
		//Tries to use addThread to add the thread in.
		if(task.addThread(thread) == GlobalVariables.FAILURE)
		{
			dispatch(); //calls dispatch before program ends
			return null; //returns null
		}
		
		threadsrq.add(thread);//adds thread once it avoids all conditionals
		
		dispatch();//calls dispatch before program ends
		return thread;//returns thread

    }

    /** 
	Kills the specified thread. 

	The status must be set to ThreadKill, the thread must be
	removed from the task's list of threads and its pending IORBs
	must be purged from all device queues.
        
	If some thread was on the ready queue, it must removed, if the 
	thread was running, the processor becomes idle, and dispatch() 
	must be called to resume a waiting thread.
	
	@OSPProject Threads
    */
    public void do_kill()
    {
        //if thread is ready, remove it.
		if(this.getStatus() == GlobalVariables.ThreadReady)
		{
			threadsrq.remove(this);
			this.setStatus(GlobalVariables.ThreadKill);
			//return;
		}
		//Checks if thread is currently running, and if it is it kills it.
		if(this.getStatus() == GlobalVariables.ThreadRunning)
		{
			if(this == MMU.getPTBR().getTask().getCurrentThread())
			{
				MMU.getPTBR().getTask().setCurrentThread(null);
				MMU.setPTBR(null);
			}
		}
		if(this.getStatus() == GlobalVariables.ThreadWaiting)
		{
			this.setStatus(GlobalVariables.ThreadKill);
		}
		//removes task from the thread.
		TaskCB task= getTask();
		task.removeThread(this);
		//sets status to threadkill
		this.setStatus(GlobalVariables.ThreadKill);
		//loops through device table to kill all pending IO.
		for (int i = 0; i < Device.getTableSize(); i++) {
			Device.get(i).cancelPendingIO(this);
		}
		//releases all resources
		ResourceCB.giveupResources(this);
		
		//calls dispatch
		dispatch();
		//kills task if it has no more threads
		if (task.getThreadCount() <= 0) {
			task.kill();
		}
		
    }

    /** Suspends the thread that is currenly on the processor on the 
        specified event. 

        Note that the thread being suspended doesn't need to be
        running. It can also be waiting for completion of a pagefault
        and be suspended on the IORB that is bringing the page in.
	
	Thread's status must be changed to ThreadWaiting or higher,
        the processor set to idle, the thread must be in the right
        waiting queue, and dispatch() must be called to give CPU
        control to some other thread.

	@param event - event on which to suspend this thread.

        @OSPProject Threads
    */
    public void do_suspend(Event event)
    {
		
		int status = this.getStatus();
		boolean changed = false;
		//If thread is running Conditional
        if(this.getStatus() == GlobalVariables.ThreadRunning)
		{
			//is it the same thread as OSP thinks is running then set it to null and set it to waiting.
			if(this == MMU.getPTBR().getTask().getCurrentThread())
			{
				changed = true;
				event.addThread(this);
				this.getTask().setCurrentThread(null);
				this.setStatus(GlobalVariables.ThreadWaiting);
				MMU.setPTBR(null);
			}
		}
		//increments waiting status if thread was already waiting.
		if(this.getStatus() >= GlobalVariables.ThreadWaiting && !changed)
		{
			setStatus(this.getStatus()+1);
			if(!threadsrq.contains(this))
			{
				event.addThread(this);
			}
		}
		//makes sure the thread is not currently in ready queue.
		threadsrq.remove(this);
		
		dispatch(); //calls dispatch

    }

    /** Resumes the thread.
        
	Only a thread with the status ThreadWaiting or higher
	can be resumed.  The status must be set to ThreadReady or
	decremented, respectively.
	A ready thread should be placed on the ready queue.
	
	@OSPProject Threads
    */
    public void do_resume()
    {
		//if thread is waiting set it to ready.
        if(this.getStatus() == GlobalVariables.ThreadWaiting)
		{
			this.setStatus(GlobalVariables.ThreadReady);
			threadsrq.add(this);
		}
		//if thread is more than waiting get it closer to waiting.
		else if(this.getStatus() > GlobalVariables.ThreadWaiting)
		{
			this.setStatus(this.getStatus()-1);
		}
		//call dispatch.
		dispatch();

    }

    /** 
        Selects a thread from the run queue and dispatches it. 

        If there is just one theread ready to run, reschedule the thread 
        currently on the processor.

        In addition to setting the correct thread status it must
        update the PTBR.
	
	@return SUCCESS or FAILURE

        @OSPProject Threads
    */
    public static int do_dispatch()
    {
		//tries to see if there is a current thread running.
		TaskCB task = null;
		ThreadCB threader = null;
		try
		{
			threader=MMU.getPTBR().getTask().getCurrentThread();
		}
		catch(NullPointerException e)
		{
		}
		if(threader != null)
		{
			//if there is a running thread we let this one's task know its not the current thread.
			threader.getTask().setCurrentThread(null);
			//then we take away CPU control
			MMU.setPTBR(null);
			//set the thread to ready
			threader.setStatus(GlobalVariables.ThreadReady);
			//and add it to the ready queue
			threadsrq.add(threader);
		}
		//if there are no threads sets PTBR to null and returns failure
		if(threadsrq.size() == 0)
		{
			MMU.setPTBR(null);
			return GlobalVariables.FAILURE;
		}
		//gets first thread.
		threader = threadsrq.remove(0);
		MMU.setPTBR(threader.getTask().getPageTable());
		//sets the head thread to the current thread.
		threader.getTask().setCurrentThread(threader);
		//says thread is running.
		threader.setStatus(GlobalVariables.ThreadRunning);
		//sets interrupt timer to 50.
		HTimer.set(50);
		//returns success.
		return GlobalVariables.SUCCESS;	

    }

    /**
       Called by OSP after printing an error message. The student can
       insert code here to print various tables and data structures in
       their state just after the error happened.  The body can be
       left empty, if this feature is not used.

       @OSPProject Threads
    */
    public static void atError()
    {
        // your code goes here

    }

    /** Called by OSP after printing a warning message. The student
        can insert code here to print various tables and data
        structures in their state just after the warning happened.
        The body can be left empty, if this feature is not used.
       
        @OSPProject Threads
     */
    public static void atWarning()
    {
        // your code goes here

    }


    /*
       Feel free to add methods/fields to improve the readability of your code
    */

}

/*
      Feel free to add local classes to improve the readability of your code
*/
