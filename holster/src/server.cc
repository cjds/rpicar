#include <boost/interprocess/file_mapping.hpp>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <functional>
#include <utility>
#include <csignal>
#include <iostream>
#include <fstream>



void signalHandler( int signum ) {
	std::cout << "Interrupt signal (" << signum << ") received.\n";

   // cleanup and close up stuff here  
   // terminate program  

   exit(signum);  
}

struct TStruct
{
  double x;
  double y;
  double z;
};

int main ()
{
    using namespace boost::interprocess;
    const char* FileName = "/dev/shm/SharedMemoryName";

      {  //Create a file
         file_mapping::remove(FileName);
         std::filebuf fbuf;
         fbuf.open(FileName, std::ios_base::in | std::ios_base::out
                              | std::ios_base::trunc | std::ios_base::binary);
         //Set the size
         fbuf.pubseekoff(sizeof(TStruct)-1, std::ios_base::beg);
         fbuf.sputc(0);
      }


    // remove earlier existing SHM
   // shared_memory_object::remove("SharedMemoryName");

    // create new 
 //   managed_shared_memory segment(create_only,"SharedMemoryName",65536);
    //boost::iostreams::mapped_file_source file;

     file_mapping m_file("/dev/shm/SharedMemoryName", read_write);

      //Map the whole file with read-write permissions in this process
      mapped_region segment(m_file, read_write);


    // Check if file was successfully opened
//    if(m_file.is_open())
    // offset ptr within SHM for map 
    /*
    offset_ptr<TStruct> data = segment.construct<TStruct>("MySHMMapName")();
    */
    double i = 0;
    while(true)
    {
    	TStruct* data = reinterpret_cast<TStruct*>(segment.get_address());
    	data->x = i;
    	data->z = i;
    	data->y = i;
	if(i<10000) i = i+1;
	else i = 0;
    }
    return 0;
}
