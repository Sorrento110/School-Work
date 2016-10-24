package osp.Ports;

import java.util.*;
import osp.IFLModules.*;
import osp.Threads.*;
import osp.Tasks.*;
import osp.Memory.*;
import osp.Utilities.*;

/**
   The studends module for dealing with ports. The methods 
   that have to be implemented are do_create(), 
   do_destroy(), do_send(Message msg), do_receive(). 


   @OSPProject Ports
*/

public class PortCB extends IflPortCB
{
	int buffer;
    /**
       Creates a new port. This constructor must have

	   super();

       as its first statement.

       @OSPProject Ports
    */
    public PortCB()
    {
        super();

    }

    /**
       This method is called once at the beginning of the
       simulation. Can be used to initialize static variables.

       @OSPProject Ports
    */
    public static void init()
    {
        

    }

    /** 
        Sets the properties of a new port, passed as an argument. 
        Creates new message buffer, sets up the owner and adds the port to 
        the task's port list. The owner is not allowed to have more 
        than the maximum number of ports, MaxPortsPerTask.

        @OSPProject Ports
    */
    public static PortCB do_create()
    {
		//creates a PortCB and TaskCB
        PortCB porter = new PortCB();
	    TaskCB tasker = null;
		//Gets current task into tasker by making sure there is one then storing it.
        try 
		{
			tasker = MMU.getPTBR().getTask();                                          
        } 
		catch (NullPointerException e)
		{
			
        }
		//Checks the port count versus the max port count.
		int portcount = tasker.getPortCount();
        if(portcount == MaxPortsPerTask)
		{
               return null;
		}
		//uses TaskCB to assign our PortCB object to the task.  If it fails, we return null.
		if(tasker.addPort(porter) == FAILURE)
		{
            return null;
        }
		
		//Sets owner of our port with .setTask()
		porter.setTask(tasker);
		//Sets status of port with .setStatus() to "PortLive".
        porter.setStatus(PortLive);
        //Keeps track of the size of the ports buffer.
        porter.buffer= PortBufferLength;

        return porter; 
    }

    /** Destroys the specified port, and unblocks all threads suspended 
        on this port. Delete all messages. Removes the port from 
        the owners port list.
        @OSPProject Ports
    */
    public void do_destroy()
    {
        //Sets status of port to destroyed using setStatus.
		this.setStatus(PortDestroyed);
		//uses notifyThreads to notify any waiting threads of port destruction.
		this.notifyThreads();
		//removes the port from the task's table of active ports using TaskCB.removePort();
		this.getTask().removePort(this);
		//Sets ports owner to null using the same way we did above (with setTask).
		this.setTask(null);
    }

    /**
       Sends the message to the specified port. If the message doesn't fit,
       keep suspending the current thread until the message fits, or the
       port is killed. If the message fits, add it to the buffer. If 
       receiving threads are blocked on this port, resume them all.

       @param msg the message to send.

       @OSPProject Ports
    */
    public int do_send(Message msg)
    {
        //Checks if message is well formed (not null or not longer than PortBufferLength).
		if( msg == null || (msg.getLength() > PortBufferLength))
		{
			return FAILURE;
		}
		//Creates a system event with the specified string to distinguish it from others in log.
		SystemEvent eventer = new SystemEvent("message_sender");
		
		//gets task and thread with task and threadCB.
	   TaskCB taskers = null;
       ThreadCB threader = null;

       try 
	   {
		   taskers = MMU.getPTBR().getTask();                                            
           threader = taskers.getCurrentThread();
       }
	   catch (NullPointerException e)
	   {        
	   }       
       //Suspends thread.
       threader.suspend(eventer);
	   
	   //makes variables that are used to keep track of the amount of buffer and if we need to stop running loop or not.
	   boolean suspenderBool = true;
	   int amountofbuffer;
	   //starts loop.
       while(suspenderBool)   
	   {
            //Checks if there is no space, and suspends port if not.
            if( msg.getLength() <= this.buffer)
			{
                   suspenderBool = false;
            }
            else
			{
                   threader.suspend(this);
            }
            //Checks if threader is ThreadKill, and removes and returns FAILURE if so.
            if(threader.getStatus() == ThreadKill)
			{
                   this.removeThread(threader);
                   return FAILURE;
            }
			//If not PortLive, wake up all threads suspended with notifyThreads and return FAILURE
            if( this.getStatus() != PortLive)
			{
                  eventer.notifyThreads();
                  return FAILURE;
            }
 
       }
	   //If above is true, append message and notify Threads.
	   this.appendMessage(msg);
       this.notifyThreads();
	   //adds size of message to buffer.
	   this.buffer -= msg.getLength();
       eventer.notifyThreads();
       return SUCCESS;

    }

    /** Receive a message from the port. Only the owner is allowed to do this.
        If there is no message in the buffer, keep suspending the current 
	thread until there is a message, or the port is killed. If there
	is a message in the buffer, remove it from the buffer. If 
	sending threads are blocked on this port, resume them all.
	Returning null means FAILURE.

        @OSPProject Ports
    */
    public Message do_receive() 
    {
		//sets up and gets current task and thread.
       TaskCB tasker = null;
       ThreadCB threader = null;
	   //Tries to get current task and thread.
       try 
	   {
          tasker = MMU.getPTBR().getTask();                                            
          threader= tasker.getCurrentThread();
	   }
	   catch (NullPointerException e)
	   {        
       }
	   
	   //checks port's task against current task.
       if(this.getTask() != tasker)
	   {
		   return null;
       }
	   //Creates a new system event to receive.
	   SystemEvent eventer = new SystemEvent("message_receiver");
       threader.suspend(eventer);
	   
	   boolean suspenderBool = true;
       while(suspenderBool)
	   {
		   //checks .isEmpty and suspends if so.
           if(this.isEmpty())
		   {
			   threader.suspend(this);
           }
           else
		   {
			   suspenderBool = false;
           }
		   //checks further complications as above in do_send.
		   if(threader.getStatus() == ThreadKill)
		   {
			   this.removeThread(threader);
               eventer.notifyThreads();
               return null;
           }

           if( this.getStatus() != PortLive)
		   {
			   eventer.notifyThreads();
               return null;
           }   
        }
	   //gets message.
	   Message messager = this.removeMessage();
	   //keeps track of buffer.
       this.buffer += messager.getLength();
	   //notifies threads.
       this.notifyThreads();
	   //notifies event threads.
       eventer.notifyThreads();
	//returns message.
       return messager; 

    }

    /** Called by OSP after printing an error message. The student can
	insert code here to print various tables and data structures
	in their state just after the error happened.  The body can be
	left empty, if this feature is not used.
	
	@OSPProject Ports
    */
    public static void atError()
    {
        // your code goes here

    }

    /** Called by OSP after printing a warning message. The student
	can insert code here to print various tables and data
	structures in their state just after the warning happened.
	The body can be left empty, if this feature is not used.
     
	@OSPProject Ports
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
