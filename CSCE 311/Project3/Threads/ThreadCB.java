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
import java.util.LinkedList;
import java.util.*;

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
	private static GenericList[] active = new GenericList[10]; //Active Array
	private static GenericList[] expired = new GenericList[10]; //Expired Array
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
		for(int i=0; i<=9; i++)
		{
			active[i] = new GenericList(); //Initializing all values of the arrays
			expired[i] = new GenericList();
		}

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
		thread.setPriority(4); //Sets to priority 4
		thread.setStatus(GlobalVariables.ThreadReady); //Sets to ready
		
		//using setTask(task) associates task with thread
		thread.setTask(task);
		//Tries to use addThread to add the thread in.
		if(task.addThread(thread) == GlobalVariables.FAILURE)
		{
			dispatch(); //calls dispatch before program ends
			return null; //returns null
		}
		
		expired[4].append(thread);//adds thread to expired once it avoids all conditionals
		
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
			active[this.getPriority()].remove(this);
			expired[this.getPriority()].remove(this);
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
			if(!expired[this.getPriority()].contains(this))
			{
				event.addThread(this);
			}
		}
		//makes sure the thread is not currently in ready queue.
		//threadsrq.remove(this);
		
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
        /*if(this.getStatus() == GlobalVariables.ThreadWaiting)
		{
			this.setStatus(GlobalVariables.ThreadReady);
			threadsrq.add(this);
			if(this.getPriority() != 0)
			{
				this.setPriority(this.getPriority() - 1);
				expired[this.getPriority()].add(this);
			}
		}
		//if thread is more than waiting get it closer to waiting.
		else if(this.getStatus() > GlobalVariables.ThreadWaiting)
		{
			this.setStatus(this.getStatus()-1);
		}*/
		
		if(getStatus() == ThreadWaiting)
		{
			setStatus(ThreadReady);
		}
		else if(getStatus() > ThreadWaiting)
			setStatus(getStatus()-1);
		//EXTRA LINES MUST BE ADDED
		if(this.getPriority() > 0)
			this.setPriority(this.getPriority() - 1);
		if(getStatus() == ThreadReady)
		{
			expired[this.getPriority()].append(this);
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
		//tries to see if there is a thread in the active queue.
		int maxed = 0;
		TaskCB task = null;
		ThreadCB threader = null;
		ThreadCB nextthreader = null;
		//Runs the try catch
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
			//set the thread to ready
			MMU.setPTBR(null);
			threader.setStatus(GlobalVariables.ThreadReady);
			if(HTimer.get() < 1 && threader.getPriority() < 9)
			{
				threader.setPriority(threader.getPriority() + 1);
			}
			//and add it to the ready queue
			expired[threader.getPriority()].append(threader);
		}
		
		//BROKEN IMPLEMENTATION
		/*for(int i=0; i<=9; i++)
		{
			if(active[i].peek() != null)
			{
				threader = active[i].remove();
				break;
			}
			maxed = i;
		}
		//If none in active queue, swaps expired queue to active queue.
		if(maxed == 9)
		{
			active = expired;
		}
		for(int i=0; i<=9; i++)
		{
			if(active[i].peek() != null)
			{
				threader = active[i].remove();
				break;
			}
			maxed =1;
		} //If both are empty, sets PTBR to null and returns failure
		if(maxed == 9);
		{
			MMU.setPTBR(null);
			return GlobalVariables.FAILURE;
		}*/
		
		
		//gets first thread.
		nextthreader = swap(); //gets a new thread for the function.
		if(nextthreader==null)
		{
			MMU.setPTBR(null);
			return FAILURE;
		}
		else 
		{
			MMU.setPTBR(nextthreader.getTask().getPageTable());
			//sets the head thread to the current thread.
			nextthreader.getTask().setCurrentThread(nextthreader);
			//says thread is running.
			nextthreader.setStatus(GlobalVariables.ThreadRunning);
		}
		
		//sets interrupt timer to 40 or 20 based on what priority your thread has.
		if(nextthreader.getPriority() <= 4)
		{
			HTimer.set(40);
		}
		else
		{
			HTimer.set(20);
		}
		//returns success.
		return GlobalVariables.SUCCESS;	
		
		

    }
	
	public static ThreadCB swap()
	{
		for(int i = 0; i<10; i++)
		{
			if(!active[i].isEmpty())
			{
				return (ThreadCB)active[i].removeHead();
			}
		}
		GenericList[] temp = new GenericList[10];
		temp = expired;
		expired = active;
		active = temp;
		for(int i = 0; i<10; i++)
		{
			if(!active[i].isEmpty())
			{
				return (ThreadCB)active[i].removeHead();
			}
		}
		return null;
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
