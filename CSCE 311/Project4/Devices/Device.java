package osp.Devices;

/**
    This class stores all pertinent information about a device in
    the device table.  This class should be sub-classed by all
    device classes, such as the Disk class.

    @OSPProject Devices
*/

import osp.IFLModules.*;
import osp.Threads.*;
import osp.Utilities.*;
import osp.Hardware.*;
import osp.Memory.*;
import osp.FileSys.*;
import osp.Tasks.*;
import java.util.*;

public class Device extends IflDevice
{
    /**
        This constructor initializes a device with the provided parameters.
	As a first statement it must have the following:

	    super(id,numberOfBlocks);

	@param numberOfBlocks -- number of blocks on device

        @OSPProject Devices
    */
    public Device(int id, int numberOfBlocks)
    {
		//Calls super with same arguments as was invoked.
        super(id, numberOfBlocks);
		//Calls IORB Queue with exact name.
		iorbQueue = new GenericList();

    }

    /**
       This method is called once at the beginning of the
       simulation. Can be used to initialize static variables.

       @OSPProject Devices
    */
    public static void init()
    {
        //Left blank for no additional data structures.

    }

    /**
       Enqueues the IORB to the IORB queue for this device
       according to some kind of scheduling algorithm.
       
       This method must lock the page (which may trigger a page fault),
       check the device's state and call startIO() if the 
       device is idle, otherwise append the IORB to the IORB queue.

       @return SUCCESS or FAILURE.
       FAILURE is returned if the IORB wasn't enqueued 
       (for instance, locking the page fails or thread is killed).
       SUCCESS is returned if the IORB is fine and either the page was 
       valid and device started on the IORB immediately or the IORB
       was successfully enqueued (possibly after causing pagefault pagefault)
       
       @OSPProject Devices
    */
    public int do_enqueueIORB(IORB iorb)
    {
		int cylinder, addressBitsPower, blocksPerTrack;
		OpenFile openFile;
		//locks page of current iorb.
        iorb.getPage().lock(iorb);
		
		//Increments iorb count.
		openFile= iorb.getOpenFile();
		openFile.incrementIORBCount();
		//Uses addressBitsPower (or bytesPerBlock) and uses it to divide the sectorsPerTrack*BytesPerSector to get blocks per track.
		addressBitsPower = (int) Math.pow(2, MMU.getVirtualAddressBits() - MMU.getPageAddressBits());
		blocksPerTrack = ((Disk) this).getSectorsPerTrack()*((Disk) this).getBytesPerSector() / addressBitsPower;
		//Sets cylinder to iorb.getBlockNumber / the blocks per track * the platters on our disk.
		cylinder = iorb.getBlockNumber() / (blocksPerTrack * ((Disk) this).getPlatters());
		
		iorb.setCylinder(cylinder);
		//If else nested to enqueue IORB and return Failure or Success.
		if(iorb.getThread().getStatus() == ThreadKill)
    	{
    		return FAILURE;
    	}
    	else
    	{
    		if(!this.isBusy())
    		{
    			startIO(iorb);
    		}
    		else
    		{
    			((GenericList)this.iorbQueue).insert(iorb);
    		}
			return SUCCESS;
    	}

    }

    /**
       Selects an IORB (according to some scheduling strategy)
       and dequeues it from the IORB queue.

       @OSPProject Devices
    */
    public IORB do_dequeueIORB()
    {
		IORB iorbreturner;
        //Checks if IorbQueue is empty and returns null if so
		if(iorbQueue.isEmpty())
    	{
    		return null;
    	}
		//If not, it removes and returns the head of the iorb queue.
		else
		{
    		iorbreturner = (IORB) ((GenericList) iorbQueue).removeHead();
    		return iorbreturner;
    	}

    }

    /**
        Remove all IORBs that belong to the given ThreadCB from 
	this device's IORB queue

        The method is called when the thread dies and the I/O 
        operations it requested are no longer necessary. The memory 
        page used by the IORB must be unlocked and the IORB count for 
	the IORB's file must be decremented.

	@param thread thread whose I/O is being canceled

        @OSPProject Devices
    */
    public void do_cancelPendingIO(ThreadCB thread)
    {
		PageTableEntry pager;
		IORB iorbgetter;
		OpenFile opener;
        // First we check if the iorbqueue is empty, and if so we return.
		if(iorbQueue.isEmpty())
    	{
    		return;
    	}
		//Next we will iterate through the iorbqueue to remove IORBs that belong to the argument passed.
		for(int i = 0; i < iorbQueue.length(); i++) 
    	{
			//This is the iterator to get the iorb
    		iorbgetter = (IORB) ((GenericList) iorbQueue).getAt(i);
    		if(iorbgetter.getThread().equals(thread))
    		{
    			//unlock the iorb page associated with the iorb.
    			pager = iorbgetter.getPage();
				pager.unlock();
    		
    			//decrement the iorb count of the file associated with thread
    			opener = iorbgetter.getOpenFile();
				opener.decrementIORBCount();
    			
    			//If iorb count is 0 then close the file
    	
    			if(opener.getIORBCount() == 0 && iorbgetter.getOpenFile().closePending)
    			{
    				opener.close();	
    			}
   				((GenericList) iorbQueue).remove(iorbgetter);
    			
    		}
    	}

    }

    /** Called by OSP after printing an error message. The student can
	insert code here to print various tables and data structures
	in their state just after the error happened.  The body can be
	left empty, if this feature is not used.
	
	@OSPProject Devices
     */
    public static void atError()
    {
        // your code goes here

    }

    /** Called by OSP after printing a warning message. The student
	can insert code here to print various tables and data
	structures in their state just after the warning happened.
	The body can be left empty, if this feature is not used.
	
	@OSPProject Devices
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
