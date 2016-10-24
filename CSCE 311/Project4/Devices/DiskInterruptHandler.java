package osp.Devices;
import java.util.*;
import osp.IFLModules.*;
import osp.Hardware.*;
import osp.Interrupts.*;
import osp.Threads.*;
import osp.Utilities.*;
import osp.Tasks.*;
import osp.Memory.*;
import osp.FileSys.*;

/**
    The disk interrupt handler.  When a disk I/O interrupt occurs,
    this class is called upon the handle the interrupt.

    @OSPProject Devices
*/
public class DiskInterruptHandler extends IflDiskInterruptHandler
{
    /** 
        Handles disk interrupts. 
        
        This method obtains the interrupt parameters from the 
        interrupt vector. The parameters are IORB that caused the 
        interrupt: (IORB)InterruptVector.getEvent(), 
        and thread that initiated the I/O operation: 
        InterruptVector.getThread().
        The IORB object contains references to the memory page 
        and open file object that participated in the I/O.
        
        The method must unlock the page, set its IORB field to null,
        and decrement the file's IORB count.
        
        The method must set the frame as dirty if it was memory write 
        (but not, if it was a swap-in, check whether the device was 
        SwapDevice)

        As the last thing, all threads that were waiting for this 
        event to finish, must be resumed.

        @OSPProject Devices 
    */
    public void do_handleInterrupt()
    {
        // Getting IORB and Thread
		IORB iorbget = (IORB) InterruptVector.getEvent();
		ThreadCB threader = (ThreadCB) InterruptVector.getThread();
		//getting the page and the frame.
		PageTableEntry pageget = iorbget.getPage();
        FrameTableEntry frameget = pageget.getFrame();
		//Opening the file handle from IORB
		OpenFile openFile = iorbget.getOpenFile();
		
		//Decrements IORB count with openFile
		openFile.decrementIORBCount();
		
		//Checks if openFile has no more IORB entries and if it is pending closing.
		if(openFile.getIORBCount() == 0 && openFile.closePending)
		{
			openFile.close();	
		}
		
		//Unlocks the page
		iorbget.getPage().unlock();
		
		//Checks if thread is not dead and frame is null
		if(threader.getStatus() == ThreadCB.ThreadKill && frameget == null)
		{
			return;
		}
		//checks if thread isnt dead, or ThreadKill
		if(threader.getStatus() != ThreadCB.ThreadKill)
		{
			//checks if I/O isnt in swap in/swap out by using getDevice ID and SwapDevice ID
			if(iorbget.getDeviceID() != SwapDeviceID)
			{
				//sets reference bit
				frameget.setReferenced(true);
				//checks if I/O is Fileread type
				if(iorbget.getIOType() == FileRead)
				{
					//The task is gotten to check the TaskTerm 
					TaskCB task = threader.getTask();
					//checks task term
					if(task.getStatus() != TaskTerm)
					{
						//sets dirty bit
						frameget.setDirty(true);
					}
				}
			}
			else
			{
				//The task is gotten to check the TaskTerm 
				TaskCB task = threader.getTask();
				//checks task term
				if(task.getStatus() != TaskTerm)
				{
					//Sets dirty bit
					frameget.setDirty(false);
				}
			}
			
		}
		
		TaskCB task = threader.getTask();
		//If task is dead or dying we unreserve frame
		if(task.getStatus() == TaskTerm && frameget.isReserved())
        {
        	frameget.setUnreserved(task);
        }
		
		//Notifies waiting threads
		iorbget.notifyThreads();
		
		//Idles the device by getting deviceID and using setBusy(false)
		int DID = iorbget.getDeviceID();
        Device.get(DID).setBusy(false);
		
		//Gets next dequeue thread and starts I/O if it isn't null.
        IORB nextdequeue = Device.get(DID).dequeueIORB();
		if (nextdequeue != null) 
    	{
    		Device.get(DID).startIO(nextdequeue);
    	}
		
		//Invokes Dispatch
		ThreadCB.dispatch();

    }


    /*
       Feel free to add methods/fields to improve the readability of your code
    */

}

/*
      Feel free to add local classes to improve the readability of your code
*/
